// KeyTool.h : KeyTool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKeyToolApp
// �йش���ʵ�ֵ���Ϣ������� KeyTool.cpp
//

class CKeyToolApp : public CWinApp
{
public:
	CKeyToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyTool();
};
