#pragma once
#include "ShareFunctions.h"
#include "Password.h"


// Parameter 對話方塊

class Parameter : public CDialog
{
	DECLARE_DYNAMIC(Parameter)

public:
	Parameter(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~Parameter();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_PARAMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

protected:
	CButton m_btnSave;
	CButton m_btnSaveAs;

	CListCtrl m_lstMPParam;
	CEdit m_edtMPParam;
	CEdit m_edtBeginSN;
	CEdit m_edtEndSN;
	CEdit m_edtSNMask;
	CEdit m_edtNVMeMN;
	CEdit m_edtSysFWVersion;
	CEdit m_edtNVMeVID;
	CEdit m_edtNVMeDID;
	CEdit m_edtSysEUI64;
	CComboBox m_cmbNVMeCapacity;
	CEdit m_edtNVMeCapacityManual;

	CShareFunctions pShareFunctions;
	int iPreItem;
	int iPreSubItem;
	BOOL boHaveEditCreate;
	BYTE bCapacityMethod;

	void SetCapacityEnableWindow(BOOL boEnable);
	void SaveUIInfo2Struct();
	void ResetItemText();

	virtual BOOL OnInitDialog();

public:
	CButton m_btnEdit;
	CComboBox* m_cmbConfigList;
	CButton* m_chkRDT;
	CLabel* m_lblTestResult;

	SYSTEM_PARAM* srtSystemParam;
	FLASH_MAPPING* srtFlashMapping;
	STRUCT_PARAM* srtStructParam;
	SERIAL_NUMBER_PARAM* srtSerialNumberParam;
	QUICK_TEST_PARAM* srtQuickTestParam;
	OTHER_SETTING* srtOtherSetting;
	BOARD_INFO srtBoardInfo;
	CString* strRootDirectoryPath;
	int* iProductionConfigCount;
	BOOL boPasswordState;
	BOOL boNewFile;

	void RefreshDisplay();
	void SetEnableWindow(BOOL boEnable);

	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedButtonSaveAs();
	afx_msg void OnCbnSelchangeComboNvmeCapacity();
	afx_msg void OnNMClickListMpParameter(NMHDR *pNMHDR, LRESULT *pResult);
};
