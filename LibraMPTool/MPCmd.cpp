#include "stdafx.h"
#include "MPCmd.h"

//#define SLEEP_REPLACE_GET_STATUS

int iThreadCount;

BOOL CMPCmd::SendAPKeyCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x00;
	//this->srtCommandSet.dw13 = 0x1D890280;//Libra Key
	this->srtCommandSet.dw13 = 0x4A455349;//Libra Super Key
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendEraseScanCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x01;
	this->srtCommandSet.dw15 = 0x0000 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendFactoryScanCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x01;
	this->srtCommandSet.dw15 = 0x0001 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendRunDownloadImageCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x02;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendProgramSBLCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x03;
	this->srtCommandSet.dw15 = 0x0000 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendProgramFWCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x03;
	this->srtCommandSet.dw15 = 0x0001 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendCheckCapacityCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x04;
	this->srtCommandSet.dw15 = 0x0000 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendPreserveBBTandErCntInfo(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x04;
	this->srtCommandSet.dw15 = 0x0001 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendDDRTestCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x04;
	this->srtCommandSet.dw15 = 0x0002 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendFlashRWTestCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x04;
	this->srtCommandSet.dw15 = 0x0003 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendSPIRWTestCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x04;
	this->srtCommandSet.dw15 = 0x0004 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = 30;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendThermalSensorTestCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x04;
	this->srtCommandSet.dw15 = 0x0005 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendCheckEfuseTestCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x04;
	this->srtCommandSet.dw15 = 0x0006 << 16;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendJump2ROMModeCmd(HANDLE hDevice, int iSelectMode, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0xF0;
	this->srtCommandSet.dw13 = iSelectMode;//0: MP mode, 1: Loader Mode
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendIDPageEraseCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x05;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendPreserveRDTCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC0;
	this->srtCommandSet.dw12 = 0x05;
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendDownloadImageCmd(HANDLE hDevice, BYTE b64KBIndex, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC1;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = (b64KBIndex << 16) + 0x00;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_OUT;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendSetProductParamCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC1;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = 0x01;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_OUT;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendGetBoardInfoCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC2;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = 0x00;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendGetProgressStatusCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC2;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = 0x01;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendGetBadBlockTableCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC2;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = 0x02;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dw15 = 0x0000 << 16;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendGetCapacityCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC2;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = 0x02;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dw15 = 0x0001 << 16;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendGetFlashIDCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC2;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = 0xF0;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendScanFlashIDCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC2;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = 0xF1;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendGetFWModeCmd(HANDLE hDevice, BYTE* bFWMode, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;
	DWORD dwLength = 4096;
	BYTE bDataBuf[4096] = {0};

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC2;
	this->srtCommandSet.dw10 = dwLength/4;
	this->srtCommandSet.dw12 = 0xF2;
	this->srtCommandSet.dw13 = dwLength;
	this->srtCommandSet.dwDataLength = dwLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);
	if(boRtnStatus)
		*bFWMode = bDataBuf[0];//1: ROM, 2: Burner, 3: RDT, 4: System

	return boRtnStatus;
}

BOOL CMPCmd::SendGetErrorCodeAndStatusCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC2;
	this->srtCommandSet.dw10 = dwDataLength/4;
	this->srtCommandSet.dw12 = 0x03;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendPowerOffCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.bVendorControl = PCIE_POWER_OFF;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::SendPowerOnCmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.bVendorControl = PCIE_POWER_ON;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);
	
	return boRtnStatus;
}

BOOL CMPCmd::SendResetBy583Cmd(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
	this->srtCommandSet.bVendorControl = INITIAL_PCIE_PRSTN_BY_583;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, NULL, bBusType);

	return boRtnStatus;
}

void CMPCmd::SetFilePath(CString strRootDirectoryPath, CString strBinPath)
{
	CTime ctCurrent;
	CString strLogFolder;
	CString strBinFolder;
	CString strInfo;

	this->strRootDirectoryPath = strRootDirectoryPath;

	//log folder
	strLogFolder.Format(_T("%s\\%s"), strRootDirectoryPath, LogFolderName);
	::CreateDirectory(strLogFolder, NULL);
	//bin folder
	strBinFolder.Format(_T("%s\\%s\\%s"), strRootDirectoryPath, BinFolderName, strBinPath);
	//::CreateDirectory(strBinFolder, NULL);
	//log file path
	ctCurrent = CTime::GetCurrentTime();
	strInfo.Format(_T("%s\\%04d%02d%02d"), strLogFolder, ctCurrent.GetYear(), ctCurrent.GetMonth(), ctCurrent.GetDay());
	::CreateDirectory(strInfo, NULL);
	this->strLogFilePath.Format(_T("%s\\MP_%02d%02d%02d.log"), strInfo, ctCurrent.GetHour(), ctCurrent.GetMinute(), ctCurrent.GetSecond());
	//bin file path
	this->strBurnerPath.Format(_T("%s\\libra_cpu0_burner_pkg.bin"), strBinFolder);
	//this->strRDTPath.Format(_T("%s\\libra_cpu0_rdt_pkg.bin"), strBinFolder);
	this->strSBLPath.Format(_T("%s\\libra_cpu0_sbl_pkg.bin"), strBinFolder);
	this->strSYSPath.Format(_T("%s\\libra_cpu01_sysfw.bin"), strBinFolder);
	this->strRDTPath.Format(_T("%s\\libra_cpu0_rdt_pkg.bin"), strBinFolder);
	//clean log file
	this->WriteLog(_T(""), this->strLogFilePath, TRUE);
}

