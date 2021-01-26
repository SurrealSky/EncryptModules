// AesPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AesTool.h"
#include "AesPanel.h"
#include "afxdialogex.h"
#include "AesCrypt.h"

using namespace CipherAes;


// CAesPanel �Ի���

IMPLEMENT_DYNAMIC(CAesPanel, CDialogEx)

CAesPanel::CAesPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAesPanel::IDD, pParent)
	, strSSLeay_version(_T(""))
{

}

CAesPanel::~CAesPanel()
{
}

void CAesPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, EncryptMode);
	DDX_Control(pDX, IDC_COMBO2, mPadding);
	DDX_Control(pDX, IDC_EDIT1, mKey);
	DDX_Control(pDX, IDC_EDIT2, mIv);
	DDX_Control(pDX, IDC_CHECK1, mCheckHex);
	DDX_Control(pDX, IDC_COMBO3, mBlock);
	DDX_Text(pDX, IDC_EDIT3, strSSLeay_version);
}


BEGIN_MESSAGE_MAP(CAesPanel, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CAesPanel::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAesPanel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAesPanel::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAesPanel ��Ϣ�������


BOOL CAesPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//����openssl�汾
	std::string str = CAesCrypt::GetSSLeay_version();
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

	mBlock.AddString(_T("128λ"));
	mBlock.AddString(_T("192λ"));
	mBlock.AddString(_T("256λ"));
	mBlock.SetCurSel(0);

	mPadding.AddString(_T("zero"));
	mPadding.AddString(_T("pkcs5"));
	mPadding.AddString(_T("pkcs7"));
	mPadding.AddString(_T("iso10126"));
	mPadding.AddString(_T("ansix923"));
	mPadding.SetCurSel(0);

	//HexControl
	pHexControl1.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl1.SetPosition(10, 120, 630, 350);
	BYTE buffer2[] = {
		0x3b, 0xca, 0x5a, 0x8b, 0xc1,
		0x17, 0xa8, 0xba, 0x12, 0x04, 0x01, 0x4a, 0xb1,
		0x20, 0x1a, 0x7f, 0xe5, 0xa8, 0x8e, 0x93, 0x54,
		0x46, 0x9a, 0xbe, 0xa9, 0xf1, 0x49, 0xc5, 0x5a,
		0x41, 0xce, 0xbd, 0xb1, 0xd9, 0xc0, 0x29, 0x35,
		0xf8, 0x7b, 0xf7, 0x87, 0x44, 0xca, 0xdb, 0x8d,
		0xae, 0x9a, 0xf0, 0x2c, 0x6b, 0x36, 0x4a, 0x6a,
		0xdd, 0xed, 0xac, 0xfc, 0x74, 0x21, 0x1e, 0x55,
		0x20, 0xc1, 0xaa, 0x79, 0x0a, 0x7e, 0xb2, 0xde,
		0x51, 0xf2, 0xf5, 0x80, 0x64, 0x65, 0x29, 0x65,
		0x7b, 0xfd, 0x82, 0x5f, 0xa9, 0xab, 0x2b, 0x86,
		0xc7, 0xe5, 0x71, 0xdc, 0xcd, 0x20, 0xc3, 0xd2,
		0xb6, 0x08, 0x45, 0x14, 0x0c, 0xce, 0x6f, 0x6e,
		0x89, 0x2c, 0xe9, 0x3c, 0x71, 0xff, 0x70, 0x52,
		0xe3, 0x8e, 0x8f, 0x63, 0xeb, 0xa0, 0x17, 0x41,
		0x7a, 0xcd, 0x5c, 0x92, 0x1f, 0x2a, 0x68, 0x7a,
		0xee, 0x22, 0xcc, 0x9a, 0x6f, 0xe4, 0x18, 0x82,
		0xee, 0x52, 0x21, 0x20, 0x1c, 0xcc, 0xd1, 0x93,
		0xe1, 0x9a, 0x40
	};
	pHexControl1.SetData( buffer2, sizeof(buffer2));
	pHexControl1.SetEditMode(EditMode::INSERT);

	mCheckHex.SetCheck(TRUE);
	mKey.SetWindowTextW(_T("5D2BEC0744086E2BDEDA0B04CF134E87"));
	mIv.SetWindowTextW(_T("11206B8EEEC3273BFA717A580B135AE5"));

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


std::string CAesPanel::HexToStr(BYTE *pbSrc, int nLen)
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

std::string CAesPanel::StrToHex(BYTE *pbSrc, int nLen)
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

std::string CAesPanel::MyWideCharToMultiByte(BYTE *pbDest, int nLen)
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

std::string CAesPanel::MyMultiByteToWideChar(BYTE *pbDest, int nLen)
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

//���Ʊ仯
void CAesPanel::OnBnClickedCheck1()
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
			strText.Append((wchar_t*)strW.c_str(), strW.length() / 2);
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

//����
void CAesPanel::OnBnClickedButton1()
{
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
	pHexControl1.GetData( srcBuffer, srclen);

	CAesCrypt mCAesCrypt;
	//���
	CString strPaddingType = _T("");
	mPadding.GetLBText(mPadding.GetCurSel(), strPaddingType);
	if (strPaddingType == "zero")
	{
		mCAesCrypt.GetPadding_zero(&srcBuffer, &srclen);
		pHexControl1.SetData(srcBuffer, srclen - mCAesCrypt.GetPaddingLen());
	}
	else if (strPaddingType == "pkcs5")
	{
		mCAesCrypt.GetPadding_pkcs5(&srcBuffer, &srclen);
		pHexControl1.SetData(srcBuffer, srclen - mCAesCrypt.GetPaddingLen());
	}
	else if (strPaddingType == "pkcs7")
	{
		mCAesCrypt.GetPadding_pkcs7(&srcBuffer, &srclen);
		pHexControl1.SetData(srcBuffer, srclen - mCAesCrypt.GetPaddingLen());
	}
	else if (strPaddingType == "iso10126")
	{
		mCAesCrypt.GetPadding_iso10126(&srcBuffer, &srclen);
		pHexControl1.SetData(srcBuffer, srclen - mCAesCrypt.GetPaddingLen());
	}
	else if (strPaddingType == "ansix923")
	{
		mCAesCrypt.GetPadding_ansix923(&srcBuffer, &srclen);
		pHexControl1.SetData(srcBuffer, srclen - mCAesCrypt.GetPaddingLen());
	}

	//��ʼ����
	CString strBlock = _T("");
	mBlock.GetLBText(mBlock.GetCurSel(), strBlock);
	KeyMode km;
	if (strBlock == "128λ")
	{
		km = MODE_128;
	}
	else if (strBlock == "192λ")
	{
		km = MODE_192;
	}
	else if (strBlock == "256λ")
	{
		km = MODE_256;
	}

	CString strEncryptMode = _T("");
	EncryptMode.GetWindowTextW(strEncryptMode);
	CipherMode cm;
	if (strEncryptMode == "ECB")
	{
		cm = MODE_ECB;
	}
	else if (strEncryptMode == "CBC")
	{
		cm = MODE_CBC;
	}
	else if (strEncryptMode == "CTR")
	{
		cm = MODE_CTR;
	}
	else if (strEncryptMode == "OFB")
	{
		cm = MODE_OFB;
	}
	else if (strEncryptMode == "CFB")
	{
		cm = MODE_CFB;
	}

	mCAesCrypt.initMode(cm, km, (unsigned char*)mb_Key.c_str(), mb_Key.length(), (unsigned char*)mb_Iv.c_str(), mb_Iv.length());

	unsigned int dstlen = srclen;
	BYTE *dstBuffer = (BYTE*)malloc(dstlen);
	memset(dstBuffer, 0, dstlen);
	mCAesCrypt.Encrypt(srcBuffer, dstlen, (unsigned char*)dstBuffer);
	pHexControl1.SetData(dstBuffer, dstlen);

	free(srcBuffer);
	free(dstBuffer);
}

//����
void CAesPanel::OnBnClickedButton2()
{
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

	//��ʼ����
	CAesCrypt mCAesCrypt;

	CString strBlock = _T("");
	mBlock.GetLBText(mBlock.GetCurSel(), strBlock);
	KeyMode km;
	if (strBlock == "128λ")
	{
		km = MODE_128;
	}
	else if (strBlock == "192λ")
	{
		km = MODE_192;
	}
	else if (strBlock == "256λ")
	{
		km = MODE_256;
	}

	CString strEncryptMode = _T("");
	EncryptMode.GetWindowTextW(strEncryptMode);
	CipherMode cm;
	if (strEncryptMode == "ECB")
	{
		cm = MODE_ECB;
	}
	else if (strEncryptMode == "CBC")
	{
		cm = MODE_CBC;
	}
	else if (strEncryptMode == "CTR")
	{
		cm = MODE_CTR;
	}
	else if (strEncryptMode == "OFB")
	{
		cm = MODE_OFB;
	}
	else if (strEncryptMode == "CFB")
	{
		cm = MODE_CFB;
	}
	mCAesCrypt.initMode(cm, km, (unsigned char*)mb_Key.c_str(), mb_Key.length(), (unsigned char*)mb_Iv.c_str(), mb_Iv.length());

	BYTE *dstBuffer = (BYTE*)malloc(srclen);
	memset(dstBuffer, 0, srclen);
	mCAesCrypt.Decrypt(srcBuffer, srclen, (unsigned char*)dstBuffer);
	pHexControl1.SetData( dstBuffer, srclen);

	free(srcBuffer);
	free(dstBuffer);
}
