// LibraMPTool.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CLibraMPToolApp:
// �аѾ\��@�����O�� LibraMPTool.cpp
//


class CLibraMPToolApp : public CWinApp
{
public:
	CLibraMPToolApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CLibraMPToolApp theApp;