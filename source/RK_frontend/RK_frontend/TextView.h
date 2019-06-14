#pragma once

class CRoEdit : public CEdit {
public:
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnEnSetfocus();
};


class CTextView : public CWnd
{
	CRoEdit m_edit;
	CFont m_font;
	bool m_bCreated;

public:
	CTextView();
	virtual ~CTextView();
	BOOL Create(CWnd* pParentWnd);

	void SetText(const CString& text);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Созданные функции схемы сообщений
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

