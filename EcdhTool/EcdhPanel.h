#pragma once
#include"stdafx.h"


// CEcdhPanel �Ի���

class CEcdhPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CEcdhPanel)

public:
	CEcdhPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEcdhPanel();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
