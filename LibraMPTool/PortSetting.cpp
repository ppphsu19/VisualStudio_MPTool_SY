// PortSetting.cpp : 實作檔
//

#include "stdafx.h"
#include "LibraMPTool.h"
#include "PortSetting.h"


// PortSetting 對話方塊

IMPLEMENT_DYNAMIC(PortSetting, CDialog)

PortSetting::PortSetting(CWnd* pParent /*=NULL*/)
	: CDialog(PortSetting::IDD, pParent)
{

}

PortSetting::~PortSetting()
{
}

void PortSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SN_PORT_0, m_edtDisk[0]);
	DDX_Control(pDX, IDC_EDIT_SN_PORT_1, m_edtDisk[1]);
	DDX_Control(pDX, IDC_EDIT_SN_PORT_2, m_edtDisk[2]);
	DDX_Control(pDX, IDC_EDIT_SN_PORT_3, m_edtDisk[3]);
	DDX_Control(pDX, IDC_EDIT_SN_PORT_4, m_edtDisk[4]);
	DDX_Control(pDX, IDC_EDIT_SN_PORT_5, m_edtDisk[5]);
	DDX_Control(pDX, IDC_EDIT_SN_PORT_6, m_edtDisk[6]);
	DDX_Control(pDX, IDC_EDIT_SN_PORT_7, m_edtDisk[7]);
}


BEGIN_MESSAGE_MAP(PortSetting, CDialog)
	ON_BN_CLICKED(IDOK, &PortSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// PortSetting 訊息處理常式
BOOL PortSetting::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i;

	for(i=0; i<MP_MAX_DISKS; i++)
		this->m_edtDisk[i].SetWindowText(*this->strPortSN[i]);
	return TRUE;
}

void PortSetting::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	int i;

	for(i=0; i<MP_MAX_DISKS; i++)
		this->m_edtDisk[i].GetWindowText(*this->strPortSN[i]);

	OnOK();
}
