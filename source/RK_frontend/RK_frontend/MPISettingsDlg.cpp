// MPISettingsDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "RK_frontend.h"
#include "MPISettingsDlg.h"
#include "afxdialogex.h"


// диалоговое окно CMPISettingsDlg

IMPLEMENT_DYNAMIC(CMPISettingsDlg, CDialog)

CMPISettingsDlg::CMPISettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MPISETTINGSDLG, pParent)
	, m_strArgs(_T(""))
{
}

CMPISettingsDlg::~CMPISettingsDlg()
{
}

void CMPISettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ARGS, m_strArgs);
}


BEGIN_MESSAGE_MAP(CMPISettingsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SETDEFAULT, &CMPISettingsDlg::OnBnClickedButtonDefault)
END_MESSAGE_MAP()


// обработчики сообщений CMPISettingsDlg


void CMPISettingsDlg::OnBnClickedButtonDefault()
{
	m_strArgs = ((CRKFrontendApp*)AfxGetApp())->GetMPIDefaultExecCmd();
	UpdateData(FALSE);
}


BOOL CMPISettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}
