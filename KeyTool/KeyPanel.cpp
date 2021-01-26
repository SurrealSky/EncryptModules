// KeyPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KeyTool.h"
#include "KeyPanel.h"
#include "afxdialogex.h"
#include"KeyExpand.h"


using namespace CipherKey;

// KeyPanel �Ի���

IMPLEMENT_DYNAMIC(KeyPanel, CDialogEx)

KeyPanel::KeyPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(KeyPanel::IDD, pParent)
	, mKeyText(_T(""))
	, mOpensslVer(_T(""))
{

}

KeyPanel::~KeyPanel()
{
}

void KeyPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mKeyType);
	DDX_Text(pDX, IDC_EDIT1, mKeyText);
	DDX_Text(pDX, IDC_EDIT3, mOpensslVer);
	DDX_Control(pDX, IDC_CHECK1, mCheckHex);
}


BEGIN_MESSAGE_MAP(KeyPanel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &KeyPanel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &KeyPanel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &KeyPanel::OnBnClickedCheck1)
END_MESSAGE_MAP()


// KeyPanel ��Ϣ�������

BOOL KeyPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//����openssl�汾
	std::string str = CKeyExpand::GetSSLeay_version();
	std::wstring strW(str.length(), L' ');
	std::copy(str.begin(), str.end(), strW.begin());
	mOpensslVer = "";
	mOpensslVer.Append(strW.c_str(), strW.size());

	mKeyType.AddString(_T("AES-128-ENC"));
	mKeyType.AddString(_T("AES-128-DEC"));
	mKeyType.AddString(_T("AES-192-ENC"));
	mKeyType.AddString(_T("AES-192-DEC"));
	mKeyType.AddString(_T("AES-256-ENC"));
	mKeyType.AddString(_T("AES-256-DEC"));
	mKeyType.AddString(_T("DES-ENC"));
	mKeyType.AddString(_T("DES-DEC"));
	mKeyType.SetCurSel(0);

	mKeyText="5D2BEC0744086E2BDEDA0B04CF134E87";
	mCheckHex.SetCheck(TRUE);

	pHexControl1.CreateHexView(AfxGetInstanceHandle(), m_hWnd);
	pHexControl1.SetPosition(10, 100, 630, 350);
	pHexControl1.SetEditMode(EditMode::INSERT);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//��ɢ
void KeyPanel::OnBnClickedButton1()
{
	UpdateData(TRUE);
	std::string mb_Key = MyWideCharToMultiByte((BYTE*)mKeyText.GetBuffer(0), mKeyText.GetLength());
	if (mCheckHex.GetCheck() == TRUE)
	{
		//16������Կ����
		mb_Key = StrToHex((BYTE*)mb_Key.c_str(), mb_Key.length());
	}

	CString strKeyType = _T("");
	mKeyType.GetLBText(mKeyType.GetCurSel(), strKeyType);
	if (strKeyType == "AES-128-ENC")
	{
		unsigned int len = mKeyExpand.GetAesKeyLen(128);
		unsigned char *buffer = new unsigned char[len];
		mKeyExpand.GetKey_AES((unsigned char*)mb_Key.c_str(), mb_Key.size(),128, true,buffer, &len);
		pHexControl1.SetData( buffer, len);
		delete[]buffer;
	}
	else if (strKeyType == "AES-128-DEC")
	{
		unsigned int len = mKeyExpand.GetAesKeyLen(128);
		unsigned char *buffer = new unsigned char[len];
		mKeyExpand.GetKey_AES((unsigned char*)mb_Key.c_str(), mb_Key.size(), 128,false,buffer, &len);
		pHexControl1.SetData( buffer, len);
		delete[]buffer;
	}
	else if (strKeyType == "AES-192-ENC")
	{
		unsigned int len = mKeyExpand.GetAesKeyLen(192);
		unsigned char *buffer = new unsigned char[len];
		mKeyExpand.GetKey_AES((unsigned char*)mb_Key.c_str(), mb_Key.size(), 192, true, buffer, &len);
		pHexControl1.SetData( buffer, len);
		delete[]buffer;
	}
	else if (strKeyType == "AES-192-DEC")
	{
		unsigned int len = mKeyExpand.GetAesKeyLen(192);
		unsigned char *buffer = new unsigned char[len];
		mKeyExpand.GetKey_AES((unsigned char*)mb_Key.c_str(), mb_Key.size(), 192, false, buffer, &len);
		pHexControl1.SetData( buffer, len);
		delete[]buffer;
	}
	else if (strKeyType == "AES-256-ENC")
	{
		unsigned int len = mKeyExpand.GetAesKeyLen(256);
		unsigned char *buffer = new unsigned char[len];
		mKeyExpand.GetKey_AES((unsigned char*)mb_Key.c_str(), mb_Key.size(), 256, true, buffer, &len);
		pHexControl1.SetData( buffer, len);
		delete[]buffer;
	}
	else if (strKeyType == "AES-256-DEC")
	{
		unsigned int len = mKeyExpand.GetAesKeyLen(256);
		unsigned char *buffer = new unsigned char[len];
		mKeyExpand.GetKey_AES((unsigned char*)mb_Key.c_str(), mb_Key.size(), 256, false, buffer, &len);
		pHexControl1.SetData( buffer, len);
		delete[]buffer;
	}
	else if (strKeyType == "DES-ENC")
	{
		unsigned int len = mKeyExpand.GetDesKeyLen();
		unsigned char *buffer = new unsigned char[len];
		mKeyExpand.GetKey_DES((unsigned char*)mb_Key.c_str(), mb_Key.size(),true, buffer, &len);
		pHexControl1.SetData( buffer, len);
		delete[]buffer;
	}
	else if (strKeyType == "DES-DEC")
	{
		unsigned int len = mKeyExpand.GetDesKeyLen();
		unsigned char *buffer = new unsigned char[len];
		mKeyExpand.GetKey_DES((unsigned char*)mb_Key.c_str(), mb_Key.size(), false, buffer, &len);
		pHexControl1.SetData( buffer, len);
		delete[]buffer;
	}
}

