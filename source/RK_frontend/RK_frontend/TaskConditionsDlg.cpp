// TaskConditionsDlg.cpp: файл реализации
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


// обработчики сообщений CTaskConditionsDlg

///////////////////////////////////////////////////////////////////////////////
BOOL CTaskConditionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_TO_LABEL1)->SetWindowTextW(_T(" до "));
	GetDlgItem(IDC_TO_LABEL2)->SetWindowTextW(_T(" до "));

	GoToPage(m_nOpenedTab);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
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

	// Валидация введённых данных, соответствующая странице.
	// Переменная bCanGoNext устанавливается в 0, если данные не верны.
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
					throw std::exception("Введите уравнение, а не просто выражение. Используйте =, <, >, !=, AND, OR, NOT.");
				if (!m_vars.size())
					throw std::exception("Не жадничайте, введите хотя бы одну переменную.");
				if (m_vars.size() > 2)
					throw std::exception("Мы не будем работать с трёхмерными и большими пространствами. Уменьшите число переменных до одной или двух.");

				for (size_t i = 0; i < m_vars.size(); i++)
					if (m_vars[i] == "t" || m_vars[i] == "T")
						throw std::exception("Имена переменных t и T использовать запрещено, выберите другие.");

				// Инициализация m_strVariableNames
				m_strVariableNames = "";
				size_t size_m1 = m_vars.size() - 1;
				for (size_t i = 0; i < size_m1; i++)
					m_strVariableNames += (m_vars[i] + CString(", "));
				m_strVariableNames += m_vars[size_m1];

				// Сохраняем полученные данные о задаче (ради них, собственно, огород и городился).
				m_taskConditions.strBodyExpression = ascii.m_psz;
			}
			catch (std::exception ex) {
				MessageBoxA(this->GetSafeHwnd(), ex.what(), "Ошибка в выражении", MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}
			catch (...) {
				MessageBox(_T("Неизвестная ошибка при разборе выражения"), _T("Ошибка"), MB_ICONEXCLAMATION);
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
				throw std::exception("Введите вещественное выражение, а не уравнение. Не используйте =, <, >, !=, AND, OR, NOT.");

			// Проверка переменных: все ли они есть среди введённых на предыдущем шаге?
			// Будем считать что если не ввели то это баг.
			for (size_t i = 0, size = vars2.size(); i < size; i++)
			{
				bool bVarFound = 0;
				for (size_t j = 0, sizeOriginal = m_vars.size(); j < sizeOriginal; j++)
					if (m_vars[j] == vars2[i]) { // Нашли.
						bVarFound = 1;
						break;
					}
				if (!bVarFound) // Не нашли :(
					throw std::exception(CString("Переменная \"") + vars2[i] + "\" не была объявлена на предыдущем шаге и не может использоваться.");
			}

			// Сохраняем полученные данные о задаче
			m_taskConditions.strTemperatureAt0 = ascii.m_psz;
		}
		catch (std::exception ex) {
			MessageBoxA(this->GetSafeHwnd(), ex.what(), "Ошибка в выражении", MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}
		catch (...) {
			MessageBox(_T("Неизвестная ошибка при разборе выражения"), _T("Ошибка"), MB_ICONEXCLAMATION);
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
				throw std::exception("Введите вещественное выражение, а не уравнение. Не используйте =, <, >, !=, AND, OR, NOT.");

			// Проверка переменных: все ли они есть среди введённых на предыдущем шаге?
			// Будем считать что если не ввели то это баг.
			for (size_t i = 0, size = vars2.size(); i < size; i++)
			{
				bool bVarFound = 0;
				for (size_t j = 0, sizeOriginal = m_vars.size(); j < sizeOriginal; j++)
					if (m_vars[j] == vars2[i]) { // Нашли.
						bVarFound = 1;
						break;
					}
				if (!bVarFound) // Не нашли :(
					throw std::exception(CString("Переменная \"") + vars2[i] + "\" не была объявлена на предыдущем шаге и не может использоваться.");
			}

			// Сохраняем полученные данные о задаче
			m_taskConditions.strEvironmentTemperatureExpression = ascii.m_psz;
		}
		catch (std::exception ex) {
			MessageBoxA(this->GetSafeHwnd(), ex.what(), "Ошибка в выражении", MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}
		catch (...) {
			MessageBox(_T("Неизвестная ошибка при разборе выражения"), _T("Ошибка"), MB_ICONEXCLAMATION);
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
			MessageBox(_T("Начало интервала должно быть меньше конца"), _T("Ошибка"), MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}

		if (!ui_intervalsVar1 || (m_vars.size() > 1 && !ui_intervalsVar1))
		{
			MessageBox(_T("Число интервалов должно быть больше 0"), _T("Ошибка"), MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}

		if (ui_fromVar1 == ui_toVar1 || (m_vars.size() > 1 && ui_fromVar2 == ui_toVar2))
		{
			MessageBox(_T("Начало и конец интервала не должны совпадать"), _T("Ошибка"), MB_ICONEXCLAMATION);
			bCanGoNext = 0;
		}
		break;

	case TabPages::PAGE_THERMAL_CONDUCTIVITY:
		if (((CButton*)GetDlgItem(IDC_RADIO_TEMP_FULL))->GetCheck())
		{
			// Выбран прямой ввод.
			if (ui_tempFull <= 0)
			{
				MessageBox(_T("Температуропроводность должна быть положительным числом"), _T("Ошибка"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			m_taskConditions.dblThermalConductivity = ui_tempFull;
		}
		else
		{
			// Выбран ввод формулой.
			if (ui_tempC == 0. || ui_tempRo == 0.)
			{
				MessageBox(_T("Не надо делить на 0, введите корректные значения."), _T("Ошибка"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			const double thermalConductivity = ui_tempX / (ui_tempRo * ui_tempC);
			if (thermalConductivity <= 0)
			{
				MessageBox(_T("Температуропроводность должна быть положительным числом"), _T("Ошибка"), MB_ICONEXCLAMATION);
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
				MessageBox(_T("Указанное время должно быть положительным числом"), _T("Ошибка"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}
			// X между Xbeg и Xend
			if (ui_taskParam2 < m_taskConditions.dblVar0From || m_taskConditions.dblVar0To < ui_taskParam2)
			{
				MessageBox(_T("Первая пеменная не входит в границы поиска решения"), _T("Ошибка"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			if (m_vars.size() > 1 && (ui_taskParam3 < m_taskConditions.dblVar1From || m_taskConditions.dblVar1To < ui_taskParam3))
			{
				MessageBox(_T("Вторая пеменная не входит в границы поиска решения"), _T("Ошибка"), MB_ICONEXCLAMATION);
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
			// X между Xbeg и Xend
			if (ui_taskParam2 < m_taskConditions.dblVar0From || m_taskConditions.dblVar0To < ui_taskParam2)
			{
				MessageBox(_T("Первая пеменная не входит в границы поиска решения"), _T("Ошибка"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			if (m_vars.size() > 1 && (ui_taskParam3 < m_taskConditions.dblVar1From || m_taskConditions.dblVar1To < ui_taskParam3))
			{
				MessageBox(_T("Вторая пеменная не входит в границы поиска решения"), _T("Ошибка"), MB_ICONEXCLAMATION);
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
				MessageBox(_T("Указанное время должно быть положительным числом"), _T("Ошибка"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}
			// X между Xbeg и Xend
			if (ui_taskParam2 < m_taskConditions.dblVar0From || m_taskConditions.dblVar0To < ui_taskParam2)
			{
				MessageBox(_T("Первая пеменная не входит в границы поиска решения"), _T("Ошибка"), MB_ICONEXCLAMATION);
				bCanGoNext = 0;
			}

			if (m_vars.size() > 1 && (ui_taskParam3 < m_taskConditions.dblVar1From || m_taskConditions.dblVar1To < ui_taskParam3))
			{
				MessageBox(_T("Вторая пеменная не входит в границы поиска решения"), _T("Ошибка"), MB_ICONEXCLAMATION);
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
				MessageBox(_T("Указанное время должно быть положительным числом"), _T("Ошибка"), MB_ICONEXCLAMATION);
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

	// Переход на следующаю страницу, если валидация пройдена успешна и есть куда переходить.
	// Если это последняя страница, закрываем окно по OnOK().
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
// Настройка элементов страницы при переходе к ней
void CTaskConditionsDlg::GoToPage(int tabIndex)
{
	using namespace lang;
	{
		// Скрываем все элементы.
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
			"Шаг 1: введите уравнение тела";
		ui_description =
			"Введите уравнение (или неравенство) нагреваемого или охлаждаемого тела на прямой или плоскости."
			" Например, \"x*x + y*y <= 4\" — уравнение замкнутого круга с центром в начале координат и радиусом 2."
			" Разрешается использовать одну или две переменные, их названия не играют никакой роли.";
		GetDlgItem(IDC_EDIT)->ShowWindow(1);
		GetDlgItem(IDC_EDIT)->SetFocus();
		GetDlgItem(IDC_NEXT)->SetWindowTextW(_T("Далее >"));
		GetDlgItem(IDC_PREV)->EnableWindow(0);

		ui_editBox = m_taskConditions.strBodyExpression.c_str();
		break;

	case TabPages::PAGE_T0:
		ui_title =
			CString("Шаг 2: введите начальную температуру тела, T(") + m_strVariableNames + CString(")=...");
		ui_description =
			CString("Введите функцию, определяющую начальную температуру тела."
			" На предыдущем шаге вы ввели уравнение с независимыми переменными (") + m_strVariableNames +
				CString("), поэтому на этом шаге можете использовать эти переменные."
			" Писать \"T(") + m_strVariableNames + CString(")=\" не требуется, пишите только правую часть данной функции."
			" Например, \"10\" задаёт тепературу 10 градусов в любой точке тела."
			" \"pow(x*x + y*y, 1/2)\" задаёт более сложное нагревание, соответствующее удалению точки от центра.");
		GetDlgItem(IDC_EDIT)->ShowWindow(1);
		GetDlgItem(IDC_PREV)->EnableWindow(1);
		GetDlgItem(IDC_EDIT)->SetFocus();

		ui_editBox = m_taskConditions.strTemperatureAt0.c_str();
		break;

	case TabPages::PAGE_ENVIRONMENT:
		ui_title =
			CString("Шаг 3: введите температуру окружающей среды, Tenv(") + m_strVariableNames + CString(")=...");
		ui_description =
			"Введите тело функции, определяющей температуру окружающей среды, аналогично предыдущему шагу для тела."
			" Температура окружающей среды будет вычисляться только в узлах, не принадлежащих телу.";
		GetDlgItem(IDC_EDIT)->ShowWindow(1);
		GetDlgItem(IDC_EDIT)->SetFocus();

		ui_editBox = m_taskConditions.strEvironmentTemperatureExpression.c_str();
		break;

	case TabPages::PAGE_LIMITS_STEPS:
		ui_title =
			"Шаг 4: введите границы области и число интервалов её разбиения";
		ui_description =
			"Введите границы области, на которой будет производиться построение (включая эти границы),"
			" по каждому из изменений. Можно вводить вещественные числа, используйте при этом вместо запятой точку,\r\nнапример, \"-1.25e3\"."
			" Количество интервалов наоборот, должно быть целым положительным числом. Чем больше интервалов, тем дольше вычисляется ответ.";

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

		// Показываем имена переменных:
		GetDlgItem(IDC_INTERVAL_LABEL1)->SetWindowTextW(CString("По ") + m_vars[0] + " от");
		GetDlgItem(IDC_LABEL_INTERVALS1)->SetWindowTextW(CString("Интервалов по ") + m_vars[0]);
		if (varCount > 1)
		{
			GetDlgItem(IDC_INTERVAL_LABEL2)->SetWindowTextW(CString("По ") + m_vars[1] + " от");
			GetDlgItem(IDC_LABEL_INTERVALS2)->SetWindowTextW(CString("Интервалов по ") + m_vars[1]);
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
			"Шаг 5: введите коэффициент температуропроводности";
		ui_description =
			"Введите коэффициент температуропроводности тела, либо вычислите его по формуле.";

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

		GetDlgItem(IDC_NEXT)->SetWindowTextW(_T("Далее >"));
		break;

	case TabPages::PAGE_TASK:
		ui_title =
			"Шаг 6: введите конечную цель задачи";
		ui_description =
			"Выберите из перечисленного тип задачи и введите её параметры."
			" После нажатия на кнопку \"Готово\" будет запущен отдельный процесс решения задачи,"
			" вы не сможете запустить решение ещё одной задачи до его окончания."
			" Все параметры — вещественные числа.";
		GetDlgItem(IDC_NEXT)->SetWindowTextW(_T("Готово"));

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

	// TODO: перенести весь срач выше в ресурсы
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

	GetDlgItem(IDC_TASK_PARAM1)->SetWindowTextW(_T("Момент времени, в секундах:"));
	GetDlgItem(IDC_TASK_PARAM2)->SetWindowTextW(CString("В какой точке, по ") + m_vars[0] + ":");
	if (m_vars.size() > 1)
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_TASK_PARAM3)->SetWindowTextW(CString("В какой точке, по ") + m_vars[1] + ":");
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

	GetDlgItem(IDC_TASK_PARAM1)->SetWindowTextW(_T("Порог температуры:"));
	GetDlgItem(IDC_TASK_PARAM2)->SetWindowTextW(CString("В какой точке, по ") + m_vars[0] + ":");
	if (m_vars.size() > 1)
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_TASK_PARAM3)->SetWindowTextW(CString("В какой точке, по ") + m_vars[1] + ":");
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

	GetDlgItem(IDC_TASK_PARAM1)->SetWindowTextW(_T("До какого момента, в секундах:"));
	GetDlgItem(IDC_TASK_PARAM2)->SetWindowTextW(CString("В какой точке, по ") + m_vars[0] + ":");
	if (m_vars.size() > 1)
	{
		GetDlgItem(IDC_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_EDIT_TASK_PARAM3)->ShowWindow(1);
		GetDlgItem(IDC_TASK_PARAM3)->SetWindowTextW(CString("В какой точке, по ") + m_vars[1] + ":");
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

	GetDlgItem(IDC_TASK_PARAM1)->SetWindowTextW(_T("Момент времени:"));
	ui_taskParam1 = m_taskConditions.BUILD_FULL_BODY_FOR_TIME.dblEndTime;
}
