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

// ChildView.cpp : ���������� ������ CChildView
//

#include "stdafx.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CTextView::CTextView()
	: m_bCreated(0)
{
}

CTextView::~CTextView()
{
}


BEGIN_MESSAGE_MAP(CTextView, CWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CTextView::Create(CWnd* pParentWnd)
{
	BOOL bResult = CWnd::Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), pParentWnd, AFX_IDW_PANE_FIRST, NULL);

	if (bResult) {
		CRect rect(0, 0, 100, 100);
		m_edit.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL, rect, this, 0);

		// ������ ����������� ����� �������.
		NONCLIENTMETRICS ncm;
		ncm.cbSize = sizeof(ncm);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
		LOGFONT lfDlgFont = ncm.lfMessageFont;
		m_font.CreateFontIndirect(&lfDlgFont);

		m_edit.SetFont(&m_font);
		m_bCreated = true;
	}

	return bResult;
}

BOOL CTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CTextView::SetText(const CString& text)
{
	m_edit.SetWindowTextW(text);
}

void CTextView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (m_bCreated)
	{
		m_edit.MoveWindow(0, 0, cx, cy, TRUE);
	}
}

BEGIN_MESSAGE_MAP(CRoEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_SETFOCUS, &CRoEdit::OnEnSetfocus)
END_MESSAGE_MAP()


HBRUSH CRoEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// �������� ����������� ����� ��� readonly-���� ����� ����� �������.
	return (HBRUSH)GetStockObject(WHITE_BRUSH);
}

void CRoEdit::OnEnSetfocus()
{
	// ���������� ������, �� ��������� ����������� �������� � ���������� �����.
	HideCaret();
}
