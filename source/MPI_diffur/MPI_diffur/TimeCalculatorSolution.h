#pragma once
#include "GenericPointSolution.h"

namespace solution
{
	///////////////////////////////////////////////////////////////////////////////
	// ����������� � ��������� ���� ����� � ���������.
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

			// ���������� �������������.
			time = 0;
			deltaTime = MaxTimeDelta();
			qx = Qx(deltaTime);
			qy = Qy(deltaTime);
			qt = Qt(deltaTime);
			mustContinue = true;

			ExchangeBorderValuesWithNeighbors();

			// �������
			for (size_t step = 0; mustContinue; step++)
			{
				time += deltaTime;

				const double oldTemperature = mtxTemperature(indexX, indexY);

				// ������������� ������ �����, ������������� ����.
				// ������ ������ � 1 ������ � ������ � ����� �� ���� ���������� ����� �� ������������ ������� ��� ��������� ������.
				for (size_t j = 1; j < nMyPointCountWithBorderY - 1; j++)
					for (size_t i = 1; i < nMyPointCountWithBorderX - 1; i++)
						// ��� ����� �� ����������� ���� - ����������.
						// ����������� - ������������� � �������� � ����� ��������� ����.
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
				// ��������.
				// ������ ���. ���������. �����������?
				// ���: ������ ������.
				// ��: ������������, ����� ��� �� 2 � ���������.
				//	'--> ����� ��������� ��������? �� �������� �������, �����������.
				// ��������� <over 9000> ������ -> ��������� �����.
				if (step == MAX_ALLOWED_ITERATION_COUNT)
					throw std::exception("The iteration limit has reached. Aborting process.");

				ExchangeBorderValuesWithNeighbors();

				// ���� �� � ���������-�������� �����, �� ������������� ������� ���������� ����������, ���� ��� ���������.
				// ����� ��������� ����� �������� �������������, ���� ��������� ���.
				// NB: �.�. ����� ��� Bcast, �� ������������ break/return/continue �� ���� ������.
				if (pointIsMy)
				{
					// ----------------------------------------------------
					// ��������� ����. �� ��� ��� ��� � ������������?
					// ��� ���������� ��� �� ����������� �����?
					// T  - ��������� �����������
					// T* - �������, T0 - � ���� (t=t0)
					// { T0 < T == T* < T } <=> �� ��������
					// { T0 < T != T* < T } <=> ��������
					// { T0 < T != T* < T } <=> { T0 < T == T* >= T }
					const bool hit = (conditionT0lessT1 == (mtxTemperature(indexX, indexY) >= temperature));

					// �����������?
					if (hit)
					{	// ���� ��, �����������.
						// ��� ����������� ������ ����������� �� ����������?
						// 0.000001 - �������� �� ����������.
						if (abs(oldTemperature - mtxTemperature(indexX, indexY)) < 0.0000001)
						{
							// �� ��������. ������ �������� ����� ��� ������ ������.
							// ���������� ����������, � ������ ���������� �������� ������ ��������.
							// ���������� �����:
							timeAnsver = time;
							// ������������� ��� ����������:
							mustContinue = false;
						}
						else
						{
							// ���, ��� ���������� ���� ����� ���������� ���������� => ��������� ��� ��� �������.
							// ������������, ����� ��� �� 2 � ���������
							time -= deltaTime;
							deltaTime /= 2;
							qx = Qx(deltaTime);
							qy = Qy(deltaTime);
							qt = Qt(deltaTime);
						}
					}
				}

				// ������� ��� ��������� �� ��������� ����� ��������� �����������.
				MPI_Bcast(allArgs, allArgCount, MPI_DOUBLE, pointOwnerRank, MPI_COMM_WORLD);
			} // for (...)

			// ��, ���������. ���� ����� � ���, �� �������� ��� � ��������� ���������.
			// �� ��, ������ ��� ������ ��� ��� ���������� �� ����� ���� �� ���� � ��� ��.
			// ���� ���� � ��� ��, �� ����� ��� ��������, �������� �� ���������.
			if (pointOwnerRank != mpiSize - 1)
			{
				if (pointOwnerRank == mpiRank)	// �������
				{
					MPI_Send(&timeAnsver, 1, MPI_DOUBLE, mpiSize - 1, 105, MPI_COMM_WORLD);
				}

				if (mpiSize - 1 == mpiRank)	// ��������
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