// Этот исходный код MFC Samples демонстрирует функционирование пользовательского интерфейса Fluent на основе MFC в Microsoft Office
// ("Fluent UI") и предоставляется исключительно как справочный материал в качестве дополнения к
// справочнику по пакету Microsoft Foundation Classes и связанной электронной документации,
// включенной в программное обеспечение библиотеки MFC C++.  
// Условия лицензионного соглашения на копирование, использование или распространение Fluent UI доступны отдельно.  
// Для получения дополнительных сведений о нашей лицензионной программе Fluent UI посетите веб-узел
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// (C) Корпорация Майкрософт (Microsoft Corp.)
// Все права защищены.

// RK_frontend.cpp : Определяет поведение классов для приложения.
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
// создание CRKFrontendApp
CRKFrontendApp::CRKFrontendApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// Если приложение построено с поддержкой среды Common Language Runtime (/clr):
	//     1) Этот дополнительный параметр требуется для правильной поддержки работы диспетчера перезагрузки.
	//   2) В своем проекте для сборки необходимо добавить ссылку на System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// формат строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	SetAppID(_T("PFUR.Lukyanov.RK.frontend.v1"));
}

// Единственный объект CRKFrontendApp

CRKFrontendApp theApp;


// инициализация CRKFrontendApp

///////////////////////////////////////////////////////////////////////////////
BOOL CRKFrontendApp::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	EnableTaskbarInteraction(FALSE);

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	SetRegistryKey(_T("PFUR.Lukyanov"));


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Чтобы создать главное окно, этот код создает новый объект окна
	// рамки, а затем задает его как объект основного окна приложения
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// создайте и загрузите рамку с его ресурсами
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;




	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
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
// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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

	GetDlgItem(IDC_DATE_TIME)->SetWindowTextW(CString(__DATE__ " в " __TIME__));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// Команда приложения для запуска диалога
void CRKFrontendApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

///////////////////////////////////////////////////////////////////////////////
// CRKFrontendApp настройка методов загрузки и сохранения
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

// обработчики сообщений CRKFrontendApp

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
