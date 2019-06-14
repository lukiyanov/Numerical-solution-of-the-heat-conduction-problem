// ���� �������� ��� MFC Samples ������������� ���������������� ����������������� ���������� Fluent �� ������ MFC � Microsoft Office
// ("Fluent UI") � ��������������� ������������� ��� ���������� �������� � �������� ���������� �
// ����������� �� ������ Microsoft Foundation Classes � ��������� ����������� ������������,
// ���������� � ����������� ����������� ���������� MFC C++.  
// ������� ������������� ���������� �� �����������, ������������� ��� ��������������� Fluent UI �������� ��������.  
// ��� ��������� �������������� �������� � ����� ������������ ��������� Fluent UI �������� ���-����
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// (C) ���������� ���������� (Microsoft Corp.)
// ��� ����� ��������.

// RK_frontend.cpp : ���������� ��������� ������� ��� ����������.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "RK_frontend.h"
#include "MainFrm.h"
#include "MPISettingsDlg.h"
#include "TaskConditionsDlg.h"
#include "TaskLauncher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRKFrontendApp

BEGIN_MESSAGE_MAP(CRKFrontendApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CRKFrontendApp::OnAppAbout)
	ON_COMMAND(ID_MPI_SETTINGS, &CRKFrontendApp::OnMpiSettings)
	ON_COMMAND(ID_BUTTON_SOLVE, &CRKFrontendApp::OnButtonSolve)
END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////////
// �������� CRKFrontendApp
CRKFrontendApp::CRKFrontendApp()
{
	// ��������� ���������� ������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// ���� ���������� ��������� � ���������� ����� Common Language Runtime (/clr):
	//     1) ���� �������������� �������� ��������� ��� ���������� ��������� ������ ���������� ������������.
	//   2) � ����� ������� ��� ������ ���������� �������� ������ �� System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// ������ ������: �����������.�����������.����������.���������������
	SetAppID(_T("PFUR.Lukyanov.RK.frontend.v1"));
}

// ������������ ������ CRKFrontendApp

CRKFrontendApp theApp;


// ������������� CRKFrontendApp

///////////////////////////////////////////////////////////////////////////////
BOOL CRKFrontendApp::InitInstance()
{
	// InitCommonControlsEx() ��������� ��� Windows XP, ���� ��������
	// ���������� ���������� ComCtl32.dll ������ 6 ��� ����� ������� ������ ��� ���������
	// ������ �����������.  � ��������� ������ ����� ��������� ���� ��� �������� ������ ����.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �������� ���� �������� ��� ��������� ���� ����� ������� ����������, ������� ���������� ������������
	// � ����� ����������.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ������������� ��������� OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	EnableTaskbarInteraction(FALSE);

	// ��� ������������� �������� ���������� RichEdit ��������� ����� AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	SetRegistryKey(_T("PFUR.Lukyanov"));


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ����� ������� ������� ����, ���� ��� ������� ����� ������ ����
	// �����, � ����� ������ ��� ��� ������ ��������� ���� ����������
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// �������� � ��������� ����� � ��� ���������
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);


	// ��������� ������������� ����������� �������� � ������� �������� ����
	CMFCToolBar::m_bExtCharTranslation = TRUE;




	// ���� � ������ ���� ���� ���� ����������������, ������� ���������� � �������� ���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
int CRKFrontendApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinAppEx::ExitInstance();
}


///////////////////////////////////////////////////////////////////////////////
// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_DATE_TIME)->SetWindowTextW(CString(__DATE__ " � " __TIME__));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����������: �������� ������� OCX ������ ���������� �������� FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ������� ���������� ��� ������� �������
void CRKFrontendApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

///////////////////////////////////////////////////////////////////////////////
// CRKFrontendApp ��������� ������� �������� � ����������
void CRKFrontendApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CRKFrontendApp::LoadCustomState()
{
}

void CRKFrontendApp::SaveCustomState()
{
}

// ����������� ��������� CRKFrontendApp

///////////////////////////////////////////////////////////////////////////////
void CRKFrontendApp::OnMpiSettings()
{
	CMPISettingsDlg settingsDlg(m_pMainWnd);
	settingsDlg.m_strArgs = GetMPIExecCmd();
	if (settingsDlg.DoModal() == IDOK)
		SetMPIExecCmd(settingsDlg.m_strArgs);
}

///////////////////////////////////////////////////////////////////////////////
const CString CRKFrontendApp::s_strSettingsSection   = _T("Settings");
const CString CRKFrontendApp::s_strDefaultMPIExecCmd = _T("MPIExecArgs");
const CString CRKFrontendApp::s_strMPISettingsEntry  = _T("mpiexec -n 4");

CString CRKFrontendApp::GetMPIExecCmd()
{
	return GetProfileStringW(s_strSettingsSection, s_strDefaultMPIExecCmd, s_strMPISettingsEntry);
}

CString CRKFrontendApp::GetMPIDefaultExecCmd()
{
	return s_strMPISettingsEntry;
}

void CRKFrontendApp::SetMPIExecCmd(const CString& cmd)
{
	WriteProfileStringW(s_strSettingsSection, s_strDefaultMPIExecCmd, cmd);
}

void CRKFrontendApp::OnButtonSolve()
{
	CTaskConditionsDlg dlg;
	dlg.m_taskConditions = theApp.m_taskConditions;
	if (dlg.DoModal() == IDOK)
	{
		theApp.m_taskConditions = dlg.m_taskConditions;
		CTaskLauncher::SolveProblem(theApp.m_taskConditions, (CMainFrame*)m_pMainWnd);
	}
}
