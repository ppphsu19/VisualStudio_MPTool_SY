#include "stdafx.h"
#include "DetectDisk.h"


BYTE* CDetectDisk::FlipData(const BYTE* str, int pos, int flip, BYTE* buf)
{
	int i;
    int j = 0;
    int k = 0;

    buf [0] = '\0';
    if (pos <= 0)
		return buf;
	if (!j)
	{
		char p = 0;
		j = 1;
		k = 0;
		buf[k] = 0;
		for (i = pos; j && str[i] != '\0'; ++i)
		{
			char c = tolower(str[i]);
			if (isspace(c))
				c = '0';
			++p;
			buf[k] <<= 4;
			if (c >= '0' && c <= '9')
				buf[k] |= (unsigned char) (c - '0');
			else if (c >= 'a' && c <= 'f')
				buf[k] |= (unsigned char) (c - 'a' + 10);
			else
			{
				j = 0;
				break;
			}
			if (p == 2)
			{
				if (buf[k] != '\0' && ! isprint(buf[k]))
				{
					j = 0;
					break;
				}

				++k;
				p = 0;
				buf[k] = 0;
			}
		}
	}
	if (!j)
	{
		j = 1;
		k = 0;
		for (i = pos; j && str[i] != '\0'; ++i)
		{
			char c = str[i];

			if ( ! isprint(c))
			{
				j = 0;
				break;
			}

			buf[k++] = c;
		}
	}
	if ( ! j)
	{
		k = 0;
	}
	buf[k] = '\0';
	if (flip)
	{
		for (j = 0; j < k; j += 2)
		{
			char t = buf[j];
			buf[j] = buf[j + 1];
			buf[j + 1] = t;
		}
	}
	i = j = -1;
	for (k = 0; buf[k] != '\0'; ++k)
	{
		if (! isspace(buf[k]))
		{
			if (i < 0)
				i = k;
			j = k;
		}
	}
	if ((i >= 0) && (j >= 0))
	{
		for (k = i; (k <= j) && (buf[k] != '\0'); ++k)
			buf[k - i] = buf[k];
		buf[k - i] = '\0';
	}
	return buf;
}

BOOL CDetectDisk::GetDriveGeometryEx(int PhysicalNumber, DISK_GEOMETRY_EX *pdg)
{
	HANDLE hDevice;
	BOOL bResult;
	DWORD junk;
	CString szDiskName;
	
	szDiskName.Format(_T("\\\\.\\PHYSICALDRIVE%d"), PhysicalNumber);

	hDevice = CreateFile(szDiskName,
		0,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hDevice == INVALID_HANDLE_VALUE)
		return (FALSE);

	bResult = DeviceIoControl(
		hDevice,
		IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,
		NULL,
		0,
		pdg,
		sizeof(*pdg),
		&junk,
		(LPOVERLAPPED) NULL);

	CloseHandle(hDevice);
	return (bResult);
}

