// Base64Panel.cpp : 实现文件
//

#include "stdafx.h"
#include "Base64Tool.h"
#include "Base64Panel.h"
#include "afxdialogex.h"
#include"Base64Encode.h"
#include"../CommonLib/include/CodedConvert.h"


// CBase64Panel 对话框

IMPLEMENT_DYNAMIC(CBase64Panel, CDialogEx)

CBase64Panel::CBase64Panel(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CBase64Panel::~CBase64Panel()
{
}

void CBase64Panel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, mEdit);
}


BEGIN_MESSAGE_MAP(CBase64Panel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CBase64Panel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBase64Panel::OnBnClickedButton2)
END_MESSAGE_MAP()


// CBase64Panel 消息处理程序


BOOL CBase64Panel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	AfxInitRichEdit();

	mEdit.MoveWindow(20, 20, 640, 180, TRUE);
	mEdit.SetWindowTextW(L"aGVsbG8gd29ybGQ=");

	pHexControl1.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl1.SetPosition(20, 205, 640, 215);
	pHexControl1.SetEditMode(EditMode::INSERT);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//解码
void CBase64Panel::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mEdit.GetWindowTextLengthW() != 0)
	{
		CString text;
		mEdit.GetWindowTextW(text);
		CipherBase64::CBase64Encode mBase64;
		SurrealConvert::CodedConvert mCoded;
		std::wstring strw = text.GetBuffer(0);
		std::string stra= mCoded.UnicodeToAscii(strw);

		stra =mBase64.base64Decode((char*)stra.c_str(), stra.length(), FALSE);

		pHexControl1.SetData( (BYTE*)stra.c_str(), stra.length());

	}
}

//编码
void CBase64Panel::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned int len=pHexControl1.GetDataLen();

	if (len>0)
	{
		BYTE *buffer = (BYTE*)malloc(len);
		pHexControl1.GetData(buffer, len);
		CipherBase64::CBase64Encode mBase64;
		std::string str= mBase64.base64Encode((char*)buffer, len, FALSE);

		SurrealConvert::CodedConvert mCoded;
		std::wstring stra = mCoded.AsciiToUnicode(str);
		CString text;
		text.Append(stra.c_str(), stra.length());
		mEdit.SetWindowTextW(text);
	}
}
