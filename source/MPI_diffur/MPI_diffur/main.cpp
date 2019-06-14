#include <mpi.h>
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

#include "../RK_frontend/lang/MathExpression.h"
#include "../RK_frontend/lang/TaskConditions.h"
using namespace lang;

#include "Matrix2D.h"
#include "GenericSolution.h"
#include "FullBuilderSolution.h"
#include "TemperatureChangesSolution.h"
#include "TemperatureCalculatorSolution.h"
#include "TimeCalculatorSolution.h"
using namespace solution;

///////////////////////////////////////////////////////////////////////////////
char szOutputFile[] = "result.txt";

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	if (int error = MPI_Init(&argc, &argv))
	{
		cout << "Error. MPI error number: " << error << endl;
		MPI_Abort(MPI_COMM_WORLD, error);
	}

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	cout << "Started processor #" << rank << " of " << size << endl;

	try
	{
		// Производим разбор параметров задачи.
		TaskConditions task(argc, argv, 1);
		//TaskConditions task; // DEBUG

		// Выбираем тип задачи.
		GenericSolution *pSolution;
		switch (task.taskType)
		{
		case FIND_TEMPERATURE_AT:
			pSolution = new TemperatureCalculatorSolution(task, rank, size);
			break;
		case FIND_TIME_WHEN_TEMPERATURE_IS:
			pSolution = new TimeCalculatorSolution(task, rank, size);
			break;
		case BUILD_TEMPERATURE_CHANGES_FOR_POINT:
			pSolution = new TemperatureChangesSolution(task, rank, size);
			break;
		case BUILD_FULL_BODY_FOR_TIME:
			pSolution = new FullBuilderSolution(task, rank, size);
			break;
		default:
			throw exception("Unknown task type found.");
		}

		// Решаем задачу.
		pSolution->Solve();

		// Выводим ответ, если мы - последний процессор.
		if (rank == size - 1)
		{
			ofstream out(szOutputFile);
			out << TaskResult::RESULT_SUCCESS << endl;
			pSolution->WriteAnsver(out);
			out.close();
		}

		// Очищаем память.
		delete pSolution;
	}
	catch (std::exception ex)
	{
		cout << "Processor #" << rank << " error: " << ex.what() << endl;

		ofstream out(szOutputFile);
		out << TaskResult::RESULT_ERROR << endl
			<< "Processor #" << rank << " error: " << ex.what() << endl;
		out.close();

		MPI_Abort(MPI_COMM_WORLD, 0);
	}

	MPI_Finalize();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////