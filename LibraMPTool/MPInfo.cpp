// MPInfo.cpp : 實作檔
//

#include "stdafx.h"
#include "LibraMPTool.h"
#include "MPInfo.h"
#include <memory>

using namespace std;


// MPInfo 對話方塊
extern int iThreadCount;


IMPLEMENT_DYNAMIC(MPInfo, CDialog)

MPInfo::MPInfo(CWnd* pParent /*=NULL*/)
	: CDialog(MPInfo::IDD, pParent)
{
	int i;
	for(i=0; i<MP_MAX_DISKS; i++)
	{
		this->boDiskExist[i] = FALSE;
		this->iDiskPhysicalIndex[i] = -1;
		this->strDiskSN[i] = _T("");
	}
}

MPInfo::~MPInfo()
{
}

void MPInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnStart);

	DDX_Control(pDX, IDC_STATIC_SN_PORT_1, m_stcMPInfoSN[0]);
	DDX_Control(pDX, IDC_STATIC_SN_PORT_2, m_stcMPInfoSN[1]);
	DDX_Control(pDX, IDC_STATIC_SN_PORT_3, m_stcMPInfoSN[2]);
	DDX_Control(pDX, IDC_STATIC_SN_PORT_4, m_stcMPInfoSN[3]);
	DDX_Control(pDX, IDC_STATIC_SN_PORT_5, m_stcMPInfoSN[4]);
	DDX_Control(pDX, IDC_STATIC_SN_PORT_6, m_stcMPInfoSN[5]);
	DDX_Control(pDX, IDC_STATIC_SN_PORT_7, m_stcMPInfoSN[6]);
	DDX_Control(pDX, IDC_STATIC_SN_PORT_8, m_stcMPInfoSN[7]);

	DDX_Control(pDX, IDC_STATIC_PHYSICAL_ADDRESS_PORT_1, m_lblPhysicalAddress[0]);
	DDX_Control(pDX, IDC_STATIC_PHYSICAL_ADDRESS_PORT_2, m_lblPhysicalAddress[1]);
	DDX_Control(pDX, IDC_STATIC_PHYSICAL_ADDRESS_PORT_3, m_lblPhysicalAddress[2]);
	DDX_Control(pDX, IDC_STATIC_PHYSICAL_ADDRESS_PORT_4, m_lblPhysicalAddress[3]);
	DDX_Control(pDX, IDC_STATIC_PHYSICAL_ADDRESS_PORT_5, m_lblPhysicalAddress[4]);
	DDX_Control(pDX, IDC_STATIC_PHYSICAL_ADDRESS_PORT_6, m_lblPhysicalAddress[5]);
	DDX_Control(pDX, IDC_STATIC_PHYSICAL_ADDRESS_PORT_7, m_lblPhysicalAddress[6]);
	DDX_Control(pDX, IDC_STATIC_PHYSICAL_ADDRESS_PORT_8, m_lblPhysicalAddress[7]);

	DDX_Control(pDX, IDC_PROGRESS_PORT_1, m_pgsPort[0]);
	DDX_Control(pDX, IDC_PROGRESS_PORT_2, m_pgsPort[1]);
	DDX_Control(pDX, IDC_PROGRESS_PORT_3, m_pgsPort[2]);
	DDX_Control(pDX, IDC_PROGRESS_PORT_4, m_pgsPort[3]);
	DDX_Control(pDX, IDC_PROGRESS_PORT_5, m_pgsPort[4]);
	DDX_Control(pDX, IDC_PROGRESS_PORT_6, m_pgsPort[5]);
	DDX_Control(pDX, IDC_PROGRESS_PORT_7, m_pgsPort[6]);
	DDX_Control(pDX, IDC_PROGRESS_PORT_8, m_pgsPort[7]);

	DDX_Control(pDX, IDC_STATIC_INFO_PORT_1, m_lblInfo[0]);
	DDX_Control(pDX, IDC_STATIC_INFO_PORT_2, m_lblInfo[1]);
	DDX_Control(pDX, IDC_STATIC_INFO_PORT_3, m_lblInfo[2]);
	DDX_Control(pDX, IDC_STATIC_INFO_PORT_4, m_lblInfo[3]);
	DDX_Control(pDX, IDC_STATIC_INFO_PORT_5, m_lblInfo[4]);
	DDX_Control(pDX, IDC_STATIC_INFO_PORT_6, m_lblInfo[5]);
	DDX_Control(pDX, IDC_STATIC_INFO_PORT_7, m_lblInfo[6]);
	DDX_Control(pDX, IDC_STATIC_INFO_PORT_8, m_lblInfo[7]);

	DDX_Control(pDX, IDC_STATIC_TIMER_PORT_1, m_lblTime[0]);
	DDX_Control(pDX, IDC_STATIC_TIMER_PORT_2, m_lblTime[1]);
	DDX_Control(pDX, IDC_STATIC_TIMER_PORT_3, m_lblTime[2]);
	DDX_Control(pDX, IDC_STATIC_TIMER_PORT_4, m_lblTime[3]);
	DDX_Control(pDX, IDC_STATIC_TIMER_PORT_5, m_lblTime[4]);
	DDX_Control(pDX, IDC_STATIC_TIMER_PORT_6, m_lblTime[5]);
	DDX_Control(pDX, IDC_STATIC_TIMER_PORT_7, m_lblTime[6]);
	DDX_Control(pDX, IDC_STATIC_TIMER_PORT_8, m_lblTime[7]);
}


