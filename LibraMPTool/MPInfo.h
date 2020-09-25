#pragma once


// MPInfo 對話方塊
#include <sys/stat.h>
#include "ShareFunctions.h"
#include "MPCmd.h"
#include "MPCmdRDT.h"

class MPInfo : public CDialog
{
	DECLARE_DYNAMIC(MPInfo)

public:
	MPInfo(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~MPInfo();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_MP_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

protected:
	CLabel m_lblPhysicalAddress[MP_MAX_DISKS];

	void DoStaticPortFunc(int iSelectIndex);

	virtual BOOL OnInitDialog();

	static DWORD Thread_MPProcess(LPVOID pParam);

public:
	CButton m_btnStart;
	CButton* m_btnExit;
	CButton* m_btnRescan;
	CButton* m_btnEdit;
	CComboBox* m_cmbConfigList;
	CButton* m_btnCreate;
	CButton* m_chkRDT;
	CLabel* m_lblTestResult;
	CLabel* m_lblSN[MP_MAX_DISKS];
	CButton* m_chkDisk[MP_MAX_DISKS];
	CStatic* m_stcDisk[MP_MAX_DISKS];
	CLabel* m_lblFWMode[MP_MAX_DISKS];
	CString* strRootDirectoryPath;
	CStatic m_stcMPInfoSN[MP_MAX_DISKS];
	CLabel m_lblInfo[MP_MAX_DISKS];
	CLabel m_lblTime[MP_MAX_DISKS];
	CTextProgressCtrl m_pgsPort[MP_MAX_DISKS];

	BOOL boDiskExist[MP_MAX_DISKS];
	int* iPort2Disk[MP_MAX_DISKS];
	int iDiskPhysicalIndex[MP_MAX_DISKS];
	BYTE bDiskBusType[MP_MAX_DISKS];
	CString* strMPSN[MP_MAX_DISKS];
	BOOL boResetState[MP_MAX_DISKS];
	CString strDiskSN[MP_MAX_DISKS];
	DWORD dwTimer[MP_MAX_DISKS];
	BOOL boPartitionMode[MP_MAX_DISKS];//0: physical, 1: logical
	SYSTEM_PARAM* srtSystemParam;
	FLASH_MAPPING* srtFlashMapping;
	STRUCT_PARAM* srtStructParam;
	SERIAL_NUMBER_PARAM* srtSerialNumberParam;
	QUICK_TEST_PARAM* srtQuickTestParam;
	OTHER_SETTING* srtOtherSetting;
	BOARD_INFO srtBoardInfo[MP_MAX_DISKS];
	SN_INFO* srtSNInfo;

	void ResetSN(int iDiskIndex);
	void RefreshDisplay();
	void SetEnableWindow(BOOL boEnable);
	void SetModifyStyle(BOOL boEnable);
	void CleanInfoDisplay();
	BOOL CheckBoardInfoFunc();
	void ConfirmCapacityLBN(int iUserChannel, int iUserBank);
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedStaticPort1();
	afx_msg void OnStnClickedStaticPort2();
	afx_msg void OnStnClickedStaticPort3();
	afx_msg void OnStnClickedStaticPort4();
	afx_msg void OnStnClickedStaticPort5();
	afx_msg void OnStnClickedStaticPort6();
	afx_msg void OnStnClickedStaticPort7();
	afx_msg void OnStnClickedStaticPort8();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};