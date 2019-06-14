#pragma once
#include "lang\TaskConditions.h"

class CMainFrame;

class CTaskLauncher
{
public:
	// Если лаунчер занят, не делает ничего.
	static void SolveProblem(const lang::TaskConditions& task, CMainFrame* pMainWnd);

private:
	CTaskLauncher() {} // статический класс
	static UINT Run(LPVOID param);

private:
	static volatile bool		s_IsBusy;
	static lang::TaskConditions	s_task;
	static CMainFrame*			s_pMainWnd;
};


