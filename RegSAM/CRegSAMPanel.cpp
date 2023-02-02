// CRegSAMPanel.cpp: 实现文件
//

#include "pch.h"
#include "RegSAM.h"
#include "CRegSAMPanel.h"
#include "afxdialogex.h"
#include "SamDecrypt.h"


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


BOOL CRegSAMPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SamDecrypt samDec;
	samDec.getensamlm(samDec.samInfo.user_V);
	samDec.getensamnt(samDec.samInfo.user_V);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