void CDetectDisk::DetectDrives()
{
	int i;
	HANDLE hDriveIOCTL = NULL;
	DWORD dwSerialNumber, dwMaxComponentLength, dwFlags;
	TCHAR tcFileSystem[MAX_INFO_LEN];
	TCHAR tcVolumeName[MAX_INFO_LEN];
	CString strDriveName;

	for (i=0; i<MAX_DISKS; i++)
	{
		strDriveName.Format(_T("\\\\.\\%c:"),i+'C');
	
		hDriveIOCTL = ::CreateFile(
			strDriveName,    
			GENERIC_READ|GENERIC_WRITE,    
			FILE_SHARE_READ|FILE_SHARE_WRITE,    
			NULL,    
			OPEN_EXISTING,    
			0,    
			NULL    
		);

		if (hDriveIOCTL != INVALID_HANDLE_VALUE)    
		{
			STORAGE_DEVICE_NUMBER sDg;  
			DWORD dwSize;

			if(DeviceIoControl(
				hDriveIOCTL,
				IOCTL_STORAGE_GET_DEVICE_NUMBER,
				NULL,
				0,
				&sDg,
				sizeof(sDg),
				&dwSize,0)
			)
			{
				strDriveName.Format(_T("\\\\.\\%c:\\"),i+'C');

				if (::GetVolumeInformation(
					strDriveName,
					tcVolumeName,
					sizeof(tcVolumeName),
					&dwSerialNumber,
					&dwMaxComponentLength,
					&dwFlags,
					tcFileSystem,
					sizeof(tcFileSystem)))
				{
					if (sDg.DeviceNumber == this->srtDiskInfo[this->iDiskAmount].iPhysicalDiskIndex)
					{
						if (::strlen(this->srtDiskInfo[this->iDiskAmount].cFileSystem) == 0)
							::strcpy_s(this->srtDiskInfo[this->iDiskAmount].cFileSystem, tcFileSystem);
						else
							::wsprintf(this->srtDiskInfo[this->iDiskAmount].cFileSystem, _T("%s, %s"), this->srtDiskInfo[this->iDiskAmount].cFileSystem, tcFileSystem);
					}
				}
				
				if (sDg.DeviceNumber == this->srtDiskInfo[this->iDiskAmount].iPhysicalDiskIndex)
				{
					if (::strlen(this->srtDiskInfo[this->iDiskAmount].cDriveName) == 0)
					{
						::wsprintf(this->srtDiskInfo[this->iDiskAmount].cDriveName, _T("%c"), i+'C');
						this->cExistDrive[this->iDriveAmount] = i+'C';
						this->iDriveAmount++;
					}
					else
					{
						::wsprintf(this->srtDiskInfo[this->iDiskAmount].cDriveName, _T("%s, %c"), this->srtDiskInfo[this->iDiskAmount].cDriveName, i+'C');
						this->cExistDrive[this->iDriveAmount] = i+'C';
						this->iDriveAmount++;
					}
				}
			}
			::CloseHandle(hDriveIOCTL);  
		}
	}
}

BOOL CDetectDisk::GetFWMode(HANDLE hDeviceIOCTL, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;
	COMMAND_SET srtCommandSet;
	DWORD dwLength = 4096;
	BYTE bDataBuf[4096] = {0};
	DWORD dwBytesRead;

	::SetFilePointer(hDeviceIOCTL, 0, NULL, FILE_BEGIN);
	boRtnStatus = ::ReadFile(hDeviceIOCTL, bDataBuf, 4096, &dwBytesRead, NULL);
	if(boRtnStatus)
	{
		::memset(&srtCommandSet, 0, sizeof(srtCommandSet));
		srtCommandSet.bOpcode = 0xC0;
		srtCommandSet.dw12 = 0x00;
		//srtCommandSet.dw13 = 0x1D890280;//Libra Key
		srtCommandSet.dw13 = 0x4A455349;//Libra Super Key
		srtCommandSet.bProtocolField = PROTOCOL_NON_DATA;
		srtCommandSet.ulTimeout = CMD_TIMEOUT;
		boRtnStatus = this->SendNVMeCmd(hDeviceIOCTL, srtCommandSet, NULL, bBusType);

		::memset(&srtCommandSet, 0, sizeof(srtCommandSet));
		::memset(bDataBuf, 0, sizeof(bDataBuf));
		srtCommandSet.bOpcode = 0xC2;
		srtCommandSet.dw10 = dwLength/4;
		srtCommandSet.dw12 = 0xF2;
		srtCommandSet.dw13 = dwLength;
		srtCommandSet.dwDataLength = dwLength;
		srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
		srtCommandSet.ulTimeout = CMD_TIMEOUT;
		if(boRtnStatus)
			boRtnStatus = this->SendNVMeCmd(hDeviceIOCTL, srtCommandSet, bDataBuf, bBusType);
		if(boRtnStatus)
			this->srtDiskInfo[this->iDiskAmount].iFWMode = bDataBuf[0];//1: ROM, 2: Burner, 3: RDT, 4: System
	}
	return boRtnStatus;
}

