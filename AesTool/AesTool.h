// AesTool.h : AesTool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAesToolApp
// �йش���ʵ�ֵ���Ϣ������� AesTool.cpp
//

class CAesToolApp : public CWinApp
{
public:
	CAesToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnAes();
};
