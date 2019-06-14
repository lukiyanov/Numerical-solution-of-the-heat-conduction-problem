// TaskConditionsDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "RK_frontend.h"
#include "TaskConditionsDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#include "RecognitionException.h"
#include "lang/MathExpression.h"
#include "lang/Transformation.h"

///////////////////////////////////////////////////////////////////////////////
enum TabPages {
	PAGE_BODY,
	PAGE_T0,
	PAGE_ENVIRONMENT,
	PAGE_LIMITS_STEPS,
	PAGE_THERMAL_CONDUCTIVITY,
	PAGE_TASK
};

IMPLEMENT_DYNAMIC(CTaskConditionsDlg, CDialog)

///////////////////////////////////////////////////////////////////////////////
CTaskConditionsDlg::CTaskConditionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TASKCONDITIONSDLG, pParent)
	, m_nOpenedTab(0)
	, m_nLastTabNumber(PAGE_TASK)
	, m_pExprBody(0)
	, m_pExprT0(0)
	, m_pExprEnvironment(0)
	, ui_editBox(_T(""))
	, ui_title(_T(""))
	, ui_description(_T(""))
	, ui_fromVar1(0)
	, ui_fromVar2(0)
	, ui_toVar1(0)
	, ui_toVar2(0)
	, ui_intervalsVar1(0)
	, ui_intervalsVar2(0)
	, ui_tempFull(0)
	, ui_tempX(0)
	, ui_tempRo(0)
	, ui_tempC(0)
	, ui_taskParam1(0)
	, ui_taskParam2(0)
	, ui_taskParam3(0)
{
}

///////////////////////////////////////////////////////////////////////////////
CTaskConditionsDlg::~CTaskConditionsDlg()
{
	delete m_pExprBody;
	delete m_pExprT0;
}

///////////////////////////////////////////////////////////////////////////////
void CTaskConditionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, ui_editBox);
	DDX_Text(pDX, IDC_TITLE, ui_title);
	DDX_Text(pDX, IDC_DESCRIPTION, ui_description);
	DDX_Text(pDX, IDC_BEG_EDIT1, ui_fromVar1);
	DDX_Text(pDX, IDC_BEG_EDIT2, ui_fromVar2);
	DDX_Text(pDX, IDC_END_EDIT1, ui_toVar1);
	DDX_Text(pDX, IDC_END_EDIT2, ui_toVar2);
	DDX_Text(pDX, IDC_EDIT_INTERVALS1, ui_intervalsVar1);
	DDX_Text(pDX, IDC_EDIT_INTERVALS2, ui_intervalsVar2);
	DDX_Text(pDX, IDC_EDIT_TEMP_FULL, ui_tempFull);
	DDX_Text(pDX, IDC_EDIT_TEMP_X, ui_tempX);
	DDX_Text(pDX, IDC_EDIT_TEMP_RO, ui_tempRo);
	DDX_Text(pDX, IDC_EDIT_TEMP_C, ui_tempC);
	DDX_Text(pDX, IDC_EDIT_TASK_PARAM1, ui_taskParam1);
	DDX_Text(pDX, IDC_EDIT_TASK_PARAM2, ui_taskParam2);
	DDX_Text(pDX, IDC_EDIT_TASK_PARAM3, ui_taskParam3);
}


BEGIN_MESSAGE_MAP(CTaskConditionsDlg, CDialog)
	ON_BN_CLICKED(IDC_NEXT, &CTaskConditionsDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PREV, &CTaskConditionsDlg::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_RADIO_TEMP_FULL, &CTaskConditionsDlg::OnBnClickedRadioTempFull)
	ON_BN_CLICKED(IDC_RADIO_TEMP_CALC, &CTaskConditionsDlg::OnBnClickedRadioTempCalc)
	ON_BN_CLICKED(IDC_TASK_TEMP, &CTaskConditionsDlg::OnBnClickedTaskTemp)
	ON_BN_CLICKED(IDC_TASK_TIME, &CTaskConditionsDlg::OnBnClickedTaskTime)
	ON_BN_CLICKED(IDC_TASK_TEMP_CHANGES, &CTaskConditionsDlg::OnBnClickedTaskTempChanges)
	ON_BN_CLICKED(IDC_TASK_SLICE_AT, &CTaskConditionsDlg::OnBnClickedTaskSliceAt)
END_MESSAGE_MAP()


