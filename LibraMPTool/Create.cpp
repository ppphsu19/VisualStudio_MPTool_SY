// Create.cpp : 實作檔
//

#include "stdafx.h"
#include "LibraMPTool.h"
#include "Create.h"


// CCreate 對話方塊

IMPLEMENT_DYNAMIC(CCreate, CDialog)

CCreate::CCreate(CWnd* pParent /*=NULL*/)
	: CDialog(CCreate::IDD, pParent)
{

}

CCreate::~CCreate()
{
}

void CCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PARAMETER, m_lstParam);
	DDX_Control(pDX, IDC_EDIT_PARAMETER, m_edtParam);
	DDX_Control(pDX, IDC_EDIT_CONFIG_FILE_NAME, m_edtConfigFileName);
	DDX_Control(pDX, IDC_EDIT_CONFIG_TYPE, m_edtConfigType);
	DDX_Control(pDX, IDC_EDIT_BIN_PATH, m_edtBinPath);
}


BEGIN_MESSAGE_MAP(CCreate, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PARAMETER, &CCreate::OnNMClickListParameter)
	ON_BN_CLICKED(IDOK, &CCreate::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCreate::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCreate 訊息處理常式
BOOL CCreate::OnInitDialog()
{
	CDialog::OnInitDialog();

	LOGFONT lf;
	CFont EditFont;
	this->GetFont()->GetLogFont(&lf);
	::strcpy_s(lf.lfFaceName, "system");
	EditFont.CreateFontIndirect(&lf);

	this->m_lstParam.SetFont(&EditFont);
	this->m_edtParam.SetFont(&EditFont);

	this->m_lstParam.InsertColumn(0, _T("Parameter"), LVCFMT_LEFT, 200);
	this->m_lstParam.InsertColumn(1, _T("Content"), LVCFMT_LEFT, 200);

	this->m_lstParam.SetExtendedStyle(this->m_lstParam.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	WORD i;
	WORD wParamCount = this->srtStructParam.wItemAmount;
	for(i=0; i<wParamCount; i++)
	{
		this->m_lstParam.InsertItem(i, this->srtStructParam.srtItemParam[i].strName);
		this->m_lstParam.SetItemText(i, 1, this->srtStructParam.srtItemParam[i].strValue);
	}

	this->m_edtBinPath.SetWindowText(this->srtFlashMapping.strBinPath);
	this->m_edtConfigType.SetWindowText(this->strBoardType);

	this->boHaveEditCreate = FALSE;

	return TRUE;
}

void CCreate::OnNMClickListParameter(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	CString strInfo;
	if(this->boHaveEditCreate)
	{
		this->m_edtParam.GetWindowText(strInfo);
		this->m_lstParam.SetItemText(this->iPreItem, this->iPreSubItem, strInfo);
		this->m_edtParam.ShowWindow(FALSE);
	}
	if(pNMItemActivate->iSubItem == 1)
	{
		CRect  EditRect;
		
		this->iPreItem = pNMItemActivate->iItem;
		this->iPreSubItem = pNMItemActivate->iSubItem;

		strInfo = this->m_lstParam.GetItemText(this->iPreItem, this->iPreSubItem);

		this->m_edtParam.SetParent(&this->m_lstParam);
		this->m_lstParam.GetSubItemRect(this->iPreItem, this->iPreSubItem, LVIR_LABEL, EditRect);
		EditRect.SetRect(EditRect.left+1, EditRect.top+1, EditRect.left + this->m_lstParam.GetColumnWidth(this->iPreSubItem)-1, EditRect.bottom + 3);
		this->m_edtParam.SetWindowText(strInfo);
		this->m_edtParam.MoveWindow(&EditRect);
		this->m_edtParam.ShowWindow(SW_SHOW);
		this->m_edtParam.SetFocus();
		this->m_edtParam.SetSel(-1);

		this->boHaveEditCreate = TRUE;
	}
	*pResult = 0;
}

void CCreate::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CShareFunctions pShareFunctions;
	CString strBinPath, strConfigFileName, strConfigType;
	WORD wParamCount = this->srtStructParam.wItemAmount;
	CString strInfo;
	WORD i;
	int iFindStatus = 0;

	if(this->boHaveEditCreate)
	{
		this->m_edtParam.GetWindowText(strInfo);
		this->m_lstParam.SetItemText(this->iPreItem, this->iPreSubItem, strInfo);
	}

	this->m_edtBinPath.GetWindowText(strBinPath);
	this->m_edtConfigFileName.GetWindowText(strConfigFileName);
	this->m_edtConfigType.GetWindowText(strConfigType);
	
	for(i=0; i<wParamCount; i++)
	{
		strInfo = this->m_lstParam.GetItemText(i, 1);
		this->srtStructParam.srtItemParam[i].strValue = strInfo;
	}

	this->srtFlashMapping.strBinPath = strBinPath;
	this->srtOtherSetting.strConfigType = strConfigType;

	iFindStatus = strConfigFileName.Find("ini");
	if((iFindStatus < 0) || (iFindStatus == 0xFFFFFFFF))
		strConfigFileName = strConfigFileName + _T(".ini");

	pShareFunctions.SaveProductionParam(this->strRootDirectoryPath, this->srtFlashMapping.strBinPath, strConfigFileName, &this->srtStructParam, &this->srtSerialNumberParam, &this->srtFlashMapping, &this->srtQuickTestParam, &this->srtOtherSetting, TRUE);

	this->m_edtParam.ShowWindow(FALSE);

	OnOK();
}

void CCreate::OnBnClickedCancel()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->m_edtParam.ShowWindow(FALSE);
	OnCancel();
}