BEGIN_MESSAGE_MAP(MPInfo, CDialog)
	ON_BN_CLICKED(IDOK, &MPInfo::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC_PORT_1, &MPInfo::OnStnClickedStaticPort1)
	ON_STN_CLICKED(IDC_STATIC_PORT_2, &MPInfo::OnStnClickedStaticPort2)
	ON_STN_CLICKED(IDC_STATIC_PORT_3, &MPInfo::OnStnClickedStaticPort3)
	ON_STN_CLICKED(IDC_STATIC_PORT_4, &MPInfo::OnStnClickedStaticPort4)
	ON_STN_CLICKED(IDC_STATIC_PORT_5, &MPInfo::OnStnClickedStaticPort5)
	ON_STN_CLICKED(IDC_STATIC_PORT_6, &MPInfo::OnStnClickedStaticPort6)
	ON_STN_CLICKED(IDC_STATIC_PORT_7, &MPInfo::OnStnClickedStaticPort7)
	ON_STN_CLICKED(IDC_STATIC_PORT_8, &MPInfo::OnStnClickedStaticPort8)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// MPInfo 訊息處理常式
BOOL MPInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	int i;

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		this->dwTimer[i] = 0;
		this->m_pgsPort[i].SetBkColor(Progress_BK_Color);
		this->m_pgsPort[i].SetRange(0, 100);
		this->m_pgsPort[i].SetStep(1);
		this->m_lblPhysicalAddress[i].SetText(_T(""));
		this->m_lblInfo[i].SetFontSize(11);
	}
	this->RefreshDisplay();

	return TRUE;
}

void MPInfo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	int iPortIndex = nIDEvent;
	int iSecond[MP_MAX_DISKS], iMinute[MP_MAX_DISKS];
	CString strInfo[MP_MAX_DISKS];

	this->dwTimer[iPortIndex]++;
	iSecond[iPortIndex] = this->dwTimer[iPortIndex] % 60;
	iMinute[iPortIndex] = (this->dwTimer[iPortIndex] / 60) % 60;
	strInfo[iPortIndex].Format(_T("[%02d:%02d]"), iMinute[iPortIndex], iSecond[iPortIndex]);
	this->m_lblTime[iPortIndex].SetWindowText(strInfo[iPortIndex]);

	CDialog::OnTimer(nIDEvent);
}

