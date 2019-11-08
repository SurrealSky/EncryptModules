#pragma once
#include "afxcmn.h"


// CBase64Panel 对话框

class CBase64Panel : public CDialogEx
{
	DECLARE_DYNAMIC(CBase64Panel)

public:
	CBase64Panel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBase64Panel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	HexControl pHexControl1;
public:
	virtual BOOL OnInitDialog();
	CRichEditCtrl mEdit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
