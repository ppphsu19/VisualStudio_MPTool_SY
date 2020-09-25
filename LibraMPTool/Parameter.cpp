// Parameter.cpp : 實作檔
//

#include "stdafx.h"
#include "LibraMPTool.h"
#include "Parameter.h"


// Parameter 對話方塊

IMPLEMENT_DYNAMIC(Parameter, CDialog)

Parameter::Parameter(CWnd* pParent /*=NULL*/)
	: CDialog(Parameter::IDD, pParent)
{

}

Parameter::~Parameter()
{
}

void Parameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK_EDIT, m_btnEdit);
	DDX_Control(pDX, IDCANCEL_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON_SAVE_AS, m_btnSaveAs);

	DDX_Control(pDX, IDC_LIST_MP_PARAMETER, m_lstMPParam);
	DDX_Control(pDX, IDC_EDIT_MP_PARAMETER, m_edtMPParam);
	DDX_Control(pDX, IDC_EDIT_BEGIN_SN, m_edtBeginSN);
	DDX_Control(pDX, IDC_EDIT_END_SN, m_edtEndSN);
	DDX_Control(pDX, IDC_EDIT_SN_MASK, m_edtSNMask);
	DDX_Control(pDX, IDC_EDIT_NVME_MN, m_edtNVMeMN);
	DDX_Control(pDX, IDC_EDIT_SYS_FW_VERSION, m_edtSysFWVersion);
	DDX_Control(pDX, IDC_EDIT_NVME_VID, m_edtNVMeVID);
	DDX_Control(pDX, IDC_EDIT_NVME_DID, m_edtNVMeDID);
	DDX_Control(pDX, IDC_EDIT_SYS_EUI64, m_edtSysEUI64);
	DDX_Control(pDX, IDC_COMBO_NVME_CAPACITY, m_cmbNVMeCapacity);
	DDX_Control(pDX, IDC_EDIT_NVME_CAPACITY_MANUAL, m_edtNVMeCapacityManual);
}


BEGIN_MESSAGE_MAP(Parameter, CDialog)
	ON_BN_CLICKED(IDOK_EDIT, &Parameter::OnBnClickedEdit)
	ON_BN_CLICKED(IDCANCEL_SAVE, &Parameter::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_AS, &Parameter::OnBnClickedButtonSaveAs)
	ON_CBN_SELCHANGE(IDC_COMBO_NVME_CAPACITY, &Parameter::OnCbnSelchangeComboNvmeCapacity)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MP_PARAMETER, &Parameter::OnNMClickListMpParameter)
END_MESSAGE_MAP()


