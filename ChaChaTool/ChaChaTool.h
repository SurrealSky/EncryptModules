// ChaChaTool.h : ChaChaTool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChaChaToolApp
// �йش���ʵ�ֵ���Ϣ������� ChaChaTool.cpp
//

class CChaChaToolApp : public CWinApp
{
public:
	CChaChaToolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnChaCha();
};