void MPInfo::RefreshDisplay()
{
	int i;
	CString strInfo;

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		if(this->boDiskExist[i])
		{
			strInfo.Format(_T("(%d)"), this->iDiskPhysicalIndex[i]);
			this->m_lblPhysicalAddress[i].SetWindowText(strInfo);
			strInfo.Format(_T("%s"), this->strDiskSN[i]);
			this->m_stcMPInfoSN[i].ModifyStyle(0, SS_NOTIFY);
			this->m_stcMPInfoSN[i].SetWindowText(strInfo);
			this->m_stcMPInfoSN[i].EnableWindow(TRUE);
			this->strDiskSN[i].Trim();
			if(this->strDiskSN[i].IsEmpty())
				this->DoStaticPortFunc(i);

			this->m_lblFWMode[i]->GetWindowText(strInfo);
			if(strInfo == _T("NULL"))
				this->m_stcMPInfoSN[i].ModifyStyle(SS_NOTIFY, 0);
		}
		else
		{
			this->m_lblPhysicalAddress[i].SetWindowText(_T(""));
			strInfo.Format(_T("Port %d"), i+1);
			this->m_stcMPInfoSN[i].ModifyStyle(SS_NOTIFY, 0);
			this->m_stcMPInfoSN[i].SetWindowText(strInfo);
			this->m_stcMPInfoSN[i].EnableWindow(FALSE);
		}
		this->m_lblTime[i].SetText(_T(""));
		this->m_lblInfo[i].SetText(_T(""));
	}
}

void MPInfo::SetEnableWindow(BOOL boEnable)
{
	int i;

	this->m_btnExit->EnableWindow(boEnable);
	this->m_btnRescan->EnableWindow(boEnable);
	this->m_cmbConfigList->EnableWindow(boEnable);
	this->m_btnCreate->EnableWindow(boEnable);
	this->m_chkRDT->EnableWindow(boEnable);
	this->m_btnEdit->EnableWindow(boEnable);
	this->m_btnStart.EnableWindow(boEnable);

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		if(this->boDiskExist[i])
			this->m_chkDisk[i]->EnableWindow(boEnable);
		else
			this->m_chkDisk[i]->EnableWindow(FALSE);
	}
}

void MPInfo::SetModifyStyle(BOOL boEnable)
{
	int i;

	if(boEnable)
	{
		for(i=0; i<MP_MAX_DISKS; i++)
		{
			if(this->boDiskExist[i])
			{
				this->m_stcMPInfoSN[i].ModifyStyle(0, SS_NOTIFY);
				this->m_lblSN[i]->ModifyStyle(0, SS_NOTIFY);
				this->m_stcDisk[i]->ModifyStyle(0, SS_NOTIFY);
			}
			else
			{
				this->m_stcMPInfoSN[i].ModifyStyle(SS_NOTIFY, 0);
				this->m_lblSN[i]->ModifyStyle(SS_NOTIFY, 0);
				this->m_stcDisk[i]->ModifyStyle(SS_NOTIFY, 0);
			}
		}
	}
	else
	{
		for(i=0; i<MP_MAX_DISKS; i++)
		{
			this->m_stcMPInfoSN[i].ModifyStyle(SS_NOTIFY, 0);
			this->m_lblSN[i]->ModifyStyle(SS_NOTIFY, 0);
			this->m_stcDisk[i]->ModifyStyle(SS_NOTIFY, 0);
		}
	}
}

void MPInfo::CleanInfoDisplay()
{
	int i;

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		this->m_lblTime[i].SetWindowText(_T(""));
		this->m_lblInfo[i].SetText(_T(""));
	}
}

