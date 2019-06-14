// Ётот исходный код MFC Samples демонстрирует функционирование пользовательского интерфейса Fluent на основе MFC в Microsoft Office
// (Fluent UI) и предоставл€етс€ исключительно как справочный материал в качестве дополнени€ к
// справочнику по пакету Microsoft Foundation Classes и св€занной электронной документации,
// включенной в программное обеспечение библиотеки MFC C++.  
// ”слови€ лицензионного соглашени€ на копирование, использование или распространение Fluent UI доступны отдельно.  
// ƒл€ получени€ дополнительных сведений о нашей лицензионной программе Fluent UI посетите веб-узел
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// (C)  орпораци€ ћайкрософт (Microsoft Corp.)
// ¬се права защищены.

// MainFrm.cpp : реализаци€ класса CMainFrame
//

#include "stdafx.h"
#include "RK_frontend.h"

#include "MainFrm.h"
#include "TaskResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_BUTTON_TEXT, &CMainFrame::OnButtonText)
	ON_COMMAND(ID_BUTTON_GRAPH, &CMainFrame::OnButtonGraph)
	ON_COMMAND(ID_BUTTON_MATRIX, &CMainFrame::OnButtonMatrix)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_GRAPH, &CMainFrame::OnUpdateButtonGraph)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MATRIX, &CMainFrame::OnUpdateButtonMatrix)
END_MESSAGE_MAP()

// создание/уничтожение CMainFrame

CMainFrame::CMainFrame()
	: m_pResult(0)
{
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// создать представление дл€ размещени€ рабочей области рамки
	if (!m_wndTextView.Create(this))
	{
		TRACE0("Ќе удалось создать текстовое окно представлений\n");
		return -1;
	}

	if (!m_wndGraphView.Create(this))
	{
		TRACE0("Ќе удалось создать текстовое окно представлений\n");
		return -1;
	}

	if (!m_wndMatrixView.Create(this))
	{
		TRACE0("Ќе удалось создать текстовое окно представлений\n");
		return -1;
	}

	SetActiveView(&m_wndTextView);
	SetResult(0);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Ќе удалось создать строку состо€ни€\n");
		return -1;      // не удалось создать
	}

	// включить режим работы закрепл€емых окон стилей Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// включить режим работы автоматического скрыти€ закрепл€емых окон стилей Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// установите нагл€дный диспетчер и стиль на основе посто€нного значени€
	OnApplicationLook(theApp.m_nAppLook);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

void CMainFrame::SetActiveView(CWnd *pView)
{
	m_wndTextView.ShowWindow(SW_HIDE);
	m_wndGraphView.ShowWindow(SW_HIDE);
	m_wndMatrixView.ShowWindow(SW_HIDE);
	m_pWndActiveView = pView;
	m_pWndActiveView->ShowWindow(SW_SHOW);
	Invalidate();
}

CWnd* CMainFrame::GetActiveView()
{
	return m_pWndActiveView;
}

// диагностика CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// обработчики сообщений CMainFrame

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// передача фокуса окну представлени€
	m_pWndActiveView->SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// разрешить ошибки в представлении при выполнении команды
	if (m_pWndActiveView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// в противном случае выполн€етс€ обработка по умолчанию
	return CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

// ћожет быть 0.
void CMainFrame::SetResult(TaskResult* pResult)
{
	delete m_pResult;
	m_pResult = pResult;

	if (!m_pResult)
		m_wndTextView.SetText(L"");
	else
		m_wndTextView.SetText(pResult->GetText());
	OnButtonText();

	m_canBuildGraph  = m_wndGraphView.SetResult(pResult);
	m_canBuildMatrix = m_wndMatrixView.SetResult(pResult);

	m_wndTextView.Invalidate();
	m_wndGraphView.Invalidate();
	m_wndMatrixView.Invalidate();
}


void CMainFrame::OnButtonText()
{
	SetActiveView(&m_wndTextView);
}


void CMainFrame::OnButtonGraph()
{
	if (m_canBuildGraph)
		SetActiveView(&m_wndGraphView);
}


void CMainFrame::OnButtonMatrix()
{
	if (m_canBuildMatrix)
		SetActiveView(&m_wndMatrixView);
}


void CMainFrame::OnUpdateButtonGraph(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_canBuildGraph);
}


void CMainFrame::OnUpdateButtonMatrix(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_canBuildMatrix);
}
