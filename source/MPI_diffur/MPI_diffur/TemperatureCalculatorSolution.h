#pragma once
#include "GenericPointSolution.h"

namespace solution
{
	///////////////////////////////////////////////////////////////////////////////
	// Температура в ближайшем узле сетки к заданному.
	class TemperatureCalculatorSolution : public GenericPointSolution {
		double result;

	public:
		///////////////////////////////////////////////////////////////////////////
		TemperatureCalculatorSolution(const TaskConditions& task, const int MPI_rank, const int MPI_size) :
			GenericPointSolution(task, MPI_rank, MPI_size)
		{
		}

		///////////////////////////////////////////////////////////////////////////
		void WriteAnsver(ofstream& out) override
		{
			if (mpiSize - 1 != mpiRank)
				return;

			out << result << endl;
		}

		///////////////////////////////////////////////////////////////////////////
		void Solve() override
		{
			GenericPointSolution::Solve();

			if (pointOwnerRank != mpiSize - 1)
			{
				if (pointOwnerRank == mpiRank)
				{
					result = mtxTemperature(indexX, indexY);
					MPI_Send(&result, 1, MPI_DOUBLE, mpiSize - 1, 101, MPI_COMM_WORLD);
				}

				if (mpiSize - 1 == mpiRank)
				{
					MPI_Status status;
					MPI_Recv(&result, 1, MPI_DOUBLE, pointOwnerRank, 101, MPI_COMM_WORLD, &status);
				}
			}
			else
				result = mtxTemperature(indexX, indexY);

		}

		///////////////////////////////////////////////////////////////////////////
	};

	///////////////////////////////////////////////////////////////////////////////
}