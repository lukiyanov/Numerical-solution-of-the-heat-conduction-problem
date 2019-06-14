#pragma once

#pragma once
#include <vector>
#include "FullBuilderSolution.h"

namespace solution
{
	///////////////////////////////////////////////////////////////////////////////
	class GenericPointSolution : public FullBuilderSolution {
	protected:
		// ������ �� ������.
		const double x, y;

		// ��������� ������� � ����� �����.
		size_t indexX, indexY;

		// true, ���� ������ ������ MPI-���������� ��������� ��� ������� �����.
		bool pointIsMy;
		// ���� ����������, ����������� �����.
		int pointOwnerRank;

	public:
		///////////////////////////////////////////////////////////////////////////
		GenericPointSolution(const TaskConditions& task, const int MPI_rank, const int MPI_size) :
			FullBuilderSolution(task, MPI_rank, MPI_size),
			x(task.BUILD_TEMPERATURE_CHANGES_FOR_POINT.point.X),
			y(task.BUILD_TEMPERATURE_CHANGES_FOR_POINT.point.Y),
			indexX(-1), indexY(-1), pointIsMy(0)
		{
			// ��� �������� ������� �� ��������� �������� ������ �������.
			mustBuildResult = 0;

			// ��������, �������� �� ����� � ������� ��������������.
			if (x < task.dblVar0From || task.dblVar0To < x
				|| ((y < task.dblVar1From || task.dblVar1To < y) && (dimensionCount >= 2))
				) throw std::exception("The point is not in the set borders.");

			double args[] = { x, y };
			if (!expressionBody.Calculate(args).boolValue)
				throw std::exception("The point does not belongs to the body.");

			// ������� ��������� ����� �� ��������� � ��� � �� �������.
			// "1 + ...", �.�. ������ � 1 ������ � ����� ������ ���� ������, ���� ��� ���������� ������.
			size_t globalIndexX = 1 + round((x - begX) / stepX);
			size_t globalIndexY = 1 + ((dimensionCount >= 2) ? round((y - begY) / stepY) : 0);

			size_t index = (dimensionCount == 1) ? globalIndexX : globalIndexY;
			size_t step = (dimensionCount == 1) ? stdPointCountX : stdPointCountY;
			pointOwnerRank = index / step;

			indexX = (dimensionCount == 1) ? (globalIndexX % stdPointCountX) : globalIndexX;
			indexY = (dimensionCount == 2) ? (globalIndexY % stdPointCountY) : globalIndexY;

			if (pointOwnerRank >= mpiSize)
			{
				pointOwnerRank = mpiSize - 1;
				if (dimensionCount == 1)
					indexX += stdPointCountX;
				else
					indexY += stdPointCountY;
			}

			if (pointOwnerRank == mpiRank)
				pointIsMy = true;

			// ��������� ������������� ���� ����� ��� ����� ������������� �� ����������� ���� => ����� ����� ������ �����.
			if (pointIsMy && !mtxIsBodyPoint(indexX, indexY))
				throw std::exception("The approximation point of the target point does not belongs to the body on this grid. Use another grid.");
		}

	protected:
		///////////////////////////////////////////////////////////////////////////
		// ���������� � ������� ������� �������������� �����.
		inline size_t round(const double f) {
			return int(f + 0.5);
		}

		///////////////////////////////////////////////////////////////////////////
	};

	///////////////////////////////////////////////////////////////////////////////
}