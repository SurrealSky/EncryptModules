#pragma once


// CRegSAMPanel 对话框

class CRegSAMPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CRegSAMPanel)

public:
	CRegSAMPanel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegSAMPanel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
