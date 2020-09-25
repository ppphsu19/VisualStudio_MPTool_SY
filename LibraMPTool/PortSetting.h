#pragma once


// PortSetting 對話方塊


class PortSetting : public CDialog
{
	DECLARE_DYNAMIC(PortSetting)

public:
	PortSetting(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~PortSetting();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_PORT_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

protected:
	CEdit m_edtDisk[8];

	virtual BOOL OnInitDialog();

public:
	CString* strPortSN[MP_MAX_DISKS];

	afx_msg void OnBnClickedOk();
};
