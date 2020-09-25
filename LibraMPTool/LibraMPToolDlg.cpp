// LibraMPToolDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "LibraMPTool.h"
#include "LibraMPToolDlg.h"
#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CLibraMPToolDlg 對話方塊




CLibraMPToolDlg::CLibraMPToolDlg(CWnd* pParent /*=NULL*/) :
	CDialog(CLibraMPToolDlg::IDD, pParent),
	_uiSlots{MP_MAX_DISKS, nullptr}
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibraMPToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnStart);
	DDX_Control(pDX, IDCANCEL, m_btnExit);
	DDX_Control(pDX, IDC_BUTTON_RESCAN, m_btnRescan);
	DDX_Control(pDX, IDC_COMBO_CONFIG_LIST, m_cmbConfigList);
	DDX_Control(pDX, IDC_BUTTON_CREATE, m_btnCreate);
	DDX_Control(pDX, IDC_CHECK_RDT, m_chkRDT);

	DDX_Control(pDX, IDC_CHECK_DISK_1, m_chkDisk[0]);
	DDX_Control(pDX, IDC_CHECK_DISK_2, m_chkDisk[1]);
	DDX_Control(pDX, IDC_CHECK_DISK_3, m_chkDisk[2]);
	DDX_Control(pDX, IDC_CHECK_DISK_4, m_chkDisk[3]);
	DDX_Control(pDX, IDC_CHECK_DISK_5, m_chkDisk[4]);
	DDX_Control(pDX, IDC_CHECK_DISK_6, m_chkDisk[5]);
	DDX_Control(pDX, IDC_CHECK_DISK_7, m_chkDisk[6]);
	DDX_Control(pDX, IDC_CHECK_DISK_8, m_chkDisk[7]);

	DDX_Control(pDX, IDC_STATIC_SN_1, m_lblSN[0]);
	DDX_Control(pDX, IDC_STATIC_SN_2, m_lblSN[1]);
	DDX_Control(pDX, IDC_STATIC_SN_3, m_lblSN[2]);
	DDX_Control(pDX, IDC_STATIC_SN_4, m_lblSN[3]);
	DDX_Control(pDX, IDC_STATIC_SN_5, m_lblSN[4]);
	DDX_Control(pDX, IDC_STATIC_SN_6, m_lblSN[5]);
	DDX_Control(pDX, IDC_STATIC_SN_7, m_lblSN[6]);
	DDX_Control(pDX, IDC_STATIC_SN_8, m_lblSN[7]);

	DDX_Control(pDX, IDC_STATIC_FW_MODE_PORT_1, m_lblFWMode[0]);
	DDX_Control(pDX, IDC_STATIC_FW_MODE_PORT_2, m_lblFWMode[1]);
	DDX_Control(pDX, IDC_STATIC_FW_MODE_PORT_3, m_lblFWMode[2]);
	DDX_Control(pDX, IDC_STATIC_FW_MODE_PORT_4, m_lblFWMode[3]);
	DDX_Control(pDX, IDC_STATIC_FW_MODE_PORT_5, m_lblFWMode[4]);
	DDX_Control(pDX, IDC_STATIC_FW_MODE_PORT_6, m_lblFWMode[5]);
	DDX_Control(pDX, IDC_STATIC_FW_MODE_PORT_7, m_lblFWMode[6]);
	DDX_Control(pDX, IDC_STATIC_FW_MODE_PORT_8, m_lblFWMode[7]);

	DDX_Control(pDX, IDC_STATIC_DISK_1, m_stcDisk[0]);
	DDX_Control(pDX, IDC_STATIC_DISK_2, m_stcDisk[1]);
	DDX_Control(pDX, IDC_STATIC_DISK_3, m_stcDisk[2]);
	DDX_Control(pDX, IDC_STATIC_DISK_4, m_stcDisk[3]);
	DDX_Control(pDX, IDC_STATIC_DISK_5, m_stcDisk[4]);
	DDX_Control(pDX, IDC_STATIC_DISK_6, m_stcDisk[5]);
	DDX_Control(pDX, IDC_STATIC_DISK_7, m_stcDisk[6]);
	DDX_Control(pDX, IDC_STATIC_DISK_8, m_stcDisk[7]);

	DDX_Control(pDX, IDC_TAB_CONTENT, m_tabContent);
	DDX_Control(pDX, IDC_STATIC_TEST_RESULT, m_lblTestResult);
}

