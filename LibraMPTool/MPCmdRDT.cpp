#include "stdafx.h"
#include "MPCmdRDT.h"

//#define SLEEP_REPLACE_GET_STATUS

CMPCmdRDT::CMPCmdRDT() : CMPCmd()
{
}

BOOL CMPCmdRDT::SendSetProductParamCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	::memset(&this->srtCommandSet, 0, sizeof(this->srtCommandSet));
	this->srtCommandSet.bOpcode = 0xC1;
	this->srtCommandSet.dw10 = dwDataLength / 4;
	this->srtCommandSet.dw12 = 0x02;
	this->srtCommandSet.dw13 = dwDataLength;
	this->srtCommandSet.dwDataLength = dwDataLength;
	this->srtCommandSet.bProtocolField = PROTOCOL_DMA_OUT;
	this->srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDevice, this->srtCommandSet, bDataBuf, bBusType);

	return boRtnStatus;
}

BOOL CMPCmdRDT::DoMPFlowFunc(int iPortIndex, HANDLE hDevice, CString strSN, BOOL boForceErase, STRUCT_PARAM* srtStructParam, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort)
{
	BOOL boRtnStatus = TRUE;
	CString strInfo;
	CSemaphore mutex;

	CSingleLock wait(&mutex);

	// Get board info
	if (boRtnStatus)
	{
		strInfo.Format(_T("Get board info ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		BYTE buffer[4096];
		boRtnStatus = this->SendGetBoardInfoCmd(hDevice, sizeof(buffer), buffer, bBusType);
		strInfo.Format(_T("Get board info %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}

	//Set Production Parameter (RDT)
	if (boRtnStatus)
	{
		strInfo.Format(_T("Write production parameter ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = SetProductParamFunc(hDevice, strSN, srtStructParam, bBusType);
		strInfo.Format(_T("Write production parameter %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
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
	
	//Check Capacity
	if (boRtnStatus)
	{
		strInfo.Format(_T("Check Capacity ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendCheckCapacityCmd(hDevice, bBusType);
		strInfo.Format(_T("Check Capacity %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);

		Sleep(5 * 1000);
	}

	//Download Image - RDT
	if (boRtnStatus)
	{
		wait.Lock(INFINITE);
		strInfo.Format(_T("Send RDT bin file ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->DownloadImageFunc(hDevice, this->strRDTPath, bBusType);
		wait.Unlock();
		strInfo.Format(_T("Send RDT bin file %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
	}
	//Program RDT
	if (boRtnStatus)
	{
		strInfo.Format(_T("Program RDT ..."));
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
		boRtnStatus = this->SendProgramSBLCmd(hDevice, bBusType);
		strInfo.Format(_T("Program RDT %s"), strResult[boRtnStatus]);
		this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);

#ifdef SLEEP_REPLACE_GET_STATUS
		Sleep(5 * 1000);
#else
		//Get Progress Status
		if (boRtnStatus)
		{
			strInfo.Format(_T("Check program RDT progress status ..."));
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, NULL);
			boRtnStatus = this->GetProgressStatusFunc(iPortIndex, hDevice, bBusType, TIMEOUT_CHECK_PROGRESS_STATUS, lblInfo);
			strInfo.Format(_T("Check program RDT progress status %s"), strResult[boRtnStatus]);
			this->SetMPMsg(iPortIndex, strInfo, lblInfo, pgsPort);
		}
#endif
	}
	
	//Get Error Code and Status
	if (!boRtnStatus)
	{
		DWORD dwECESLength = 4096;
		BYTE bECESBuf[4096] = { 0 };
		BOOL boECESStatus = FALSE;
		CString strTmp;
		lblInfo->GetWindowText(strTmp);
		boECESStatus = this->SendGetErrorCodeAndStatusCmd(hDevice, dwECESLength, bECESBuf, bBusType);
		if (boECESStatus)
			strInfo.Format(_T("(EC: 0x%02X%02X%02X%02X, ES: 0x%02X%02X%02X%02X)"), bECESBuf[3], bECESBuf[2], bECESBuf[1], bECESBuf[0], bECESBuf[7], bECESBuf[6], bECESBuf[5], bECESBuf[4]);
		else
			strInfo.Format(_T("(Get error status failed!)"));
		strInfo = strTmp + strInfo;
		lblInfo->SetText(strInfo);
	}
	return boRtnStatus;
}