void MPInfo::ResetSN(int iDiskIndex)
{
	CString strInfo;
	int iSNCount;
	int iStatus;

	iSNCount = this->srtSerialNumberParam->strBeginSN.GetLength();
	strInfo.Format(_T("%d"), this->srtSNInfo->ui64CurrentSN);
	iStatus = strInfo.GetLength();
	this->strMPSN[iDiskIndex]->Format(_T("%s%s"), this->srtSerialNumberParam->strBeginSN.Left(iSNCount - iStatus), strInfo);

	this->srtSNInfo->ui64CurrentSN++;
	if(this->srtSNInfo->ui64CurrentSN > this->srtSNInfo->ui64EndSN)
		this->srtSNInfo->ui64CurrentSN = this->srtSNInfo->ui64BeginSN;
	this->srtSerialNumberParam->dwSNResetCount++;
}

void MPInfo::DoStaticPortFunc(int iSelectIndex)
{
	if(this->srtSerialNumberParam->bSNRule == 0)
	{
		if(!this->boResetState[*this->iPort2Disk[iSelectIndex]])
		{
			this->ResetSN(*this->iPort2Disk[iSelectIndex]);
			this->strDiskSN[iSelectIndex] = *this->strMPSN[*this->iPort2Disk[iSelectIndex]];
			this->m_stcMPInfoSN[iSelectIndex].SetWindowText(this->strDiskSN[iSelectIndex]);
			this->boResetState[*this->iPort2Disk[iSelectIndex]] = TRUE;
		}
	}
}

void MPInfo::ConfirmCapacityLBN(int iUserChannel, int iUserBank)
{
	CShareFunctions pShareFunctions;
	WORD wItemCount = this->srtStructParam->wItemAmount;
	WORD i;
	CString strItemName;
	int iDiskCapacityGB = 0;
	unsigned __int64 ui64LBNValue = 0;
	CString strInfo;

	for(i=0; i<wItemCount; i++)
	{
		strItemName.Format(_T("%s"), this->srtStructParam->srtItemParam[i].strName.GetString());
		if((strItemName == _T("NVMe_Drv_Total_Capacity_LBN")) || (strItemName == _T("NVMe_LBN_Num")))
		{
			iDiskCapacityGB = pShareFunctions.GetDiskCapacity(iUserChannel, iUserBank, this->srtFlashMapping->bLunPerTarget, this->srtFlashMapping->wDieCapacityGb);
			ui64LBNValue = pShareFunctions.GetLBNValue(iDiskCapacityGB);
			strInfo.Format(_T("%I64d"), ui64LBNValue);
			this->srtStructParam->srtItemParam[i].strValue = strInfo;
		}
	}
}

