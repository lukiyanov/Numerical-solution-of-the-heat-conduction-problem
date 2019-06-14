#pragma once
#include "GenericPointSolution.h"

namespace solution
{
	///////////////////////////////////////////////////////////////////////////////
	// Температура в ближайшем узле сетки к заданному.
	class TimeCalculatorSolution : public GenericPointSolution {
		const double temperature;
		const bool conditionT0lessT1;

		double timeAnsver;

	public:
		///////////////////////////////////////////////////////////////////////////
		TimeCalculatorSolution(const TaskConditions& task, const int MPI_rank, const int MPI_size) :
			GenericPointSolution(task, MPI_rank, MPI_size),
			temperature(task.FIND_TIME_WHEN_TEMPERATURE_IS.dblTemperature),
			conditionT0lessT1(mtxTemperatureNew(indexX, indexY) < temperature)
		{
		}

		///////////////////////////////////////////////////////////////////////////
		void WriteAnsver(ofstream& out) override
		{
			if (mpiRank != mpiSize - 1)
				return;

			out << timeAnsver << endl;
		}

		///////////////////////////////////////////////////////////////////////////
		void Solve() override
		{
			const int allArgCount = 6;
			lang::Variant allArgs[allArgCount];
			
			double& time      = allArgs[0].doubleValue;
			double& deltaTime = allArgs[1].doubleValue;
			double& qx        = allArgs[2].doubleValue;
			double& qy        = allArgs[3].doubleValue;
			double& qt        = allArgs[4].doubleValue;
			bool& mustContinue = allArgs[5].boolValue;

			// Вычисление коэффициентов.
			time = 0;
			deltaTime = MaxTimeDelta();
			qx = Qx(deltaTime);
			qy = Qy(deltaTime);
			qt = Qt(deltaTime);
			mustContinue = true;

			ExchangeBorderValuesWithNeighbors();

			// Поехали
			for (size_t step = 0; mustContinue; step++)
			{
				time += deltaTime;

				const double oldTemperature = mtxTemperature(indexX, indexY);

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

				// ----------------------------------------------------
				// Алгоритм.
				// Делаем шаг. Проверяем. Перешагнули?
				// Нет: шагаем дальше.
				// Да: откатываемся, делим шаг на 2 и повторяем.
				//	'--> Число перестало меняться? Мы достигли предела, заканчиваем.
				// Навернули <over 9000> циклов -> аварийный выход.
				if (step == MAX_ALLOWED_ITERATION_COUNT)
					throw std::exception("The iteration limit has reached. Aborting process.");

				ExchangeBorderValuesWithNeighbors();

				// Если мы — процессор-владелец точки, то устанавливаем признак завершения вычислений, если это требуется.
				// Также рассылаем новые значения коэффициентов, если уменьшаем шаг.
				// NB: т.к. далее идёт Bcast, то использовать break/return/continue до него нельзя.
				if (pointIsMy)
				{
					// ----------------------------------------------------
					// Вычислили слой. Ну что там как с температурой?
					// Как определить что мы перешагнули порог?
					// T  - требуемая температура
					// T* - текущая, T0 - в нуле (t=t0)
					// { T0 < T == T* < T } <=> не достигли
					// { T0 < T != T* < T } <=> достигли
					// { T0 < T != T* < T } <=> { T0 < T == T* >= T }
					const bool hit = (conditionT0lessT1 == (mtxTemperature(indexX, indexY) >= temperature));

					// Перешагнули?
					if (hit)
					{	// Таки да, перешагнули.
						// При преодолении порога температура не изменилась?
						// 0.000001 - точность до миллионных.
						if (abs(oldTemperature - mtxTemperature(indexX, indexY)) < 0.0000001)
						{
							// Не меняется. Значит уточнить ответ ещё больше нельзя.
							// Прекращаем вычисления, в другие процессоры отсылаем сигнал останова.
							// Запоминаем ответ:
							timeAnsver = time;
							// Останавливаем все процессоры:
							mustContinue = false;
						}
						else
						{
							// Нет, при уменьшении шага ответ продолжает изменяться => уменьшаем шаг ещё сильнее.
							// Откатываемся, делим шаг на 2 и повторяем
							time -= deltaTime;
							deltaTime /= 2;
							qx = Qx(deltaTime);
							qy = Qy(deltaTime);
							qt = Qt(deltaTime);
						}
					}
				}

				// Передаём все аргументы от владельца точки остальным процессорам.
				MPI_Bcast(allArgs, allArgCount, MPI_DOUBLE, pointOwnerRank, MPI_COMM_WORLD);
			} // for (...)

			// Ок, закончили. Если ответ у нас, то отсылаем его в последний процессор.
			// Ах да, делаем это только эти два процессора на самом деле не одни и тот же.
			// Если один и тот же, то ответ уже вычислен, действий не требуется.
			if (pointOwnerRank != mpiSize - 1)
			{
				if (pointOwnerRank == mpiRank)	// Передаём
				{
					MPI_Send(&timeAnsver, 1, MPI_DOUBLE, mpiSize - 1, 105, MPI_COMM_WORLD);
				}

				if (mpiSize - 1 == mpiRank)	// Получаем
				{
					MPI_Status status;
					MPI_Recv(&timeAnsver, 1, MPI_DOUBLE, pointOwnerRank, 105, MPI_COMM_WORLD, &status);
				}
			}

		}

		///////////////////////////////////////////////////////////////////////////
	};

	///////////////////////////////////////////////////////////////////////////////
}