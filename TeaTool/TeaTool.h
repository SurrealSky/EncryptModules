// TeaTool.h : TeaTool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTeaToolApp
// �йش���ʵ�ֵ���Ϣ������� TeaTool.cpp
//

class CTeaToolApp : public CWinApp
{
public:
	CTeaToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTEA();
};
