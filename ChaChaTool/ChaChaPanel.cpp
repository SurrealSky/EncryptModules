// ChaChaPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChaChaTool.h"
#include "ChaChaPanel.h"
#include "afxdialogex.h"
#include"ChaCha20.h"


// ChaChaPanel �Ի���

IMPLEMENT_DYNAMIC(ChaChaPanel, CDialogEx)

ChaChaPanel::ChaChaPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChaChaPanel::IDD, pParent)
	, mKey(_T(""))
	, mNonce(_T(""))
	, bVerify(FALSE)
	, strSSLeay_version(_T(""))
{

}

ChaChaPanel::~ChaChaPanel()
{
}

void ChaChaPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mKey);
	DDX_Text(pDX, IDC_EDIT2, mNonce);
	DDX_Control(pDX, IDC_CHECK1, mCheckHex);
	DDX_Check(pDX, IDC_CHECK2, bVerify);
	DDX_Text(pDX, IDC_EDIT3, strSSLeay_version);
}


BEGIN_MESSAGE_MAP(ChaChaPanel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChaChaPanel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ChaChaPanel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &ChaChaPanel::OnBnClickedCheck1)
END_MESSAGE_MAP()


// ChaChaPanel ��Ϣ�������

BOOL ChaChaPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//����sodium�汾
	std::string str = ChaCha20::Getsodium_version();
	std::wstring strW(str.length(), L' ');
	std::copy(str.begin(), str.end(), strW.begin());
	strSSLeay_version = "";
	strSSLeay_version.Append(strW.c_str(), strW.size());

	//���ص�һ��HexControl
	pHexControl1.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl1.SetPosition(10, 120, 630, 350);
	BYTE buffer2[] = "1213123213213 dsdfsafsda";
	pHexControl1.SetData( buffer2, sizeof(buffer2));

	mKey = "356BAA7CC713F17F0C0126A47C7FFFBB393B723CEF8B0065127D8678ADE9C53E";
	mNonce = "A65B988BAED0375A";
	mCheckHex.SetCheck(TRUE);
	bVerify = FALSE;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//����
void ChaChaPanel::OnBnClickedButton1()
{
	UpdateData(TRUE);
	std::string mb_Key = MyWideCharToMultiByte((BYTE*)mKey.GetBuffer(0), mKey.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16������Կ����
		mb_Key = StrToHex((BYTE*)mb_Key.c_str(), mb_Key.length());
	}
	//ȡ��Nonce
	std::string mb_Nonce = MyWideCharToMultiByte((BYTE*)mNonce.GetBuffer(0), mNonce.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16����IV����
		mb_Nonce = StrToHex((BYTE*)mb_Nonce.c_str(), mb_Nonce.length());
	}

	//ȡ��Դ����
	unsigned __int64 srclen = pHexControl1.GetDataLen();
	if (srclen == 0)
	{
		AfxMessageBox(_T("����Ϊ��"));
		return;
	}
	BYTE *srcBuffer = (BYTE*)malloc(srclen);
	memset(srcBuffer, 0, srclen);
	pHexControl1.GetData(srcBuffer, srclen);

	ChaCha20 mChaCha20;
	mChaCha20.SetKey((unsigned char*)mb_Key.c_str(), crypto_aead_chacha20poly1305_KEYBYTES, (unsigned char*)mb_Nonce.c_str(), crypto_aead_chacha20poly1305_NPUBBYTES);
	unsigned long long dstlen =0;
	unsigned char *dstbuffer=NULL;
	mChaCha20.Encrypt(srcBuffer, srclen, &dstbuffer, dstlen);
	if (dstlen)
	{
		pHexControl1.SetData( dstbuffer, dstlen);
	}
	mChaCha20.FreeBuffer(&dstbuffer);
}

