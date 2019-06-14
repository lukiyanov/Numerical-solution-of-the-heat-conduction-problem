#pragma once
#include <string>
#include "Transformation.h"

namespace lang
{
	// Тип задачи, которую требуется решить.
	enum TaskType {
		FIND_TEMPERATURE_AT,
		FIND_TIME_WHEN_TEMPERATURE_IS,
		BUILD_TEMPERATURE_CHANGES_FOR_POINT,
		BUILD_FULL_BODY_FOR_TIME
	};

	// Успешность решения задачи.
	enum TaskResult {
		RESULT_SUCCESS,
		RESULT_ERROR
	};

	// Представляет условия задачи.
	struct TaskConditions
	{
		// Эти параметры должны указываться для любой задачи. -----------------
		std::string strBodyExpression;
		std::string strTemperatureAt0;
		std::string strEvironmentTemperatureExpression;
		double dblVar0From, dblVar0To;
		double dblVar1From, dblVar1To;
		int nVar0IntervalCount, nVar1IntervalCount;
		double dblThermalConductivity;

		TaskType taskType;

		// Эти параметры специфичны для конкретных задач. ---------------------
		union {
			struct
			{
				double dblTime;
				struct { double X, Y; } point;
			} FIND_TEMPERATURE_AT;

			struct
			{
				double dblTemperature;
				struct { double X, Y; } point;
			} FIND_TIME_WHEN_TEMPERATURE_IS;

			struct
			{
				double dblEndTime;
				struct { double X, Y; } point;
			} BUILD_TEMPERATURE_CHANGES_FOR_POINT;

			struct
			{
				double dblEndTime;
			} BUILD_FULL_BODY_FOR_TIME;
		};

		// --------------------------------------------------------------------
		TaskConditions(int argc, char **argv, int firstParamNumber)
		{
			RestoreFromArgList(argc, argv, firstParamNumber);
		}

		// --------------------------------------------------------------------
		TaskConditions() :
			strBodyExpression("(x*x + y*y <= 0.0004) AND (x*x + y*y >= 0.000324)"),
			strTemperatureAt0("36.6 - 8300 * (pow(x*x + y*y, 0.5) - 0.018)"),
			strEvironmentTemperatureExpression("if (x*x + y*y >= 0.0004) 20 else 36.6;"),
			dblVar0From(-0.02), dblVar0To(0.02),
			dblVar1From(-0.02), dblVar1To(0.02),
			nVar0IntervalCount(100),
			nVar1IntervalCount(100),
			dblThermalConductivity(0.000126),
			taskType(TaskType::BUILD_FULL_BODY_FOR_TIME),
			BUILD_FULL_BODY_FOR_TIME{ 0.0001 }
		{}

		// --------------------------------------------------------------------
		std::string SaveToString() const
		{
			std::string total =
				std::string("\"") + strBodyExpression + "\" \""
				+ strTemperatureAt0 + "\" \""
				+ strEvironmentTemperatureExpression + "\" \""
				+ ToString(dblVar0From) + "\" \""
				+ ToString(dblVar1From) + "\" \""
				+ ToString(dblVar0To) + "\" \""
				+ ToString(dblVar1To) + "\" \""
				+ ToString(nVar0IntervalCount) + "\" \""
				+ ToString(nVar1IntervalCount) + "\" \""
				+ ToString(dblThermalConductivity) + "\" \""
				+ ToString(taskType) + "\" \""
				// Сериализуем union просто как 3 переменных типа double.
				+ ToString(FIND_TEMPERATURE_AT.dblTime) + "\" \""
				+ ToString(FIND_TEMPERATURE_AT.point.X) + "\" \""
				+ ToString(FIND_TEMPERATURE_AT.point.Y) + "\"";

			return total;
		}

