// Password.cpp : 實作檔
//

#include "stdafx.h"
#include "LibraMPTool.h"
#include "Password.h"


// Password 對話方塊

IMPLEMENT_DYNAMIC(Password, CDialog)

Password::Password(CWnd* pParent /*=NULL*/)
	: CDialog(Password::IDD, pParent)
{

}

Password::~Password()
{
}

void Password::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edtPassword);
}


BEGIN_MESSAGE_MAP(Password, CDialog)
	ON_BN_CLICKED(IDOK, &Password::OnBnClickedOk)
END_MESSAGE_MAP()


// Password 訊息處理常式

void Password::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString strInfo;
	this->m_edtPassword.GetWindowText(strInfo);
	if(strInfo == _T("   "))
		*this->boPasswordState = TRUE;
	OnOK();
}