BOOL CDetectDisk::DecodeBoardInfoData(BYTE* bDataBuf)
{
	int iChannel = 0;
	int iBank = 0;
	int i, j;
	BOOL boFindID = FALSE;
	BYTE bFlashIDBuf[8] = {0};
	int iGetCh = 0;

	if(this->srtDiskInfo[this->iDiskAmount].iFWMode == 1)
	{
		for(i=0; i<8; i++)
		{
			for(j=0; j<8; j++)
			{
				if(bDataBuf[i*64 + j*8] == 0)
					continue;
				if(!boFindID)
				{
					boFindID = TRUE;
					iGetCh = i;
					::memcpy(bFlashIDBuf, bDataBuf + i*64 + j*8, 8);
				}
				if(bDataBuf[i*64+j*8] != bFlashIDBuf[0])
					continue;
				if(bDataBuf[i*64+j*8+1] != bFlashIDBuf[1])
					continue;
				if(bDataBuf[i*64+j*8+2] != bFlashIDBuf[2])
					continue;
				if(bDataBuf[i*64+j*8+3] != bFlashIDBuf[3])
					continue;
				if(bDataBuf[i*64+j*8+4] != bFlashIDBuf[4])
					continue;
				if(bDataBuf[i*64+j*8+5] != bFlashIDBuf[5])
					continue;
				if(j == 0)
					iChannel++;
				if(i == iGetCh)
					iBank++;
				else
					break;
			}
		}
		::memcpy(this->srtDiskInfo[this->iDiskAmount].srtBoardInfo.bFlashID, bFlashIDBuf, 8);
	}
	else
	{
		iChannel = bDataBuf[640];
		iBank = bDataBuf[641];
		::memcpy(this->srtDiskInfo[this->iDiskAmount].srtBoardInfo.bFlashID, bDataBuf+2, 8);
	}
	this->srtDiskInfo[this->iDiskAmount].srtBoardInfo.iChannelNum = iChannel;
	this->srtDiskInfo[this->iDiskAmount].srtBoardInfo.iBankNum = iBank;
	if(this->srtDiskInfo[this->iDiskAmount].srtBoardInfo.bFlashID[0] != 0x00)
		return TRUE;
	return FALSE;
}

BOOL CDetectDisk::GetBoardInfo(HANDLE hDeviceIOCTL, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;
	COMMAND_SET srtCommandSet;
	DWORD dwLength = 4096;
	BYTE bDataBuf[4096] = {0};

	if(this->srtDiskInfo[this->iDiskAmount].iFWMode == 0)
		return boRtnStatus;

	if(this->srtDiskInfo[this->iDiskAmount].iFWMode == 1)
		dwLength = 512;
	else
		dwLength = 4096;

	::memset(&srtCommandSet, 0, sizeof(srtCommandSet));
	srtCommandSet.bOpcode = 0xC2;
	srtCommandSet.dw10 = dwLength/4;
	if(this->srtDiskInfo[this->iDiskAmount].iFWMode == 1)
		srtCommandSet.dw12 = 0xF1;
	else
		srtCommandSet.dw12 = 0x00;
	srtCommandSet.dw13 = dwLength;
	srtCommandSet.dwDataLength = dwLength;
	srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
	srtCommandSet.ulTimeout = CMD_TIMEOUT;
	boRtnStatus = this->SendNVMeCmd(hDeviceIOCTL, srtCommandSet, bDataBuf, bBusType);
	if(boRtnStatus)
		boRtnStatus = this->DecodeBoardInfoData(bDataBuf);

	return boRtnStatus;
}