BEGIN_MESSAGE_MAP(CLibraMPToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CLibraMPToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLibraMPToolDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_RESCAN, &CLibraMPToolDlg::OnBnClickedButtonRescan)
	ON_STN_CLICKED(IDC_STATIC_SN_1, &CLibraMPToolDlg::OnStnClickedStaticSN)
	ON_STN_CLICKED(IDC_STATIC_SN_2, &CLibraMPToolDlg::OnStnClickedStaticSN)
	ON_STN_CLICKED(IDC_STATIC_SN_3, &CLibraMPToolDlg::OnStnClickedStaticSN)
	ON_STN_CLICKED(IDC_STATIC_SN_4, &CLibraMPToolDlg::OnStnClickedStaticSN)
	ON_STN_CLICKED(IDC_STATIC_SN_5, &CLibraMPToolDlg::OnStnClickedStaticSN)
	ON_STN_CLICKED(IDC_STATIC_SN_6, &CLibraMPToolDlg::OnStnClickedStaticSN)
	ON_STN_CLICKED(IDC_STATIC_SN_7, &CLibraMPToolDlg::OnStnClickedStaticSN)
	ON_STN_CLICKED(IDC_STATIC_SN_8, &CLibraMPToolDlg::OnStnClickedStaticSN)
	ON_STN_CLICKED(IDC_STATIC_DISK_1, &CLibraMPToolDlg::OnStnClickedStaticDisk1)
	ON_STN_CLICKED(IDC_STATIC_DISK_2, &CLibraMPToolDlg::OnStnClickedStaticDisk2)
	ON_STN_CLICKED(IDC_STATIC_DISK_3, &CLibraMPToolDlg::OnStnClickedStaticDisk3)
	ON_STN_CLICKED(IDC_STATIC_DISK_4, &CLibraMPToolDlg::OnStnClickedStaticDisk4)
	ON_STN_CLICKED(IDC_STATIC_DISK_5, &CLibraMPToolDlg::OnStnClickedStaticDisk5)
	ON_STN_CLICKED(IDC_STATIC_DISK_6, &CLibraMPToolDlg::OnStnClickedStaticDisk6)
	ON_STN_CLICKED(IDC_STATIC_DISK_7, &CLibraMPToolDlg::OnStnClickedStaticDisk7)
	ON_STN_CLICKED(IDC_STATIC_DISK_8, &CLibraMPToolDlg::OnStnClickedStaticDisk8)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTENT, &CLibraMPToolDlg::OnTcnSelchangeTabContent)
	ON_CBN_SELCHANGE(IDC_COMBO_CONFIG_LIST, &CLibraMPToolDlg::OnCbnSelchangeComboConfigList)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CLibraMPToolDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_CHECK_RDT, &CLibraMPToolDlg::OnBnClickedCheckRdt)
END_MESSAGE_MAP()


// CLibraMPToolDlg 訊息處理常式

BOOL CLibraMPToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	CString strInfo;
	strInfo.Format(_T("%s_%04X_%04X"), AP_NAME, MP_MAJOR_VERSION, MP_MINOR_VERSION);
	this->iProductionConfigCount = 0;
	this->iDiskCapacityGB = 0;
	this->strFlashVendor = _T("");
	this->strBoardType = _T("");
	this->SetWindowText(strInfo);
	this->GetRootDirectoryPath();
	this->GetDiskImages();
	this->CreateTabContent();
	this->LinkMPInfoObjectAndParam();
	this->LinkParameterObjectAndParam();
	this->SetInit();
	this->pDetectDisk.GetSysIniFile(this->strRootDirectoryPath, &this->srtSystemParam);
	this->RescanFunc();


	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CLibraMPToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CLibraMPToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CLibraMPToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLibraMPToolDlg::GetRootDirectoryPath()
{
	char cBuf[MAX_PATH*2];
	CString strInfo;

	::GetModuleFileName(NULL, cBuf, sizeof(cBuf));
	strInfo = cBuf;
	this->strRootDirectoryPath = strInfo.Left(strInfo.ReverseFind('\\')+1);
}

