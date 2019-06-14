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

// MainFrm.h : ��������� ������ CMainFrame
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

// ��������
public:
	void SetResult(TaskResult* pResult);

// ���������������
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	void SetActiveView(CWnd *pView);
	CWnd* GetActiveView();

// ����������
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ���������� ����� ������ ��������� ����������
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

// ��������� ������� ����� ���������
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