// Parameter 訊息處理常式
BOOL Parameter::OnInitDialog()
{
	CDialog::OnInitDialog();

	LOGFONT lf;
	CFont EditFont;
	this->GetFont()->GetLogFont(&lf);
	::strcpy_s(lf.lfFaceName, "system");
	EditFont.CreateFontIndirect(&lf);

	this->boPasswordState = FALSE;
	this->boNewFile = FALSE;
	this->boHaveEditCreate = FALSE;
	this->SetEnableWindow(FALSE);

	this->m_lstMPParam.SetFont(&EditFont);
	this->m_edtBeginSN.SetFont(&EditFont);
	this->m_edtEndSN.SetFont(&EditFont);
	this->m_edtSNMask.SetFont(&EditFont);
	this->m_edtNVMeMN.SetFont(&EditFont);
	this->m_edtSysFWVersion.SetFont(&EditFont);
	this->m_edtNVMeVID.SetFont(&EditFont);
	this->m_edtNVMeDID.SetFont(&EditFont);
	this->m_edtSysEUI64.SetFont(&EditFont);

	this->m_cmbNVMeCapacity.AddString(_T("Default"));
	this->m_cmbNVMeCapacity.AddString(_T("Manual"));

	this->m_lstMPParam.DeleteAllItems();
	this->m_lstMPParam.InsertColumn(0, _T("Parameter"), LVCFMT_LEFT, 200);
	this->m_lstMPParam.InsertColumn(1, _T("Content"), LVCFMT_LEFT, 200);

	this->m_lstMPParam.SetExtendedStyle(this->m_lstMPParam.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	return TRUE;
}

void Parameter::RefreshDisplay()
{
	CString strItemName;
	WORD wItemCount = this->srtStructParam->wItemAmount;
	WORD i;
	CString strInfo;
	int iDisplayCount = 0;

	this->bCapacityMethod = this->srtOtherSetting->bCapacityMethod;

	this->m_edtBeginSN.SetWindowText(this->srtSerialNumberParam->strBeginSN);
	this->m_edtEndSN.SetWindowText(this->srtSerialNumberParam->strEndSN);
	this->m_edtSNMask.SetWindowText(this->srtSerialNumberParam->strSNMask);

	this->m_cmbNVMeCapacity.SetCurSel(this->srtOtherSetting->bCapacityMethod);
	if(this->m_chkRDT->GetCheck())
		this->m_cmbNVMeCapacity.EnableWindow(FALSE);

	this->m_lstMPParam.DeleteAllItems();
	for(i=0; i<wItemCount; i++)
	{
		strItemName.Format(_T("%s"), this->srtStructParam->srtItemParam[i].strName);

		if(this->srtStructParam->srtItemParam[i].boDisplay)
		{
			this->m_lstMPParam.InsertItem(iDisplayCount, strItemName);
			if((strItemName == _T("NVMe_Drv_Total_Capacity_LBN")) || (strItemName == _T("NVMe_LBN_Num")))
			{
				if(this->srtOtherSetting->bCapacityMethod == 1)
					strInfo = this->srtStructParam->srtItemParam[i].strValue;
				else
					strInfo = _T("");
			}
			else
				strInfo = this->srtStructParam->srtItemParam[i].strValue;
			this->m_lstMPParam.SetItemText(iDisplayCount, 1, strInfo);
			iDisplayCount++;
		}
	}
}

void Parameter::SetCapacityEnableWindow(BOOL boEnable)
{
	if(this->m_cmbNVMeCapacity.GetCurSel() == 1)
		this->m_edtNVMeCapacityManual.EnableWindow(boEnable);
	else
		this->m_edtNVMeCapacityManual.EnableWindow(FALSE);
}

void Parameter::SetEnableWindow(BOOL boEnable)
{
	this->m_btnEdit.EnableWindow(!boEnable);
	this->m_btnSave.EnableWindow(boEnable);
	this->m_btnSaveAs.EnableWindow(boEnable);

	this->m_lstMPParam.EnableWindow(boEnable);
	this->m_edtMPParam.EnableWindow(boEnable);
	this->m_edtBeginSN.EnableWindow(boEnable);
	this->m_edtEndSN.EnableWindow(boEnable);
	this->m_edtSNMask.EnableWindow(boEnable);
	this->m_edtNVMeMN.EnableWindow(boEnable);
	this->m_edtSysFWVersion.EnableWindow(boEnable);
	this->m_edtNVMeVID.EnableWindow(boEnable);
	this->m_edtNVMeDID.EnableWindow(boEnable);
	this->m_edtSysEUI64.EnableWindow(boEnable);
	this->m_cmbNVMeCapacity.EnableWindow(boEnable);
	this->SetCapacityEnableWindow(boEnable);
}

void Parameter::SaveUIInfo2Struct()
{
	CString strItemName;
	CString strListName, strListValue;
	WORD wItemCount = this->srtStructParam->wItemAmount;
	WORD wListCount = this->m_lstMPParam.GetItemCount();
	WORD i, j;
	CString strInfo;
	int iDiskCapacityGB = 0;
	unsigned __int64 ui64DiskLBN = 0;

	this->srtOtherSetting->bCapacityMethod = this->m_cmbNVMeCapacity.GetCurSel();

	this->m_edtBeginSN.GetWindowText(strInfo);
	this->srtSerialNumberParam->strBeginSN = strInfo;
	this->m_edtEndSN.GetWindowText(strInfo);
	this->srtSerialNumberParam->strEndSN = strInfo;
	this->m_edtSNMask.GetWindowText(strInfo);
	this->srtSerialNumberParam->strSNMask = strInfo;

	for(i=0; i<wListCount; i++)
	{
		strListName = this->m_lstMPParam.GetItemText(i, 0);
		strListValue = this->m_lstMPParam.GetItemText(i, 1);
		for(j=0; j<wItemCount; j++)
		{
			strItemName.Format(_T("%s"), this->srtStructParam->srtItemParam[j].strName);
			if(strItemName == strListName)
			{
				if((strListName == _T("NVMe_Drv_Total_Capacity_LBN")) || (strListName == _T("NVMe_LBN_Num")))
				{
					if(this->srtOtherSetting->bCapacityMethod == 1)
						this->srtStructParam->srtItemParam[j].strValue = strListValue;
					else
					{
						iDiskCapacityGB = this->pShareFunctions.GetDiskCapacity(this->srtBoardInfo.iChannelNum, this->srtBoardInfo.iBankNum, this->srtFlashMapping->bLunPerTarget, this->srtFlashMapping->wDieCapacityGb);
						ui64DiskLBN = this->pShareFunctions.GetLBNValue(iDiskCapacityGB);
						strInfo.Format(_T("%I64d"), ui64DiskLBN);
						this->srtStructParam->srtItemParam[j].strValue = strInfo;
					}
				}
				else
					this->srtStructParam->srtItemParam[j].strValue = strListValue;
				break;
			}
		}
	}
}

void Parameter::ResetItemText()
{
	CString strInfo;
	strInfo = this->m_lstMPParam.GetItemText(this->iPreItem, 0);
	if((strInfo == _T("NVMe_Drv_Total_Capacity_LBN")) || (strInfo == _T("NVMe_LBN_Num")))
	{
		if(this->bCapacityMethod == 0)
			strInfo = _T("");
		else
			this->m_edtMPParam.GetWindowText(strInfo);
	}
	else
		this->m_edtMPParam.GetWindowText(strInfo);
	this->m_lstMPParam.SetItemText(this->iPreItem, this->iPreSubItem, strInfo);
	this->m_edtMPParam.ShowWindow(FALSE);
}

void Parameter::OnBnClickedEdit()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Password pPassword;
	pPassword.boPasswordState = &this->boPasswordState;
	pPassword.DoModal();
	if(this->boPasswordState)
		this->SetEnableWindow(TRUE);
	else
		::AfxMessageBox("Password is not correct!!!");
}