//��ԭ
void KeyPanel::OnBnClickedButton2()
{
	CString strKeyType = _T("");
	mKeyType.GetLBText(mKeyType.GetCurSel(), strKeyType);
	if (strKeyType == "AES-128-ENC")
	{
		unsigned int len = pHexControl1.GetDataLen();
		unsigned char *buffer = new unsigned char[len];
		pHexControl1.GetData(buffer, len);
		unsigned char userkey[0x10] = { 0 };
		mKeyExpand.GetAesKeyFromExpand128(buffer, &len, 128,true,userkey );
		delete[]buffer;
		pHexControl1.SetData( userkey, sizeof(userkey));
	}
	else if (strKeyType == "AES-128-DEC")
	{
		unsigned int len = pHexControl1.GetDataLen();
		unsigned char *buffer = new unsigned char[len];
		pHexControl1.GetData(buffer, len);
		unsigned char userkey[0x10] = { 0 };
		mKeyExpand.GetAesKeyFromExpand128(buffer, &len, 128, false, userkey);
		delete[]buffer;
		pHexControl1.SetData( userkey, sizeof(userkey));
	}
	else if (strKeyType == "AES-192-ENC")
	{
		unsigned int len = pHexControl1.GetDataLen();
		unsigned char *buffer = new unsigned char[len];
		pHexControl1.GetData(buffer, len);
		unsigned char userkey[0x18] = { 0 };
		mKeyExpand.GetAesKeyFromExpand192(buffer, &len, 192,true, userkey);
		delete[]buffer;
		pHexControl1.SetData( userkey, sizeof(userkey));
	}
	else if (strKeyType == "AES-192-DEC")
	{
		unsigned int len = pHexControl1.GetDataLen();
		unsigned char *buffer = new unsigned char[len];
		pHexControl1.GetData(buffer, len);
		unsigned char userkey[0x18] = { 0 };
		mKeyExpand.GetAesKeyFromExpand192(buffer, &len, 192, false, userkey);
		delete[]buffer;
		pHexControl1.SetData( userkey, sizeof(userkey));
	}
	else if (strKeyType == "AES-256-ENC")
	{
		unsigned int len = pHexControl1.GetDataLen();
		unsigned char *buffer = new unsigned char[len];
		pHexControl1.GetData(buffer, len);
		unsigned char userkey[0x20] = { 0 };
		mKeyExpand.GetAesKeyFromExpand256(buffer, &len, 256, true, userkey);
		delete[]buffer;
		pHexControl1.SetData( userkey, sizeof(userkey));
	}
	else if (strKeyType == "AES-256-DEC")
	{
	}
	else if (strKeyType == "DES-ENC")
	{
	}
	else if (strKeyType == "DES-DEC")
	{
	}

}


//���Ʊ仯
void KeyPanel::OnBnClickedCheck1()
{
	UpdateData(TRUE);
	if (mCheckHex.GetCheck() == TRUE)
	{
		if (mKeyText.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)mKeyText.GetBuffer(0), mKeyText.GetLength());
			std::string str = HexToStr((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			mKeyText = "";
			mKeyText.Append((wchar_t*)strW.c_str(), strW.length() / 2);
		}
	}
	else
	{
		if (mKeyText.GetLength() != 0)
		{
			std::string strM = MyWideCharToMultiByte((BYTE*)mKeyText.GetBuffer(0), mKeyText.GetLength());
			std::string str = StrToHex((BYTE*)strM.c_str(), strM.length());
			std::string strW = MyMultiByteToWideChar((BYTE*)str.c_str(), str.length());
			mKeyText = "";
			mKeyText.Append((wchar_t*)strW.c_str(), strW.length() / 2);
		}
	}
	UpdateData(FALSE);
}


std::string KeyPanel::HexToStr(BYTE *pbSrc, int nLen)
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

std::string KeyPanel::StrToHex(BYTE *pbSrc, int nLen)
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

std::string KeyPanel::MyWideCharToMultiByte(BYTE *pbDest, int nLen)
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

std::string KeyPanel::MyMultiByteToWideChar(BYTE *pbDest, int nLen)
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