BOOL CDetectDisk::DecodeData(int iDiskIndex, HANDLE hDeviceIOCTL, int iBusType)
{
	int i;
	CString strInfo;
	DISK_GEOMETRY_EX pdgEx;
	BOOL boStatus = FALSE;

	if((iBusType == BusTypeUsb) || (iBusType == BusTypeMax))
	{
		boStatus = this->GetFWMode(hDeviceIOCTL, iBusType);
		if(!boStatus)
			return FALSE;
		if((this->srtDiskInfo[this->iDiskAmount].iFWMode == 0) || (this->srtDiskInfo[this->iDiskAmount].iFWMode > 4))
		{
			strInfo.Format(_T("(%d)FW mode error - %d!!!"), iDiskIndex, this->srtDiskInfo[this->iDiskAmount].iFWMode);
			::AfxMessageBox(strInfo);
			return FALSE;
		}
		boStatus = this->GetBoardInfo(hDeviceIOCTL, iBusType);
		if(!boStatus)
			return FALSE;
	}

	this->srtDiskInfo[this->iDiskAmount].iPhysicalDiskIndex = iDiskIndex;
	this->srtDiskInfo[this->iDiskAmount].bDiskBusType = iBusType;

	switch(iBusType)
	{
	case BusTypeUsb:
		::memcpy(this->srtDiskInfo[this->iDiskAmount].cUSBBridgeSN, this->bTmpBridgeSN, 20);
	case BusTypeMax:
		::memcpy(this->srtDiskInfo[this->iDiskAmount].cModelName, this->pIdCtrlr->MN, 40);
		::memcpy(this->srtDiskInfo[this->iDiskAmount].cSerialNumber, this->pIdCtrlr->SN, 20);
		::memcpy(this->srtDiskInfo[this->iDiskAmount].cFirmwareVersion, this->pIdCtrlr->FR, 8);
		break;
	case BusTypeSata:
		for(i=0; i<40; i+=2)
		{
			this->srtDiskInfo[this->iDiskAmount].cModelName[i] = this->bIdentifyDataSATA[i+55];
			this->srtDiskInfo[this->iDiskAmount].cModelName[i+1] = this->bIdentifyDataSATA[i+54];
		}
		for(i=0; i<20; i+=2)
		{
			this->srtDiskInfo[this->iDiskAmount].cSerialNumber[i] = this->bIdentifyDataSATA[i+21];
			this->srtDiskInfo[this->iDiskAmount].cSerialNumber[i+1] = this->bIdentifyDataSATA[i+20];
		}
		for(i=0; i<8; i+=2)
		{
			this->srtDiskInfo[this->iDiskAmount].cFirmwareVersion[i] = this->bIdentifyDataSATA[i+47];
			this->srtDiskInfo[this->iDiskAmount].cFirmwareVersion[i+1] = this->bIdentifyDataSATA[i+46];
		}
		break;
	default:
		return FALSE;
	}
	this->GetDriveGeometryEx(iDiskIndex, &pdgEx);
	this->srtDiskInfo[this->iDiskAmount].iSectorSize = pdgEx.Geometry.BytesPerSector;
	if(pdgEx.DiskSize.QuadPart == 0)
		return FALSE;
	
	this->srtDiskInfo[this->iDiskAmount].ui64LBA = pdgEx.DiskSize.QuadPart/pdgEx.Geometry.BytesPerSector;

	this->srtDiskInfo[this->iDiskAmount].iGBCapacity = (int)(this->srtDiskInfo[this->iDiskAmount].ui64LBA/1024/1024*pdgEx.Geometry.BytesPerSector/1024);

	if((this->srtDiskInfo[this->iDiskAmount].ui64LBA/1024*pdgEx.Geometry.BytesPerSector) >= 1024)
	{
		if ((this->srtDiskInfo[this->iDiskAmount].ui64LBA/1024/1024*pdgEx.Geometry.BytesPerSector) >= 1024)
		{
			if ((this->srtDiskInfo[this->iDiskAmount].ui64LBA/1024/1024*pdgEx.Geometry.BytesPerSector/1024) >= 1024)
				strInfo.Format(_T("%6.2fTB"), (double)((double)((__int64)(this->srtDiskInfo[this->iDiskAmount].ui64LBA))/1024/1024/1024*pdgEx.Geometry.BytesPerSector/1024));
			else
				strInfo.Format(_T("%6.2fGB"), (double)((double)((__int64)(this->srtDiskInfo[this->iDiskAmount].ui64LBA))/1024/1024*pdgEx.Geometry.BytesPerSector/1024));
		}
		else
			strInfo.Format(_T("%6.2fMB"), (double)((double)((__int64)(this->srtDiskInfo[this->iDiskAmount].ui64LBA))/1024*pdgEx.Geometry.BytesPerSector/1024));
	}
	else
		strInfo.Format(_T("%6.2fKB"), (double)((double)((__int64)(this->srtDiskInfo[this->iDiskAmount].ui64LBA))*pdgEx.Geometry.BytesPerSector/1024));
	this->srtDiskInfo[this->iDiskAmount].strCapacity = strInfo;

	this->DetectDrives();

	this->iDiskAmount++;
	return TRUE;
}