BOOL CMPCmd::CheckImage(CString* strErrorMsg)
{
	BOOL boRtnStatus = FALSE;
	CStdioFile stdFile;

	this->WriteLog(this->strBurnerPath, this->strLogFilePath, FALSE);
	this->WriteLog(this->strSBLPath, this->strLogFilePath, FALSE);
//	this->WriteLog(this->strRDTPath, this->strLogFilePath, FASLE);
	this->WriteLog(this->strSYSPath, this->strLogFilePath, FALSE);

	boRtnStatus = stdFile.Open(this->strBurnerPath, CFile::modeRead);
	if(boRtnStatus)
		stdFile.Close();
	else
	{
		strErrorMsg->Format(_T("Bunner bin file is error"));
		this->WriteLog(*strErrorMsg, this->strLogFilePath, FALSE);
		return boRtnStatus;
	}
	boRtnStatus = stdFile.Open(this->strSBLPath, CFile::modeRead);
	if(boRtnStatus)
		stdFile.Close();
	else
	{
		strErrorMsg->Format(_T("SBL bin file is error"));
		this->WriteLog(*strErrorMsg, this->strLogFilePath, FALSE);
		return boRtnStatus;
	}
//	boRtnStatus = stdFile.Open(this->strRDTPath, CFile::modeRead);
//	if(boRtnStatus)
//		stdFile.Close();
//	else
//	{
//		strErrorMsg->Format(_T("RDT bin file is error"));
//		this->WriteLog(*strErrorMsg, this->strLogFilePath, FALSE);
//		return boRtnStatus;
//	}
	boRtnStatus = stdFile.Open(this->strSYSPath, CFile::modeRead);
	if(boRtnStatus)
		stdFile.Close();
	else
	{
		strErrorMsg->Format(_T("FW bin file is error"));
		this->WriteLog(*strErrorMsg, this->strLogFilePath, FALSE);
		return boRtnStatus;
	}

	return boRtnStatus;
}

void CMPCmd::SetMPMsg(int iPortIndex, CString strMsg, CLabel* lblInfo, CTextProgressCtrl* pgsPort)
{
	int iProgress = 0;
	CString strLogInfo;

	strLogInfo.Format(_T("%d, %s"), iPortIndex + 1, strMsg);
	this->WriteLog(strLogInfo, this->strLogFilePath, FALSE);
	if(lblInfo != NULL)
		lblInfo->SetText(strMsg);
	if(pgsPort != NULL)
	{
		this->iCmdCurrent[iPortIndex]++;
		iProgress = (int)((float)this->iCmdCurrent[iPortIndex] / this->iCmdAmount[iPortIndex] * 100.00);
		pgsPort->SetPos(iProgress);
	}
}

BOOL CMPCmd::WaitAPProcessDone(int iPortIndex, int iTimeoutSecond, CLabel* lblInfo)
{
	BOOL boStatus = TRUE;
	CString strInfo;
	CTime StartTime, EndTime;
	CTimeSpan ts;

	StartTime = CTime::GetCurrentTime();
	while(1)
	{
		boStatus = this->CheckAPProcess(PARTITION_AP);
		if(boStatus == FALSE)
			break;
		EndTime = CTime::GetCurrentTime();
		ts = EndTime - StartTime;
		if(ts.GetTotalSeconds() >= iTimeoutSecond)
		{
			StartTime = CTime::GetCurrentTime();
			strInfo.Format("Wait delete partition over %ds", iTimeoutSecond);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			break;
		}
	}
	return !boStatus;
}

BOOL CMPCmd::DeletePartitionFunc(int iPortIndex, int iPhysicalIndex, int iTimeoutSecond, CLabel* lblInfo)
{
	BOOL boRtnStatus = FALSE;
	CString strInfo;

	strInfo.Format(_T("Start Delete Partition..."));
	this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);

	this->RunDeletePartitionSetupFunc(iPhysicalIndex);
	::Sleep(1000);
	boRtnStatus = this->WaitAPProcessDone(iPortIndex, iTimeoutSecond, lblInfo);
	if(boRtnStatus)
	{
		strInfo.Format(_T("Delete partition is done!!!"));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
	}
	return boRtnStatus;
}

