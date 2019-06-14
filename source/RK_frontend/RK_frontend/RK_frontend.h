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

// RK_frontend.h : главный файл заголовка для приложения RK_frontend
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы
#include "lang/TaskConditions.h"

// CRKFrontendApp:
// О реализации данного класса см. RK_frontend.cpp
//

class CRKFrontendApp : public CWinAppEx
{
public:
	lang::TaskConditions m_taskConditions;

public:
	CRKFrontendApp();


// Переопределение
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

// Реализация
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
