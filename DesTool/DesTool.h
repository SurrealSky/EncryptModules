// DesTool.h : DesTool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDesToolApp
// �йش���ʵ�ֵ���Ϣ������� DesTool.cpp
//

class CDesToolApp : public CWinApp
{
public:
	CDesToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnDES();
};
