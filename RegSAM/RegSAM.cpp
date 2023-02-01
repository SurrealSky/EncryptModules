﻿// RegSAM.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "RegSAM.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CRegSAMApp

BEGIN_MESSAGE_MAP(CRegSAMApp, CWinApp)
	ON_COMMAND(ID_32771, &CRegSAMApp::OnRegSAMPanel)
END_MESSAGE_MAP()


// CRegSAMApp 构造

CRegSAMApp::CRegSAMApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CRegSAMApp 对象

CRegSAMApp theApp;


// CRegSAMApp 初始化

BOOL CRegSAMApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


void CRegSAMApp::OnRegSAMPanel()
{
	// TODO: 在此添加命令处理程序代码
	CRuntimeClass* pThis = RUNTIME_CLASS(CChildFrame);
	CWnd* main = AfxGetMainWnd();
	DWORD data[2] = { 0 };
	data[0] = (DWORD)pThis;
	data[1] = IDR_MAINFRAME;
	main->SendMessage(WM_LOAD_CHILDWIN, (WPARAM)m_hInstance, (LPARAM)&data);
}
