
// screenshot.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CscreenshotApp:
// �йش����ʵ�֣������ screenshot.cpp
//

class CscreenshotApp : public CWinApp
{
public:
	HWND m_hwndDlg;
	CscreenshotApp();
	virtual BOOL ProcessMessageFilter(int code,LPMSG lpMsg);
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CscreenshotApp theApp;