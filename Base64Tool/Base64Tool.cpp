// Base64Tool.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Base64Tool.h"
#include"ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CBase64ToolApp

BEGIN_MESSAGE_MAP(CBase64ToolApp, CWinApp)
	ON_COMMAND(ID_32771, &CBase64ToolApp::OnBase64)
END_MESSAGE_MAP()


// CBase64ToolApp ����

CBase64ToolApp::CBase64ToolApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBase64ToolApp ����

CBase64ToolApp theApp;


// CBase64ToolApp ��ʼ��

BOOL CBase64ToolApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	CWinApp::InitInstance();

	return TRUE;
}


void CBase64ToolApp::OnBase64()
{
	// TODO: �ڴ���������������
	CRuntimeClass* pThis = RUNTIME_CLASS(CChildFrame);
	CWnd *main = AfxGetMainWnd();
	DWORD data[2] = { 0 };
	data[0] = (DWORD)pThis;
	data[1] = IDR_MAINFRAME;
	main->SendMessage(WM_LOAD_CHILDWIN, (WPARAM)m_hInstance, (LPARAM)&data);
}