BOOL CDetectDisk::DetectUSB(HANDLE hDeviceIOCTL)
{
	BOOL boRtnStatus = FALSE;
	STORAGE_PROPERTY_QUERY sQuery;
	DWORD dwBytesReturned = 0;
	BYTE bBuf[1024];

	::memset ((void *)&sQuery, 0, sizeof(sQuery));
	::memset(bBuf, 0, sizeof(bBuf));

	sQuery.PropertyId = StorageDeviceProperty;
	sQuery.QueryType = PropertyStandardQuery;

	boRtnStatus = ::DeviceIoControl(hDeviceIOCTL, IOCTL_STORAGE_QUERY_PROPERTY, &sQuery, sizeof(sQuery), &bBuf, sizeof(bBuf), &dwBytesReturned, NULL);
	if(boRtnStatus)
	{
		STORAGE_DEVICE_DESCRIPTOR* sDescriptor = (STORAGE_DEVICE_DESCRIPTOR *)&bBuf;
		if(sDescriptor->BusType == BusTypeUsb)
		{
			int iFindStatus;
			CString strInfo;
			BYTE bIdName[MAX_INFO_LEN];
			this->FlipData(bBuf, sDescriptor->VendorIdOffset, 0, bIdName);
			strInfo.Format(_T("%s"), bIdName);
			iFindStatus = strInfo.Find("JMi");
			if(iFindStatus >= 0 && iFindStatus != 0xFFFFFFFF)
			{
				this->FlipData(bBuf, sDescriptor->SerialNumberOffset, 0, this->bTmpBridgeSN);
				COMMAND_SET srtCommandSet;

				::memset(&srtCommandSet, 0, sizeof(srtCommandSet));
				::memset(this->bIdentifyDataNVMe, 0, sizeof(this->bIdentifyDataNVMe));
				srtCommandSet.bOpcode = ADMIN_IDENTIFY;
				srtCommandSet.dw10 = 1;
				srtCommandSet.dw13 = 4096;
				srtCommandSet.dwDataLength = 4096;
				srtCommandSet.bProtocolField = PROTOCOL_DMA_IN;
				srtCommandSet.ulTimeout = CMD_TIMEOUT;
				boRtnStatus = this->SendNVMeCmd(hDeviceIOCTL, srtCommandSet, this->bIdentifyDataNVMe, BusTypeUsb);
				if(boRtnStatus)
					pIdCtrlr = (PADMIN_IDENTIFY_CONTROLLER)this->bIdentifyDataNVMe;
			}
			else
				boRtnStatus = FALSE;
		}
		else
			boRtnStatus = FALSE;
	}
	return boRtnStatus;
}

BOOL CDetectDisk::DetectSATA(HANDLE hDeviceIOCTL)
{
	BOOL boRtnStatus = FALSE;
	PSENDCMDINPARAMS pSCIP;
	PSENDCMDOUTPARAMS pSCOP;
	DWORD dwOutBytes;

	pSCIP = (PSENDCMDINPARAMS)::GlobalAlloc( LMEM_ZEROINIT, sizeof(SENDCMDINPARAMS)-1);
	pSCOP = (PSENDCMDOUTPARAMS)::GlobalAlloc(LMEM_ZEROINIT, sizeof(SENDCMDOUTPARAMS)+511);

	pSCIP->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
	pSCIP->cBufferSize = 0;
	pSCOP->cBufferSize = 512;

	boRtnStatus = ::DeviceIoControl(hDeviceIOCTL, DFP_RECEIVE_DRIVE_DATA, pSCIP, sizeof(SENDCMDINPARAMS) - 1, pSCOP, sizeof(SENDCMDOUTPARAMS) + 511,&dwOutBytes, (LPOVERLAPPED)NULL);

	if(boRtnStatus)
		::memcpy(this->bIdentifyDataSATA, pSCOP->bBuffer, sizeof(this->bIdentifyDataSATA));
	::GlobalFree(pSCOP);
	::GlobalFree(pSCIP);
	return boRtnStatus;
}

