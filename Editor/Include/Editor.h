
// Editor.h : Editor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif	

#include "resource.h"       // �� ��ȣ�Դϴ�.

// EditorApp:
// �� Ŭ������ ������ ���ؼ��� Editor.cpp�� �����Ͻʽÿ�.
//

class EditorApp : public CWinApp
{
public:
	EditorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int Run();
	virtual BOOL OnIdle(LONG lCount);

};

extern EditorApp theApp;