//����
void ChaChaPanel::OnBnClickedButton2()
{
	UpdateData(TRUE);
	std::string mb_Key = MyWideCharToMultiByte((BYTE*)mKey.GetBuffer(0), mKey.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16������Կ����
		mb_Key = StrToHex((BYTE*)mb_Key.c_str(), mb_Key.length());
	}
	//ȡ��Nonce
	std::string mb_Nonce = MyWideCharToMultiByte((BYTE*)mNonce.GetBuffer(0), mNonce.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16����IV����
		mb_Nonce = StrToHex((BYTE*)mb_Nonce.c_str(), mb_Nonce.length());
	}

	//ȡ��Դ����
	UINT srclen = pHexControl1.GetDataLen();
	if (srclen == 0)
	{
		AfxMessageBox(_T("����Ϊ��"));
		return;
	}
	BYTE *srcBuffer = (BYTE*)malloc(srclen);
	memset(srcBuffer, 0, srclen);
	pHexControl1.GetData(srcBuffer, srclen);

	ChaCha20 mChaCha20;
	mChaCha20.SetKey((unsigned char*)mb_Key.c_str(), crypto_aead_chacha20poly1305_KEYBYTES, (unsigned char*)mb_Nonce.c_str(), crypto_aead_chacha20poly1305_NPUBBYTES);
	unsigned long long dstlen = 0;
	unsigned char *dstbuffer = NULL;
	if (bVerify)
		mChaCha20.Decrypt(srcBuffer, srclen, &dstbuffer, dstlen);
	else
		mChaCha20.DecryptAndNoVerify(srcBuffer, srclen, &dstbuffer, dstlen);
	if (dstlen)
	{
		pHexControl1.SetData( dstbuffer, dstlen);
	}else
		pHexControl1.SetData( 0, 0);
	mChaCha20.FreeBuffer(&dstbuffer);
}

//�л�������̬
void ChaChaPanel::OnBnClickedCheck1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (mCheckHex.GetCheck() == TRUE)
	{
		if (mKey.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)mKey.GetBuffer(0), mKey.GetLength());
			std::string str = HexToStr((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			mKey = "";
			mKey.Append((wchar_t*)strW.c_str(), strW.length() / 2);
		}
		if (mNonce.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)mNonce.GetBuffer(0), mNonce.GetLength());
			std::string str = HexToStr((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			mNonce = "";
			mNonce.Append((wchar_t*)strW.c_str(), strW.length() / 2);
		}
	}
	else
	{
		if (mKey.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)mKey.GetBuffer(0), mKey.GetLength());
			std::string str = StrToHex((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			mKey = "";
			mKey.Append((wchar_t*)strW.c_str(), strW.length() / 2);
		}
		if (mNonce.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)mNonce.GetBuffer(0), mNonce.GetLength());
			std::string str = StrToHex((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			mNonce = "";
			mNonce.Append((wchar_t*)strW.c_str(), strW.length() / 2);
		}
	}
	UpdateData(FALSE);
}

std::string ChaChaPanel::HexToStr(BYTE *pbSrc, int nLen)
{
	std::string str;
	char ddl, ddh;
	int i;

	for (i = 0; i<nLen; i++)
	{
		ddh = 48 + pbSrc[i] / 16;
		ddl = 48 + pbSrc[i] % 16;
		if (ddh > 57) ddh = ddh + 7;
		if (ddl > 57) ddl = ddl + 7;
		str.push_back(ddh);
		str.push_back(ddl);
	}
	return str;
}

std::string ChaChaPanel::StrToHex(BYTE *pbSrc, int nLen)
{
	std::string str;
	char h1, h2;
	BYTE s1, s2;
	int i;

	for (i = 0; i<nLen / 2; i++)
	{
		h1 = pbSrc[2 * i];
		h2 = pbSrc[2 * i + 1];

		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;

		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;

		str.push_back(s1 * 16 + s2);
	}
	return str;
}

std::string ChaChaPanel::MyWideCharToMultiByte(BYTE *pbDest, int nLen)
{
	//������Ҫ���ٸ��ֽڲ��ܱ�ʾ��Ӧ�Ķ��ֽ��ַ���
	DWORD num = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)pbDest, nLen, NULL, 0, NULL, 0);
	//���ٿռ�
	char *pChar = NULL;
	pChar = (char*)malloc(num*sizeof(char));
	if (pChar == NULL)
	{
		free(pChar);
	}
	memset(pChar, 0, num*sizeof(char));
	//�����ֽ��ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)pbDest, nLen, pChar, num, NULL, 0);
	std::string retString;
	retString.append(pChar, num);
	free(pChar);
	return retString;
}

std::string ChaChaPanel::MyMultiByteToWideChar(BYTE *pbDest, int nLen)
{
	char* pWCHAR = NULL;

	//����pChar��ָ��Ķ��ֽ��ַ����൱�ڶ��ٸ����ֽ�
	DWORD num = MultiByteToWideChar(CP_ACP, 0, (LPCCH)pbDest, nLen, NULL, 0);

	num = num*sizeof(wchar_t);
	pWCHAR = (char*)malloc(num);

	if (pWCHAR == NULL)
	{
		free(pWCHAR);
	}

	memset(pWCHAR, 0, num);

	//���ֽ�ת��Ϊ���ֽ�
	MultiByteToWideChar(CP_ACP, 0, (LPCCH)pbDest, nLen, (LPWSTR)pWCHAR, num);
	std::string retString;
	retString.append(pWCHAR, num);
	free(pWCHAR);
	return retString;

}