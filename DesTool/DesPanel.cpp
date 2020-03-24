// DesPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DesTool.h"
#include "DesPanel.h"
#include "afxdialogex.h"
#include"DesCrypt.h"
using namespace CipherDes;


// CDesPanel �Ի���

IMPLEMENT_DYNAMIC(CDesPanel, CDialogEx)

CDesPanel::CDesPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDesPanel::IDD, pParent)
	, strSSLeay_version(_T(""))
{

}

CDesPanel::~CDesPanel()
{
}

void CDesPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, EncryptMode);
	DDX_Control(pDX, IDC_COMBO2, mPadding);
	DDX_Control(pDX, IDC_EDIT1, mKey);
	DDX_Control(pDX, IDC_EDIT2, mIv);
	DDX_Control(pDX, IDC_CHECK1, mCheckHex);
	DDX_Text(pDX, IDC_EDIT3, strSSLeay_version);
	DDX_Control(pDX, IDC_CHECK2, m3DesCheck);
}


BEGIN_MESSAGE_MAP(CDesPanel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDesPanel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDesPanel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &CDesPanel::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CDesPanel ��Ϣ�������


BOOL CDesPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//����openssl�汾
	std::string str = CDesCrypt::GetSSLeay_version();
	std::wstring strW(str.length(), L' ');
	std::copy(str.begin(), str.end(), strW.begin());
	strSSLeay_version = "";
	strSSLeay_version.Append(strW.c_str(), strW.size());

	EncryptMode.AddString(_T("ECB"));
	EncryptMode.AddString(_T("CBC"));
	EncryptMode.AddString(_T("CTR"));
	EncryptMode.AddString(_T("OFB"));
	EncryptMode.AddString(_T("CFB"));
	EncryptMode.SetCurSel(0);

	mPadding.AddString(_T("zero"));
	mPadding.AddString(_T("pkcs5"));
	mPadding.AddString(_T("pkcs7"));
	mPadding.AddString(_T("iso10126"));
	mPadding.AddString(_T("ansix923"));
	mPadding.SetCurSel(0);

	//����HexControl
	pHexControl1.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl1.SetPosition(10, 120, 630, 350);
	BYTE buffer2[] = "12345678";
	pHexControl1.SetData( buffer2, sizeof(buffer2)-1);

	mCheckHex.SetCheck(FALSE);
	m3DesCheck.SetCheck(FALSE);
	mKey.SetWindowTextW(_T("12345678"));
	mIv.SetWindowTextW(_T("12345678"));

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//����
void CDesPanel::OnBnClickedButton1()
{
	//ȡ��3des��ʶ
	bool is3Des = m3DesCheck.GetCheck();
	
	//ȡ����Կ
	CString strKey = _T("");
	mKey.GetWindowTextW(strKey);
	std::string mb_Key = MyWideCharToMultiByte((BYTE*)strKey.GetBuffer(0), strKey.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16������Կ����
		mb_Key=StrToHex((BYTE*)mb_Key.c_str(), mb_Key.length());
	}
	//ȡ��IV
	CString strIV = _T("");
	mIv.GetWindowTextW(strIV);
	std::string mb_Iv = MyWideCharToMultiByte((BYTE*)strIV.GetBuffer(0), strIV.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16����IV����
		mb_Iv = StrToHex((BYTE*)mb_Iv.c_str(), mb_Iv.length());
	}

	CDesCrypt mCDesCrypt;
	//�����Ƿ�3des
	mCDesCrypt.Set3Des(is3Des);
	//���ü���ģʽ
	CString strEncryptMode = _T("");
	EncryptMode.GetWindowTextW(strEncryptMode);
	if (strEncryptMode == "ECB")
	{
		mCDesCrypt.SetMode(MODE_ECB);
	}
	else if (strEncryptMode == "CBC")
	{
		mCDesCrypt.SetMode(MODE_CBC);
	}
	else if (strEncryptMode == "CTR")
	{
		mCDesCrypt.SetMode(MODE_CTR);
	}
	else if (strEncryptMode == "OFB")
	{
		mCDesCrypt.SetMode(MODE_OFB);
	}
	else if (strEncryptMode == "CFB")
	{
		mCDesCrypt.SetMode(MODE_CFB);
	}
	//������Կ
	mCDesCrypt.SetKey((unsigned char*)mb_Key.c_str(), mb_Key.length());
	//����IV
	mCDesCrypt.SetIv((unsigned char*)mb_Iv.c_str(), mb_Iv.length());
	
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

	//Դ�������
	CString strPaddingType = _T("");
	mPadding.GetLBText(mPadding.GetCurSel(), strPaddingType);
	if (strPaddingType == "zero")
	{
		mCDesCrypt.GetPadding_zero(&srcBuffer, &srclen);
		pHexControl1.SetData( srcBuffer, srclen - mCDesCrypt.GetPaddingLen());
	}
	else if (strPaddingType == "pkcs5")
	{
		mCDesCrypt.GetPadding_pkcs5(&srcBuffer, &srclen);
		pHexControl1.SetData( srcBuffer, srclen - mCDesCrypt.GetPaddingLen());
	}
	else if (strPaddingType == "pkcs7")
	{
		mCDesCrypt.GetPadding_pkcs7(&srcBuffer, &srclen);
		pHexControl1.SetData( srcBuffer, srclen - mCDesCrypt.GetPaddingLen());
	}
	else if (strPaddingType == "iso10126")
	{
		mCDesCrypt.GetPadding_iso10126(&srcBuffer, &srclen);
		pHexControl1.SetData( srcBuffer, srclen - mCDesCrypt.GetPaddingLen());
	}
	else if (strPaddingType=="ansix923")
	{
		mCDesCrypt.GetPadding_ansix923(&srcBuffer, &srclen);
		pHexControl1.SetData( srcBuffer, srclen - mCDesCrypt.GetPaddingLen());
	}

	//��ʼ����
	unsigned int dstlen = srclen;
	BYTE *dstBuffer = (BYTE*)malloc(dstlen);
	memset(dstBuffer, 0, dstlen);
	mCDesCrypt.Encrypt(srcBuffer, dstlen, (unsigned char*)dstBuffer);
	pHexControl1.SetData( dstBuffer, dstlen);

	free(srcBuffer);
	free(dstBuffer);
}

//����
void CDesPanel::OnBnClickedButton2()
{
	//ȡ��3des��ʶ
	bool is3Des = m3DesCheck.GetCheck();
	//ȡ����Կ
	CString strKey = _T("");
	mKey.GetWindowTextW(strKey);
	std::string mb_Key = MyWideCharToMultiByte((BYTE*)strKey.GetBuffer(0), strKey.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16������Կ����
		mb_Key = StrToHex((BYTE*)mb_Key.c_str(), mb_Key.length());
	}
	//ȡ��IV
	CString strIV = _T("");
	mIv.GetWindowTextW(strIV);
	std::string mb_Iv = MyWideCharToMultiByte((BYTE*)strIV.GetBuffer(0), strIV.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16����IV����
		mb_Iv = StrToHex((BYTE*)mb_Iv.c_str(), mb_Iv.length());
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

	CDesCrypt mCDesCrypt;
	 //�����Ƿ�3DES
	mCDesCrypt.Set3Des(is3Des);
	//���ý���ģʽ
	CString strEncryptMode = _T("");
	EncryptMode.GetWindowTextW(strEncryptMode);
	if (strEncryptMode == "ECB")
	{
		mCDesCrypt.SetMode(MODE_ECB);
	}
	else if (strEncryptMode == "CBC")
	{
		mCDesCrypt.SetMode(MODE_CBC);
	}
	else if (strEncryptMode == "CTR")
	{
		mCDesCrypt.SetMode(MODE_CTR);
	}
	else if (strEncryptMode == "OFB")
	{
		mCDesCrypt.SetMode(MODE_OFB);
		mCDesCrypt.SetIv((unsigned char*)mb_Iv.c_str(), mb_Iv.length());
	}
	else if (strEncryptMode == "CFB")
	{
		mCDesCrypt.SetMode(MODE_CFB);
	}
	//������Կ
	mCDesCrypt.SetKey((unsigned char*)mb_Key.c_str(), mb_Key.length());
	//����IV
	mCDesCrypt.SetIv((unsigned char*)mb_Iv.c_str(), mb_Iv.length());

	//��ʼ����
	BYTE *dstBuffer = (BYTE*)malloc(srclen);
	memset(dstBuffer, 0, srclen);
	mCDesCrypt.Decrypt(srcBuffer, srclen, (unsigned char*)dstBuffer);
	pHexControl1.SetData( dstBuffer, srclen);

	free(srcBuffer);
	free(dstBuffer);
}

//���Ʊ仯
void CDesPanel::OnBnClickedCheck1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (mCheckHex.GetCheck() == TRUE)
	{
		CString strText;
		mKey.GetWindowTextW(strText);
		if (strText.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)strText.GetBuffer(0), strText.GetLength());
			std::string str = HexToStr((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			strText = "";
			strText.Append((wchar_t*)strW.c_str(), strW.length()/2);
			mKey.SetWindowTextW(strText);
		}
		mIv.GetWindowTextW(strText);
		if (strText.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)strText.GetBuffer(0), strText.GetLength());
			std::string str = HexToStr((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			strText = "";
			strText.Append((wchar_t*)strW.c_str(), strW.length() / 2);
			mIv.SetWindowTextW(strText);
		}
	}
	else
	{
		CString strText;
		mKey.GetWindowTextW(strText);
		if (strText.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)strText.GetBuffer(0), strText.GetLength());
			std::string str = StrToHex((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			strText = "";
			strText.Append((wchar_t*)strW.c_str(), strW.length() / 2);
			mKey.SetWindowTextW(strText);
		}
		mIv.GetWindowTextW(strText);
		if (strText.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)strText.GetBuffer(0), strText.GetLength());
			std::string str = StrToHex((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			strText = "";
			strText.Append((wchar_t*)strW.c_str(), strW.length() / 2);
			mIv.SetWindowTextW(strText);
		}
	}
}


std::string CDesPanel::HexToStr(BYTE *pbSrc, int nLen)
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

std::string CDesPanel::StrToHex(BYTE *pbSrc, int nLen)
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

std::string CDesPanel::MyWideCharToMultiByte(BYTE *pbDest, int nLen)
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

std::string CDesPanel::MyMultiByteToWideChar(BYTE *pbDest, int nLen)
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