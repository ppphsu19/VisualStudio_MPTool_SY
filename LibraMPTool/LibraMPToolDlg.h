// LibraMPToolDlg.h : 標頭檔
//

#pragma once
#include <atlimage.h>
#include "afxwin.h"
#include "DetectDisk.h"
#include "PortSetting.h"
#include "MPInfo.h"
#include "Parameter.h"
#include "Create.h"
#include <vector>

#define AP_NAME _T("Libra_MPTool_Beta15")


// CLibraMPToolDlg 對話方塊
class CLibraMPToolDlg : public CDialog
{
// 建構
public:
	CLibraMPToolDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_LIBRAMPTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	CButton m_btnStart;
	CButton m_btnExit;
	CButton m_btnRescan;
	CComboBox m_cmbConfigList;
	CButton m_chkRDT;
	CButton m_btnCreate;
	CButton m_chkDisk[MP_MAX_DISKS];
	CLabel m_lblSN[MP_MAX_DISKS];
	CLabel m_lblFWMode[MP_MAX_DISKS];
	CStatic m_stcDisk[MP_MAX_DISKS];
	CTabCtrl m_tabContent;
	CLabel m_lblTestResult;

	HBITMAP bmpDiskScan;
	HBITMAP bmpDiskNull;
	HBITMAP bmpDiskNormal;
	HBITMAP bmpDiskInfo;
	HBITMAP bmpDiskRunning;
	HBITMAP bmpDiskSuccess;
	HBITMAP bmpDiskFail;

	BOOL boDiskExist[MP_MAX_DISKS];
	CString strRootDirectoryPath;

	CDetectDisk pDetectDisk;
	MPInfo pMPInfo;
	Parameter pParam;
	int iPort2Disk[MP_MAX_DISKS];
	CString strMPSN[MP_MAX_DISKS];
	SYSTEM_PARAM srtSystemParam;
	FLASH_MAPPING srtFlashMapping;
	STRUCT_PARAM srtStructParam;
	SERIAL_NUMBER_PARAM srtSerialNumberParam;
	QUICK_TEST_PARAM srtQuickTestParam;
	OTHER_SETTING srtOtherSetting;
	SN_INFO srtSNInfo;
	int iProductionConfigCount;
	int iDiskCapacityGB;
	CString strFlashVendor;
	CString strBoardType;

	std::vector<const DISKINFO*> _uiSlots;

	void SetEnableWindow(BOOL boEnable);
	void GetRootDirectoryPath();
	void SetInit();
	void SetSNInit();
	void DiskSetInit();
	void GetDiskImages();
	void CreateTabContent();
	void RescanFunc();
	void ShowDiskInfo();
	int FindUISlotByUsbBridgeSN(CString sn) const;
	int FindNotUsedUISlot() const;
	void SetSingleDiskInfo(int UIIndex, const DISKINFO* pDiskInfo);
	void DoStaticDiskFunc(int iSelectIndex);
	void SetMPInfoDisplay();
	void SetParameterDisplay();
	void LinkMPInfoObjectAndParam();
	void LinkParameterObjectAndParam();
	BOOL GetConfigParam();
	void GetCurrentMaxSN();
	BOOL GetFlashMappingParam();
	void GetCapacityLBN();
	void CheckStructConfigVersion();
	void NewFileResetInfo();

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonRescan();
	afx_msg void OnStnClickedStaticSN();
	afx_msg void OnStnClickedStaticDisk1();
	afx_msg void OnStnClickedStaticDisk2();
	afx_msg void OnStnClickedStaticDisk3();
	afx_msg void OnStnClickedStaticDisk4();
	afx_msg void OnStnClickedStaticDisk5();
	afx_msg void OnStnClickedStaticDisk6();
	afx_msg void OnStnClickedStaticDisk7();
	afx_msg void OnStnClickedStaticDisk8();
	afx_msg void OnTcnSelchangeTabContent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboConfigList();
	afx_msg void OnBnClickedButtonCreate();
	afx_msg void OnBnClickedCheckRdt();
};