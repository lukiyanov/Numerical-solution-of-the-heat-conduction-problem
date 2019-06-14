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

// RK_frontend.h : ������� ���� ��������� ��� ���������� RK_frontend
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������
#include "lang/TaskConditions.h"

// CRKFrontendApp:
// � ���������� ������� ������ ��. RK_frontend.cpp
//

class CRKFrontendApp : public CWinAppEx
{
public:
	lang::TaskConditions m_taskConditions;

public:
	CRKFrontendApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

private:
	static const CString s_strSettingsSection;
	static const CString s_strDefaultMPIExecCmd;
	static const CString s_strMPISettingsEntry;

public:
	CString GetMPIExecCmd();
	CString GetMPIDefaultExecCmd();
	void SetMPIExecCmd(const CString& cmd);

// ����������
public:
	UINT  m_nAppLook;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMpiSettings();
	afx_msg void OnButtonSolve();
};

extern CRKFrontendApp theApp;
