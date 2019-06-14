#pragma once
#include <vector>
#include <string>
#include "lang/TaskConditions.h"

// диалоговое окно CTaskConditionsDlg

namespace lang {
	class MathExpression;
}

class CTaskConditionsDlg : public CDialog
{
	DECLARE_DYNAMIC(CTaskConditionsDlg)

public:
	CTaskConditionsDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CTaskConditionsDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASKCONDITIONSDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	lang::TaskConditions m_taskConditions;

private:
	void GoToPage(int tabIndex);
	void StdStrToMFCStr(const std::vector<std::string>& in, std::vector<CString>& out);

private:
	int m_nOpenedTab;
	const int m_nLastTabNumber;

	lang::MathExpression *m_pExprBody;
	lang::MathExpression *m_pExprT0;
	lang::MathExpression *m_pExprEnvironment;

	std::vector<CString> m_vars;
	CString m_strVariableNames; // В одну строку

private:
	// Переменные, связанные с UI.
	CString ui_editBox;
	CString ui_title;
	CString ui_description;

	double ui_fromVar1;
	double ui_fromVar2;
	double ui_toVar1;
	double ui_toVar2;
	UINT ui_intervalsVar1;
	UINT ui_intervalsVar2;

	double ui_tempFull;
	double ui_tempX;
	double ui_tempRo;
	double ui_tempC;

	double ui_taskParam1;
	double ui_taskParam2;
	double ui_taskParam3;

private:
	// События UI
	afx_msg void OnBnClickedRadioTempFull();
	afx_msg void OnBnClickedRadioTempCalc();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedTaskTemp();
	afx_msg void OnBnClickedTaskTime();
	afx_msg void OnBnClickedTaskTempChanges();
	afx_msg void OnBnClickedTaskSliceAt();
};