void Parameter::OnBnClickedSave()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString strInfo;

	if(this->boHaveEditCreate)
		this->ResetItemText();
	this->SaveUIInfo2Struct();
	this->m_cmbConfigList->GetWindowText(strInfo);
	this->pShareFunctions.SaveProductionParam(*this->strRootDirectoryPath, this->srtFlashMapping->strBinPath, strInfo, this->srtStructParam, this->srtSerialNumberParam, this->srtFlashMapping, this->srtQuickTestParam, this->srtOtherSetting, FALSE);
	this->boPasswordState = FALSE;
	this->SetEnableWindow(FALSE);
	this->m_edtMPParam.ShowWindow(FALSE);
}

void Parameter::OnBnClickedButtonSaveAs()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString strFileName;
	CString strFilter;
	CString strInfo;
	BOOL boIsNewFile = TRUE;
	int i;

	strFilter = _T("Ini File(*.ini)|*.ini||");
	CFileDialog dlgFile(FALSE, "ini", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if(dlgFile.DoModal() == IDOK)
    {
		strFileName = dlgFile.GetFileName();

		this->srtSystemParam->strConfigFile = strFileName;

		for(i=0; i<*this->iProductionConfigCount; i++)
		{
			this->m_cmbConfigList->GetLBText(i, strInfo);
			if(strInfo == strFileName)
			{
				this->m_cmbConfigList->SetCurSel(i);
				boIsNewFile = FALSE;
				break;
			}
		}
		if(boIsNewFile)
		{
			this->m_cmbConfigList->AddString(strFileName);
			this->m_cmbConfigList->SetCurSel(*this->iProductionConfigCount);
			*this->iProductionConfigCount = *this->iProductionConfigCount + 1;
		}

		if(this->boHaveEditCreate)
			this->ResetItemText();
		this->SaveUIInfo2Struct();
		this->pShareFunctions.SaveProductionParam(*this->strRootDirectoryPath, this->srtFlashMapping->strBinPath, strFileName, this->srtStructParam, this->srtSerialNumberParam, this->srtFlashMapping, this->srtQuickTestParam, this->srtOtherSetting, TRUE);
		this->pShareFunctions.ShowTestResult(this->srtSerialNumberParam, this->m_lblTestResult);

		this->boPasswordState = FALSE;
		this->boNewFile = TRUE;
		this->SetEnableWindow(FALSE);
		this->m_edtMPParam.ShowWindow(FALSE);
    }
}

void Parameter::OnCbnSelchangeComboNvmeCapacity()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->bCapacityMethod = this->m_cmbNVMeCapacity.GetCurSel();
}

void Parameter::OnNMClickListMpParameter(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	CString strInfo;

	strInfo = this->m_lstMPParam.GetItemText(pNMItemActivate->iItem, 0);
	if((strInfo == _T("NVMe_Drv_Total_Capacity_LBN")) || (strInfo == _T("NVMe_LBN_Num")))
	{
		if(this->bCapacityMethod == 0)
			return;
	}

	if(this->boHaveEditCreate)
		this->ResetItemText();

	if(pNMItemActivate->iSubItem == 1)
	{
		CRect  EditRect;
		
		this->iPreItem = pNMItemActivate->iItem;
		this->iPreSubItem = pNMItemActivate->iSubItem;

		strInfo = this->m_lstMPParam.GetItemText(this->iPreItem, this->iPreSubItem);

		this->m_edtMPParam.SetParent(&this->m_lstMPParam);
		this->m_lstMPParam.GetSubItemRect(this->iPreItem, this->iPreSubItem, LVIR_LABEL, EditRect);
		EditRect.SetRect(EditRect.left+1, EditRect.top+1, EditRect.left + this->m_lstMPParam.GetColumnWidth(this->iPreSubItem)-1, EditRect.bottom + 3);
		this->m_edtMPParam.SetWindowText(strInfo);
		this->m_edtMPParam.MoveWindow(&EditRect);
		this->m_edtMPParam.ShowWindow(SW_SHOW);
		this->m_edtMPParam.SetFocus();
		this->m_edtMPParam.SetSel(-1);

		this->boHaveEditCreate = TRUE;
	}
	*pResult = 0;
}
