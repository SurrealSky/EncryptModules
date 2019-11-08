#pragma once
#include "afxwin.h"
#include<string>


// CAesPanel �Ի���

class CAesPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CAesPanel)

public:
	CAesPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAesPanel();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	HexControl pHexControl1;
	CComboBox EncryptMode;
	CComboBox mPadding;
	CEdit mKey;
	CEdit mIv;
	CButton mCheckHex;
	CComboBox mBlock;
	CString strSSLeay_version;
public:
	std::string HexToStr(BYTE *pbDest, int nLen);
	std::string StrToHex(BYTE *pbDest, int nLen);
	std::string MyWideCharToMultiByte(BYTE *pbDest, int nLen);
	std::string MyMultiByteToWideChar(BYTE *pbDest, int nLen);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

};
