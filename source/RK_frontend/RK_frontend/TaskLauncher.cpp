// LauncherThread.cpp: файл реализации
//

#include "stdafx.h"
#include "RK_frontend.h"
#include "TaskLauncher.h"
#include "MainFrm.h"
#include "resource.h"
#include "TaskResult.h"
#include <time.h>

///////////////////////////////////////////////////////////////////////////////
volatile bool		CTaskLauncher::s_IsBusy;
lang::TaskConditions	CTaskLauncher::s_task;
CMainFrame*			CTaskLauncher::s_pMainWnd;

///////////////////////////////////////////////////////////////////////////////
CString ExePath() {
	wchar_t buf[MAX_PATH];
	GetModuleFileName(NULL, buf, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buf).find_last_of(L"\\/");
	return CString(buf, pos);
}

///////////////////////////////////////////////////////////////////////////////
UINT CTaskLauncher::Run(LPVOID param)
{
	CString command = ((CRKFrontendApp*)AfxGetApp())->GetMPIExecCmd() + CString(" \"") + ExePath() + "\\MPI_diffur.exe\" " + CString(s_task.SaveToString().c_str());
	wchar_t *pBuf = new wchar_t[command.GetLength()];
	StrCpyNW(pBuf, command, command.GetLength());

	STARTUPINFO info = { sizeof(info) };
	info.wShowWindow = SW_HIDE;
	info.dwFlags = STARTF_USESHOWWINDOW;

	PROCESS_INFORMATION processInfo;

	const clock_t timeBegin = clock();

	if (CreateProcess(NULL, pBuf, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		WaitForSingleObject(processInfo.hProcess, INFINITE);

		const clock_t time = clock() - timeBegin;
		s_pMainWnd->SetResult(new TaskResult(s_task, (double)time / CLOCKS_PER_SEC));

		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}

	delete[] pBuf;
	s_IsBusy = false;
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
void CTaskLauncher::SolveProblem(const lang::TaskConditions& task, CMainFrame* pMainWnd)
{
	if (s_IsBusy)
	{
		CString title, message;
		bool bLoadValid;
		bLoadValid = title.LoadString(IDS_ERROR);
		ASSERT(bLoadValid);
		bLoadValid = message.LoadString(IDS_MUTEX_ERROR_MPI_LAUNCH);
		ASSERT(bLoadValid);

		MessageBox(pMainWnd->GetSafeHwnd(), message, title, MB_ICONINFORMATION);
		return;
	}

	s_IsBusy = true;
	s_pMainWnd = pMainWnd;
	s_task = task;

	AfxBeginThread(Run, 0);
}

///////////////////////////////////////////////////////////////////////////////