void CLibraMPToolDlg::GetDiskImages()
{
	CBitmap bmpTmp;
	bmpTmp.LoadBitmap(IDB_BITMAP_DISK_SCAN);
	this->bmpDiskScan = (HBITMAP)bmpTmp.Detach();
	bmpTmp.LoadBitmap(IDB_BITMAP_DISK_NULL);
	this->bmpDiskNull = (HBITMAP)bmpTmp.Detach();
	bmpTmp.LoadBitmap(IDB_BITMAP_DISK_NORMAL);
	this->bmpDiskNormal = (HBITMAP)bmpTmp.Detach();
	bmpTmp.LoadBitmap(IDB_BITMAP_DISK_INFO);
	this->bmpDiskInfo = (HBITMAP)bmpTmp.Detach();
	bmpTmp.LoadBitmap(IDB_BITMAP_DISK_RUNNING);
	this->bmpDiskRunning = (HBITMAP)bmpTmp.Detach();
	bmpTmp.LoadBitmap(IDB_BITMAP_DISK_SUCCESS);
	this->bmpDiskSuccess = (HBITMAP)bmpTmp.Detach();
	bmpTmp.LoadBitmap(IDB_BITMAP_DISK_FAIL);
	this->bmpDiskFail = (HBITMAP)bmpTmp.Detach();
}

void CLibraMPToolDlg::CreateTabContent()
{
	CRect rTmp;

	this->m_tabContent.GetClientRect(&rTmp);
	rTmp.top += 23;
	rTmp.bottom -= 5;
	rTmp.left += 5;
	rTmp.right -= 5;
	//tab 1
	this->m_tabContent.InsertItem(0, "Main");
	this->pMPInfo.Create(IDD_DIALOG_MP_INFO, GetDlgItem(IDC_TAB_CONTENT));
	this->pMPInfo.MoveWindow(&rTmp);
	//tab 2
	this->m_tabContent.InsertItem(1, "Parameter");
	this->pParam.Create(IDD_DIALOG_PARAMETER, GetDlgItem(IDC_TAB_CONTENT));
	this->pParam.MoveWindow(&rTmp);
	//show tab 1
	this->pMPInfo.ShowWindow(TRUE);
	this->pParam.ShowWindow(FALSE);
	this->m_tabContent.SetCurSel(0);
}

void CLibraMPToolDlg::CheckStructConfigVersion()
{
	WORD wItemCount = this->srtStructParam.wItemAmount;
	CString strItemName;
	WORD i;
	CString strInfo;

	for(i=0; i<wItemCount; i++)
	{
		strItemName.Format(_T("%s"), this->srtStructParam.srtItemParam[i].strName);
		if(strItemName == _T("Param_Version"))
		{
			strInfo.Format(_T("%d"), this->srtStructParam.dwStructVersion);
			if(strInfo != this->srtStructParam.srtItemParam[i].strValue)
			{
				strInfo.Format(_T("Production parameter version is not match!!!\nStructure version is %d, Parameter version is %s"),
					this->srtStructParam.dwStructVersion, this->srtStructParam.srtItemParam[i].strValue);
				::AfxMessageBox(strInfo);
			}
			break;
		}
	}
}

BOOL CLibraMPToolDlg::GetConfigParam()
{
	CString strInfo;
	BOOL boStatus = FALSE;

	this->pDetectDisk.GetConfigFiles(this->strRootDirectoryPath, this->strBoardType, this->srtFlashMapping.strBinPath, this->m_chkRDT.GetCheck(), &this->iProductionConfigCount, &this->m_cmbConfigList);
	if(this->iProductionConfigCount == 0)
	{
		this->SetEnableWindow(FALSE);
		if(this->m_chkRDT.GetCheck())
			strInfo.Format(_T("RDT config file not detected. Path:%s\\%s"), this->strRootDirectoryPath, this->srtFlashMapping.strBinPath);
		else
			strInfo.Format(_T("SYS config file not detected. Path:%s\\%s"), this->strRootDirectoryPath, this->srtFlashMapping.strBinPath);
		::AfxMessageBox(strInfo);
		return FALSE;
	}
	else
		this->SetEnableWindow(TRUE);
	if(this->iProductionConfigCount > 1)
		this->m_cmbConfigList.EnableWindow(TRUE);
	else
		this->m_cmbConfigList.EnableWindow(FALSE);
	boStatus = this->pDetectDisk.GetStructItems(this->strRootDirectoryPath, this->m_chkRDT.GetCheck(), &this->srtStructParam);
	if(!boStatus)
	{
		if(this->m_chkRDT.GetCheck())
			strInfo.Format(_T("RDT struct file not detected. Path:%s"), this->strRootDirectoryPath);
		else
			strInfo.Format(_T("SYS struct file not detected. Path:%s"), this->strRootDirectoryPath);
		::AfxMessageBox(strInfo);
		return FALSE;
	}

	if(this->srtStructParam.wItemAmount > MAX_ITEM_AMOUNT)
	{
		strInfo.Format(_T("Parameter items is over!!!\nProduction parameter max support %d items"), MAX_ITEM_AMOUNT);
		::AfxMessageBox(strInfo);
		this->m_cmbConfigList.EnableWindow(FALSE);
		this->pMPInfo.m_btnStart.EnableWindow(FALSE);
		return FALSE;
	}

	this->m_cmbConfigList.GetWindowText(strInfo);
	this->pDetectDisk.GetProductionParam(this->strRootDirectoryPath, this->srtFlashMapping.strBinPath, strInfo, &this->srtStructParam, &this->srtSerialNumberParam, &this->srtQuickTestParam, &this->srtOtherSetting);
	
	this->GetCurrentMaxSN();

	this->CheckStructConfigVersion();
	return TRUE;
}