BOOL CMPCmd::GetFlashIDFunc(HANDLE hDevice, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;
	DWORD dwDataLength = FIX_FLASH_ID_LENGTH;
	BYTE bFlashIDBuf[FIX_FLASH_ID_LENGTH] = {0};
	BYTE bFlashID[8] = {0};
	BYTE bChannelROM = 0;
	BYTE bBankROM = 0;
	int i, j;
	CString strInfo;

	boRtnStatus = this->SendScanFlashIDCmd(hDevice, dwDataLength, bFlashIDBuf, bBusType);
	if(boRtnStatus)
	{
		::memcpy(bFlashID, bFlashIDBuf, 8);
		strInfo.Format(_T("ch=%d, ce=%d, ID=0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X"),
			bChannelROM, bBankROM, bFlashID[0], bFlashID[1], bFlashID[2], bFlashID[3], bFlashID[4], bFlashID[5]);
		this->WriteLog(strInfo, this->strLogFilePath, FALSE);
		bChannelROM = 1;
		bBankROM = 1;
		for(i=0; i<8; i++)
		{
			for(j=0; j<8; j++)
			{
				if((i == 0) && (j == 0))
					continue;
				if(bFlashIDBuf[i*64+j*8] != bFlashIDBuf[0])
					continue;
				if(bFlashIDBuf[i*64+j*8+1] != bFlashIDBuf[1])
					continue;
				if(bFlashIDBuf[i*64+j*8+2] != bFlashIDBuf[2])
					continue;
				if(bFlashIDBuf[i*64+j*8+3] != bFlashIDBuf[3])
					continue;
				if(bFlashIDBuf[i*64+j*8+4] != bFlashIDBuf[4])
					continue;
				if(bFlashIDBuf[i*64+j*8+5] != bFlashIDBuf[5])
					continue;
				strInfo.Format(_T("ch=%d, ce=%d, ID=0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X"),
					i, j, bFlashID[i*64+j*8], bFlashID[i*64+j*8+1], bFlashID[i*64+j*8+2], bFlashID[i*64+j*8+3], bFlashID[i*64+j*8+4], bFlashID[i*64+j*8+5]);
				this->WriteLog(strInfo, this->strLogFilePath, FALSE);
				if(j == 0)
					bChannelROM++;
				if(i == 0)
					bBankROM++;
			}
		}
	}
	return boRtnStatus;
}

BOOL CMPCmd::DownloadImageFunc(HANDLE hDevice, CString strFilePath, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;
	int iStatus;
	struct _stat sInfo;
	HANDLE hFile;
	DWORD dwRead;
	DWORD dwFileSize = 0;
	int iCmdCount = 0;
	DWORD dwDataLength;
	int i;

	iStatus = _stat(strFilePath, &sInfo);
	if(iStatus == 0)
	{
		dwFileSize = sInfo.st_size;
		hFile = ::CreateFile(strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile != INVALID_HANDLE_VALUE)    
		{
			this->bImageBuf = (BYTE *)::malloc((size_t)dwFileSize);
			if(this->bImageBuf != NULL)
			{
				::SetFilePointer(hFile, 0 , NULL, FILE_BEGIN);
				boRtnStatus = ::ReadFile(hFile, this->bImageBuf, dwFileSize, &dwRead, NULL);
				::CloseHandle(hFile);
			}
		}
	}
	if(boRtnStatus)
	{
		iCmdCount = dwFileSize / DOWNLOAD_IMAGE_MAX_LENGTH;
		if((dwFileSize % DOWNLOAD_IMAGE_MAX_LENGTH) != 0)
			iCmdCount++;
		for(i=0; i<iCmdCount; i++)
		{
			if((DWORD)((i * DOWNLOAD_IMAGE_MAX_LENGTH) + DOWNLOAD_IMAGE_MAX_LENGTH) > dwFileSize)
				dwDataLength = dwFileSize - (i * DOWNLOAD_IMAGE_MAX_LENGTH);
			else
				dwDataLength = DOWNLOAD_IMAGE_MAX_LENGTH;
			this->SendDownloadImageCmd(hDevice, i, dwDataLength, this->bImageBuf + (i * DOWNLOAD_IMAGE_MAX_LENGTH), bBusType);
		}
		::free(this->bImageBuf);
	}
	return boRtnStatus;
}

