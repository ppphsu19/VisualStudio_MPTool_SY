#pragma once


// PortSetting ��ܤ��


class PortSetting : public CDialog
{
	DECLARE_DYNAMIC(PortSetting)

public:
	PortSetting(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~PortSetting();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_PORT_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()

protected:
	CEdit m_edtDisk[8];

	virtual BOOL OnInitDialog();

public:
	CString* strPortSN[MP_MAX_DISKS];

	afx_msg void OnBnClickedOk();
};