void CLibraMPToolDlg::SetInit()
{
	int i;

	this->m_btnRescan.SetBitmap(this->bmpDiskScan);

	this->m_lblTestResult.SetFontSize(11);
	for(i=0; i<MP_MAX_DISKS; i++)
	{
		this->m_lblFWMode[i].SetText(_T(""));
		this->m_lblFWMode[i].SetFontSize(12);
	}
	this->srtSerialNumberParam.bSNRule = 2;
	this->srtSerialNumberParam.dwSNFailCount = 0;
	this->srtSerialNumberParam.dwSNPassCount = 0;
	this->srtSerialNumberParam.dwSNResetCount = 0;
}

void CLibraMPToolDlg::DiskSetInit()
{
	int i;

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		this->m_chkDisk[i].SetCheck(FALSE);
		this->m_chkDisk[i].EnableWindow(FALSE);
		this->m_lblSN[i].SetText(_T(""));
		this->m_lblSN[i].ModifyStyle(SS_NOTIFY, 0);
		this->m_stcDisk[i].SetBitmap(this->bmpDiskNull);
		this->m_stcDisk[i].ModifyStyle(SS_NOTIFY, 0);
		this->m_lblFWMode[i].SetBkColor(::GetSysColor(COLOR_3DFACE));
		this->m_lblFWMode[i].SetText(_T(""));
		this->iPort2Disk[i] = -1;
	}
}

void CLibraMPToolDlg::SetSNInit()
{
	WORD i;
	int iDiskAmount = this->pDetectDisk.iDiskAmount;
	CString strItemName;
	CString strInfo;

	for(i=0; i<MP_MAX_DISKS; i++)
		this->pMPInfo.boResetState[i] = FALSE;

	for(i=0; i<iDiskAmount; i++)
	{
		this->strMPSN[i].Format(_T("%s"), this->pDetectDisk.srtDiskInfo[i].cSerialNumber);
		if(this->srtSerialNumberParam.bSNRule == 1)
			this->pMPInfo.ResetSN(i);
	}
}

BOOL CLibraMPToolDlg::GetFlashMappingParam()
{
	BOOL boRtnStatus = FALSE;
	CString strInfo, strTmp;

	strInfo.Format(_T("0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X"),
		this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[0], this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[1], this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[2], this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[3],
		this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[4], this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[5], this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[6], this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[7]);
	if(this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.bFlashID[0] == 0x2C)
		this->strFlashVendor = FLASH_VENDOR_MICRON;
	else
	{
		strTmp.Format(_T("Flash not support! Flash ID: %s"), strInfo);
		::AfxMessageBox(strTmp);
		return boRtnStatus;
	}
	boRtnStatus = this->pDetectDisk.GetFlashParam(this->strRootDirectoryPath, this->strFlashVendor, strInfo, &this->srtFlashMapping);
	if(!boRtnStatus)
	{
		strTmp.Format(_T("Flash ID mismatch!!!\n\nBoard Flash ID: %s"), strInfo);
		::AfxMessageBox(strTmp);
	}
	return boRtnStatus;
}

void CLibraMPToolDlg::GetCapacityLBN()
{
	WORD wItemCount = this->srtStructParam.wItemAmount;
	WORD i;
	CString strItemName;
	unsigned __int64 ui64LBNValue = 0;
	CString strInfo;

	if(this->srtOtherSetting.bCapacityMethod == 0)
	{
		for(i=0; i<wItemCount; i++)
		{
			strItemName.Format(_T("%s"), this->srtStructParam.srtItemParam[i].strName);
			if((strItemName == _T("NVMe_Drv_Total_Capacity_LBN")) || (strItemName == _T("NVMe_LBN_Num")))
			{
				ui64LBNValue = this->pDetectDisk.GetLBNValue(this->iDiskCapacityGB);
				strInfo.Format(_T("%I64d"), ui64LBNValue);
				this->srtStructParam.srtItemParam[i].strValue = strInfo;
			}
		}
	}
}

