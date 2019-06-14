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
		enum PontLocation { ENVIRONMENT_POINT = 0, BODY_POINT = 1, CALCULATE }; // ��������� ��������� ����� ��� ��������� ����������� �������� �� ����������.

	protected:
		// MPI
		const int mpiRank;		// ����� ������� ���������� ������ ������
		const int mpiSize;		// ���������� ����������� � ������
		const int mpiLeftID;	// ����� MPI-����� (���� ����), � ������� ����� ������������ �������
		const int mpiRightID;	// ������ MPI-����� (���� ����), � ������� ����� ������������ �������

		MathExpression expressionBody;
		MathExpression expressionInitBodyTemperature;
		MathExpression expressionEvironmentTemperature;

		const size_t dimensionCount;

		// ����� ����� ����� ����
		const size_t pointCountX;
		const size_t pointCountY;

		// ����� �����, ������� ��������� ��� ���������
		// ���������� ����� �� X, ��������� �� Y
		const size_t myPointCountX;
		const size_t myPointCountY;

		// ����� �����, ������� ��������� ��� ���������� ����� ����������, �� X (��� ������)
		const size_t stdPointCountX;
		// ����� �����, ������� ��������� ��� ���������� ����� ����������, �� Y (��� ������)
		const size_t stdPointCountY;

		// ����� �����, ������� ��������� ��� ���������, ������� �������
		const size_t nMyPointCountWithBorderX;
		const size_t nMyPointCountWithBorderY;

		Matrix2D<double> mtxTemperature;
		Matrix2D<double> mtxTemperatureNew;
		Matrix2D<bool>   mtxIsBodyPoint;	// ����������� �� ����� ����.

		const double begX;
		const double begY;

		const double stepX;
		const double stepY;

		// ����������� ����������������������, ����� ������������ ��� "�����".
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

			// ��� ��������� ������� ����� ����� ��������� ������ ������ ����� ���������� ����� �� 1.
			pointCountX(task.nVar0IntervalCount + 1),
			pointCountY((dimensionCount == 2) ? task.nVar1IntervalCount + 1 : 1),

			// � ���������� ������� ����� �� X, � ��������� �� Y.
			// ������� ����� ��������� �� ������ ����������, � �������� ����� ��������.
			// �� ����� ����� MPI-������������ ������ �������� ������ ������ ����������, �.�. ��� ���� ������.
			// ����� �������, �� ��������� MPI-��������� �������� ����� ������� �� �������.
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

			// ���� � ��� ���� ����� ��� ������ �����, ������� �����/������ ������� �� ����� ��������� �� ����.
			// ����� �����/������ ������� ����� ��������� ����������� ���������� �����.
			// ��� ��� �����, ���� � 1 ������� � ����� ������ ���� ������ � ������� �� ���������������.
			nMyPointCountWithBorderX(myPointCountX + 2),
			// �� Y ������ � ����� �� ������ ����� ���� � 1 ������, ����������� ������������ ���������� �����.
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
		// ������������ ��� �� �������, ����������� �� ������ ���������� ������.
		inline double MaxTimeDelta() const
		{
			// ������������ ��� ������������ �������� ������������:
			//             step * step
			// deltaTime < -----------.
			//             2 * alpha
			// �� �� ���� �������� �� �������������:
			return 0.25 * stepX * stepX * ((dimensionCount >= 2) ? stepY * stepY : 1) / alpha;
		}

		///////////////////////////////////////////////////////////////////////////
		// ������������ ��������� ������������� ��� ���������� ���� �� �������.
		inline double Qx(const double timeDelta) const { return                         alpha * timeDelta / (stepX * stepX); }
		inline double Qy(const double timeDelta) const { return (dimensionCount == 2) ? alpha * timeDelta / (stepY * stepY) : 0; }
		inline double Qt(const double timeDelta) const { return 1 - 2 * Qx(timeDelta) - 2 * Qy(timeDelta); }

		///////////////////////////////////////////////////////////////////////////
		// ������������� �������� ����� � ��������� ������������ mtxIsBodyPoint[] � mtxTemperature[].
		// ���� ����� ����������� �����, �� ������� ��������� ��� �� ����������� ������� ����� � ������ �����.
		// ���� ����� ����������� ����, �� ������� ������� ��� �� ��������� ����������� ���� � ������ �����.
		// ���� location ����������� � CALCULATE, �� ��������� ����������� �� ����� ���� ��������������.
		// ������������ ��� ������������� ������.
		inline void SetPointAs(const PontLocation location, const size_t indexX, const size_t indexY)
		{
			// ����� ��������/�����, ������� �� ���������� ��-�� MPI-���������.
			const int offsetX = (dimensionCount == 1) ? (stdPointCountX * mpiRank) : 0;
			const int offsetY = (dimensionCount == 2) ? (stdPointCountY * mpiRank) : 0;

			// ����� �������� ���������� ������ ���������� ����� ������� ��������,
			// ��������� ������ �������� ����������. ����� ��� ��� ������� ���������� ������
			// ��� �������������, � �� �� ������ �������� ��������� �����,
			// ��� ��� ������� �� �������� ������������ ���������.
			//
			// NB: (indexX - 1), �.�. ����� � ��� ���������� � �������, � ������� ������ - ����.
			double args[] = {
				begX + stepX * (((int)indexX) - 1 + offsetX),	// -1 ��� �������� �������
				begY + stepY * (((int)indexY) - 1 + offsetY)	// -1 ��� �������� �������
			};

			// ����������� �� ��� ����� ����?
			const bool isBody =
				(location == PontLocation::CALCULATE) ? (expressionBody.Calculate(args).boolValue)
				: location;

			mtxIsBodyPoint(indexX, indexY) = isBody;

			mtxTemperature(indexX, indexY) = (isBody) ?
				expressionInitBodyTemperature.Calculate(args).doubleValue
				: expressionEvironmentTemperature.Calculate(args).doubleValue;
		}

		///////////////////////////////////////////////////////////////////////////
		// �������������� ������� ���������� (t=0) � ���������� (T ���������� �����) ���������.
		// AHTUNG: �������������� ��� ������� ������������ ������� �����.
		// ����� ����� ������������� ����������� ��������� ����� � ��������� ���������� � ������ �������� ���������� ������ �� ������ ����������.
		void InitMatrixes()
		{
			// ���������� ����� ��������.
			// �� ���� ��� � ����� ������ �� ������� �������� "������� ������" � ���� ������ �������.
			// �������� ��� ����� � ��� ���� ����� � ����� ����� ���� ���� ������� ����������.
			// ������� ����������� ����.
			for (size_t j = 0; j < nMyPointCountWithBorderY; j++)
				for (size_t i = 0; i < nMyPointCountWithBorderX; i++)
					SetPointAs(PontLocation::CALCULATE, i, j);

			// �������. ---------------
			// �����
			// ���� ����� �� Y, �� ������ ����, ���� �� X, �� ���� ����� ��� ������
			if (dimensionCount == 2 || mpiLeftID == MPI_PROC_NULL)
				for (size_t j = 0; j < nMyPointCountWithBorderY; j++)
					SetPointAs(PontLocation::ENVIRONMENT_POINT, 0, j);

			// ������
			if (dimensionCount == 2 || mpiRightID == MPI_PROC_NULL)
				for (size_t j = 0; j < nMyPointCountWithBorderY; j++)
					SetPointAs(PontLocation::ENVIRONMENT_POINT, nMyPointCountWithBorderX - 1, j);

			// ������
			if (dimensionCount == 1 || mpiLeftID == MPI_PROC_NULL)
				for (size_t i = 0; i < nMyPointCountWithBorderX; i++)
					SetPointAs(PontLocation::ENVIRONMENT_POINT, i, 0);

			// �����
			if (dimensionCount == 1 || mpiRightID == MPI_PROC_NULL)
				for (size_t i = 0; i < nMyPointCountWithBorderX; i++)
					SetPointAs(PontLocation::ENVIRONMENT_POINT, i, nMyPointCountWithBorderY - 1);

			mtxTemperatureNew = mtxTemperature;
		}

		///////////////////////////////////////////////////////////////////////////
	};

	///////////////////////////////////////////////////////////////////////////////
}