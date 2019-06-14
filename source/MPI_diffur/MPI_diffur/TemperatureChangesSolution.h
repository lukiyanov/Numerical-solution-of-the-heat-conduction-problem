#pragma once
#include <vector>
#include "GenericPointSolution.h"

namespace solution
{
	///////////////////////////////////////////////////////////////////////////////
	class TemperatureChangesSolution : public GenericPointSolution {
		// Тут мы храним температуру и время. Могли бы сразу писать их в файл, если бы не были MPI.
		// Размер обоих массивов одинаков и составляет currentArraySize.
		double* pTemperatureArray;
		double* pTimeArray;
		size_t currentArraySize;
		size_t size;

	public:
		///////////////////////////////////////////////////////////////////////////
		TemperatureChangesSolution(const TaskConditions& task, const int MPI_rank, const int MPI_size) :
			GenericPointSolution(task, MPI_rank, MPI_size),
			currentArraySize(0)
		{
			size = static_cast<size_t>(endTime / MaxTimeDelta()) + 2;

			if (pointIsMy)
			{
				// Почему +2?
				// 1 - на t=t0
				// 1 - на последнюю дополнительную итерацию, когда шаг уже меньше deltaTime.
				try {
					pTemperatureArray = new double[size];
					pTimeArray = new double[size];
				}
				catch (exception ex) {
					throw std::exception((std::string("Too big iteration count (") + ToString(size) + "), enter the grid with bigger steps.").c_str());
				}

				// Сохраняем температуру в нуле (t=t0):
				pTemperatureArray[currentArraySize] = mtxTemperature(indexX, indexY);
				pTimeArray[currentArraySize++] = 0;
			}
		}

		///////////////////////////////////////////////////////////////////////////
		~TemperatureChangesSolution()
		{
			if (pointIsMy)
			{
				delete[] pTemperatureArray;
				delete[] pTimeArray;
			}
		}

		///////////////////////////////////////////////////////////////////////////
		void AdditionalTimeSliceThings() override
		{
			if (pointIsMy)
			{
				pTemperatureArray[currentArraySize] = mtxTemperature(indexX, indexY);
				pTimeArray[currentArraySize++] = time;
			}
		}

		///////////////////////////////////////////////////////////////////////////
		void Solve() override
		{
			GenericPointSolution::Solve();

			if (pointOwnerRank == mpiSize - 1)
				return;

			if (pointOwnerRank == mpiRank)
			{
				MPI_Send(pTemperatureArray, size, MPI_DOUBLE, mpiSize - 1, 102, MPI_COMM_WORLD);
				MPI_Send(pTimeArray, size, MPI_DOUBLE, mpiSize - 1, 103, MPI_COMM_WORLD);
				MPI_Send(&currentArraySize, 1, MPI_INT, mpiSize - 1, 101, MPI_COMM_WORLD);
			}

			if (mpiSize - 1 == mpiRank)
			{
				pTemperatureArray = new double[size];
				pTimeArray = new double[size];

				MPI_Status status;
				MPI_Recv(pTemperatureArray, size, MPI_DOUBLE, pointOwnerRank, 102, MPI_COMM_WORLD, &status);
				MPI_Recv(pTimeArray, size, MPI_DOUBLE, pointOwnerRank, 103, MPI_COMM_WORLD, &status);
				MPI_Recv(&currentArraySize, 1, MPI_INT, pointOwnerRank, 101, MPI_COMM_WORLD, &status);
			}
		}

		///////////////////////////////////////////////////////////////////////////
		void WriteAnsver(ofstream& out) override
		{
			if (mpiSize - 1 != mpiRank)
				return;

			for (size_t i = 0; i < size; i++)
				out << pTimeArray[i] << ' ' << pTemperatureArray[i] << endl;
		}

		///////////////////////////////////////////////////////////////////////////
	};

	///////////////////////////////////////////////////////////////////////////////
}