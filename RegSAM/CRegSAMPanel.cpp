// CRegSAMPanel.cpp: 实现文件
//

#include "pch.h"
#include "RegSAM.h"
#include "CRegSAMPanel.h"
#include "afxdialogex.h"


// CRegSAMPanel 对话框

IMPLEMENT_DYNAMIC(CRegSAMPanel, CDialogEx)

CRegSAMPanel::CRegSAMPanel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CRegSAMPanel::~CRegSAMPanel()
{
}

void CRegSAMPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegSAMPanel, CDialogEx)
END_MESSAGE_MAP()


// CRegSAMPanel 消息处理程序