void CLibraMPToolDlg::SetSingleDiskInfo(int UIIndex, const DISKINFO* pDiskInfo)
{
	if (pDiskInfo == nullptr)
		return;

	int iDiskCapacity = this->pDetectDisk.GetDiskCapacity(pDiskInfo->srtBoardInfo.iChannelNum, pDiskInfo->srtBoardInfo.iBankNum, this->srtFlashMapping.bLunPerTarget, this->srtFlashMapping.wDieCapacityGb);
	this->iPort2Disk[UIIndex] = (pDiskInfo - &this->pDetectDisk.srtDiskInfo[0]) / sizeof(DISKINFO*);
	this->m_chkDisk[UIIndex].EnableWindow(TRUE);

	CString strUsbSN;
	strUsbSN.Format(_T("%s"), pDiskInfo->cUSBBridgeSN);
	CString strInfo;
	strInfo.Format(_T("USB(%d) %dGB: %s"), pDiskInfo->iPhysicalDiskIndex, iDiskCapacity, strUsbSN.GetString());

	this->m_lblSN[UIIndex].SetWindowText(strInfo);
	this->m_lblSN[UIIndex].ModifyStyle(0, SS_NOTIFY);
	this->m_stcDisk[UIIndex].SetBitmap(this->bmpDiskNormal);
	this->m_stcDisk[UIIndex].ModifyStyle(0, SS_NOTIFY);

	CString strFWMode[5];
	strFWMode[0] = _T("NULL");
	strFWMode[1] = _T("ROM");
	strFWMode[2] = _T("BNR");
	strFWMode[3] = _T("RDT");
	strFWMode[4] = _T("SYS");
	this->m_lblFWMode[UIIndex].SetText(strFWMode[pDiskInfo->iFWMode]);
	this->m_lblFWMode[UIIndex].SetTextColor(FW_Mode_Text_Color);
	this->m_lblFWMode[UIIndex].SetBkColor(FW_Mode_BK_Color);

	this->srtSystemParam.strPortSN[UIIndex] = strUsbSN;
					
	if(pDiskInfo->iFWMode == 0)
	{
		this->m_chkDisk[UIIndex].EnableWindow(FALSE);
		this->m_stcDisk[UIIndex].ModifyStyle(SS_NOTIFY, 0);// We do not need this?
	}
}

int CLibraMPToolDlg::FindUISlotByUsbBridgeSN(CString sn) const
{
	for (int i = 0; i < MP_MAX_DISKS; i++)
		if (sn.Compare(this->srtSystemParam.strPortSN[i]) == 0)
			return i;

	return -1; // Slot not found
}

int CLibraMPToolDlg::FindNotUsedUISlot() const
{
	for (int i = 0; i < MP_MAX_DISKS; i++)
		if (_uiSlots[i] == nullptr)
			return i;

	return -1; // Slot not found
}

void CLibraMPToolDlg::ShowDiskInfo()
{
	CString strUsbSN;
	int iDiskAmount = this->pDetectDisk.iDiskAmount;
	std::list<const DISKINFO*> MPDisks;

	_uiSlots.assign(MP_MAX_DISKS, nullptr);// Clear mapping

	for (int i = 0; i < iDiskAmount; i++)
		MPDisks.push_back(&pDetectDisk.srtDiskInfo[i]);

	// First, map USB bridge SerialNumber in system.ini to MPDisk. (UISlot, MPDisk)
	for (int i = 0; i < iDiskAmount; i++)
	{
		strUsbSN.Format(_T("%s"), this->pDetectDisk.srtDiskInfo[i].cUSBBridgeSN);

		int uiSlotIndex = FindUISlotByUsbBridgeSN(strUsbSN);
		if (uiSlotIndex != -1) // USB bridge SerialNumber is found in system.ini
		{
			_uiSlots[uiSlotIndex] = &pDetectDisk.srtDiskInfo[i];
			MPDisks.remove(&pDetectDisk.srtDiskInfo[i]);
		}
	}
	// Assign non-mapped MPDisk to a non-mapped UISlot
	auto it = MPDisks.begin();
	while (it != MPDisks.end())
	{
		int uiSlotIndex = FindNotUsedUISlot();
		if (uiSlotIndex != -1)
		{
			_uiSlots[uiSlotIndex] = *it;
			MPDisks.erase(it++);
		}
		else
			break;
	}

	for (int i = 0; i < static_cast<int>(_uiSlots.size()); i++)
		SetSingleDiskInfo(i, _uiSlots[i]);

	this->SetMPInfoDisplay();
	this->SetParameterDisplay();
	this->pDetectDisk.ShowTestResult(&this->srtSerialNumberParam, &this->m_lblTestResult);
}