		// --------------------------------------------------------------------
		void RestoreFromArgList(int argc, char **argv, int firstParamNumber)
		{
			const int varCount = 14;

			if (argc < varCount + firstParamNumber)
				throw std::exception("Cannot restore TaskConditions struct from an arg list: parameter count is not enough.");

			strBodyExpression					= argv[firstParamNumber + 0];
			strTemperatureAt0					= argv[firstParamNumber + 1];
			strEvironmentTemperatureExpression	= argv[firstParamNumber + 2];

			dblVar0From	= atof(argv[firstParamNumber + 3]);
			dblVar1From = atof(argv[firstParamNumber + 4]);
			dblVar0To   = atof(argv[firstParamNumber + 5]);
			dblVar1To   = atof(argv[firstParamNumber + 6]);

			nVar0IntervalCount = atoi(argv[firstParamNumber + 7]);
			nVar1IntervalCount = atoi(argv[firstParamNumber + 8]);

			dblThermalConductivity = atof(argv[firstParamNumber + 9]);

			taskType    = (TaskType) atoi(argv[firstParamNumber + 10]);

			FIND_TEMPERATURE_AT.dblTime = atof(argv[firstParamNumber + 11]);
			FIND_TEMPERATURE_AT.point.X = atof(argv[firstParamNumber + 12]);
			FIND_TEMPERATURE_AT.point.Y = atof(argv[firstParamNumber + 13]);

			switch (taskType) {
			case TaskType::FIND_TEMPERATURE_AT:
			case TaskType::FIND_TIME_WHEN_TEMPERATURE_IS:
			case TaskType::BUILD_TEMPERATURE_CHANGES_FOR_POINT:
			case TaskType::BUILD_FULL_BODY_FOR_TIME:
				break;
			default:
				throw std::exception("unknown task in switch, TaskConditions::RestoreFromArgList()");
			}
		}

		// --------------------------------------------------------------------
	};
}

/*
// Задача про пластины:
strBodyExpression("(x >= 0) AND (x <= 0.1)"),
strTemperatureAt0("20"),
strEvironmentTemperatureExpression("if (x <= 0) 300 else 100;"),
dblVar0From(0), dblVar0To(0.1),
dblVar1From(0), dblVar1To(0),
nVar0IntervalCount(100),
nVar1IntervalCount(0),
dblThermalConductivity(46.0 / (460. * 7800)),	// Заданная в задаче температуропроводность
taskType(TaskType::BUILD_TEMPERATURE_CHANGES_FOR_POINT),
BUILD_TEMPERATURE_CHANGES_FOR_POINT{ 60,{ 0.0 } }

// Стандартная задача для тестирования про апельсины
// Диаметр апельсина 0.1 => радиус 0.05, квадрат радиуса 0.05^2 = 0.0025.
// Чуть увеличим этот радиус чтобы избежать случая, когда граница не считается частью тела из-за погрешности вроде 4e-19.
strBodyExpression("x*x + y*y <= 0.0025000000001"),
strTemperatureAt0("5"),
strEvironmentTemperatureExpression("-5"),
dblVar0From(-0.05), dblVar0To(0.05),
dblVar1From(-0.05), dblVar1To(0.05),
nVar0IntervalCount(10),
nVar1IntervalCount(10),
dblThermalConductivity(0.47 / ( 3800. * 940)),	// Заданная в задаче температуропроводность
taskType(TaskType::BUILD_TEMPERATURE_CHANGES_FOR_POINT),
BUILD_TEMPERATURE_CHANGES_FOR_POINT{ 60 * 60, { 0.05, 0 } }

// Кольцо
strBodyExpression("x*x + y*y <= 4.0e-4 AND x*x + y*y >= 3.24e-4"),
strTemperatureAt0("30"),
strEvironmentTemperatureExpression("if (x*x + y*y >= 3.61e-4) 20 else 36.6;"),
dblVar0From(-2e-2), dblVar0To(2e-2),
dblVar1From(-2e-2), dblVar1To(2e-2),
nVar0IntervalCount(100),
nVar1IntervalCount(100),
dblThermalConductivity(126e-6),	// Заданная в задаче температуропроводность
taskType(TaskType::BUILD_FULL_BODY_FOR_TIME),
BUILD_FULL_BODY_FOR_TIME{ 1e-06 } // 18 секунд вычислений даже для такого маленького интервала

*/