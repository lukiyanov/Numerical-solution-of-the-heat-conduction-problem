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

// MainFrm.h : интерфейс класса CMainFrame
//

#pragma once
#include "TextView.h"
#include "GraphView.h"
#include "MatrixView.h"

class TaskResult;

class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Операции
public:
	void SetResult(TaskResult* pResult);

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	void SetActiveView(CWnd *pView);
	CWnd* GetActiveView();

// Реализация
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // встроенные члены панели элементов управления
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CWnd* m_pWndActiveView;
	CTextView	m_wndTextView;
	CGraphView	m_wndGraphView;
	CMatrixView	m_wndMatrixView;

	TaskResult* m_pResult;

	bool m_canBuildGraph;
	bool m_canBuildMatrix;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);

	afx_msg void OnButtonText();
	afx_msg void OnButtonGraph();
	afx_msg void OnButtonMatrix();
public:
	afx_msg void OnUpdateButtonGraph(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonMatrix(CCmdUI *pCmdUI);
};


