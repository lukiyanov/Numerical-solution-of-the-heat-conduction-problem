#include "stdafx.h"
#include "TaskResult.h"
#include "lang\Transformation.h"
#include "lang\MathExpression.h"
#include <fstream>
#include <string>
using namespace std;

const char TaskResult::szOutputFile[] = "result.txt";

///////////////////////////////////////////////////////////////////////////////
TaskResult::TaskResult(lang::TaskConditions task, const double calculationTime)
	:m_task(task)
{
	ifstream in(szOutputFile);

	int tmp;
	in >> tmp;
	m_resultStatus = (lang::TaskResult) tmp;

	// Обрабатываем случай ошибки.
	if (m_resultStatus == lang::TaskResult::RESULT_ERROR)
	{
		ERROR_OCCURRED.strError = _T("Произошла ошибка: ");

		typedef istreambuf_iterator<char> iter;
		string str((iter(in)), iter());
		ERROR_OCCURRED.strError += str.c_str();

		m_strFullText = ERROR_OCCURRED.strError;
		return;
	}

	wostringstream oss;

	oss << L"Вычислено за " << calculationTime << L" секунд.\r\n"
		<< L"\r\nУсловия задачи:\r\n  Уравнение тела:\t\t\t" << m_task.strBodyExpression.c_str()
		<< L"\r\n  Начальная температура тела:\t"			  << m_task.strTemperatureAt0.c_str()
		<< L"\r\n  Температура окружающей среды:\t"		  << m_task.strEvironmentTemperatureExpression.c_str()
		<< L"\r\n  Температуропроводность материала:\t"		  << m_task.dblThermalConductivity
		<< L"\r\n  Границы поиска решения:\t";

	lang::MathExpression body(task.strBodyExpression);
	vector<string> vars;
	body.GetVariableNames(vars);

	oss << "\r\n    " << vars[0].c_str() << L" ∈ [" << task.dblVar0From << ", " << task.dblVar0To << L"], число интервалов сетки: " << task.nVar0IntervalCount;

	if (vars.size() > 1)
		oss << "\r\n    " << vars[1].c_str() << L" ∈ [" << task.dblVar1From << ", " << task.dblVar1To << L"], число интервалов сетки: " << task.nVar1IntervalCount;

	oss << L"\r\n  ] ƒ(" << vars[0].c_str();
	if (vars.size() > 1)
		oss << L", " << vars[1].c_str();
	oss << L", t) = T — функция температуры T тела в точке (" << vars[0].c_str();
	if (vars.size() > 1)
		oss << L", " << vars[1].c_str();
	oss << L") в момент времени t.";


	oss << L"\r\n\r\nНайти:";

	switch (task.taskType)
	{
	case lang::FIND_TEMPERATURE_AT:
		in >> FIND_TEMPERATURE_AT.temperatureFound;

		oss << L"\r\n  ƒ(" << vars[0].c_str() << " = " << task.FIND_TEMPERATURE_AT.point.X;
		if (vars.size() > 1)
			oss << L", " << vars[1].c_str() << " = " << task.FIND_TEMPERATURE_AT.point.Y;
		oss << L", t = " << task.FIND_TEMPERATURE_AT.dblTime << ") = T; T = ?";

		oss << L"\r\n\r\nОтвет:";

		oss << L"\r\n  ƒ(" << vars[0].c_str() << " = " << task.FIND_TEMPERATURE_AT.point.X;
		if (vars.size() > 1)
			oss << L", " << vars[1].c_str() << " = " << task.FIND_TEMPERATURE_AT.point.Y;
		oss << L", t = " << task.FIND_TEMPERATURE_AT.dblTime << ") = " << FIND_TEMPERATURE_AT.temperatureFound
			<< "; T = " << FIND_TEMPERATURE_AT.temperatureFound;
		break;

	case lang::FIND_TIME_WHEN_TEMPERATURE_IS:
		in >> FIND_TIME_WHEN_TEMPERATURE_IS.timeFound;

		oss << L"\r\n  ƒ(" << vars[0].c_str() << " = " << task.FIND_TIME_WHEN_TEMPERATURE_IS.point.X;
		if (vars.size() > 1)
			oss << L", " << vars[1].c_str() << " = " << task.FIND_TIME_WHEN_TEMPERATURE_IS.point.Y;
		oss << L", t) = " << task.FIND_TIME_WHEN_TEMPERATURE_IS.dblTemperature << "; t = ?";

		oss << L"\r\n\r\nОтвет:";

		oss << L"\r\n  ƒ(" << vars[0].c_str() << " = " << task.FIND_TIME_WHEN_TEMPERATURE_IS.point.X;
		if (vars.size() > 1)
			oss << L", " << vars[1].c_str() << " = " << task.FIND_TIME_WHEN_TEMPERATURE_IS.point.Y;
		oss << L", t = " << FIND_TIME_WHEN_TEMPERATURE_IS.timeFound << ") = " << task.FIND_TIME_WHEN_TEMPERATURE_IS.dblTemperature
			<< "; t = " << FIND_TIME_WHEN_TEMPERATURE_IS.timeFound;
		break;

	case lang::BUILD_TEMPERATURE_CHANGES_FOR_POINT:
		{
			oss << L"\r\n  График функции ƒ'(t) = ƒ(" << vars[0].c_str() << " = " << task.BUILD_TEMPERATURE_CHANGES_FOR_POINT.point.X;
			if (vars.size() > 1)
				oss << L", " << vars[1].c_str() << " = " << task.BUILD_TEMPERATURE_CHANGES_FOR_POINT.point.Y;
			oss << L", t)";

			oss << L"\r\n\r\nОтвет:";
			double time, temperature;
			while (in && !in.eof())
			{
				in >> time >> temperature;
				BUILD_TEMPERATURE_CHANGES_FOR_POINT.vctPointsT.push_back({ time, temperature });
				oss << L"\r\n  ƒ'(t = " << time << L") = " << temperature;
			}
		}
		break;

	case lang::BUILD_FULL_BODY_FOR_TIME:
	{
		oss << L"\r\n  График функции ƒ'(" << vars[0].c_str();
		if (vars.size() > 1)
			oss << L", " << vars[1].c_str();
		oss << L") = ƒ(" << vars[0].c_str();
		if (vars.size() > 1)
			oss << L", " << vars[1].c_str();
		oss << L", t = " << task.BUILD_FULL_BODY_FOR_TIME.dblEndTime << ")";

		oss << L"\r\n\r\nОтвет:";
		double x, y, temperature;
		while (in && !in.eof())
		{
			in >> x >> y >> temperature;
			BUILD_FULL_BODY_FOR_TIME.vctPointsXY.push_back({ x, y, temperature });

			if (temperature == 100)
				temperature = temperature;

			oss << L"\r\n  ƒ'(" << vars[0].c_str() << " = " << x;
			if (vars.size() > 1)
				oss << L", " << vars[1].c_str() << " = " << y;
			oss << L") = " << temperature;
		}
	}
	break;

	default:
		throw new exception("Unknown task type found in TaskResult::TaskResult().");
	}

	m_strFullText = oss.str().c_str();
}

///////////////////////////////////////////////////////////////////////////////
CString TaskResult::GetText()
{
	return m_strFullText;
}

///////////////////////////////////////////////////////////////////////////////