// Base64Tool.h : Base64Tool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBase64ToolApp
// �йش���ʵ�ֵ���Ϣ������� Base64Tool.cpp
//

class CBase64ToolApp : public CWinApp
{
public:
	CBase64ToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBase64();
};
