// Password.cpp : ��@��
//

#include "stdafx.h"
#include "LibraMPTool.h"
#include "Password.h"


// Password ��ܤ��

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


// Password �T���B�z�`��

void Password::OnBnClickedOk()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CString strInfo;
	this->m_edtPassword.GetWindowText(strInfo);
	if(strInfo == _T("   "))
		*this->boPasswordState = TRUE;
	OnOK();
}
