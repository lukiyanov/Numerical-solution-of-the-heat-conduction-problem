#pragma once
#include <mpi.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "../RK_frontend/lang/MathExpression.h"
#include "../RK_frontend/lang/TaskConditions.h"
using namespace lang;

#include "Matrix2D.h"
using namespace solution;


namespace solution {

	///////////////////////////////////////////////////////////////////////////////
	class GenericSolution
	{
	public:
		enum PontLocation { ENVIRONMENT_POINT = 0, BODY_POINT = 1, CALCULATE }; // Нумерация оставлена чтобы при случайной перетасовке значения не поменялись.

	protected:
		// MPI
		const int mpiRank;		// Номер данного процессора внутри группы
		const int mpiSize;		// Количество процессоров в группе
		const int mpiLeftID;	// Левый MPI-сосед (если есть), с которым будем обмениваться данными
		const int mpiRightID;	// Правый MPI-сосед (если есть), с которым будем обмениваться данными

		MathExpression expressionBody;
		MathExpression expressionInitBodyTemperature;
		MathExpression expressionEvironmentTemperature;

		const size_t dimensionCount;

		// общее число точек тела
		const size_t pointCountX;
		const size_t pointCountY;

		// число точек, которое вычисляет наш процессор
		// одномерные делим по X, двумерные по Y
		const size_t myPointCountX;
		const size_t myPointCountY;

		// число точек, которое вычисляют все процессоры кроме последнего, по X (без границ)
		const size_t stdPointCountX;
		// число точек, которое вычисляют все процессоры кроме последнего, по Y (без границ)
		const size_t stdPointCountY;

		// число точек, которое вычисляет наш процессор, включая границу
		const size_t nMyPointCountWithBorderX;
		const size_t nMyPointCountWithBorderY;

		Matrix2D<double> mtxTemperature;
		Matrix2D<double> mtxTemperatureNew;
		Matrix2D<bool>   mtxIsBodyPoint;	// Принадлежит ли точка телу.

		const double begX;
		const double begY;

		const double stepX;
		const double stepY;

		// Коэффициент температуропроводности, везде обозначается как "альфа".
		const double alpha;


	public:
		///////////////////////////////////////////////////////////////////////////
		GenericSolution(const TaskConditions& task, const int MPI_rank, const int MPI_size) :
			mpiRank(MPI_rank),
			mpiSize(MPI_size),
			mpiLeftID(MPI_rank ? MPI_rank - 1 : MPI_PROC_NULL),
			mpiRightID(MPI_rank < (MPI_size - 1) ? MPI_rank + 1 : MPI_PROC_NULL),

			expressionBody(task.strBodyExpression),
			expressionInitBodyTemperature(task.strTemperatureAt0),
			expressionEvironmentTemperature(task.strEvironmentTemperatureExpression),

			dimensionCount(expressionBody.GetVariableCount()),

			// При разбиении отрезка число точек разбиения всегда больше числа интервалов ровно на 1.
			pointCountX(task.nVar0IntervalCount + 1),
			pointCountY((dimensionCount == 2) ? task.nVar1IntervalCount + 1 : 1),

			// В одномерных задачах делим по X, в двумерных по Y.
			// Находим число элементов по первой переменной, с которыми будем работать.
			// Мы делим между MPI-процессорами всегда итерации именно первой переменной, т.к. она есть всегда.
			// Делим поровну, но последний MPI-процессор получает также остаток от деления.
			myPointCountX(
				(dimensionCount == 1) ?
				((MPI_rank < MPI_size - 1) ? (pointCountX / MPI_size) : (pointCountX / MPI_size + pointCountX % MPI_size))
				: pointCountX),

			myPointCountY(
				(dimensionCount == 2) ?
				((MPI_rank < MPI_size - 1) ? (pointCountY / MPI_size) : (pointCountY / MPI_size + pointCountY % MPI_size))
				: pointCountY),

			stdPointCountX((dimensionCount == 1) ? (pointCountX / MPI_size) : pointCountX),
			stdPointCountY((dimensionCount == 2) ? (pointCountY / MPI_size) : pointCountY),

			// Если у нас есть левый или правый сосед, крайний влево/вправо столбец мы будем принимать от него.
			// Иначе левый/правый столбец будет содержать температуру окружающей среды.
			// Так или иначе, край в 1 столбец с обеих сторон есть всегда и никогда не пересчитывается.
			nMyPointCountWithBorderX(myPointCountX + 2),
			// По Y сверху и снизу мы всегда имеем край в 1 строку, заполненный температурой окружающей среды.
			nMyPointCountWithBorderY(myPointCountY + 2),

			mtxTemperature(nMyPointCountWithBorderX, nMyPointCountWithBorderY),
			mtxTemperatureNew(nMyPointCountWithBorderX, nMyPointCountWithBorderY),
			mtxIsBodyPoint(nMyPointCountWithBorderX, nMyPointCountWithBorderY),

			begX(task.dblVar0From),
			begY((dimensionCount == 2) ? task.dblVar1From : 0),

			stepX(abs(task.dblVar0To - task.dblVar0From) / task.nVar0IntervalCount),
			stepY((dimensionCount == 2) ? abs(task.dblVar1To - task.dblVar1From) / task.nVar1IntervalCount : 0),

			alpha(task.dblThermalConductivity)
		{
			if (task.dblVar0From >= task.dblVar0To
			|| (dimensionCount == 2 && task.dblVar1From >= task.dblVar1To))
				throw std::exception("Invalid field borders: FROM must be < TO.");

			if (dimensionCount != 1 && dimensionCount != 2)
				throw std::exception("Invalid dimension count of the body expression. Can be 1 or 2.");

			if (task.nVar0IntervalCount < mpiSize)
				throw std::exception("Invalid interval count of the first variable. It must be greater or equal to count of MPI-processors.");

			if (task.dblThermalConductivity <= 0)
				throw exception("Thermal conductivity must be >= 0.");

			InitMatrixes();
		}

