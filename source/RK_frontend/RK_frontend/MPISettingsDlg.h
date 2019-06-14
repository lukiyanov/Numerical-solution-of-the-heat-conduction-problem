#pragma once


// диалоговое окно CMPISettingsDlg

class CMPISettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CMPISettingsDlg)

public:
	CMPISettingsDlg(CWnd* pParent = NULL);
	virtual ~CMPISettingsDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MPISETTINGSDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDefault();
	CString m_strArgs;
	virtual BOOL OnInitDialog();
};
