#pragma once


// Password 對話方塊

class Password : public CDialog
{
	DECLARE_DYNAMIC(Password)

public:
	Password(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~Password();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

protected:
	CEdit m_edtPassword;

public:
	BOOL* boPasswordState;

	afx_msg void OnBnClickedOk();
};
