#pragma once
#include "afxwin.h"
#include<string>


// ChaChaPanel �Ի���

class ChaChaPanel : public CDialogEx
{
	DECLARE_DYNAMIC(ChaChaPanel)

public:
	ChaChaPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChaChaPanel();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
public:
	HexControl pHexControl1;
	CString mKey;
	CString mNonce;
	CButton mCheckHex;
	BOOL bVerify;
	CString strSSLeay_version;
	CComboBox mEncType;
	CString mIC;
public:
	std::string HexToStr(BYTE *pbDest, int nLen);
	std::string StrToHex(BYTE *pbDest, int nLen);
	std::string MyWideCharToMultiByte(BYTE *pbDest, int nLen);
	std::string MyMultiByteToWideChar(BYTE *pbDest, int nLen);
};
