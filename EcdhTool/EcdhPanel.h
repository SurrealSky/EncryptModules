#pragma once
#include"stdafx.h"


// CEcdhPanel 对话框

class CEcdhPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CEcdhPanel)

public:
	CEcdhPanel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEcdhPanel();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	HexControl pHexControl1;
	HexControl pHexControl2;
	HexControl pHexControl3;
	HexControl pHexControl4;
	HexControl pHexControl5;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