void CLibraMPToolDlg::RescanFunc()
{
	BOOL boStatus = FALSE;
	this->SetEnableWindow(FALSE);
	this->pDetectDisk.ScanDisks();
	this->DiskSetInit();
	if(this->pDetectDisk.iDiskAmount == 0)
		return;
	boStatus = this->GetFlashMappingParam();
	if(!boStatus)
		return;
	this->iDiskCapacityGB = this->pDetectDisk.GetDiskCapacity(this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.iChannelNum, this->pDetectDisk.srtDiskInfo[0].srtBoardInfo.iBankNum, this->srtFlashMapping.bLunPerTarget, this->srtFlashMapping.wDieCapacityGb);
	this->strBoardType.Format(_T("%s_%s_%dG"), this->strFlashVendor, this->srtFlashMapping.strType, iDiskCapacityGB);
	boStatus = this->GetConfigParam();
	if(!boStatus)
		return;
	this->GetCapacityLBN();
	this->SetSNInit();
	this->ShowDiskInfo();
}

void CLibraMPToolDlg::GetCurrentMaxSN()
{
	int iStatus;
	int iSNCount;
	int i;
	char cBuf[20];
	unsigned __int64 dwValue = 0;

	iStatus = this->srtSerialNumberParam.strSNMask.Find('#');
	
	dwValue = 0;
	iSNCount = this->srtSerialNumberParam.strBeginSN.GetLength();
	::memset(cBuf, 0, sizeof(cBuf));
	::memcpy(cBuf, this->srtSerialNumberParam.strBeginSN, iSNCount);
	for(i=iStatus; i<iSNCount; i++)
	{
		if(cBuf[i] >= '0' && cBuf[i] <= '9')
			dwValue = (dwValue * 10) + (cBuf[i] - '0');
	}
	this->srtSNInfo.ui64BeginSN = dwValue;

	dwValue = 0;
	iSNCount = this->srtSerialNumberParam.strEndSN.GetLength();
	::memset(cBuf, 0, sizeof(cBuf));
	::memcpy(cBuf, this->srtSerialNumberParam.strEndSN, iSNCount);
	for(i=iStatus; i<iSNCount; i++)
	{
		if(cBuf[i] >= '0' && cBuf[i] <= '9')
			dwValue = (dwValue * 10) + (cBuf[i] - '0');
	}
	this->srtSNInfo.ui64EndSN = dwValue;

	this->srtSNInfo.ui64CurrentSN = this->srtSNInfo.ui64BeginSN + this->srtSerialNumberParam.dwSNResetCount;
}

void CLibraMPToolDlg::SetMPInfoDisplay()
{
	int i;
	CString strInfo;

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		this->pMPInfo.boDiskExist[i] = FALSE;
		this->pMPInfo.iDiskPhysicalIndex[i] = -1;
		this->pMPInfo.bDiskBusType[i] = 0;
		this->pMPInfo.strDiskSN[i] = _T("");
		this->pMPInfo.boPartitionMode[i] = FALSE;
	}

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		if (_uiSlots[i] != nullptr)
		{
			this->pMPInfo.boDiskExist[i] = TRUE;
			this->pMPInfo.iDiskPhysicalIndex[i] = this->pDetectDisk.srtDiskInfo[this->iPort2Disk[i]].iPhysicalDiskIndex;
			this->pMPInfo.bDiskBusType[i] = this->pDetectDisk.srtDiskInfo[this->iPort2Disk[i]].bDiskBusType;
			this->pMPInfo.strDiskSN[i] = this->strMPSN[this->iPort2Disk[i]];
			strInfo.Format(_T("%s"), this->pDetectDisk.srtDiskInfo[this->iPort2Disk[i]].cDriveName);
			if(strInfo.IsEmpty())
				this->pMPInfo.boPartitionMode[i] = FALSE;
			else
				this->pMPInfo.boPartitionMode[i] = TRUE;
			::memcpy(&this->pMPInfo.srtBoardInfo[i], &this->pDetectDisk.srtDiskInfo[this->iPort2Disk[i]].srtBoardInfo, sizeof(this->pMPInfo.srtBoardInfo[i]));
		}
	}
	this->pMPInfo.RefreshDisplay();
}

