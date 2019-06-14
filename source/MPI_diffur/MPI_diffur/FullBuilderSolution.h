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
				for (size_t j = 0; j < pointCountY; j++) // �� Y ��� ��������
					for (size_t i = 1; i < pointCountX + 1; i++) // 1 == ��������, ������ �� ��������
						out << '\n'
						<< begX + stepX * (i - 1) << ' '
						<< begY + stepY * j << ' '
						<< (*pResult)(i, j);
			}
		}

		///////////////////////////////////////////////////////////////////////////
		void Solve() override
		{
			// ���������� �������������.
			double deltaTime = MaxTimeDelta();
			double qx = Qx(deltaTime);
			double qy = Qy(deltaTime);
			double qt = Qt(deltaTime);

			// ����������, �������.
			bool endIsNotReached = true;	// ���� true ���������� ������������

			// ����� ������� ��� ������� ������������ ������������ ������� �����.
			ExchangeBorderValuesWithNeighbors();

			// ����������, ���� ���������� ����� ��������� ���� � ����� �� ������� deltaTime.
			for (size_t step = 1; endIsNotReached; step++)
			{
				// NB: ������ �������� - �� � ����, � � deltaTime.

				// ������� ���� ������� (��� ���� �������� ����� ���������).
				// ���� ��������� ��� ����� �������� �� ������� ���������� ����������� � ��� �������, ��� ������ ��������.
				// ����� ��������� ���� ���������, �� �� ��������� � ���������� ������� ��� �����.
				time = step * deltaTime;
				if (time >= endTime)
				{
					deltaTime = endTime - (step - 1) * deltaTime; // Dt = end - �����_�����������_����������_����
					time = endTime;
					// ��������� ������������.
					qx = Qx(deltaTime);
					qy = Qy(deltaTime);
					qt = Qt(deltaTime);
					// ��� ��������� ��������.
					endIsNotReached = false;
				}

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

				// ��� ���������� ������������� ����� �������� ������� ��� ��������� �� ����� ���� ��������� �� �������� �����.
				if (step == MAX_ALLOWED_ITERATION_COUNT)
					throw std::exception("The iteration limit has reached. Aborting process.");

				ExchangeBorderValuesWithNeighbors();

				AdditionalTimeSliceThings();
			}

			// ---------------------------------------------------------------------------
			// ����� �������� ��������� � ���� ������� ������� pResult, ���� ��� ���������
			if (!mustBuildResult)
				return;

			// ��-��������, ��������� �� ��������� 1D � 2D ���-�� �����, �������� ��������� � ������ ������, ���� �� �������������.

			// 1D
			if (dimensionCount == 1)
			{
				if (mpiRank == mpiSize - 1)
					pResult = new Matrix2D<double>(pointCountX, 1);

				MPI_Gather(mtxTemperature.GetRawPointer(1, 1), stdPointCountX, MPI_DOUBLE,
					(pResult) ? pResult->GetRawPointer(0, 0) : 0, stdPointCountX, MPI_DOUBLE, mpiSize - 1, MPI_COMM_WORLD);

				// ���������� �������, (myPointCountX - stdPointCountX) �����.
				// ��� �������� � ������� stdPointCountX * mpiSize �����.
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
				// � ������ - ������ ���� + ������� �� X. ������� �� Y �������.
				if (mpiRank == mpiSize - 1)
					pResult = new Matrix2D<double>(pointCountX + 2, pointCountY);

				int blockSize = stdPointCountY * (stdPointCountX + 2);

				// �������� ������ �� ��������� MPI-���������� ������ ������ �� ��? ������ ��� � ���� ������ ���������,
				// ��� � ������ �������, �.�. ������ ��� �������� �������. � ���� ������� �� ������ ��������.
				MPI_Gather(mtxTemperature.GetRawPointer(0, 1), blockSize, MPI_DOUBLE,
					(pResult) ? pResult->GetRawPointer(0, 0) : 0, blockSize, MPI_DOUBLE, mpiSize - 1, MPI_COMM_WORLD);

				// ���������� �������, (myPointCountY - stdPointCountY) �����.
				// ��� �������� � ������� stdPointCountY * mpiSize �����.
				if (mpiRank == mpiSize - 1)
				{
					int lineInResult   = stdPointCountY * mpiSize;
					int lineInMyMatrix = stdPointCountY + 1; // 1 == ������, ������� ��� ����� ������ �� ������� � ���� ������

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
			// ������������ ������� � ���������� MPI-������������, ���� ��� ����������.
			MPI_Status status;
			// 1D
			if (dimensionCount == 1)
			{
				// Y == 1 ��� ����������� ������
				MPI_Sendrecv(
					mtxTemperature.GetRawPointer(1, 1), 1, MPI_DOUBLE, mpiLeftID, 100,	// ���������� [1] �� X
					mtxTemperature.GetRawPointer(0, 1), 1, MPI_DOUBLE, mpiLeftID, 100,	// ���������  [0] �� X
					MPI_COMM_WORLD, &status);

				MPI_Sendrecv(
					mtxTemperature.GetRawPointer(nMyPointCountWithBorderX - 2, 1), 1, MPI_DOUBLE, mpiRightID, 100, // ���������� [last-1] �� X
					mtxTemperature.GetRawPointer(nMyPointCountWithBorderX - 1, 1), 1, MPI_DOUBLE, mpiRightID, 100, // ���������  [last]   �� X
					MPI_COMM_WORLD, &status);
			}
			// 2D
			else
			{
				// ��� 2D ����� �� Y
				MPI_Sendrecv(
					// ��� ������ (�� �������!) ������ ������ ������. �� ������ ��� ��������� ���� ����.
					mtxTemperature.GetRawPointer(0, 1), nMyPointCountWithBorderX, MPI_DOUBLE, mpiLeftID, 100,
					// ��������� ������� ������ �� ������ ������.
					mtxTemperature.GetRawPointer(0, 0), nMyPointCountWithBorderX, MPI_DOUBLE, mpiLeftID, 100,
					MPI_COMM_WORLD, &status);

				MPI_Sendrecv(
					// ��� ������������� ������ ������� ������.
					mtxTemperature.GetRawPointer(0, nMyPointCountWithBorderY - 2), nMyPointCountWithBorderX, MPI_DOUBLE, mpiRightID, 100,
					// ��������� ��������� ������ ����.
					mtxTemperature.GetRawPointer(0, nMyPointCountWithBorderY - 1), nMyPointCountWithBorderX, MPI_DOUBLE, mpiRightID, 100,
					MPI_COMM_WORLD, &status);
			}
		}

	};

	///////////////////////////////////////////////////////////////////////////////
}