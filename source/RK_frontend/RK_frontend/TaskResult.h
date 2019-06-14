#pragma once

#include "stdafx.h"
#include "lang\TaskConditions.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////////
class TaskResult
{
	static const char szOutputFile[];
	CString m_strFullText;

public:
	lang::TaskConditions m_task;
	lang::TaskResult m_resultStatus;

	struct PointT { double time, temperature; };
	struct PointXY { double x, y, temperature; };

	struct
	{
		CString strError;
	} ERROR_OCCURRED;

	struct
	{
		double temperatureFound;
	} FIND_TEMPERATURE_AT;

	struct
	{
		double timeFound;
	} FIND_TIME_WHEN_TEMPERATURE_IS;

	struct
	{
		std::vector<PointT> vctPointsT;
	} BUILD_TEMPERATURE_CHANGES_FOR_POINT;

	struct
	{
		std::vector<PointXY> vctPointsXY;
	} BUILD_FULL_BODY_FOR_TIME;

public:
	TaskResult(lang::TaskConditions task, const double calculationTime);
	CString GetText();
};

///////////////////////////////////////////////////////////////////////////////