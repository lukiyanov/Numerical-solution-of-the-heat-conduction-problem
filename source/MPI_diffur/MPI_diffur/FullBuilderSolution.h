#pragma once
#include "GenericSolution.h"
#include <limits.h>

namespace solution
{
	///////////////////////////////////////////////////////////////////////////////
	class FullBuilderSolution : public GenericSolution {
	protected:
		static const size_t MAX_ALLOWED_ITERATION_COUNT = UINT_MAX;

	protected:
		const double endTime;

		double time;

		bool mustBuildResult;
		Matrix2D<double>* pResult;

	public:
		///////////////////////////////////////////////////////////////////////////
		FullBuilderSolution(const TaskConditions& task, const int MPI_rank, const int MPI_size) :
			GenericSolution(task, MPI_rank, MPI_size),
			endTime(task.BUILD_FULL_BODY_FOR_TIME.dblEndTime),
			pResult(0),
			mustBuildResult(1)
		{}

		///////////////////////////////////////////////////////////////////////////
		void WriteAnsver(ofstream& out) override
		{
			if (mpiRank != mpiSize - 1)
				return;

			if (dimensionCount == 1)
			{
				// 1D
					for (size_t i = 0; i < pointCountX; i++)
						out << '\n'
						<< begX + stepX * i << ' '
						<< 0 << ' '
						<< (*pResult)(i, 0);
			}
			else
			{
				// 2D
				for (size_t j = 0; j < pointCountY; j++) // по Y без смещения
					for (size_t i = 1; i < pointCountX + 1; i++) // 1 == смещение, бордюр не печатаем
						out << '\n'
						<< begX + stepX * (i - 1) << ' '
						<< begY + stepY * j << ' '
						<< (*pResult)(i, j);
			}
		}

		///////////////////////////////////////////////////////////////////////////
		void Solve() override
		{
			// Вычисление коэффициентов.
			double deltaTime = MaxTimeDelta();
			double qx = Qx(deltaTime);
			double qy = Qy(deltaTime);
			double qt = Qt(deltaTime);

			// Собственно, расчёты.
			bool endIsNotReached = true;	// Пока true вычисления продолжаются

			// Иначе получим все границы заполненными температурой внешней среды.
			ExchangeBorderValuesWithNeighbors();

			// Собственно, цикл вычисления новых временных слоёв с шагом по времени deltaTime.
			for (size_t step = 1; endIsNotReached; step++)
			{
				// NB: первая итерация - не в нуле, а в deltaTime.

				// Текущий слой времени (для всех итераций кроме последней).
				// Если вычислять его через сложение то получим накопление погрешности и тем большее, чем больше итераций.
				// Через умножение чуть медленнее, но по сравнению с пересчётом матрицы это ничто.
				time = step * deltaTime;
				if (time >= endTime)
				{
					deltaTime = endTime - (step - 1) * deltaTime; // Dt = end - время_предыдущего_временного_слоя
					time = endTime;
					// Обновляем коэффициенты.
					qx = Qx(deltaTime);
					qy = Qy(deltaTime);
					qt = Qt(deltaTime);
					// Это последняя итерация.
					endIsNotReached = false;
				}

				// Пересчитываем только точки, принадлежащие телу.
				// Делаем отступ в 1 ячейку с начала и конца по всем измерениям чтобы не обрабатывать границу как отдельный случай.
				for (size_t j = 1; j < nMyPointCountWithBorderY - 1; j++)
					for (size_t i = 1; i < nMyPointCountWithBorderX - 1; i++)
						// Это точка не принадлежит телу - пропускаем.
						// Принадлежит - пересчитываем её значение в новом временном слое.
						if (mtxIsBodyPoint(i, j))
							mtxTemperatureNew(i, j) =
							qt * mtxTemperature(i, j) +
							qx * mtxTemperature(i + 1, j) +
							qx * mtxTemperature(i - 1, j) +
							((dimensionCount == 2) ?
								(qy * mtxTemperature(i, j + 1) +
									qy * mtxTemperature(i, j - 1))
								: 0);

				mtxTemperature = mtxTemperatureNew;

				// При достижении максимального числа итераций считаем что результат не может быть достигнут за разумное время.
				if (step == MAX_ALLOWED_ITERATION_COUNT)
					throw std::exception("The iteration limit has reached. Aborting process.");

				ExchangeBorderValuesWithNeighbors();

				AdditionalTimeSliceThings();
			}

			// ---------------------------------------------------------------------------
			// Далее собираем результат в одну большую матрицу pResult, если это требуется
			if (!mustBuildResult)
				return;

			// По-хорошему, следовало бы разделить 1D и 2D как-то иначе, например запихнуть в разные классы, либо же унифицировать.

			// 1D
			if (dimensionCount == 1)
			{
				if (mpiRank == mpiSize - 1)
					pResult = new Matrix2D<double>(pointCountX, 1);

				MPI_Gather(mtxTemperature.GetRawPointer(1, 1), stdPointCountX, MPI_DOUBLE,
					(pResult) ? pResult->GetRawPointer(0, 0) : 0, stdPointCountX, MPI_DOUBLE, mpiSize - 1, MPI_COMM_WORLD);

				// Дописываем остаток, (myPointCountX - stdPointCountX) строк.
				// Уже записано в матрицу stdPointCountX * mpiSize строк.
				if (mpiRank == mpiSize - 1)
				{
					int rowInResult = stdPointCountX * mpiSize;
					int rowInMyMatrix = stdPointCountX + 1;

					for (size_t i = 0; i < myPointCountX - stdPointCountX; i++)
					{
						(*pResult)(i + rowInResult, 0) = mtxTemperature(i + rowInMyMatrix, 1);
					}
				}
			}
			// 2D
			else
			{
				// В ответе - полное тело + граница по X. Границы по Y скипаем.
				if (mpiRank == mpiSize - 1)
					pResult = new Matrix2D<double>(pointCountX + 2, pointCountY);

				int blockSize = stdPointCountY * (stdPointCountX + 2);

				// Собираем данные на последнем MPI-процессоре Почему именно на нём? Потому что у него больше элементов,
				// чем у любого другого, т.к. именно ему достаётся остаток. И этот остаток он должен дописать.
				MPI_Gather(mtxTemperature.GetRawPointer(0, 1), blockSize, MPI_DOUBLE,
					(pResult) ? pResult->GetRawPointer(0, 0) : 0, blockSize, MPI_DOUBLE, mpiSize - 1, MPI_COMM_WORLD);

				// Дописываем остаток, (myPointCountY - stdPointCountY) строк.
				// Уже записано в матрицу stdPointCountY * mpiSize строк.
				if (mpiRank == mpiSize - 1)
				{
					int lineInResult   = stdPointCountY * mpiSize;
					int lineInMyMatrix = stdPointCountY + 1; // 1 == бордюр, который при сборе ответа мы скипаем у всех блоков

					for (size_t i = 0; i < myPointCountY - stdPointCountY; i++)
						for (size_t j = 0; j < nMyPointCountWithBorderX; j++)
							(*pResult)(j, i + lineInResult) = mtxTemperature(j, i + lineInMyMatrix);
				}
			}
		}