// ����������� ��������� CTaskConditionsDlg

///////////////////////////////////////////////////////////////////////////////
BOOL CTaskConditionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_TO_LABEL1)->SetWindowTextW(_T(" �� "));
	GetDlgItem(IDC_TO_LABEL2)->SetWindowTextW(_T(" �� "));

	GoToPage(m_nOpenedTab);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����������: �������� ������� OCX ������ ���������� �������� FALSE
}

///////////////////////////////////////////////////////////////////////////////
void CTaskConditionsDlg::StdStrToMFCStr(const std::vector<std::string>& in, std::vector<CString>& out)
{
	out.clear();
	for (size_t i = 0, size = in.size(); i < size; i++)
		out.push_back(CString(in[i].c_str()));
}

///////////////////////////////////////////////////////////////////////////////
void CTaskConditionsDlg::OnBnClickedNext()
{
	UpdateData(true);

	bool bCanGoNext = 1;

	// ��������� �������� ������, ��������������� ��������.
	// ���������� bCanGoNext ��������������� � 0, ���� ������ �� �����.
	switch (m_nOpenedTab)
	{
	case TabPages::PAGE_BODY:
		{
			try
			{
				CT2A ascii(ui_editBox);
				delete m_pExprBody;
				m_pExprBody = new lang::MathExpression(ascii.m_psz);
				std::vector<std::string> tmp;
				m_pExprBody->GetVariableNames(tmp);
				StdStrToMFCStr(tmp, m_vars);

				if (m_pExprBody->GetType() != lang::ExpressionType::Bool)
					throw std::exception("������� ���������, � �� ������ ���������. ����������� =, <, >, !=, AND, OR, NOT.");
				if (!m_vars.size())
					throw std::exception("�� ����������, ������� ���� �� ���� ����������.");
				if (m_vars.size() > 2)
					throw std::exception("�� �� ����� �������� � ���������� � �������� ��������������. ��������� ����� ���������� �� ����� ��� ����.");

				for (size_t i = 0; i < m_vars.size(); i++)
					if (m_vars[i] == "t" || m_vars[i] == "T")
						throw std::exception("����� ���������� t � T ������������ ���������, �������� ������.");

				// ������������� m_strVariableNames
				m_strVariableNames = "";
				size_t size_m1 = m_vars.size() - 1;
				for (size_t i = 0; i < size_m1; i++)
					m_strVariableNames += (m_vars[i] + CString(", "));
				m_strVariableNames += m_vars[size_m1];

				// ��������� ���������� ������ � ������ (���� ���, ����������, ������ � ���������).
				m_taskConditions.strBodyExpression = ascii.m_psz;
			}
			catch (std::exception ex) {
				MessageBoxA(this->GetSafeHwnd(), ex.what(), "������ � ���������", MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}
			catch (...) {
				MessageBox(_T("����������� ������ ��� ������� ���������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}
		}
		break;

	case TabPages::PAGE_T0:
		try
		{
			CT2A ascii(ui_editBox);

			delete m_pExprT0;
			m_pExprT0 = new lang::MathExpression(ascii.m_psz);
			std::vector<CString> vars2;
			std::vector<std::string> tmp;
			m_pExprBody->GetVariableNames(tmp);
			StdStrToMFCStr(tmp, vars2);

			if (m_pExprT0->GetType() != lang::ExpressionType::Double)
				throw std::exception("������� ������������ ���������, � �� ���������. �� ����������� =, <, >, !=, AND, OR, NOT.");

			// �������� ����������: ��� �� ��� ���� ����� �������� �� ���������� ����?
			// ����� ������� ��� ���� �� ����� �� ��� ���.
			for (size_t i = 0, size = vars2.size(); i < size; i++)
			{
				bool bVarFound = 0;
				for (size_t j = 0, sizeOriginal = m_vars.size(); j < sizeOriginal; j++)
					if (m_vars[j] == vars2[i]) { // �����.
						bVarFound = 1;
						break;
					}
				if (!bVarFound) // �� ����� :(
					throw std::exception(CString("���������� \"") + vars2[i] + "\" �� ���� ��������� �� ���������� ���� � �� ����� ��������������.");
			}

			// ��������� ���������� ������ � ������
			m_taskConditions.strTemperatureAt0 = ascii.m_psz;
		}
		catch (std::exception ex) {
			MessageBoxA(this->GetSafeHwnd(), ex.what(), "������ � ���������", MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}
		catch (...) {
			MessageBox(_T("����������� ������ ��� ������� ���������"), _T("������"), MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}
		break;

	case TabPages::PAGE_ENVIRONMENT:
		try
		{
			CT2A ascii(ui_editBox);

			delete m_pExprEnvironment;
			m_pExprEnvironment = new lang::MathExpression(ascii.m_psz);
			std::vector<CString> vars2;
			std::vector<std::string> tmp;
			m_pExprBody->GetVariableNames(tmp);
			StdStrToMFCStr(tmp, vars2);

			if (m_pExprEnvironment->GetType() != lang::ExpressionType::Double)
				throw std::exception("������� ������������ ���������, � �� ���������. �� ����������� =, <, >, !=, AND, OR, NOT.");

			// �������� ����������: ��� �� ��� ���� ����� �������� �� ���������� ����?
			// ����� ������� ��� ���� �� ����� �� ��� ���.
			for (size_t i = 0, size = vars2.size(); i < size; i++)
			{
				bool bVarFound = 0;
				for (size_t j = 0, sizeOriginal = m_vars.size(); j < sizeOriginal; j++)
					if (m_vars[j] == vars2[i]) { // �����.
						bVarFound = 1;
						break;
					}
				if (!bVarFound) // �� ����� :(
					throw std::exception(CString("���������� \"") + vars2[i] + "\" �� ���� ��������� �� ���������� ���� � �� ����� ��������������.");
			}

			// ��������� ���������� ������ � ������
			m_taskConditions.strEvironmentTemperatureExpression = ascii.m_psz;
		}
		catch (std::exception ex) {
			MessageBoxA(this->GetSafeHwnd(), ex.what(), "������ � ���������", MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}
		catch (...) {
			MessageBox(_T("����������� ������ ��� ������� ���������"), _T("������"), MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}
		break;

	case TabPages::PAGE_LIMITS_STEPS:		
		m_taskConditions.dblVar0From = ui_fromVar1;
		m_taskConditions.dblVar1From = ui_fromVar2;
		m_taskConditions.dblVar0To = ui_toVar1;
		m_taskConditions.dblVar1To = ui_toVar2;
		m_taskConditions.nVar0IntervalCount = ui_intervalsVar1;
		m_taskConditions.nVar1IntervalCount = ui_intervalsVar2;

		if (ui_fromVar1 > ui_toVar1 || (m_vars.size() > 1 && ui_fromVar2 > ui_toVar2))
		{
			MessageBox(_T("������ ��������� ������ ���� ������ �����"), _T("������"), MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}

		if (!ui_intervalsVar1 || (m_vars.size() > 1 && !ui_intervalsVar1))
		{
			MessageBox(_T("����� ���������� ������ ���� ������ 0"), _T("������"), MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}

		if (ui_fromVar1 == ui_toVar1 || (m_vars.size() > 1 && ui_fromVar2 == ui_toVar2))
		{
			MessageBox(_T("������ � ����� ��������� �� ������ ���������"), _T("������"), MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}
		break;

	case TabPages::PAGE_THERMAL_CONDUCTIVITY:
		if (((CButton*)GetDlgItem(IDC_RADIO_TEMP_FULL))->GetCheck())
		{
			// ������ ������ ����.
			if (ui_tempFull <= 0)
			{
				MessageBox(_T("���������������������� ������ ���� ������������� ������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			m_taskConditions.dblThermalConductivity = ui_tempFull;
		}
		else
		{
			// ������ ���� ��������.
			if (ui_tempC == 0. || ui_tempRo == 0.)
			{
				MessageBox(_T("�� ���� ������ �� 0, ������� ���������� ��������."), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			const double thermalConductivity = ui_tempX / (ui_tempRo * ui_tempC);
			if (thermalConductivity <= 0)
			{
				MessageBox(_T("���������������������� ������ ���� ������������� ������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			m_taskConditions.dblThermalConductivity = thermalConductivity;
		}

		break;

	case TabPages::PAGE_TASK:
		using namespace lang;

		// FIND_TEMPERATURE_AT:

		if (((CButton*)GetDlgItem(IDC_TASK_TEMP))->GetCheck())
		{
			// t >= 0
			if (ui_taskParam1 < 0)
			{
				MessageBox(_T("��������� ����� ������ ���� ������������� ������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}
			// X ����� Xbeg � Xend
			if (ui_taskParam2 < m_taskConditions.dblVar0From || m_taskConditions.dblVar0To < ui_taskParam2)
			{
				MessageBox(_T("������ �������� �� ������ � ������� ������ �������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			if (m_vars.size() > 1 && (ui_taskParam3 < m_taskConditions.dblVar1From || m_taskConditions.dblVar1To < ui_taskParam3))
			{
				MessageBox(_T("������ �������� �� ������ � ������� ������ �������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			m_taskConditions.taskType = FIND_TEMPERATURE_AT;
			m_taskConditions.FIND_TEMPERATURE_AT.dblTime = ui_taskParam1;
			m_taskConditions.FIND_TEMPERATURE_AT.point.X = ui_taskParam2;
			m_taskConditions.FIND_TEMPERATURE_AT.point.Y = ui_taskParam3;
		}
		// FIND_TIME_WHEN_TEMPERATURE_IS:
		else if (((CButton*)GetDlgItem(IDC_TASK_TIME))->GetCheck())
		{
			// X ����� Xbeg � Xend
			if (ui_taskParam2 < m_taskConditions.dblVar0From || m_taskConditions.dblVar0To < ui_taskParam2)
			{
				MessageBox(_T("������ �������� �� ������ � ������� ������ �������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			if (m_vars.size() > 1 && (ui_taskParam3 < m_taskConditions.dblVar1From || m_taskConditions.dblVar1To < ui_taskParam3))
			{
				MessageBox(_T("������ �������� �� ������ � ������� ������ �������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			m_taskConditions.taskType = FIND_TIME_WHEN_TEMPERATURE_IS;
			m_taskConditions.FIND_TIME_WHEN_TEMPERATURE_IS.dblTemperature = ui_taskParam1;
			m_taskConditions.FIND_TIME_WHEN_TEMPERATURE_IS.point.X = ui_taskParam2;
			m_taskConditions.FIND_TIME_WHEN_TEMPERATURE_IS.point.Y = ui_taskParam3;
		}
		// BUILD_TEMPERATURE_CHANGES_FOR_POINT:
		else if (((CButton*)GetDlgItem(IDC_TASK_TEMP_CHANGES))->GetCheck())
		{
			// t >= 0
			if (ui_taskParam1 < 0)
			{
				MessageBox(_T("��������� ����� ������ ���� ������������� ������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}
			// X ����� Xbeg � Xend
			if (ui_taskParam2 < m_taskConditions.dblVar0From || m_taskConditions.dblVar0To < ui_taskParam2)
			{
				MessageBox(_T("������ �������� �� ������ � ������� ������ �������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			if (m_vars.size() > 1 && (ui_taskParam3 < m_taskConditions.dblVar1From || m_taskConditions.dblVar1To < ui_taskParam3))
			{
				MessageBox(_T("������ �������� �� ������ � ������� ������ �������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			m_taskConditions.taskType = BUILD_TEMPERATURE_CHANGES_FOR_POINT;
			m_taskConditions.BUILD_TEMPERATURE_CHANGES_FOR_POINT.dblEndTime = ui_taskParam1;
			m_taskConditions.BUILD_TEMPERATURE_CHANGES_FOR_POINT.point.X = ui_taskParam2;
			m_taskConditions.BUILD_TEMPERATURE_CHANGES_FOR_POINT.point.Y = ui_taskParam3;
		}
		// BUILD_FULL_BODY_FOR_TIME:
		else if (((CButton*)GetDlgItem(IDC_TASK_SLICE_AT))->GetCheck())
		{
			// t >= 0
			if (ui_taskParam1 < 0)
			{
				MessageBox(_T("��������� ����� ������ ���� ������������� ������"), _T("������"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			m_taskConditions.taskType = BUILD_FULL_BODY_FOR_TIME;
			m_taskConditions.BUILD_FULL_BODY_FOR_TIME.dblEndTime = ui_taskParam1;
		}
		else
			throw std::exception("Unknown task type found");
		break;

	default:
		throw std::exception("TODO: Unknown page opened");
		break;
	}

	// ������� �� ��������� ��������, ���� ��������� �������� ������� � ���� ���� ����������.
	// ���� ��� ��������� ��������, ��������� ���� �� OnOK().
	if (bCanGoNext)
	{
		if (m_nLastTabNumber != m_nOpenedTab)
			GoToPage(++m_nOpenedTab);
		else
			OnOK();
	}
}


///////////////////////////////////////////////////////////////////////////////
void CTaskConditionsDlg::OnBnClickedPrev()
{
	GoToPage(--m_nOpenedTab);
}

///////////////////////////////////////////////////////////////////////////////
// ��������� ��������� �������� ��� �������� � ���
void CTaskConditionsDlg::GoToPage(int tabIndex)
{
	using namespace lang;
	{
		// �������� ��� ��������.
		static int elements[] = {
			IDC_EDIT,
			IDC_INTERVAL_LABEL1,
			IDC_INTERVAL_LABEL2,
			IDC_BEG_EDIT1,
			IDC_BEG_EDIT2,
			IDC_END_EDIT1,
			IDC_END_EDIT2,
			IDC_TO_LABEL1,
			IDC_TO_LABEL2,
			IDC_LABEL_INTERVALS1,
			IDC_LABEL_INTERVALS2,
			IDC_EDIT_INTERVALS1,
			IDC_EDIT_INTERVALS2,
			IDC_TEMP_1,
			IDC_TEMP_2,
			IDC_TEMP_3,
			IDC_TEMP_4,
			IDC_TEMP_5,
			IDC_TEMP_6,
			IDC_TEMP_7,
			IDC_BORDER_TEMP,
			IDC_RADIO_TEMP_FULL,
			IDC_RADIO_TEMP_CALC,
			IDC_EDIT_TEMP_FULL,
			IDC_EDIT_TEMP_X,
			IDC_EDIT_TEMP_C,
			IDC_EDIT_TEMP_RO,
			IDC_BORDER_TASK,
			IDC_TASK_TEMP,
			IDC_TASK_TIME,
			IDC_TASK_TEMP_CHANGES,
			IDC_TASK_SLICE_AT,
			IDC_TASK_PARAM1,
			IDC_TASK_PARAM2,
			IDC_TASK_PARAM3,
			IDC_EDIT_TASK_PARAM1,
			IDC_EDIT_TASK_PARAM2,
			IDC_EDIT_TASK_PARAM3
		};

		static const int elemCount = sizeof(elements) / sizeof(int);

		for (int i = 0; i < elemCount; i++)
			GetDlgItem(elements[i])->ShowWindow(0);
	}

	const size_t varCount = m_vars.size();

	switch (tabIndex) {
	case TabPages::PAGE_BODY:
		ui_title =
			"��� 1: ������� ��������� ����";
		ui_description =
			"������� ��������� (��� �����������) ������������ ��� ������������ ���� �� ������ ��� ���������."
			" ��������, \"x*x + y*y <= 4\" � ��������� ���������� ����� � ������� � ������ ��������� � �������� 2."
			" ����������� ������������ ���� ��� ��� ����������, �� �������� �� ������ ������� ����.";
		GetDlgItem(IDC_EDIT)->ShowWindow(1);
		GetDlgItem(IDC_EDIT)->SetFocus();
		GetDlgItem(IDC_NEXT)->SetWindowTextW(_T("����� >"));
		GetDlgItem(IDC_PREV)->EnableWindow(0);

		ui_editBox = m_taskConditions.strBodyExpression.c_str();
		break;

	case TabPages::PAGE_T0:
		ui_title =
			CString("��� 2: ������� ��������� ����������� ����, T(") + m_strVariableNames + CString(")=...");
		ui_description =
			CString("������� �������, ������������ ��������� ����������� ����."
			" �� ���������� ���� �� ����� ��������� � ������������ ����������� (") + m_strVariableNames +
				CString("), ������� �� ���� ���� ������ ������������ ��� ����������."
			" ������ \"T(") + m_strVariableNames + CString(")=\" �� ���������, ������ ������ ������ ����� ������ �������."
			" ��������, \"10\" ����� ���������� 10 �������� � ����� ����� ����."
			" \"pow(x*x + y*y, 1/2)\" ����� ����� ������� ����������, ��������������� �������� ����� �� ������.");
		GetDlgItem(IDC_EDIT)->ShowWindow(1);
		GetDlgItem(IDC_PREV)->EnableWindow(1);
		GetDlgItem(IDC_EDIT)->SetFocus();

		ui_editBox = m_taskConditions.strTemperatureAt0.c_str();
		break;

	case TabPages::PAGE_ENVIRONMENT:
		ui_title =
			CString("��� 3: ������� ����������� ���������� �����, Tenv(") + m_strVariableNames + CString(")=...");
		ui_description =
			"������� ���� �������, ������������ ����������� ���������� �����, ���������� ����������� ���� ��� ����."
			" ����������� ���������� ����� ����� ����������� ������ � �����, �� ������������� ����.";
		GetDlgItem(IDC_EDIT)->ShowWindow(1);
		GetDlgItem(IDC_EDIT)->SetFocus();

		ui_editBox = m_taskConditions.strEvironmentTemperatureExpression.c_str();
		break;

	case TabPages::PAGE_LIMITS_STEPS:
		ui_title =
			"��� 4: ������� ������� ������� � ����� ���������� � ���������";
		ui_description =
			"������� ������� �������, �� ������� ����� ������������� ���������� (������� ��� �������),"
			" �� ������� �� ���������. ����� ������� ������������ �����, ����������� ��� ���� ������ ������� �����,\r\n��������, \"-1.25e3\"."
			" ���������� ���������� ��������, ������ ���� ����� ������������� ������. ��� ������ ����������, ��� ������ ����������� �����.";

		GetDlgItem(IDC_INTERVAL_LABEL1)->ShowWindow(1);
		GetDlgItem(IDC_BEG_EDIT1)->ShowWindow(1);
		GetDlgItem(IDC_TO_LABEL1)->ShowWindow(1);
		GetDlgItem(IDC_END_EDIT1)->ShowWindow(1);
		GetDlgItem(IDC_LABEL_INTERVALS1)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_INTERVALS1)->ShowWindow(1);
		GetDlgItem(IDC_BEG_EDIT1)->SetFocus();

		if (m_vars.size() > 1)
		{
			GetDlgItem(IDC_INTERVAL_LABEL2)->ShowWindow(1);
			GetDlgItem(IDC_BEG_EDIT2)->ShowWindow(1);
			GetDlgItem(IDC_TO_LABEL2)->ShowWindow(1);
			GetDlgItem(IDC_END_EDIT2)->ShowWindow(1);
			GetDlgItem(IDC_LABEL_INTERVALS2)->ShowWindow(1);
			GetDlgItem(IDC_EDIT_INTERVALS2)->ShowWindow(1);
		}

		// ���������� ����� ����������:
		GetDlgItem(IDC_INTERVAL_LABEL1)->SetWindowTextW(CString("�� ") + m_vars[0] + " ��");
		GetDlgItem(IDC_LABEL_INTERVALS1)->SetWindowTextW(CString("���������� �� ") + m_vars[0]);
		if (varCount > 1)
		{
			GetDlgItem(IDC_INTERVAL_LABEL2)->SetWindowTextW(CString("�� ") + m_vars[1] + " ��");
			GetDlgItem(IDC_LABEL_INTERVALS2)->SetWindowTextW(CString("���������� �� ") + m_vars[1]);
		}

		ui_fromVar1 = m_taskConditions.dblVar0From;
		ui_fromVar2 = m_taskConditions.dblVar1From;
		ui_toVar1 = m_taskConditions.dblVar0To;
		ui_toVar2 = m_taskConditions.dblVar1To;

		ui_intervalsVar1 = m_taskConditions.nVar0IntervalCount;
		ui_intervalsVar2 = m_taskConditions.nVar1IntervalCount;
		break;

	case TabPages::PAGE_THERMAL_CONDUCTIVITY:
		ui_title =
			"��� 5: ������� ����������� ����������������������";
		ui_description =
			"������� ����������� ���������������������� ����, ���� ��������� ��� �� �������.";

		GetDlgItem(IDC_TEMP_1)->ShowWindow(1);
		GetDlgItem(IDC_TEMP_2)->ShowWindow(1);
		GetDlgItem(IDC_TEMP_3)->ShowWindow(1);
		GetDlgItem(IDC_TEMP_4)->ShowWindow(1);
		GetDlgItem(IDC_TEMP_5)->ShowWindow(1);
		GetDlgItem(IDC_TEMP_6)->ShowWindow(1);
		GetDlgItem(IDC_TEMP_7)->ShowWindow(1);
		GetDlgItem(IDC_BORDER_TEMP)->ShowWindow(1);
		GetDlgItem(IDC_RADIO_TEMP_FULL)->ShowWindow(1);
		GetDlgItem(IDC_RADIO_TEMP_CALC)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TEMP_FULL)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TEMP_X)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TEMP_C)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TEMP_RO)->ShowWindow(1);

		ui_tempFull = m_taskConditions.dblThermalConductivity;
		((CButton*)GetDlgItem(IDC_RADIO_TEMP_FULL))->SetCheck(true);
		((CButton*)GetDlgItem(IDC_RADIO_TEMP_CALC))->SetCheck(false);
		OnBnClickedRadioTempFull();
		GetDlgItem(IDC_EDIT_TEMP_FULL)->SetFocus();

		GetDlgItem(IDC_NEXT)->SetWindowTextW(_T("����� >"));
		break;

	case TabPages::PAGE_TASK:
		ui_title =
			"��� 6: ������� �������� ���� ������";
		ui_description =
			"�������� �� �������������� ��� ������ � ������� � ���������."
			" ����� ������� �� ������ \"������\" ����� ������� ��������� ������� ������� ������,"
			" �� �� ������� ��������� ������� ��� ����� ������ �� ��� ���������."
			" ��� ��������� � ������������ �����.";
		GetDlgItem(IDC_NEXT)->SetWindowTextW(_T("������"));

		GetDlgItem(IDC_BORDER_TASK)->ShowWindow(1);
		GetDlgItem(IDC_TASK_TEMP)->ShowWindow(1);
		GetDlgItem(IDC_TASK_TIME)->ShowWindow(1);
		GetDlgItem(IDC_TASK_TEMP_CHANGES)->ShowWindow(1);
		GetDlgItem(IDC_TASK_SLICE_AT)->ShowWindow(1);

		((CButton*)GetDlgItem(IDC_TASK_TEMP))->SetCheck(false);
		((CButton*)GetDlgItem(IDC_TASK_TIME))->SetCheck(false);
		((CButton*)GetDlgItem(IDC_TASK_TEMP_CHANGES))->SetCheck(false);
		((CButton*)GetDlgItem(IDC_TASK_SLICE_AT))->SetCheck(false);

		switch (m_taskConditions.taskType)
		{
		case FIND_TEMPERATURE_AT:
			((CButton*)GetDlgItem(IDC_TASK_TEMP))->SetCheck(true);
			OnBnClickedTaskTemp();
			break;

		case FIND_TIME_WHEN_TEMPERATURE_IS:
			((CButton*)GetDlgItem(IDC_TASK_TIME))->SetCheck(true);
			OnBnClickedTaskTime();
			break;

		case BUILD_TEMPERATURE_CHANGES_FOR_POINT:
			((CButton*)GetDlgItem(IDC_TASK_TEMP_CHANGES))->SetCheck(true);
			OnBnClickedTaskTempChanges();
			break;

		case BUILD_FULL_BODY_FOR_TIME:
			((CButton*)GetDlgItem(IDC_TASK_SLICE_AT))->SetCheck(true);
			OnBnClickedTaskSliceAt();
			break;

		default:
			throw std::exception("Unknown task type found");
			break;
		}
		break;

	default:
		throw std::exception("TODO: Unknown page opened");
		break;
	}
	UpdateData(false);

	// TODO: ��������� ���� ���� ���� � �������
	// CString str;
	// bool bLoadValid = str.LoadString(IDS_EDIT_MENU);
	// ASSERT(bLoadValid);
}

///////////////////////////////////////////////////////////////////////////////


void CTaskConditionsDlg::OnBnClickedRadioTempFull()
{
	GetDlgItem(IDC_EDIT_TEMP_FULL)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_TEMP_X)->EnableWindow(0);
	GetDlgItem(IDC_EDIT_TEMP_C)->EnableWindow(0);
	GetDlgItem(IDC_EDIT_TEMP_RO)->EnableWindow(0);
}


void CTaskConditionsDlg::OnBnClickedRadioTempCalc()
{
	GetDlgItem(IDC_EDIT_TEMP_FULL)->EnableWindow(0);
	GetDlgItem(IDC_EDIT_TEMP_X)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_TEMP_C)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_TEMP_RO)->EnableWindow(1);
}


void CTaskConditionsDlg::OnBnClickedTaskTemp()
{
	GetDlgItem(IDC_TASK_PARAM1)->ShowWindow(1);
	GetDlgItem(IDC_TASK_PARAM2)->ShowWindow(1);
	GetDlgItem(IDC_EDIT_TASK_PARAM1)->ShowWindow(1);
	GetDlgItem(IDC_EDIT_TASK_PARAM2)->ShowWindow(1);

	GetDlgItem(IDC_TASK_PARAM1)->SetWindowTextW(_T("������ �������, � ��������:"));
	GetDlgItem(IDC_TASK_PARAM2)->SetWindowTextW(CString("� ����� �����, �� ") + m_vars[0] + ":");
	if (m_vars.size() > 1)
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_TASK_PARAM3)->SetWindowTextW(CString("� ����� �����, �� ") + m_vars[1] + ":");
	}
	else
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(0);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(0);
	}

	ui_taskParam1 = m_taskConditions.FIND_TEMPERATURE_AT.dblTime;
	ui_taskParam2 = m_taskConditions.FIND_TEMPERATURE_AT.point.X;
	ui_taskParam3 = m_taskConditions.FIND_TEMPERATURE_AT.point.Y;
}


void CTaskConditionsDlg::OnBnClickedTaskTime()
{
	GetDlgItem(IDC_TASK_PARAM1)->ShowWindow(1);
	GetDlgItem(IDC_TASK_PARAM2)->ShowWindow(1);
	GetDlgItem(IDC_EDIT_TASK_PARAM1)->ShowWindow(1);
	GetDlgItem(IDC_EDIT_TASK_PARAM2)->ShowWindow(1);

	GetDlgItem(IDC_TASK_PARAM1)->SetWindowTextW(_T("����� �����������:"));
	GetDlgItem(IDC_TASK_PARAM2)->SetWindowTextW(CString("� ����� �����, �� ") + m_vars[0] + ":");
	if (m_vars.size() > 1)
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_TASK_PARAM3)->SetWindowTextW(CString("� ����� �����, �� ") + m_vars[1] + ":");
	}
	else
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(0);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(0);
	}

	ui_taskParam1 = m_taskConditions.FIND_TIME_WHEN_TEMPERATURE_IS.dblTemperature;
	ui_taskParam2 = m_taskConditions.FIND_TIME_WHEN_TEMPERATURE_IS.point.X;
	ui_taskParam3 = m_taskConditions.FIND_TIME_WHEN_TEMPERATURE_IS.point.Y;
}


void CTaskConditionsDlg::OnBnClickedTaskTempChanges()
{
	GetDlgItem(IDC_TASK_PARAM1)->ShowWindow(1);
	GetDlgItem(IDC_TASK_PARAM2)->ShowWindow(1);
	GetDlgItem(IDC_EDIT_TASK_PARAM1)->ShowWindow(1);
	GetDlgItem(IDC_EDIT_TASK_PARAM2)->ShowWindow(1);

	GetDlgItem(IDC_TASK_PARAM1)->SetWindowTextW(_T("�� ������ �������, � ��������:"));
	GetDlgItem(IDC_TASK_PARAM2)->SetWindowTextW(CString("� ����� �����, �� ") + m_vars[0] + ":");
	if (m_vars.size() > 1)
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_TASK_PARAM3)->SetWindowTextW(CString("� ����� �����, �� ") + m_vars[1] + ":");
	}
	else
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(0);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(0);
	}

	ui_taskParam1 = m_taskConditions.BUILD_TEMPERATURE_CHANGES_FOR_POINT.dblEndTime;
	ui_taskParam2 = m_taskConditions.BUILD_TEMPERATURE_CHANGES_FOR_POINT.point.X;
	ui_taskParam3 = m_taskConditions.BUILD_TEMPERATURE_CHANGES_FOR_POINT.point.Y;
}


void CTaskConditionsDlg::OnBnClickedTaskSliceAt()
{
	GetDlgItem(IDC_TASK_PARAM1)->ShowWindow(1);
	GetDlgItem(IDC_TASK_PARAM2)->ShowWindow(0);
	GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(0);
	GetDlgItem(IDC_EDIT_TASK_PARAM1)->ShowWindow(1);
	GetDlgItem(IDC_EDIT_TASK_PARAM2)->ShowWindow(0);
	GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(0);

	GetDlgItem(IDC_TASK_PARAM1)->SetWindowTextW(_T("������ �������:"));
	ui_taskParam1 = m_taskConditions.BUILD_FULL_BODY_FOR_TIME.dblEndTime;
}