BOOL CMPCmd::SetProductParamFunc(HANDLE hDevice, CString strSN, STRUCT_PARAM* srtParam, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;
	BYTE bParamBuf[FIX_DATA_LENGTH] = {};
	BYTE bTmpBuf[112] = {};
	CTime ctCurrent;
	CString strItemName;
	WORD wItemCount = srtParam->wItemAmount;
	WORD i, j;
	CString strTmp;

	ctCurrent = CTime::GetCurrentTime();
	for(i=0; i<wItemCount; i++)
	{
		strItemName.Format(_T("%s"), srtParam->srtItemParam[i].strName);
		if(strItemName == _T("Sys_MP_Time_YY"))
			srtParam->srtItemParam[i].strValue.Format(_T("%d"), ctCurrent.GetYear());
		//if(strItemName == _T("Sys_MP_Time_MM"))
		//	srtParam->srtItemParam[i].strValue.Format(_T("%d"), ctCurrent.GetMonth());
		//if(strItemName == _T("Sys_MP_Time_DD"))
		//	srtParam->srtItemParam[i].strValue.Format(_T("%d"), ctCurrent.GetDay());
		//if(strItemName == _T("Sys_MP_Version_Major"))
		//	srtParam->srtItemParam[i].strValue.Format(_T("%d"), MP_MAJOR_VERSION);
		//if(strItemName == _T("Sys_MP_Version_Minor"))
		//	srtParam->srtItemParam[i].strValue.Format(_T("%d"), MP_MINOR_VERSION);
		//if(strItemName == _T("NVMe_Serial_Num"))
		//	srtParam->srtItemParam[i].strValue = strSN;

		::memset(bTmpBuf, 0, sizeof(bTmpBuf));
		if(srtParam->srtItemParam[i].boType)
			::memcpy(bTmpBuf, srtParam->srtItemParam[i].strValue, srtParam->srtItemParam[i].strValue.GetLength());
		else
			this->GetStrValueFunc(srtParam->srtItemParam[i].strValue, ',', srtParam->srtItemParam[i].bLength, bTmpBuf);
		for(j=0; j<srtParam->srtItemParam[i].bLength; j++)
			bParamBuf[srtParam->srtItemParam[i].wOffset + j] = bTmpBuf[j];
	}

	boRtnStatus = this->SendSetProductParamCmd(hDevice, FIX_DATA_LENGTH, bParamBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmd::GetProgressStatusFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType,  int iTimeoutSeconds, CLabel* lblInfo)
{
	BOOL boRtnStatus = FALSE;
	BYTE bStatusBuf[FIX_DATA_LENGTH] = {0};
	CTime StartTime, EndTime;
	CTimeSpan ts;
	CString strInfo;

	StartTime = CTime::GetCurrentTime();
	while(1)
	{
		::memset(bStatusBuf, 0, sizeof(bStatusBuf));
		boRtnStatus = this->SendGetProgressStatusCmd(hDevice, FIX_DATA_LENGTH, bStatusBuf, bBusType);
		if(boRtnStatus)
		{
			if(bStatusBuf[0] == 100)
				break;
		}
		else
			break;
		EndTime = CTime::GetCurrentTime();
		ts = EndTime - StartTime;
		if(ts.GetTotalSeconds() >= iTimeoutSeconds)
		{
			boRtnStatus = FALSE;
			strInfo.Format(_T("Check progress status timout over %ds"), iTimeoutSeconds);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			break;
		}
		::Sleep(500);
	}

	return boRtnStatus;
}

BOOL CMPCmd::CheckDiskReady(HANDLE hDevice, BYTE bBusType, int iTimeoutSeconds)
{
	BOOL boRtnStatus = FALSE;
	CTime StartTime, EndTime;
	CTimeSpan ts;
	BYTE bDataBuf[4096] = {0};
	DWORD dwBytesRead;

	::SetFilePointer(hDevice, 0, NULL, FILE_BEGIN);
	StartTime = CTime::GetCurrentTime();
	while(1)
	{
		boRtnStatus = ::ReadFile(hDevice, bDataBuf, 4096, &dwBytesRead, NULL);
		if(boRtnStatus)
			break;
		EndTime = CTime::GetCurrentTime();
		ts = EndTime - StartTime;
		if(ts.GetTotalSeconds() >= iTimeoutSeconds)
			break;
		::Sleep(1000);
	}

	return boRtnStatus;
}

BOOL CMPCmd::DoSysMode2RomModeFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort)
{
	BOOL boRtnStatus = TRUE;
	CString strInfo, strLogInfo;
	BYTE bFWMode;

	//ID Page Erase
	if(boRtnStatus)
	{
		strInfo.Format(_T("ID page erase ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendIDPageEraseCmd(hDevice, bBusType);
		strInfo.Format(_T("ID page erase %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Power Off
	if(boRtnStatus)
	{
		strInfo.Format(_T("Power off ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendPowerOffCmd(hDevice, bBusType);
		strInfo.Format(_T("Power off %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Delay 2s
	if(boRtnStatus)
		::Sleep(2*1000);
	//Reset by 583
	if(boRtnStatus)
	{
		strInfo.Format(_T("PCIE_PRSTN ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendResetBy583Cmd(hDevice, bBusType);
		strInfo.Format(_T("PCIE_PRSTN %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Delay 3s
	if(boRtnStatus)
		::Sleep(3*1000);
	////check if rom mode
	if(boRtnStatus)
	{
		strInfo.Format(_T("Check ROM code ready ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->CheckDiskReady(hDevice, bBusType, TIMEOUT_CHECK_CHANGE_MODE);
		strInfo.Format(_T("Check ROM code %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//AP Key - ROM
	if(boRtnStatus)
	{
		strInfo.Format(_T("AP Key check ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendAPKeyCmd(hDevice, bBusType);
		strInfo.Format(_T("AP Key check %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Get FW Mode
	if(boRtnStatus)
	{
		strInfo.Format(_T("Get FW mode - ROM ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendGetFWModeCmd(hDevice, &bFWMode, bBusType);
		if(boRtnStatus)
		{
			strInfo.Format(_T("%s"), this->strFWState[bFWMode - 1]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			if(bFWMode != FW_MODE_ROM)
				return FALSE;
		}
		strInfo.Format(_T("Get FW mode %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Get Error Code and Status
	if(!boRtnStatus)
	{
		DWORD dwECESLength = 4096;
		BYTE bECESBuf[4096] = {0};
		BOOL boECESStatus = FALSE;
		CString strTmp;
		lblInfo->GetWindowText(strTmp);
		boECESStatus = this->SendGetErrorCodeAndStatusCmd(hDevice, dwECESLength, bECESBuf, bBusType);
		if(boECESStatus)
			strInfo.Format(_T("(EC: 0x%02X%02X%02X%02X, ES: 0x%02X%02X%02X%02X)"), bECESBuf[3], bECESBuf[2], bECESBuf[1], bECESBuf[0], bECESBuf[7], bECESBuf[6], bECESBuf[5], bECESBuf[4]);
		else
			strInfo.Format(_T("(Get error status failed!)"));
		strInfo = strTmp + strInfo;
		lblInfo->SetText(strInfo);
	}

	return boRtnStatus;
}

BOOL CMPCmd::DoRomMode2BnrModeFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort)
{
	BOOL boRtnStatus = TRUE;
	CString strInfo;
	BYTE bFWMode;
	CSemaphore mutex;

	CSingleLock wait(&mutex);

	//AP Key - BNR
	if (boRtnStatus)
	{
		strInfo.Format(_T("AP Key check ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendAPKeyCmd(hDevice, bBusType);
		strInfo.Format(_T("AP Key check %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}

	//Download Image - Burner
	if(boRtnStatus)
	{
		wait.Lock(INFINITE);
		strInfo.Format(_T("Send burner bin file ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->DownloadImageFunc(hDevice, this->strBurnerPath, bBusType);
		wait.Unlock();
		strInfo.Format(_T("Write burner bin file %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Run Image - Burner
	if(boRtnStatus)
	{
		strInfo.Format(_T("Wait burner ready ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendRunDownloadImageCmd(hDevice, bBusType);
		strInfo.Format(_T("Jump burner %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	////check if burner mode
	//AP Key - BNR
	if(boRtnStatus)
	{
		strInfo.Format(_T("AP Key check ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendAPKeyCmd(hDevice, bBusType);
		strInfo.Format(_T("AP Key check %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Get FW Mode
	if(boRtnStatus)
	{
		strInfo.Format(_T("Get FW mode - Burner ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendGetFWModeCmd(hDevice, &bFWMode, bBusType);
		if(boRtnStatus)
		{
			strInfo.Format(_T("%s"), this->strFWState[bFWMode - 1]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			if(bFWMode != FW_MODE_BNR)
				return FALSE;
		}
		strInfo.Format(_T("Get FW mode %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Get Error Code and Status
	if(!boRtnStatus)
	{
		DWORD dwECESLength = 4096;
		BYTE bECESBuf[4096] = {0};
		BOOL boECESStatus = FALSE;
		CString strTmp;
		lblInfo->GetWindowText(strTmp);
		boECESStatus = this->SendGetErrorCodeAndStatusCmd(hDevice, dwECESLength, bECESBuf, bBusType);
		if(boECESStatus)
			strInfo.Format(_T("(EC: 0x%02X%02X%02X%02X, ES: 0x%02X%02X%02X%02X)"), bECESBuf[3], bECESBuf[2], bECESBuf[1], bECESBuf[0], bECESBuf[7], bECESBuf[6], bECESBuf[5], bECESBuf[4]);
		else
			strInfo.Format(_T("(Get error status failed!)"));
		strInfo = strTmp + strInfo;
		lblInfo->SetText(strInfo);
	}

	return boRtnStatus;
}

BOOL CMPCmd::DoQuickTestFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, QUICK_TEST_PARAM* srtQuickTestParam, CLabel* lblInfo, CTextProgressCtrl* pgsPort)
{
	BOOL boRtnStatus = TRUE;
	CString strInfo;

	//DDR Test
	if(boRtnStatus && srtQuickTestParam->boDDRTest)
	{
		strInfo.Format(_T("DDR test ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendDDRTestCmd(hDevice, bBusType);
		strInfo.Format(_T("DDR test %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	//Get Progress Status
		if(boRtnStatus)
		{
			strInfo.Format(_T("Check DDR test progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check DDR test progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
	}
	//Flash RW Test
	if(boRtnStatus && srtQuickTestParam->boFlashTest)
	{
		strInfo.Format(_T("Flash W/R test ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendFlashRWTestCmd(hDevice, bBusType);
		strInfo.Format(_T("Flash W/R test %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	//Get Progress Status
		if(boRtnStatus)
		{
			strInfo.Format(_T("Check flash W/R test progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check flash W/R test progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
	}
	//SPI RW Test
	if(boRtnStatus && srtQuickTestParam->boSPITest)
	{
		strInfo.Format(_T("SPI W/R test ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendSPIRWTestCmd(hDevice, bBusType);
		strInfo.Format(_T("SPI W/R test %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	//Get Progress Status
		if(boRtnStatus)
		{
			strInfo.Format(_T("Check SPI W/R test progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check SPI W/R test progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
	}
	//Thermal Sensor Test
	if(boRtnStatus && srtQuickTestParam->boThermalTest)
	{
		strInfo.Format(_T("Thermal sensor test ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendThermalSensorTestCmd(hDevice, bBusType);
		strInfo.Format(_T("Thermal sensor test %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	//Get Progress Status
		if(boRtnStatus)
		{
			strInfo.Format(_T("Check thermal sensor test progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check thermal sensor test progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
	}
	//Check Efuse Test
	if(boRtnStatus && srtQuickTestParam->boEfuseTest)
	{
		strInfo.Format(_T("Check efuse test ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendCheckEfuseTestCmd(hDevice, bBusType);
		strInfo.Format(_T("Check efuse test %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	//Get Progress Status
		if(boRtnStatus)
		{
			strInfo.Format(_T("Check efuse test progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check efuse test progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
	}
	//Get Error Code and Status
	if(!boRtnStatus)
	{
		DWORD dwECESLength = 4096;
		BYTE bECESBuf[4096] = {0};
		BOOL boECESStatus = FALSE;
		CString strTmp;
		lblInfo->GetWindowText(strTmp);
		boECESStatus = this->SendGetErrorCodeAndStatusCmd(hDevice, dwECESLength, bECESBuf, bBusType);
		if(boECESStatus)
			strInfo.Format(_T("(EC: 0x%02X%02X%02X%02X, ES: 0x%02X%02X%02X%02X)"), bECESBuf[3], bECESBuf[2], bECESBuf[1], bECESBuf[0], bECESBuf[7], bECESBuf[6], bECESBuf[5], bECESBuf[4]);
		else
			strInfo.Format(_T("(Get error status failed!)"));
		strInfo = strTmp + strInfo;
		lblInfo->SetText(strInfo);
	}

	return boRtnStatus;
}

BOOL CMPCmd::DoMPFlowFunc(int iPortIndex, HANDLE hDevice, CString strSN, BOOL boForceErase, STRUCT_PARAM* srtStructParam, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort)
{
	BOOL boRtnStatus = TRUE;
	CString strInfo;
	CSemaphore mutex;

	CSingleLock wait(&mutex);

	//Set Production Parameter
	if(boRtnStatus)
	{
		strInfo.Format(_T("Write production parameter ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SetProductParamFunc(hDevice, strSN, srtStructParam, bBusType);
		strInfo.Format(_T("Write production parameter %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	
	// PreserveRDT
	if (boRtnStatus)
	{
		strInfo.Format(_T("Preserve RDT ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendPreserveRDTCmd(hDevice, bBusType);
		strInfo.Format(_T("Preserve RDT %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);

#ifdef SLEEP_REPLACE_GET_STATUS
		Sleep(10 * 1000);
#else
		//Get Progress Status
		if (boRtnStatus)
		{
			strInfo.Format(_T("Check Preserve RDT progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check Preserve RDT progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
#endif
	}
	if (boRtnStatus)
	{
		if (!boForceErase)
		{
			//Preserve BBT and ErCnt Info
			strInfo.Format(_T("Preserve BBT and ErCnt Info ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->SendPreserveBBTandErCntInfo(hDevice, bBusType);
			strInfo.Format(_T("Preserve BBT and ErCnt Info %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
	}
	//Erase Scan
	if (boRtnStatus)
	{
		strInfo.Format(_T("Erase and scan block ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendEraseScanCmd(hDevice, bBusType);
		strInfo.Format(_T("Erase and scan block %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);

#ifdef SLEEP_REPLACE_GET_STATUS
		Sleep(10 * 1000);
#else
		//Get Progress Status
		if (boRtnStatus)
		{
			strInfo.Format(_T("Check erase scan progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check erase scan progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
#endif
	}
	//Factory Scan
	if (boRtnStatus)
	{
		strInfo.Format(_T("Scan factory bad block ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendFactoryScanCmd(hDevice, bBusType);
		strInfo.Format(_T("Scan factory bad block %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);

#ifdef SLEEP_REPLACE_GET_STATUS
		Sleep(5 * 1000);
#else
		//Get Progress Status
		if (boRtnStatus)
		{
			strInfo.Format(_T("Check factory scan progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check factory scan progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
#endif
	}

	//Check Capacity
	if (boRtnStatus)
	{
		strInfo.Format(_T("Check Capacity ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendCheckCapacityCmd(hDevice, bBusType);
		strInfo.Format(_T("Check Capacity %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}

	//Download Image - SBL
	if(boRtnStatus)
	{
		wait.Lock(INFINITE);
		strInfo.Format(_T("Send SBL bin file ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->DownloadImageFunc(hDevice, this->strSBLPath, bBusType);
		wait.Unlock();
		strInfo.Format(_T("Send SBL bin file %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Program SBL
	if(boRtnStatus)
	{
		strInfo.Format(_T("Program SBL ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendProgramSBLCmd(hDevice, bBusType);
		strInfo.Format(_T("Program SBL %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);

#ifdef SLEEP_REPLACE_GET_STATUS
		Sleep(10 * 1000);
#else
	    //Get Progress Status
		if(boRtnStatus)
		{
			strInfo.Format(_T("Check program SBL progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check program SBL progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
#endif
	}
	//Download Image - SYS
	if(boRtnStatus)
	{
		wait.Lock(INFINITE);
		strInfo.Format(_T("Send FW bin file ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->DownloadImageFunc(hDevice, this->strSYSPath, bBusType);
		wait.Unlock();
		strInfo.Format(_T("Send FW bin file %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Program SYS
	if(boRtnStatus)
	{
		strInfo.Format(_T("Program FW ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendProgramFWCmd(hDevice, bBusType);
		strInfo.Format(_T("Program FW %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);

#ifdef SLEEP_REPLACE_GET_STATUS
		Sleep(15 * 1000);
#else
	    //Get Progress Status
		if(boRtnStatus)
		{
			strInfo.Format(_T("Check program FW progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check program FW progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
#endif
	}

	//Get Error Code and Status
	if(!boRtnStatus)
	{
		DWORD dwECESLength = 4096;
		BYTE bECESBuf[4096] = {0};
		BOOL boECESStatus = FALSE;
		CString strTmp;
		lblInfo->GetWindowText(strTmp);
		boECESStatus = this->SendGetErrorCodeAndStatusCmd(hDevice, dwECESLength, bECESBuf, bBusType);
		if(boECESStatus)
			strInfo.Format(_T("(EC: 0x%02X%02X%02X%02X, ES: 0x%02X%02X%02X%02X)"), bECESBuf[3], bECESBuf[2], bECESBuf[1], bECESBuf[0], bECESBuf[7], bECESBuf[6], bECESBuf[5], bECESBuf[4]);
		else
			strInfo.Format(_T("(Get error status failed!)"));
		strInfo = strTmp + strInfo;
		lblInfo->SetText(strInfo);
	}
	return boRtnStatus;
}

BOOL CMPCmd::DoBurMode2SysModeFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, CLabel *lblInfo, CTextProgressCtrl *pgsPort)
{
	BOOL boRtnStatus = FALSE;

	return boRtnStatus;
}

UINT Thread_MPFlowFunc(LPVOID pParam)
{
	MP_THREAD_PARAM* pMPParam = (MP_THREAD_PARAM*)pParam;
	CMPCmd* pClass = (CMPCmd*)pMPParam->pCmdClass;
	BOOL boStatus = FALSE;
	CString strDeviceName;
	HANDLE hDeviceIOCTL = NULL;
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD dwShareMoode = FILE_SHARE_READ | FILE_SHARE_WRITE;
	DWORD dwCreationDisposition = OPEN_EXISTING;
	CString strInfo;
	CString strFWMode;
	BYTE bDataBuf[4096];
	DWORD dwBytesRead;
	int DoSys2RomCmd = 6;
	int DoRom2BnrCmd = 4;
	int DoQuickTestCmd = 0;
	int DoMpCmd = 13;
	int DoBnr2SysCmd = 0;

	pClass->strFWState[0] = _T("ROM CODE");
	pClass->strFWState[1] = _T("BNR CODE");
	pClass->strFWState[2] = _T("RDT CODE");
	pClass->strFWState[3] = _T("SYS CODE");

	pClass->strResult[0] = _T("fail");
	pClass->strResult[1] = _T("finish");

	pMPParam->m_lblFWMode->GetWindowText(strFWMode);

	if(pMPParam->boForceErase)
		DoMpCmd = DoMpCmd - 1;

	if(pMPParam->bQuickTest != 0)
	{
		if(pMPParam->srtQuickTestParam->boDDRTest)
			DoQuickTestCmd = DoQuickTestCmd + 2;
		if(pMPParam->srtQuickTestParam->boFlashTest)
			DoQuickTestCmd = DoQuickTestCmd + 2;
		if(pMPParam->srtQuickTestParam->boSPITest)
			DoQuickTestCmd = DoQuickTestCmd + 2;
		if(pMPParam->srtQuickTestParam->boThermalTest)
			DoQuickTestCmd = DoQuickTestCmd + 2;
		if(pMPParam->srtQuickTestParam->boEfuseTest)
			DoQuickTestCmd = DoQuickTestCmd + 2;
	}

	if(pMPParam->bQuickTest == 0)
		DoQuickTestCmd = 0;
	else if(pMPParam->bQuickTest == 2)
		DoMpCmd = 0;
	
	pClass->iCmdCurrent[pMPParam->iPortIndex] = 0;
	if(strFWMode == _T("ROM"))
		pClass->iCmdAmount[pMPParam->iPortIndex] = DoRom2BnrCmd + DoQuickTestCmd + DoMpCmd + DoBnr2SysCmd;
	else if(strFWMode == _T("BNR"))
		pClass->iCmdAmount[pMPParam->iPortIndex] = DoQuickTestCmd +DoMpCmd + DoBnr2SysCmd;
	else
		pClass->iCmdAmount[pMPParam->iPortIndex] = DoSys2RomCmd + DoRom2BnrCmd + DoQuickTestCmd + DoMpCmd + DoBnr2SysCmd;

	::SetTimer(pMPParam->hWndMPInfo, pMPParam->iPortIndex, 1000, NULL);

	strDeviceName.Format(_T("%s%d"), PHYSICAL_DRIVE_PATH, pMPParam->iDiskPhysicalIndex);
	pMPParam->m_lblInfo->SetText(strDeviceName);
	hDeviceIOCTL = ::CreateFile(strDeviceName, dwDesiredAccess, dwShareMoode, NULL, dwCreationDisposition, 0, NULL);
	if(hDeviceIOCTL != INVALID_HANDLE_VALUE)
	{
		if(pMPParam->boPartitionFlag)
		{
			pClass->SetDeletePartitionSetupInfo(pMPParam->iDiskPhysicalIndex);
			boStatus = pClass->DeletePartitionFunc(pMPParam->iPortIndex, pMPParam->iDiskPhysicalIndex, CleanPartitionTimeout, pMPParam->m_lblInfo);
			pClass->DeleteSetupInfo(pMPParam->iDiskPhysicalIndex);
		}
		else
		{
			::SetFilePointer(hDeviceIOCTL, 0, NULL, FILE_BEGIN);
			boStatus = ::ReadFile(hDeviceIOCTL, bDataBuf, 4096, &dwBytesRead, NULL);
			if(!boStatus)
			{
				strInfo.Format(_T("Read LBA 0 Length 4KB fail - %s"), pClass->GetErrorMessage(::GetLastError()));
				pClass->SetMPMsg(pMPParam->iPortIndex, strInfo, pMPParam->m_lblInfo, NULL);
			}
		}
		if(boStatus && ((strFWMode == _T("SYS")) || (strFWMode == _T("RDT"))))
			boStatus = pClass->DoSysMode2RomModeFunc(pMPParam->iPortIndex, hDeviceIOCTL, pMPParam->bDiskBusType, pMPParam->m_lblInfo, pMPParam->m_pgsPort);
		if(boStatus && (strFWMode != _T("BNR")))
			boStatus = pClass->DoRomMode2BnrModeFunc(pMPParam->iPortIndex, hDeviceIOCTL, pMPParam->bDiskBusType, pMPParam->m_lblInfo, pMPParam->m_pgsPort);
		if(boStatus && (pMPParam->bQuickTest != 0))
			boStatus = pClass->DoQuickTestFunc(pMPParam->iPortIndex, hDeviceIOCTL, pMPParam->bDiskBusType, pMPParam->srtQuickTestParam, pMPParam->m_lblInfo, pMPParam->m_pgsPort);
		if(boStatus && (pMPParam->bQuickTest != 2))
			boStatus = pClass->DoMPFlowFunc(pMPParam->iPortIndex, hDeviceIOCTL, pMPParam->strMPSN, pMPParam->boForceErase, pMPParam->srtStructParam, pMPParam->bDiskBusType, pMPParam->m_lblInfo, pMPParam->m_pgsPort);
		//if(boStatus)
		//	boStatus = pClass->DoBurMode2SysModeFunc(pMPParam->iPortIndex, hDeviceIOCTL, pMPParam->bDiskBusType, pMPParam->m_lblInfo, pMPParam->m_pgsPort);

		::CloseHandle(hDeviceIOCTL);
	}
	else
	{
		strInfo.Format(_T("Get disk handle fail - %s"), strDeviceName);
		pClass->SetMPMsg(pMPParam->iPortIndex, strInfo, pMPParam->m_lblInfo, NULL);
	}
	if(boStatus)
	{
		strInfo.Format(_T("MP SUCCESS"));
		pMPParam->m_lblFWMode->SetBkColor(Success_BK_Color);
		*pMPParam->dwSNPassCount = *pMPParam->dwSNPassCount + 1;
		pMPParam->m_lblInfo->SetText(strInfo);
	}
	else
	{
		strInfo.Format(_T("MP FAIL"));
		pMPParam->m_lblFWMode->SetBkColor(Fail_BK_Color);
		*pMPParam->dwSNFailCount = *pMPParam->dwSNFailCount + 1;
	}
	pClass->SetMPMsg(pMPParam->iPortIndex, strInfo, NULL, NULL);
	::KillTimer(pMPParam->hWndMPInfo, pMPParam->iPortIndex);
	iThreadCount--;
	return 0;
}