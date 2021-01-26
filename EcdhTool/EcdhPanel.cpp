// EcdhPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EcdhTool.h"
#include "EcdhPanel.h"
#include "afxdialogex.h"
#include"Ecdh.h"


// CEcdhPanel �Ի���

IMPLEMENT_DYNAMIC(CEcdhPanel, CDialogEx)

CEcdhPanel::CEcdhPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEcdhPanel::IDD, pParent)
{

}

CEcdhPanel::~CEcdhPanel()
{
}

void CEcdhPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEcdhPanel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CEcdhPanel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEcdhPanel::OnBnClickedButton2)
END_MESSAGE_MAP()


// CEcdhPanel ��Ϣ�������


BOOL CEcdhPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//���ص�һ��HexControl
	pHexControl1.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl1.SetPosition(10, 40, 600, 35);
	pHexControl1.SetEditMode(EditMode::INSERT);

	//���صڶ���HexControl
	pHexControl2.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl2.SetPosition(10, 100, 600, 70);
	pHexControl2.SetEditMode(EditMode::INSERT);

	pHexControl3.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl3.SetPosition(10, 245, 600, 35);
	pHexControl3.SetEditMode(EditMode::INSERT);

	pHexControl4.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl4.SetPosition(10, 305, 600, 70);
	pHexControl4.SetEditMode(EditMode::INSERT);

	pHexControl5.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl5.SetPosition(10, 395, 600, 35);
	pHexControl5.SetEditMode(EditMode::INSERT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//������Կ
void CEcdhPanel::OnBnClickedButton1()
{
	CEcdh mEcdh;
	unsigned char privateKey1[0x50] = { 0 };
	unsigned int	len1 = sizeof(privateKey1);
	unsigned char publicKey1[0x50] = { 0 };
	unsigned int	len2 = sizeof(publicKey1);
	mEcdh.GenerateECKey(privateKey1, &len1, publicKey1, &len2,false);

	pHexControl1.SetData( privateKey1, len1);
	pHexControl2.SetData(publicKey1, len2);

}

//���㹲����Կ
void CEcdhPanel::OnBnClickedButton2()
{
	unsigned int pri_key_len= pHexControl3.GetDataLen();
	unsigned int pub_key_len = pHexControl4.GetDataLen();
	if (pri_key_len != 0 && pub_key_len != 0)
	{
		unsigned char *pri_key = (unsigned char*)malloc(pri_key_len);
		unsigned char *pub_key = (unsigned char*)malloc(pub_key_len);
		pHexControl3.GetData(pri_key, pri_key_len);
		pHexControl4.GetData(pub_key, pub_key_len);
		unsigned char sharekey[0x50] = { 0 };
		unsigned int sharekeylen = 0x50;
		CEcdh mEcdh;
		if (!mEcdh.ComputeShareKey(pri_key, pri_key_len, pub_key, pub_key_len, sharekey, &sharekeylen))
		{
			AfxMessageBox(L"����ʧ��");
			return;
		}
		pHexControl5.SetData(sharekey, sharekeylen);
	}
}