BOOL CDetectDisk::DetectNVMeInbox(HANDLE hDeviceIOCTL)
{
	BOOL boRtnStatus = FALSE;
	StorageQuery::TStorageQueryWithBuffer nptwb;
	DWORD dwReturned = 0;

	::ZeroMemory(&nptwb, sizeof(nptwb));

	nptwb.ProtocolSpecific.ProtocolType = StorageQuery::ProtocolTypeNvme;
	nptwb.ProtocolSpecific.DataType = StorageQuery::NVMeDataTypeIdentify;
	nptwb.ProtocolSpecific.ProtocolDataOffset = sizeof(StorageQuery::TStorageProtocolSpecificData);
	nptwb.ProtocolSpecific.ProtocolDataLength = NVMe_IDENTIFY_BUFFER_SIZE;
	nptwb.Query.PropertyId = StorageQuery::StorageAdapterProtocolSpecificProperty;
	nptwb.Query.QueryType = StorageQuery::PropertyStandardQuery;

	boRtnStatus = ::DeviceIoControl(
		hDeviceIOCTL, 
		IOCTL_STORAGE_QUERY_PROPERTY,
		&nptwb, 
		sizeof(nptwb), 
		&nptwb, 
		sizeof(nptwb), 
		&dwReturned, 
		NULL);

	if (boRtnStatus)
		pIdCtrlr = (PADMIN_IDENTIFY_CONTROLLER)nptwb.Buffer;

	return boRtnStatus;
}

BOOL CDetectDisk::GetScsiPath(CString strPath, CString* strpRtnValue)
{
	BOOL boRtnStatus = FALSE;
	SCSI_ADDRESS sAddr;
	DWORD dwReturned;
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD dwShareMoode = FILE_SHARE_READ | FILE_SHARE_WRITE;
	DWORD dwCreationDisposition = OPEN_EXISTING;
	DWORD dwFlagAttribute = FILE_ATTRIBUTE_NORMAL;

	HANDLE hIoCtrl = ::CreateFile(strPath, dwDesiredAccess, dwShareMoode, NULL, dwCreationDisposition, dwFlagAttribute, 0);

	boRtnStatus = ::DeviceIoControl(
				hIoCtrl, 
				IOCTL_SCSI_GET_ADDRESS,
				NULL, 
				0, 
				&sAddr, 
				sizeof(sAddr), 
				&dwReturned, 
				NULL);
	
	if(boRtnStatus)
		strpRtnValue->Format(_T("\\\\.\\SCSI%d:"), sAddr.PortNumber);
	::CloseHandle(hIoCtrl);
	return boRtnStatus;
}

BOOL CDetectDisk::DetectNVMeOther(HANDLE hDeviceIOCTL)
{
	BOOL boRtnStatus = FALSE;
	PNVMe_COMMAND pCmd;
    UCHAR myIoctlBuf[sizeof(NVME_PASS_THROUGH_IOCTL) + sizeof(ADMIN_IDENTIFY_CONTROLLER)];
    PNVME_PASS_THROUGH_IOCTL pMyIoctl = (PNVME_PASS_THROUGH_IOCTL) myIoctlBuf;
    DWORD dwReturned;
    PADMIN_IDENTIFY_COMMAND_DW10 dw10;

	pMyIoctl->SrbIoCtrl.HeaderLength = sizeof(SRB_IO_CONTROL);
	::memcpy(pMyIoctl->SrbIoCtrl.Signature, NVME_SIG_STR, sizeof(NVME_SIG_STR));
	pMyIoctl->SrbIoCtrl.Timeout = 30;
	pMyIoctl->SrbIoCtrl.ControlCode = (ULONG)NVME_PASS_THROUGH_SRB_IO_CODE;
	pMyIoctl->SrbIoCtrl.ReturnCode = 0;
	pMyIoctl->SrbIoCtrl.Length = sizeof(myIoctlBuf) - sizeof(SRB_IO_CONTROL);

	pCmd = (PNVMe_COMMAND)pMyIoctl->NVMeCmd;
	pCmd->CDW0.OPC = ADMIN_IDENTIFY;
	dw10 = (PADMIN_IDENTIFY_COMMAND_DW10)&(pCmd->CDW10);
	dw10->CNS = 1;
 
	pMyIoctl->QueueId = 0;
	pMyIoctl->DataBufferLen = NVMe_IDENTIFY_BUFFER_SIZE;
	pMyIoctl->Direction = NVME_FROM_DEV_TO_HOST;
	pMyIoctl->ReturnBufferLen = sizeof(ADMIN_IDENTIFY_CONTROLLER) + sizeof(NVME_PASS_THROUGH_IOCTL);
	pMyIoctl->VendorSpecific[0] = (DWORD) 0;
	pMyIoctl->VendorSpecific[1] = (DWORD) 0;

	boRtnStatus = ::DeviceIoControl(
			hDeviceIOCTL,
			IOCTL_SCSI_MINIPORT,
			pMyIoctl,
			sizeof(myIoctlBuf),
			pMyIoctl,
			sizeof(myIoctlBuf),
			&dwReturned,
			NULL);

	if(boRtnStatus)
		pIdCtrlr = (PADMIN_IDENTIFY_CONTROLLER)pMyIoctl->DataBuffer;
	return boRtnStatus;
}