BOOL MPInfo::CheckBoardInfoFunc()
{
	BOOL boRtnStatus = TRUE;
	int j;
	BOOL boMultiFlag = FALSE;
	int iBaseInfo = -1;
	int iMPCount = 0;
	CString strBoardInfo[MP_MAX_DISKS];
	CString strInfo;
	int iConfigChannel = 0;
	int iConfigBank = 0;

	CString strItemName;
	WORD wItemCount = this->srtStructParam->wItemAmount;
	WORD i;

	for(i=0; i<wItemCount; i++)
	{
		strItemName.Format(_T("%s"), this->srtStructParam->srtItemParam[i].strName.GetString());
		if((strItemName == _T("Nand_Channel_Num")) || (strItemName == _T("RdtProductCfg_Nand_Channel_Num")))
			iConfigChannel = ::atoi(this->srtStructParam->srtItemParam[i].strValue);
		if((strItemName == _T("Nand_Bank_Num")) || (strItemName == _T("RdtProductCfg_Nand_Bank_Num")))
			iConfigBank = ::atoi(this->srtStructParam->srtItemParam[i].strValue);
	}

	for(i=0; i<MP_MAX_DISKS; i++)
	{
		strBoardInfo[i] = _T("");
		if(this->m_chkDisk[i]->GetCheck())
		{
			strBoardInfo[iMPCount].Format(_T("Port %d - Channel: %d, Bank: %d, Flash ID: 0x%02X0x%02X0x%02X0x%02X0x%02X0x%02X0x%02X0x%02X"),
				i + 1, this->srtBoardInfo[i].iChannelNum, this->srtBoardInfo[i].iBankNum,
				this->srtBoardInfo[i].bFlashID[0], this->srtBoardInfo[i].bFlashID[1], this->srtBoardInfo[i].bFlashID[2], this->srtBoardInfo[i].bFlashID[3],
				this->srtBoardInfo[i].bFlashID[4], this->srtBoardInfo[i].bFlashID[5], this->srtBoardInfo[i].bFlashID[6], this->srtBoardInfo[i].bFlashID[7]);
			iMPCount++;
			if(!boMultiFlag)
			{
				boMultiFlag = TRUE;
				iBaseInfo = i;
				if(this->srtSystemParam->bEpoStar == 77)
				{
				}
				else
				{
					if(this->srtBoardInfo[i].iChannelNum != iConfigChannel)
					{
						boRtnStatus = FALSE;
						continue;
					}
					if(this->srtBoardInfo[i].iBankNum != iConfigBank)
					{
						boRtnStatus = FALSE;
						continue;
					}
				}
			}
			else
			{
				if(this->srtSystemParam->bEpoStar == 77)
				{
				}
				else
				{
					if(this->srtBoardInfo[i].iChannelNum != iConfigChannel)
					{
						boRtnStatus = FALSE;
						continue;
					}
					if(this->srtBoardInfo[i].iBankNum != iConfigBank)
					{
						boRtnStatus = FALSE;
						continue;
					}
				}
				for(j=0; j<8; j++)
				{
					if(this->srtBoardInfo[i].bFlashID[j] != this->srtBoardInfo[iBaseInfo].bFlashID[j])
					{
						boRtnStatus = FALSE;
						break;
					}
				}
			}
		}
	}
	if(!boRtnStatus)
	{
		strInfo.Format(_T("Check board info fail!!!\n\nConfig - Channel: %d, Bank: %d"), iConfigChannel, iConfigBank);
		for(i=0; i<iMPCount; i++)
			strInfo = strInfo+ _T("\n") + strBoardInfo[i];
		::AfxMessageBox(strInfo);
	}
	else
	{
		if(this->srtOtherSetting->bCapacityMethod == 0)
			this->ConfirmCapacityLBN(iConfigChannel, iConfigBank);
	}
	return boRtnStatus;
}

