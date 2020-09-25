#pragma once
#include "ShareFunctions.h"


// CCreate ��ܤ��

class CCreate : public CDialog
{
	DECLARE_DYNAMIC(CCreate)

public:
	CCreate(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CCreate();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_CREATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()

protected:
	CListCtrl m_lstParam;
	CEdit m_edtParam;
	CEdit m_edtConfigFileName;
	CEdit m_edtConfigType;
	CEdit m_edtBinPath;

	int iPreItem;
	int iPreSubItem;
	BOOL boHaveEditCreate;

	void CreateEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);
	void DistroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);

	virtual BOOL OnInitDialog();

public:

	SYSTEM_PARAM srtSystemParam;
	FLASH_MAPPING srtFlashMapping;
	STRUCT_PARAM srtStructParam;
	SERIAL_NUMBER_PARAM srtSerialNumberParam;
	QUICK_TEST_PARAM srtQuickTestParam;
	OTHER_SETTING srtOtherSetting;
	CString strRootDirectoryPath;
	CString strBoardType;

	afx_msg void OnNMClickListParameter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