		///////////////////////////////////////////////////////////////////////////
		virtual void AdditionalTimeSliceThings() { }

		///////////////////////////////////////////////////////////////////////////
		void ExchangeBorderValuesWithNeighbors()
		{
			// Обмениваемся данными с остальными MPI-процессорами, если они существуют.
			MPI_Status status;
			// 1D
			if (dimensionCount == 1)
			{
				// Y == 1 для одномерного случая
				MPI_Sendrecv(
					mtxTemperature.GetRawPointer(1, 1), 1, MPI_DOUBLE, mpiLeftID, 100,	// Отправляем [1] по X
					mtxTemperature.GetRawPointer(0, 1), 1, MPI_DOUBLE, mpiLeftID, 100,	// Принимаем  [0] по X
					MPI_COMM_WORLD, &status);

				MPI_Sendrecv(
					mtxTemperature.GetRawPointer(nMyPointCountWithBorderX - 2, 1), 1, MPI_DOUBLE, mpiRightID, 100, // отправляем [last-1] по X
					mtxTemperature.GetRawPointer(nMyPointCountWithBorderX - 1, 1), 1, MPI_DOUBLE, mpiRightID, 100, // принимаем  [last]   по X
					MPI_COMM_WORLD, &status);
			}
			// 2D
			else
			{
				// Для 2D делим по Y
				MPI_Sendrecv(
					// Шлём ПЕРВУЮ (не нулевую!) строку левому соседу. Мы только что вычислили этот блок.
					mtxTemperature.GetRawPointer(0, 1), nMyPointCountWithBorderX, MPI_DOUBLE, mpiLeftID, 100,
					// Принимаем НУЛЕВУЮ строку от левого соседа.
					mtxTemperature.GetRawPointer(0, 0), nMyPointCountWithBorderX, MPI_DOUBLE, mpiLeftID, 100,
					MPI_COMM_WORLD, &status);

				MPI_Sendrecv(
					// Шлём ПРЕДПОСЛЕДНЮЮ строку правому соседу.
					mtxTemperature.GetRawPointer(0, nMyPointCountWithBorderY - 2), nMyPointCountWithBorderX, MPI_DOUBLE, mpiRightID, 100,
					// Принимаем ПОСЛЕДНЮЮ строку него.
					mtxTemperature.GetRawPointer(0, nMyPointCountWithBorderY - 1), nMyPointCountWithBorderX, MPI_DOUBLE, mpiRightID, 100,
					MPI_COMM_WORLD, &status);
			}
		}

	};

	///////////////////////////////////////////////////////////////////////////////
}