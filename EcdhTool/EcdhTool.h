// EcdhTool.h : EcdhTool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEcdhToolApp
// �йش���ʵ�ֵ���Ϣ������� EcdhTool.cpp
//

class CEcdhToolApp : public CWinApp
{
public:
	CEcdhToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEcdh();
};