		///////////////////////////////////////////////////////////////////////////
		virtual ~GenericSolution() {}

		///////////////////////////////////////////////////////////////////////////
		virtual void Solve() = 0;

		///////////////////////////////////////////////////////////////////////////
		virtual void WriteAnsver(ofstream& out) = 0;


	protected:
		///////////////////////////////////////////////////////////////////////////
		// Максимальный шаг по времени, вычисляется на основе параметров задачи.
		inline double MaxTimeDelta() const
		{
			// Максимальный шаг определяется условием устойчивости:
			//             step * step
			// deltaTime < -----------.
			//             2 * alpha
			// Мы же берём половину от максимального:
			return 0.25 * stepX * stepX * ((dimensionCount >= 2) ? stepY * stepY : 1) / alpha;
		}

		///////////////////////////////////////////////////////////////////////////
		// Коэффициенты уравнения аппроксимации для указанного шага по времени.
		inline double Qx(const double timeDelta) const { return                         alpha * timeDelta / (stepX * stepX); }
		inline double Qy(const double timeDelta) const { return (dimensionCount == 2) ? alpha * timeDelta / (stepY * stepY) : 0; }
		inline double Qt(const double timeDelta) const { return 1 - 2 * Qx(timeDelta) - 2 * Qy(timeDelta); }

		///////////////////////////////////////////////////////////////////////////
		// Устанавливает значение точки с заданными координатами mtxIsBodyPoint[] и mtxTemperature[].
		// Если точка принадлежит среде, то функция вычисляет для неё температуру внешней среды в данной точке.
		// Если точка принадлежит телу, то функция находит для неё начальную температуру тела в данной точке.
		// Если location установлена в CALCULATE, то вычисляет принадлежит ли точка телу самостоятельно.
		// Используется для инициализации матриц.
		inline void SetPointAs(const PontLocation location, const size_t indexX, const size_t indexY)
		{
			// Число столбцов/строк, которые мы пропустили из-за MPI-разбиения.
			const int offsetX = (dimensionCount == 1) ? (stdPointCountX * mpiRank) : 0;
			const int offsetY = (dimensionCount == 2) ? (stdPointCountY * mpiRank) : 0;

			// Чтобы избежать накопления ошибок округления после каждого сложения,
			// вычисляем данные значения умножением. Благо что эта функция вызывается только
			// при инициализации, а не на каждой итерации основного цикла,
			// так что оверхед за точность относительно небольшой.
			//
			// NB: (indexX - 1), т.к. сетка у нас начинается с единицы, а нулевой индекс - край.
			double args[] = {
				begX + stepX * (((int)indexX) - 1 + offsetX),	// -1 для нулевого индекса
				begY + stepY * (((int)indexY) - 1 + offsetY)	// -1 для нулевого индекса
			};

			// Принадлежит ли эта точка телу?
			const bool isBody =
				(location == PontLocation::CALCULATE) ? (expressionBody.Calculate(args).boolValue)
				: location;

			mtxIsBodyPoint(indexX, indexY) = isBody;

			mtxTemperature(indexX, indexY) = (isBody) ?
				expressionInitBodyTemperature.Calculate(args).doubleValue
				: expressionEvironmentTemperature.Calculate(args).doubleValue;
		}

		///////////////////////////////////////////////////////////////////////////
		// Инициализирует матрицы начальными (t=0) и граничными (T окружающей среды) условиями.
		// AHTUNG: Инициализирует ВСЕ границы температурой внешней среды.
		// После такой инициализации обязательно требуется обмен с соседними элементами и замена значений внутренних границ ДО начала вычислений.
		void InitMatrixes()
		{
			// Внутренняя часть массивов.
			// Не факт что с обеих сторон всё решение окружено "внешней средой" в одну ячейку шириной.
			// Возможно что слева у нас есть сосед и тогда левый край тоже следует рассчитать.
			// Границы перезапишем ниже.
			for (size_t j = 0; j < nMyPointCountWithBorderY; j++)
				for (size_t i = 0; i < nMyPointCountWithBorderX; i++)
					SetPointAs(PontLocation::CALCULATE, i, j);

			// Границы. ---------------
			// слева
			// Если делим по Y, то всегда есть, если по X, то если слева нет соседа
			if (dimensionCount == 2 || mpiLeftID == MPI_PROC_NULL)
				for (size_t j = 0; j < nMyPointCountWithBorderY; j++)
					SetPointAs(PontLocation::ENVIRONMENT_POINT, 0, j);

			// справа
			if (dimensionCount == 2 || mpiRightID == MPI_PROC_NULL)
				for (size_t j = 0; j < nMyPointCountWithBorderY; j++)
					SetPointAs(PontLocation::ENVIRONMENT_POINT, nMyPointCountWithBorderX - 1, j);

			// сверху
			if (dimensionCount == 1 || mpiLeftID == MPI_PROC_NULL)
				for (size_t i = 0; i < nMyPointCountWithBorderX; i++)
					SetPointAs(PontLocation::ENVIRONMENT_POINT, i, 0);

			// снизу
			if (dimensionCount == 1 || mpiRightID == MPI_PROC_NULL)
				for (size_t i = 0; i < nMyPointCountWithBorderX; i++)
					SetPointAs(PontLocation::ENVIRONMENT_POINT, i, nMyPointCountWithBorderY - 1);

			mtxTemperatureNew = mtxTemperature;
		}

		///////////////////////////////////////////////////////////////////////////
	};

	///////////////////////////////////////////////////////////////////////////////
}