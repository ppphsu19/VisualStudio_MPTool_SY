#pragma once


// Password ��ܤ��

class Password : public CDialog
{
	DECLARE_DYNAMIC(Password)

public:
	Password(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~Password();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()

protected:
	CEdit m_edtPassword;

public:
	BOOL* boPasswordState;

	afx_msg void OnBnClickedOk();
};