void CLibraMPToolDlg::SetParameterDisplay()
{
	::memcpy(&this->pParam.srtBoardInfo, &this->pDetectDisk.srtDiskInfo[0].srtBoardInfo, sizeof(this->pParam.srtBoardInfo));
	this->pParam.RefreshDisplay();
}

void CLibraMPToolDlg::LinkMPInfoObjectAndParam()
{
	int i;

	this->pMPInfo.m_btnExit = &this->m_btnExit;
	this->pMPInfo.m_btnRescan = &this->m_btnRescan;
	this->pMPInfo.m_btnEdit = &this->pParam.m_btnEdit;
	this->pMPInfo.m_cmbConfigList = &this->m_cmbConfigList;
	this->pMPInfo.m_btnCreate = &this->m_btnCreate;
	this->pMPInfo.m_chkRDT = &this->m_chkRDT;
	this->pMPInfo.m_lblTestResult = &this->m_lblTestResult;
	for(i=0; i<MP_MAX_DISKS; i++)
	{
		this->pMPInfo.m_lblSN[i] = &this->m_lblSN[i];
		this->pMPInfo.m_chkDisk[i] = &this->m_chkDisk[i];
		this->pMPInfo.m_stcDisk[i] = &this->m_stcDisk[i];
		this->pMPInfo.m_lblFWMode[i] = &this->m_lblFWMode[i];

		this->pMPInfo.iPort2Disk[i] = &this->iPort2Disk[i];
		this->pMPInfo.strMPSN[i] = &this->strMPSN[i];
	}
	this->pMPInfo.strRootDirectoryPath = &this->strRootDirectoryPath;
	this->pMPInfo.srtSystemParam = &this->srtSystemParam;
	this->pMPInfo.srtFlashMapping = &this->srtFlashMapping;
	this->pMPInfo.srtStructParam = &this->srtStructParam;
	this->pMPInfo.srtSerialNumberParam = &this->srtSerialNumberParam;
	this->pMPInfo.srtQuickTestParam = &this->srtQuickTestParam;
	this->pMPInfo.srtOtherSetting = &this->srtOtherSetting;
	this->pMPInfo.srtSNInfo = &this->srtSNInfo;
}

void CLibraMPToolDlg::LinkParameterObjectAndParam()
{
	this->pParam.m_cmbConfigList = &this->m_cmbConfigList;
	this->pParam.m_chkRDT = &this->m_chkRDT;
	this->pParam.m_lblTestResult = &this->m_lblTestResult;
	this->pParam.strRootDirectoryPath = &this->strRootDirectoryPath;
	this->pParam.srtSystemParam = &this->srtSystemParam;
	this->pParam.srtFlashMapping = &this->srtFlashMapping;
	this->pParam.srtStructParam = &this->srtStructParam;
	this->pParam.srtSerialNumberParam = &this->srtSerialNumberParam;
	this->pParam.srtQuickTestParam = &this->srtQuickTestParam;
	this->pParam.srtOtherSetting = &this->srtOtherSetting;
	this->pParam.iProductionConfigCount = &this->iProductionConfigCount;
}

void CLibraMPToolDlg::NewFileResetInfo()
{
	int i;

	this->GetCurrentMaxSN();

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		if(this->pMPInfo.boResetState[i])
			this->pMPInfo.ResetSN(i);
	}
	this->SetMPInfoDisplay();
}

void CLibraMPToolDlg::DoStaticDiskFunc(int iSelectIndex)
{
	BOOL boCState;
	boCState = this->m_chkDisk[iSelectIndex].GetCheck();
	this->m_chkDisk[iSelectIndex].SetCheck(!boCState);
}

void CLibraMPToolDlg::SetEnableWindow(BOOL boEnable)
{
	if(this->srtSystemParam.bEpoStar != 77)
	{
		this->m_cmbConfigList.EnableWindow(FALSE);
		this->m_btnCreate.EnableWindow(FALSE);
		this->m_btnCreate.ShowWindow(FALSE);
	}
	else
	{
		this->m_cmbConfigList.EnableWindow(boEnable);
		this->m_chkRDT.EnableWindow(boEnable);
		this->m_btnCreate.ShowWindow(boEnable);
	}
	this->pMPInfo.m_btnStart.EnableWindow(boEnable);
	this->pParam.m_btnEdit.EnableWindow(boEnable);
}

void CLibraMPToolDlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	//OnOK();
}

void CLibraMPToolDlg::OnBnClickedCancel()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	OnCancel();
}

void CLibraMPToolDlg::OnBnClickedButtonRescan()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->RescanFunc();
}

void CLibraMPToolDlg::OnTcnSelchangeTabContent(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
	switch(this->m_tabContent.GetCurSel())
	{
	case 0:
		if(this->pParam.boNewFile)
			this->NewFileResetInfo();
		this->pMPInfo.ShowWindow(TRUE);
		this->pParam.ShowWindow(FALSE);
		break;
	case 1:
		this->pMPInfo.ShowWindow(FALSE);
		this->pParam.boPasswordState = FALSE;
		this->pParam.SetEnableWindow(FALSE);
		this->pParam.ShowWindow(TRUE);
		if(this->srtStructParam.wItemAmount > MAX_ITEM_AMOUNT)
			this->pParam.m_btnEdit.EnableWindow(FALSE);
		if(this->m_cmbConfigList.GetCount() <= 0)
			this->pParam.m_btnEdit.EnableWindow(FALSE);
		break;
	default:
		break;
	}
}

void CLibraMPToolDlg::OnStnClickedStaticSN()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	PortSetting pPortSetting;
	int i;

	for(i=0; i<MP_MAX_DISKS; i++)
		pPortSetting.strPortSN[i] = &this->srtSystemParam.strPortSN[i];
	pPortSetting.DoModal();

	this->DiskSetInit();
	this->ShowDiskInfo();
}

void CLibraMPToolDlg::OnStnClickedStaticDisk1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticDiskFunc(0);
}

void CLibraMPToolDlg::OnStnClickedStaticDisk2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticDiskFunc(1);
}

void CLibraMPToolDlg::OnStnClickedStaticDisk3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticDiskFunc(2);
}

void CLibraMPToolDlg::OnStnClickedStaticDisk4()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticDiskFunc(3);
}

void CLibraMPToolDlg::OnStnClickedStaticDisk5()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticDiskFunc(4);
}

void CLibraMPToolDlg::OnStnClickedStaticDisk6()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticDiskFunc(5);
}

void CLibraMPToolDlg::OnStnClickedStaticDisk7()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticDiskFunc(6);
}

void CLibraMPToolDlg::OnStnClickedStaticDisk8()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticDiskFunc(7);
}

void CLibraMPToolDlg::OnCbnSelchangeComboConfigList()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString strInfo;
	//int i;

	this->m_cmbConfigList.GetWindowText(strInfo);
	this->srtSystemParam.strConfigFile = strInfo;
	this->pDetectDisk.GetProductionParam(this->strRootDirectoryPath, this->srtFlashMapping.strBinPath, this->srtSystemParam.strConfigFile, &this->srtStructParam, &this->srtSerialNumberParam, &this->srtQuickTestParam, &this->srtOtherSetting);
	this->GetCapacityLBN();
	this->pDetectDisk.ShowTestResult(&this->srtSerialNumberParam, &this->m_lblTestResult);

	this->SetParameterDisplay();

	this->NewFileResetInfo();

	this->pParam.boPasswordState = FALSE;
	this->pParam.SetEnableWindow(FALSE);

	this->CheckStructConfigVersion();
}

void CLibraMPToolDlg::OnBnClickedButtonCreate()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CCreate pCreate;
	pCreate.srtSystemParam = this->srtSystemParam;
	pCreate.srtFlashMapping = this->srtFlashMapping;
	pCreate.srtStructParam = this->srtStructParam;
	pCreate.srtSerialNumberParam = this->srtSerialNumberParam;
	pCreate.srtQuickTestParam = this->srtQuickTestParam;
	pCreate.srtOtherSetting = this->srtOtherSetting;
	pCreate.strRootDirectoryPath = this->strRootDirectoryPath;
	pCreate.strBoardType = this->strBoardType;
	pCreate.DoModal();
}

void CLibraMPToolDlg::OnBnClickedCheckRdt()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	BOOL boStatus = FALSE;
	CString strInfo;
	boStatus = this->GetConfigParam();
	if(!boStatus)
	{
		this->m_chkRDT.EnableWindow(TRUE);
		return;
	}
	this->SetSNInit();
	this->ShowDiskInfo();
}