void CDetectDisk::DetectDisks()
{
	int i;
	BOOL boStatus = FALSE;
	CString strDeviceName, strScsiName;
	HANDLE hDeviceIOCTL = NULL;
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	DWORD dwShareMoode = FILE_SHARE_READ | FILE_SHARE_WRITE;
	DWORD dwCreationDisposition = OPEN_EXISTING;

	for(i=0; i<MAX_DISKS; i++)
	{
		::memset(this->bTmpBridgeSN, 0, sizeof(this->bTmpBridgeSN));

		strDeviceName.Format(_T("%s%d"), PHYSICAL_DRIVE_PATH, i);
		hDeviceIOCTL = ::CreateFile(strDeviceName, dwDesiredAccess, dwShareMoode, NULL, dwCreationDisposition, 0, NULL);

		if(hDeviceIOCTL != INVALID_HANDLE_VALUE)
		{
			boStatus = this->DetectUSB(hDeviceIOCTL);
			if(boStatus)
			{
				boStatus = this->DecodeData(i, hDeviceIOCTL, BusTypeUsb);
				if(boStatus)
				{
					::CloseHandle(hDeviceIOCTL);
					continue;
				}
			}
			boStatus = this->DetectNVMeInbox(hDeviceIOCTL);
			if(boStatus)
				boStatus = this->DecodeData(i, hDeviceIOCTL, BusTypeMax);
			::CloseHandle(hDeviceIOCTL);
		}
	}
}

void CDetectDisk::ScanDisks()
{
	int i;

	for(i=0; i<MAX_DISKS; i++)
	{
		this->srtDiskInfo[i].iPhysicalDiskIndex = -1;
		this->srtDiskInfo[i].iGBCapacity = 0;
		this->srtDiskInfo[i].ui64LBA = 0;
		this->srtDiskInfo[i].iSectorSize = 0;
		this->srtDiskInfo[i].strCapacity = _T("");
		this->srtDiskInfo[i].bDiskBusType = 0;
		this->srtDiskInfo[i].iFWMode = 0;
		this->srtDiskInfo[i].srtBoardInfo.iChannelNum = 0;
		this->srtDiskInfo[i].srtBoardInfo.iBankNum = 0;
		::memset(this->srtDiskInfo[i].cModelName, 0, MAX_INFO_LEN);
		::memset(this->srtDiskInfo[i].cSerialNumber, 0, MAX_INFO_LEN);
		::memset(this->srtDiskInfo[i].cFirmwareVersion, 0, MAX_INFO_LEN);
		::memset(this->srtDiskInfo[i].cDriveName, 0, MAX_INFO_LEN);
		::memset(this->srtDiskInfo[i].cFileSystem, 0, MAX_INFO_LEN);
		::memset(this->srtDiskInfo[i].cUSBBridgeSN, 0, MAX_INFO_LEN);
		::memset(this->srtDiskInfo[i].srtBoardInfo.bFlashID, 0, 8);
		this->cExistDrive[i] = 0;
	}
	this->iDiskAmount = 0;
	this->iDriveAmount = 0;

	this->DetectDisks();
}