DWORD MPInfo::Thread_MPProcess(LPVOID pParam)
{
	MPInfo* pDlg = (MPInfo*)pParam;
	MP_THREAD_PARAM srtMPThreadParam[MP_MAX_DISKS];
	CMPCmd* pMPCmd;
	CShareFunctions pShareFunctions;
	int i;
	CString strInfo;
	BOOL boMPRunning = FALSE;
	BOOL boStatus = FALSE;

	std::unique_ptr<CMPCmd> cmd = pDlg->m_chkRDT->GetCheck() ? std::make_unique<CMPCmdRDT>() : std::make_unique<CMPCmd>();
	pMPCmd = cmd.get();

	pDlg->SetEnableWindow(FALSE);
	pDlg->SetModifyStyle(FALSE);
	pDlg->CleanInfoDisplay();

	pDlg->m_cmbConfigList->GetWindowText(strInfo);
	pDlg->srtSystemParam->strConfigFile = strInfo;

	pMPCmd->SetFilePath(*pDlg->strRootDirectoryPath, pDlg->srtFlashMapping->strBinPath);
	strInfo.Format(_T("Check image ..."));
	pMPCmd->WriteLog(strInfo, pMPCmd->strLogFilePath, FALSE);
	boStatus = pMPCmd->CheckImage(&strInfo);
	if(boStatus)
	{
		strInfo.Format(_T("Check image finish"));
		pMPCmd->WriteLog(strInfo, pMPCmd->strLogFilePath, FALSE);
		//check multi port board info
		strInfo.Format(_T("Check board info ..."));
		pMPCmd->WriteLog(strInfo, pMPCmd->strLogFilePath, FALSE);
		boStatus = pDlg->CheckBoardInfoFunc();
		if(boStatus)
		{
			strInfo.Format(_T("Check board info finish"));
			pMPCmd->WriteLog(strInfo, pMPCmd->strLogFilePath, FALSE);

			iThreadCount = 0;
			for(i=0; i<MP_MAX_DISKS; i++)
			{
				if(pDlg->m_chkDisk[i]->GetCheck())
				{
					boMPRunning = TRUE;
					pDlg->dwTimer[i] = 0;
					srtMPThreadParam[i].hWndMPInfo = pDlg->GetSafeHwnd();
					srtMPThreadParam[i].iPortIndex = i;
					srtMPThreadParam[i].iDiskPhysicalIndex = pDlg->iDiskPhysicalIndex[i];
					srtMPThreadParam[i].bDiskBusType = pDlg->bDiskBusType[i];
					srtMPThreadParam[i].boPartitionFlag = pDlg->boPartitionMode[i];
					srtMPThreadParam[i].pCmdClass = (LPVOID)pMPCmd;
					srtMPThreadParam[i].m_lblInfo = &pDlg->m_lblInfo[i];
					srtMPThreadParam[i].m_pgsPort = &pDlg->m_pgsPort[i];
					srtMPThreadParam[i].m_lblFWMode = pDlg->m_lblFWMode[i];
					srtMPThreadParam[i].srtStructParam = pDlg->srtStructParam;
					srtMPThreadParam[i].srtQuickTestParam = pDlg->srtQuickTestParam;
					pDlg->m_stcMPInfoSN[i].GetWindowText(strInfo);
					srtMPThreadParam[i].strMPSN = strInfo;
					srtMPThreadParam[i].dwSNPassCount = &pDlg->srtSerialNumberParam->dwSNPassCount;
					srtMPThreadParam[i].dwSNFailCount = &pDlg->srtSerialNumberParam->dwSNFailCount;
					srtMPThreadParam[i].boForceErase = pDlg->srtOtherSetting->boForceErase;
					srtMPThreadParam[i].bQuickTest = pDlg->srtOtherSetting->bQuickTest;
					AfxBeginThread(Thread_MPFlowFunc, &srtMPThreadParam[i]);
					iThreadCount++;
				}
			}
			while(boMPRunning)
			{
				::Sleep(500);
				if(iThreadCount == 0)
					break;
			}
			pShareFunctions.ShowTestResult(pDlg->srtSerialNumberParam, pDlg->m_lblTestResult);
			pShareFunctions.SaveSysIniFile(*pDlg->strRootDirectoryPath, pDlg->srtSystemParam);
			pShareFunctions.SaveProductionParam(*pDlg->strRootDirectoryPath, pDlg->srtFlashMapping->strBinPath, pDlg->srtSystemParam->strConfigFile, pDlg->srtStructParam, pDlg->srtSerialNumberParam, pDlg->srtFlashMapping, pDlg->srtQuickTestParam, pDlg->srtOtherSetting, FALSE);
		}
	}
	else
		::AfxMessageBox(strInfo, MB_OK);

	pDlg->SetModifyStyle(TRUE);
	pDlg->SetEnableWindow(TRUE);

	return 0;
}

void MPInfo::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	//OnOK();
	AfxBeginThread((AFX_THREADPROC)Thread_MPProcess, this);
}

void MPInfo::OnStnClickedStaticPort1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticPortFunc(0);
}

void MPInfo::OnStnClickedStaticPort2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticPortFunc(1);
}

void MPInfo::OnStnClickedStaticPort3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticPortFunc(2);
}

void MPInfo::OnStnClickedStaticPort4()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticPortFunc(3);
}

void MPInfo::OnStnClickedStaticPort5()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticPortFunc(4);
}

void MPInfo::OnStnClickedStaticPort6()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticPortFunc(5);
}

void MPInfo::OnStnClickedStaticPort7()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticPortFunc(6);
}

void MPInfo::OnStnClickedStaticPort8()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	this->DoStaticPortFunc(7);
}
