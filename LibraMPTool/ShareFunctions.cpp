#include "stdafx.h"
#include "ShareFunctions.h"

bool CheckHandle(HANDLE handle)
{
	return handle != nullptr;
}

void CShareFunctions::WriteLog(CString strWriteInfo, CString strFileName, BOOL boClean)
{
	FILE* fLogFile;
	CTime ctCurrent;
	CString strInfo;

	CSingleLock wait(&this->mutex);
	wait.Lock(INFINITE);

	ctCurrent = CTime::GetCurrentTime();
	strInfo.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"), ctCurrent.GetYear(), ctCurrent.GetMonth(), ctCurrent.GetDay(), ctCurrent.GetHour(), ctCurrent.GetMinute(), ctCurrent.GetSecond());

	if (::fopen_s(&fLogFile, strFileName, boClean ? "w" : "a") == 0)
	{
		::fprintf(fLogFile, "%s, %s\n", strInfo.GetString(), strWriteInfo.GetString());
		::fclose(fLogFile);
	}

	wait.Unlock();
}

CString CShareFunctions::GetErrorMessage(DWORD dwErrorCode)
{
	CString strRtnMsg;
	LPVOID lpMsgBuf;

	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	strRtnMsg.Format(_T("(Error Info¡G%s / Error Code¡G0x%X)"), lpMsgBuf, dwErrorCode);
	LocalFree(lpMsgBuf);

	strRtnMsg.Remove('\n');

	return strRtnMsg;
}

void CShareFunctions::ShowTestResult(SERIAL_NUMBER_PARAM* srtSNParam, CLabel* lblResult)
{
	CString strInfo;

	strInfo.Format(_T("Total Test: %d  Pass: %d  Fail: %d"),
		srtSNParam->dwSNPassCount + srtSNParam->dwSNFailCount, srtSNParam->dwSNPassCount, srtSNParam->dwSNFailCount);
	lblResult->SetText(strInfo);
}

int CShareFunctions::GetDiskCapacity(int iChannel, int iBank, BYTE bLunPerTarget, WORD wDieCapacityGb)
{
	int iRtnDiskCapacityGB = 0;
	iRtnDiskCapacityGB = iChannel * iBank * bLunPerTarget * wDieCapacityGb / 8;
	return iRtnDiskCapacityGB;
}

unsigned __int64 CShareFunctions::GetLBNValue(int iCapacityGB)
{
	unsigned __int64 ui64RtnLBNValue = 0;
	ui64RtnLBNValue = iCapacityGB * 244188 + 2646;
	return ui64RtnLBNValue;
}

unsigned __int64 CShareFunctions::GetStrValue(CString strValue)
{
	unsigned __int64 ui64RtnValue = 0;
	BOOL boStatus = FALSE;
	int iStatus = 0;
	CString strInfo;

	iStatus = strValue.Find("0x");
	if(iStatus >= 0)
	{
		strInfo = strValue.Right(strValue.GetLength() - iStatus - 2);
		boStatus = this->StrParsing(strInfo, PARSING_MODE_HEX, &ui64RtnValue);
	}
	else
		boStatus = this->StrParsing(strValue, PARSING_MODE_DEC, &ui64RtnValue);

	return ui64RtnValue;
}

void CShareFunctions::GetStrValueFunc(CString strValue, char cFindKey, int iDataLength, BYTE* bValueBuf)
{
	CString strTmp = strValue;
	int iStatus;
	unsigned __int64 ui64Value;
	int iUnitLength = iDataLength;
	int iDataCount;
	CString strUnitValue;
	int i, j;

	iDataCount = strTmp.Remove(cFindKey);
	if(iDataCount == 0)
	{
		ui64Value = this->GetStrValue(strValue);
		for(i=0; i<iUnitLength; i++)
			bValueBuf[i] = (BYTE)(ui64Value >> i*8) & 0xFF;
	}
	else
	{
		iUnitLength = iDataLength / (iDataCount + 1);
		strTmp = strValue;
		for(i=0; i<=iDataCount; i++)
		{
			iStatus = strTmp.Find(cFindKey);
			if(iStatus >= 0)
			{
				strUnitValue = strTmp.Left(iStatus);
				strTmp = strTmp.Right(strTmp.GetLength() - iStatus - 1);
			}
			else
				strUnitValue = strTmp;

			ui64Value = this->GetStrValue(strUnitValue);
			for(j=0; j<iUnitLength; j++)
				bValueBuf[i*iUnitLength + j] = (BYTE)(ui64Value >> j*8) & 0xFF;
		}
	}
}

void CShareFunctions::GetSysIniFile(CString strRootDirectoryPath, SYSTEM_PARAM* srtSysParam)
{
	CString strPath;
	CString strInfo;
	char cBuf[MAX_PATH*2];
	int i;

	strPath.Format(_T("%s\\%s"), strRootDirectoryPath, SysIniFileName);

	::GetPrivateProfileString(_T("Setting"), _T("EpoStar"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtSysParam->bEpoStar = (BYTE)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("Setting"), _T("Config_File"), _T("Default.ini"), cBuf, sizeof(cBuf), strPath);
	srtSysParam->strConfigFile.Format(_T("%s"), cBuf);

	//port setting
	for(i=0; i<MP_MAX_DISKS; i++)
	{
		strInfo.Format(_T("SN%d"), i + 1);
		::GetPrivateProfileString(_T("USBPortSetting"), strInfo, _T(""), cBuf, sizeof(cBuf), strPath);
		srtSysParam->strPortSN[i].Format(_T("%s"), cBuf);
	}
}

void CShareFunctions::SaveSysIniFile(CString strRootDirectoryPath, SYSTEM_PARAM* srtSysParam)
{
	CString strPath;
	CString strInfo;
	int i;

	strPath.Format(_T("%s\\%s"), strRootDirectoryPath, SysIniFileName);

	strInfo.Format(_T("%d"), srtSysParam->bEpoStar);
	::WritePrivateProfileString(_T("Setting"), _T("EpoStar"), strInfo, strPath);
	::WritePrivateProfileString(_T("Setting"), _T("Config_File"), srtSysParam->strConfigFile, strPath);
	//port setting
	for(i=0; i<MP_MAX_DISKS; i++)
	{
		strInfo.Format(_T("SN%d"), i + 1);
		::WritePrivateProfileString(_T("USBPortSetting"), strInfo, srtSysParam->strPortSN[i], strPath);
	}
}

void CShareFunctions::GetConfigFiles(CString strRootDirectoryPath, CString strBoardType, CString strBinPath, BOOL boRDTFlag, int* iFileCount, CComboBox* cmbConfigList)
{
	CString strConfigPath;
	CString strConfigName;
	CString strInfo;
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	int iGetCount = 0;
	char cBuf[256];
	int iFindStatus = 0;
	BOOL boFindConfig = FALSE;

	cmbConfigList->ResetContent();
	
	strInfo.Format(_T("%s\\%s\\%s\\%s"), strRootDirectoryPath, BinFolderName, strBinPath, ConfigFileType);
	hFind = ::FindFirstFile(strInfo, &FindFileData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				strConfigName.Format(_T("%s"), FindFileData.cFileName);
				strConfigPath.Format(_T("%s\\%s\\%s\\%s"), strRootDirectoryPath, BinFolderName, strBinPath, strConfigName);
				::GetPrivateProfileString(_T("OtherSetting"), _T("Config_Type"), _T(""), cBuf, sizeof(cBuf), strConfigPath);
				strInfo.Format(_T("%s"), cBuf);
				if(strInfo.Compare(strBoardType) == 0)
				{
					iFindStatus = strConfigName.Find("RDT");
					if((iFindStatus >= 0) && (iFindStatus != 0xFFFFFFFF))
					{
						if(boRDTFlag)
							boFindConfig = TRUE;
					}
					else
					{
						if(!boRDTFlag)
							boFindConfig = TRUE;
					}
					if(boFindConfig)
					{
						boFindConfig = FALSE;
						cmbConfigList->AddString(strConfigName);
						iGetCount++;
					}
				}
			}
		}while(::FindNextFile(hFind, &FindFileData));
		::FindClose(hFind);
	}
	if(iGetCount > 0)
		cmbConfigList->SetCurSel(0);
	*iFileCount = iGetCount;
}

BOOL CShareFunctions::GetStructItems(CString strRootDirectoryPath, BOOL boRDTFlag, STRUCT_PARAM* srtStructParam)
{
	BOOL boRtnStatus = FALSE;
	char cBuf[256];
	CString strPath;
	CString strItem;
	CString strInfo;
	WORD wItemCount = 0;
	WORD i;

	if(boRDTFlag)
		strPath.Format(_T("%s\\%s"), strRootDirectoryPath, RDTStructFileName);
	else
		strPath.Format(_T("%s\\%s"), strRootDirectoryPath, SYSStructFileName);
	boRtnStatus = PathFileExists(strPath);
	if(!boRtnStatus)
		return boRtnStatus;
	::GetPrivateProfileString(_T("Setting"), _T("StructureVersion"), _T("1"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtStructParam->dwStructVersion = (DWORD)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("Setting"), _T("ItemAmount"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	wItemCount = (WORD)this->GetStrValue(strInfo);
	srtStructParam->wItemAmount = wItemCount;
	if(wItemCount > MAX_ITEM_AMOUNT)
		wItemCount = MAX_ITEM_AMOUNT;
	for(i=0; i<wItemCount; i++)
	{
		strItem.Format(_T("Item_%d"), i+1);
		::GetPrivateProfileString(strItem, _T("ItemOffset"), _T("0"), cBuf, sizeof(cBuf), strPath);
		strInfo.Format(_T("%s"), cBuf);
		srtStructParam->srtItemParam[i].wOffset = (WORD)this->GetStrValue(strInfo);
		::GetPrivateProfileString(strItem, _T("ItemLength"), _T("0"), cBuf, sizeof(cBuf), strPath);
		strInfo.Format(_T("%s"), cBuf);
		srtStructParam->srtItemParam[i].bLength = (BYTE)this->GetStrValue(strInfo);
		::GetPrivateProfileString(strItem, _T("ItemType"), _T("0"), cBuf, sizeof(cBuf), strPath);
		strInfo.Format(_T("%s"), cBuf);
		srtStructParam->srtItemParam[i].boType = (BOOL)this->GetStrValue(strInfo);
		::GetPrivateProfileString(strItem, _T("ItemModify"), _T("0"), cBuf, sizeof(cBuf), strPath);
		strInfo.Format(_T("%s"), cBuf);
		srtStructParam->srtItemParam[i].boDisplay = (BOOL)this->GetStrValue(strInfo);
		::GetPrivateProfileString(strItem, _T("ItemName"), _T("0"), cBuf, sizeof(cBuf), strPath);
		srtStructParam->srtItemParam[i].strName.Format(_T("%s"), cBuf);
		srtStructParam->srtItemParam[i].strValue = _T("");
	}
	return boRtnStatus;
}

void CShareFunctions::GetProductionParam(CString strRootDirectoryPath, CString strBinPath, CString strFileName, STRUCT_PARAM* srtStructParam, SERIAL_NUMBER_PARAM* srtSNParam, QUICK_TEST_PARAM* srtQuickTestParam, OTHER_SETTING* srtOtherParam)
{
	char cBuf[1024];
	CString strPath;
	CString strInfo;
	WORD i;

	strPath.Format(_T("%s\\%s\\%s\\%s"), strRootDirectoryPath.GetString(), BinFolderName, strBinPath.GetString(), strFileName.GetString());

	//ProductionParam
	GetProductionParamValuesFromFile(strPath, srtStructParam);

	//SerialNumInfo
	::GetPrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Rule"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtSNParam->bSNRule = (BYTE)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Begin"), _T("SN000000000000000001"), cBuf, sizeof(cBuf), strPath);
	srtSNParam->strBeginSN.Format(_T("%s"), cBuf);
	::GetPrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_End"), _T("SN000000000000100000"), cBuf, sizeof(cBuf), strPath);
	srtSNParam->strEndSN.Format(_T("%s"), cBuf);
	::GetPrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Mask"), _T("SN000000000000######"), cBuf, sizeof(cBuf), strPath);
	srtSNParam->strSNMask.Format(_T("%s"), cBuf);
	::GetPrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Reset_Count"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtSNParam->dwSNResetCount = (DWORD)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Pass_Count"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtSNParam->dwSNPassCount = (DWORD)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Fail_Count"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtSNParam->dwSNFailCount = (DWORD)this->GetStrValue(strInfo);

	//QuickTest
	::GetPrivateProfileString(_T("QuickTest"), _T("Enable_DDR_Test"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtQuickTestParam->boDDRTest = (BOOL)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("QuickTest"), _T("Enable_Flash_Test"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtQuickTestParam->boFlashTest = (BOOL)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("QuickTest"), _T("Enable_SPI_Test"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtQuickTestParam->boSPITest = (BOOL)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("QuickTest"), _T("Enable_Thermal_Test"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtQuickTestParam->boThermalTest = (BOOL)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("QuickTest"), _T("Enable_Efuse_Test"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtQuickTestParam->boEfuseTest = (BOOL)this->GetStrValue(strInfo);

	//OtherSetting
	::GetPrivateProfileString(_T("OtherSetting"), _T("Config_Type"), _T("Micron_B16A_512G"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtOtherParam->strConfigType = strInfo;
	::GetPrivateProfileString(_T("OtherSetting"), _T("Capacity_Method"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtOtherParam->bCapacityMethod = (BYTE)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("OtherSetting"), _T("Enable_Force_Erase"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtOtherParam->boForceErase = (BOOL)this->GetStrValue(strInfo);
	::GetPrivateProfileString(_T("OtherSetting"), _T("Enable_Quick_Test"), _T("0"), cBuf, sizeof(cBuf), strPath);
	strInfo.Format(_T("%s"), cBuf);
	srtOtherParam->bQuickTest = (BYTE)this->GetStrValue(strInfo);
}

void CShareFunctions::GetProductionParamValuesFromFile(CString fileFullName, STRUCT_PARAM* srtStructParam)
{
	char cBuf[1024];
	CString strItemName;
	CString strInfo;
	WORD wItemCount = srtStructParam->wItemAmount;
	WORD i;

	//ProductionParam
	for (i = 0; i < wItemCount; i++)
	{
		strItemName.Format(_T("%s"), srtStructParam->srtItemParam[i].strName);
		::GetPrivateProfileString(_T("ProductionParam"), strItemName, _T("0"), cBuf, sizeof(cBuf), fileFullName);
		srtStructParam->srtItemParam[i].strValue.Format(_T("%s"), cBuf);
	}
}

void CShareFunctions::SaveProductionParam(CString strRootDirectoryPath, CString strBinPath, CString strFileName, STRUCT_PARAM* srtStructParam, SERIAL_NUMBER_PARAM* srtSNParam, FLASH_MAPPING* srtFlashParam, QUICK_TEST_PARAM* srtQuickTestParam, OTHER_SETTING* srtOtherParam, BOOL boNewFile)
{
	CString strPath;
	CString strItemName;
	CString strInfo;
	CTime ctCurrent;
	WORD wItemCount = srtStructParam->wItemAmount;
	WORD i;

	strPath.Format(_T("%s\\%s\\%s\\%s"), strRootDirectoryPath, BinFolderName, strBinPath, strFileName);
	ctCurrent = CTime::GetCurrentTime();
	//ProductionParam
	for(i=0; i<wItemCount; i++)
	{
		strItemName.Format(_T("%s"), srtStructParam->srtItemParam[i].strName);
		if(strItemName == _T("Sys_MP_Time_YY"))
			srtStructParam->srtItemParam[i].strValue.Format(_T("%d"), ctCurrent.GetYear());
		if(strItemName == _T("Sys_MP_Time_MM"))
			srtStructParam->srtItemParam[i].strValue.Format(_T("%d"), ctCurrent.GetMonth());
		if(strItemName == _T("Sys_MP_Time_DD"))
			srtStructParam->srtItemParam[i].strValue.Format(_T("%d"), ctCurrent.GetDay());
		if(strItemName == _T("Sys_MP_Version_Major"))
			srtStructParam->srtItemParam[i].strValue.Format(_T("%d"), MP_MAJOR_VERSION);
		if(strItemName == _T("Sys_MP_Version_Minor"))
			srtStructParam->srtItemParam[i].strValue.Format(_T("%d"), MP_MINOR_VERSION);
		if(strItemName == _T("NVMe_Serial_Num"))
			srtStructParam->srtItemParam[i].strValue.Format(_T(""));
		::WritePrivateProfileString(_T("ProductionParam"), strItemName, srtStructParam->srtItemParam[i].strValue, strPath);
	}

	//SerialNumInfo
	if(boNewFile)
	{
		srtSNParam->dwSNResetCount = 0;
		srtSNParam->dwSNPassCount = 0;
		srtSNParam->dwSNFailCount = 0;
	}
	strInfo.Format(_T("%d"), srtSNParam->bSNRule);
	::WritePrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Rule"), strInfo, strPath);
	::WritePrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Begin"), srtSNParam->strBeginSN, strPath);
	::WritePrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_End"), srtSNParam->strEndSN, strPath);
	::WritePrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Mask"), srtSNParam->strSNMask, strPath);
	strInfo.Format(_T("%d"), srtSNParam->dwSNResetCount);
	::WritePrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Reset_Count"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtSNParam->dwSNPassCount);
	::WritePrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Pass_Count"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtSNParam->dwSNFailCount);
	::WritePrivateProfileString(_T("SerialNumInfo"), _T("Serial_Num_Fail_Count"), strInfo, strPath);

	//FlashInfo
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_Type"), srtFlashParam->strType, strPath);
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_Part_Num"), srtFlashParam->strPartNumber, strPath);
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_ID"), srtFlashParam->strID, strPath);
	strInfo.Format(_T("%d"), srtFlashParam->wDieCapacityGb);
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_Die_Capacity_Gb"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtFlashParam->bLunPerTarget);
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_Lun_Per_Target"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtFlashParam->bPlanePerLun);
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_Plane_Per_Lun"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtFlashParam->wBlkPerPlane);
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_Block_Per_Plane"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtFlashParam->wPagePerBlk);
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_Page_Per_Block"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtFlashParam->wPageSize);
	::WritePrivateProfileString(_T("FlashInfo"), _T("Flash_Page_Size"), strInfo, strPath);

	//QuickTest
	strInfo.Format(_T("%d"), srtQuickTestParam->boDDRTest);
	::WritePrivateProfileString(_T("QuickTest"), _T("Enable_DDR_Test"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtQuickTestParam->boFlashTest);
	::WritePrivateProfileString(_T("QuickTest"), _T("Enable_Flash_Test"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtQuickTestParam->boSPITest);
	::WritePrivateProfileString(_T("QuickTest"), _T("Enable_SPI_Test"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtQuickTestParam->boThermalTest);
	::WritePrivateProfileString(_T("QuickTest"), _T("Enable_Thermal_Test"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtQuickTestParam->boEfuseTest);
	::WritePrivateProfileString(_T("QuickTest"), _T("Enable_Efuse_Test"), strInfo, strPath);

	//OtherSetting
	::WritePrivateProfileString(_T("OtherSetting"), _T("Config_Type"), srtOtherParam->strConfigType, strPath);
	strInfo.Format(_T("%d"), srtOtherParam->bCapacityMethod);
	::WritePrivateProfileString(_T("OtherSetting"), _T("Capacity_Method"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtOtherParam->boForceErase);
	::WritePrivateProfileString(_T("OtherSetting"), _T("Enable_Force_Erase"), strInfo, strPath);
	strInfo.Format(_T("%d"), srtOtherParam->bQuickTest);
	::WritePrivateProfileString(_T("OtherSetting"), _T("Enable_Quick_Test"), strInfo, strPath);
}

BOOL CShareFunctions::GetFlashParam(CString strRootDirectoryPath, CString strVendor, CString strFlashID, FLASH_MAPPING *srtFlashParam)
{
	CString strPath;
	BOOL boFind = FALSE;
	int iDataCount = 0;
	CString strContent[10];
	char cBuf[1024];
	int i, j;
	CString strInfo;
	int iStatus;
	CString strTmp;
	unsigned __int64 ui64Value = 0;

	strPath.Format(_T("%s\\%s"), strRootDirectoryPath, FlashMappingFile);

	for(i=0; i<MAX_FLASH_AMOUNT; i++)
	{
		if(strVendor == FLASH_VENDOR_MICRON)
			strInfo.Format(_T("M%d"), i);
		::GetPrivateProfileString(strVendor, strInfo, _T(""), cBuf, sizeof(cBuf), strPath);
		strInfo.Format(_T("%s"), cBuf);
		if(strInfo.IsEmpty())
			break;
		strTmp = strInfo;
		iDataCount = strTmp.Remove(',');
		strTmp = strInfo;
		strTmp.TrimLeft();
		for(j=0; j<=iDataCount; j++)
		{
			iStatus = strTmp.Find(',');
			if(iStatus >= 0)
			{
				strContent[j] = strTmp.Left(iStatus);
				strTmp = strTmp.Right(strTmp.GetLength() - iStatus - 1);
				strTmp.TrimLeft();
			}
			else
				strContent[j] = strTmp;
		}
		strContent[2].Replace(' ', ',');
		if(strContent[2] == strFlashID)
		{
			boFind = TRUE;
			break;
		}
	}
	if(boFind)
	{
		srtFlashParam->strType = strContent[0];
		srtFlashParam->strPartNumber = strContent[1];
		srtFlashParam->strID = strContent[2];
		ui64Value = this->GetStrValue(strContent[3]);
		srtFlashParam->wDieCapacityGb = (WORD)ui64Value;
		ui64Value = this->GetStrValue(strContent[4]);
		srtFlashParam->bLunPerTarget = (BYTE)ui64Value;
		ui64Value = this->GetStrValue(strContent[5]);
		srtFlashParam->bPlanePerLun = (BYTE)ui64Value;
		ui64Value = this->GetStrValue(strContent[6]);
		srtFlashParam->wBlkPerPlane = (WORD)ui64Value;
		ui64Value = this->GetStrValue(strContent[7]);
		srtFlashParam->wPagePerBlk = (WORD)ui64Value;
		ui64Value = this->GetStrValue(strContent[8]);
		srtFlashParam->wPageSize = (WORD)ui64Value;
		srtFlashParam->strBinPath = strContent[9];
		return TRUE;
	}
	return FALSE;
}

BOOL CShareFunctions::CheckAPProcess(CString strTerminateProcessName)
{
	BOOL bStatus = FALSE;
	PROCESSENTRY32 pServer;
    pServer.dwSize = sizeof(pServer);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL bMore = ::Process32First(hProcessSnap,&pServer);
	DWORD m_ProcessID;
	
	CString strAppName;
	CString strTempAppName = strTerminateProcessName;
	strTempAppName.MakeUpper();
	
	while(bMore)
    {
		strAppName = pServer.szExeFile;
		strAppName.MakeUpper();

		if(strAppName.Find(strTempAppName) != -1)
		{
			bStatus = TRUE;
			m_ProcessID = pServer.th32ProcessID;
			break;
		}

		bMore = ::Process32Next(hProcessSnap,&pServer);
	}

	::CloseHandle(hProcessSnap);
	return bStatus;
}

void CShareFunctions::SetDeletePartitionSetupInfo(int iPhysicalIndex)
{
	DWORD rpt = 0;
	HANDLE fHandle = NULL;
	CString strTmp, strFileName, strFileExtension;
	char cBuffer[8192];

	strFileExtension = SETUPINFO_EXTENSION;

	::memset(cBuffer, 0, sizeof(cBuffer));
	::sprintf_s(cBuffer, sizeof(cBuffer), " list disk""\n select disk %d""\n clean ", iPhysicalIndex);

	strTmp = SETUPINFO_CLEAN;
	strFileName.Format(_T("%s%d.%s"), strTmp, iPhysicalIndex, strFileExtension);

	try
	{
		::DeleteFile(strFileName);

		fHandle = ::CreateFile(strFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
		if(fHandle)
		{
			::SetFilePointer(fHandle, 0, NULL, FILE_BEGIN);
			::WriteFile(fHandle, cBuffer, (DWORD)strlen(cBuffer), &rpt, NULL);
			::CloseHandle(fHandle);
		}
	}
	catch(...)
	{
	}
}

void CShareFunctions::DeleteSetupInfo(int iPhysicalIndex)
{
	CString strTmp, strFileExtension;
	CString strCreateFile, strDeleteFile;

	strFileExtension = SETUPINFO_EXTENSION;

	strTmp = SETUPINFO_CLEAN;

	strDeleteFile.Format(_T("%s%d.%s"), strTmp, iPhysicalIndex, strFileExtension);
	::DeleteFile(strDeleteFile);
}

void CShareFunctions::RunDeletePartitionSetupFunc(int iPhysicalIndex)
{
	CString strInfo;
	CString strTmp, strFileExtension;
	SHELLEXECUTEINFO SEI;

	strFileExtension = SETUPINFO_EXTENSION;
	strTmp = SETUPINFO_CLEAN;
	strInfo.Format(_T(" /s %s%d.%s"), strTmp, iPhysicalIndex, strFileExtension);
	
	::ZeroMemory(&SEI, sizeof(SHELLEXECUTEINFO));
	SEI.cbSize = sizeof(SHELLEXECUTEINFO);
	SEI.lpFile = PARTITION_AP;
	SEI.nShow = SW_HIDE;
	SEI.lpParameters = strInfo;
	ShellExecuteEx(&SEI);
}

BOOL CShareFunctions::USBBridgeCmd(HANDLE hDeviceIOCTL, BOOL boAdmin, BYTE bProtocol, DWORD dwTransferLength, BYTE bDataInOut, ULONG ulTimeout, BYTE* bIOBuf)
{
	BOOL boRtnStatus = 0;
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER sptdwb;
	BYTE bControl = 0;
	ULONG length, returned;

	if(ulTimeout == 0)
		ulTimeout = CMD_TIMEOUT;

	::memset(&sptdwb, 0, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));

	sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptdwb.sptd.PathId = 0;
	sptdwb.sptd.TargetId = 1;
	sptdwb.sptd.Lun = 0;
	sptdwb.sptd.CdbLength = CDB_LENGTH;
	sptdwb.sptd.SenseInfoLength = 0;
	sptdwb.sptd.DataIn = bDataInOut;
	sptdwb.sptd.DataTransferLength = dwTransferLength;
	sptdwb.sptd.TimeOutValue = ulTimeout;
	sptdwb.sptd.DataBuffer = bIOBuf;
	sptdwb.sptd.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

	sptdwb.sptd.Cdb[0] = OPERATION_CODE;
	sptdwb.sptd.Cdb[1] = ((boAdmin & 0x01) << 7) | (bProtocol & 0xFF);
	sptdwb.sptd.Cdb[3] = (BYTE)(dwTransferLength >> 16) & 0xFF;
	sptdwb.sptd.Cdb[4] = (BYTE)(dwTransferLength >> 8) & 0xFF;
	sptdwb.sptd.Cdb[5] = (BYTE)dwTransferLength & 0xFF;
	sptdwb.sptd.Cdb[11] = bControl;

	length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
	boRtnStatus = ::DeviceIoControl(hDeviceIOCTL, IOCTL_SCSI_PASS_THROUGH_DIRECT, &sptdwb, length, &sptdwb, length, &returned, NULL);

	return boRtnStatus;
}

BOOL CShareFunctions::SendNVMeByUSB(HANDLE hDeviceIOCTL, COMMAND_SET srtCommandSet, BYTE* bIOBuf)
{
	BOOL boRtnStatus = 1;
	BOOL boAdmin = 1;
	BYTE bBridgeBuf[BRIDGE_DATA_LENGTH];
	BYTE bSetDataInOut;

	this->dwCompletionQueueEntry[0] = 0;
	this->dwCompletionQueueEntry[1] = 0;
	this->dwCompletionQueueEntry[2] = 0;
	this->dwCompletionQueueEntry[3] = 0;

	::memset(bBridgeBuf, 0, BRIDGE_DATA_LENGTH);
	bBridgeBuf[0] = 'N';
	bBridgeBuf[1] = 'V';
	bBridgeBuf[2] = 'M';
	bBridgeBuf[3] = 'E';
	bBridgeBuf[8] = srtCommandSet.bOpcode;
	bBridgeBuf[48] = (BYTE)srtCommandSet.dw10 & 0xFF;
	bBridgeBuf[49] = (BYTE)(srtCommandSet.dw10 >> 8) & 0xFF;
	bBridgeBuf[50] = (BYTE)(srtCommandSet.dw10 >> 16) & 0xFF;
	bBridgeBuf[51] = (BYTE)(srtCommandSet.dw10 >> 24) & 0xFF;
	bBridgeBuf[52] = (BYTE)srtCommandSet.dw11 & 0xFF;
	bBridgeBuf[53] = (BYTE)(srtCommandSet.dw11 >> 8) & 0xFF;
	bBridgeBuf[54] = (BYTE)(srtCommandSet.dw11 >> 16) & 0xFF;
	bBridgeBuf[55] = (BYTE)(srtCommandSet.dw11 >> 24) & 0xFF;
	bBridgeBuf[56] = (BYTE)srtCommandSet.dw12 & 0xFF;
	bBridgeBuf[57] = (BYTE)(srtCommandSet.dw12 >> 8) & 0xFF;
	bBridgeBuf[58] = (BYTE)(srtCommandSet.dw12 >> 16) & 0xFF;
	bBridgeBuf[59] = (BYTE)(srtCommandSet.dw12 >> 24) & 0xFF;
	bBridgeBuf[60] = (BYTE)srtCommandSet.dw13 & 0xFF;
	bBridgeBuf[61] = (BYTE)(srtCommandSet.dw13 >> 8) & 0xFF;
	bBridgeBuf[62] = (BYTE)(srtCommandSet.dw13 >> 16) & 0xFF;
	bBridgeBuf[63] = (BYTE)(srtCommandSet.dw13 >> 24) & 0xFF;
	bBridgeBuf[64] = (BYTE)srtCommandSet.dw14 & 0xFF;
	bBridgeBuf[65] = (BYTE)(srtCommandSet.dw14 >> 8) & 0xFF;
	bBridgeBuf[66] = (BYTE)(srtCommandSet.dw14 >> 16) & 0xFF;
	bBridgeBuf[67] = (BYTE)(srtCommandSet.dw14 >> 24) & 0xFF;
	bBridgeBuf[68] = (BYTE)srtCommandSet.dw15 & 0xFF;
	bBridgeBuf[69] = (BYTE)(srtCommandSet.dw15 >> 8) & 0xFF;
	bBridgeBuf[70] = (BYTE)(srtCommandSet.dw15 >> 16) & 0xFF;
	bBridgeBuf[71] = (BYTE)(srtCommandSet.dw15 >> 24) & 0xFF;
	bBridgeBuf[72] = srtCommandSet.bVendorControl;

	if(srtCommandSet.bProtocolField == PROTOCOL_DMA_OUT)
		bSetDataInOut = SCSI_IOCTL_DATA_OUT;
	else
		bSetDataInOut = SCSI_IOCTL_DATA_IN;

	boRtnStatus = this->USBBridgeCmd(hDeviceIOCTL, boAdmin, PROTOCOL_SET_PAYLOAD, BRIDGE_DATA_LENGTH, SCSI_IOCTL_DATA_OUT, CMD_TIMEOUT, bBridgeBuf);
	if(boRtnStatus)
		boRtnStatus = this->USBBridgeCmd(hDeviceIOCTL, boAdmin, srtCommandSet.bProtocolField, srtCommandSet.dwDataLength, bSetDataInOut, srtCommandSet.ulTimeout, bIOBuf);
	if(boRtnStatus)
	{
		::memset(bBridgeBuf, 0, BRIDGE_DATA_LENGTH);
		boRtnStatus = this->USBBridgeCmd(hDeviceIOCTL, boAdmin, PROTOCOL_RESPONSE_INFO, BRIDGE_DATA_LENGTH, SCSI_IOCTL_DATA_IN, CMD_TIMEOUT, bBridgeBuf);
		if(boRtnStatus)
		{
			if((bBridgeBuf[22] != 0) || (bBridgeBuf[23] != 0))
				boRtnStatus = FALSE;
		}
		this->dwCompletionQueueEntry[0] = bBridgeBuf[11];
		this->dwCompletionQueueEntry[0] = (this->dwCompletionQueueEntry[0] << 8) + bBridgeBuf[10];
		this->dwCompletionQueueEntry[0] = (this->dwCompletionQueueEntry[0] << 8) + bBridgeBuf[9];
		this->dwCompletionQueueEntry[0] = (this->dwCompletionQueueEntry[0] << 8) + bBridgeBuf[8];
		this->dwCompletionQueueEntry[1] = bBridgeBuf[15];
		this->dwCompletionQueueEntry[1] = (this->dwCompletionQueueEntry[1] << 8) + bBridgeBuf[14];
		this->dwCompletionQueueEntry[1] = (this->dwCompletionQueueEntry[1] << 8) + bBridgeBuf[13];
		this->dwCompletionQueueEntry[1] = (this->dwCompletionQueueEntry[1] << 8) + bBridgeBuf[12];
		this->dwCompletionQueueEntry[2] = bBridgeBuf[19];
		this->dwCompletionQueueEntry[2] = (this->dwCompletionQueueEntry[2] << 8) + bBridgeBuf[18];
		this->dwCompletionQueueEntry[2] = (this->dwCompletionQueueEntry[2] << 8) + bBridgeBuf[17];
		this->dwCompletionQueueEntry[2] = (this->dwCompletionQueueEntry[2] << 8) + bBridgeBuf[16];
		this->dwCompletionQueueEntry[3] = bBridgeBuf[23];
		this->dwCompletionQueueEntry[3] = (this->dwCompletionQueueEntry[3] << 8) + bBridgeBuf[22];
		this->dwCompletionQueueEntry[3] = (this->dwCompletionQueueEntry[3] << 8) + bBridgeBuf[21];
		this->dwCompletionQueueEntry[3] = (this->dwCompletionQueueEntry[3] << 8) + bBridgeBuf[20];
	}

	return boRtnStatus;
}

BOOL CShareFunctions::SendNVMeInbox(HANDLE hDeviceIOCTL, COMMAND_SET srtCommandSet, BYTE *bIOBuf)
{
	BOOL boRtnStatus = FALSE;
	PSTORAGE_PROTOCOL_COMMAND pProtocolCmd = NULL;
	PNVME_COMMAND pCmd = NULL;
	BYTE* bTmpBuf = NULL;
    DWORD dwTmpBufSize = 0;
	DWORD dwRtnLength = 0;

	dwTmpBufSize = FIELD_OFFSET(STORAGE_PROTOCOL_COMMAND, Command) + STORAGE_PROTOCOL_COMMAND_LENGTH_NVME + sizeof(NVME_ERROR_INFO_LOG) + srtCommandSet.dwDataLength;
    bTmpBuf = (BYTE *)::malloc((size_t)dwTmpBufSize);
    if(bTmpBuf == NULL)
        return 0;

	if(srtCommandSet.ulTimeout == 0)
		srtCommandSet.ulTimeout = CMD_TIMEOUT;

	::ZeroMemory(bTmpBuf, dwTmpBufSize);

	pProtocolCmd = (PSTORAGE_PROTOCOL_COMMAND)bTmpBuf;
    pProtocolCmd->Version = STORAGE_PROTOCOL_STRUCTURE_VERSION;
    pProtocolCmd->Length = sizeof(STORAGE_PROTOCOL_COMMAND);
    pProtocolCmd->ProtocolType = ProtocolTypeNvme;
    pProtocolCmd->Flags = STORAGE_PROTOCOL_COMMAND_FLAG_ADAPTER_REQUEST;
    pProtocolCmd->CommandLength = STORAGE_PROTOCOL_COMMAND_LENGTH_NVME;
    pProtocolCmd->ErrorInfoLength = sizeof(NVME_ERROR_INFO_LOG);
	pProtocolCmd->TimeOutValue = srtCommandSet.ulTimeout;
	pProtocolCmd->ErrorInfoOffset = FIELD_OFFSET(STORAGE_PROTOCOL_COMMAND, Command) + STORAGE_PROTOCOL_COMMAND_LENGTH_NVME;
    pProtocolCmd->CommandSpecific = STORAGE_PROTOCOL_SPECIFIC_NVME_ADMIN_COMMAND;

	if(srtCommandSet.bProtocolField == PROTOCOL_DMA_IN)
    {
		pProtocolCmd->DataFromDeviceTransferLength = srtCommandSet.dwDataLength;
        pProtocolCmd->DataFromDeviceBufferOffset = pProtocolCmd->ErrorInfoOffset + pProtocolCmd->ErrorInfoLength;
    }
	else if(srtCommandSet.bProtocolField == PROTOCOL_DMA_OUT)
    {
		pProtocolCmd->DataToDeviceTransferLength = srtCommandSet.dwDataLength;
        pProtocolCmd->DataToDeviceBufferOffset = pProtocolCmd->ErrorInfoOffset + pProtocolCmd->ErrorInfoLength;

		::CopyMemory(((PCHAR)pProtocolCmd + pProtocolCmd->DataToDeviceBufferOffset), bIOBuf, srtCommandSet.dwDataLength);
    }

	pCmd = (PNVME_COMMAND)pProtocolCmd->Command;
	pCmd->CDW0.OPC = srtCommandSet.bOpcode;
	pCmd->NSID = srtCommandSet.dwNSID;
	pCmd->u.GENERAL.CDW10 = srtCommandSet.dw10;
	pCmd->u.GENERAL.CDW11 = srtCommandSet.dw11;
	pCmd->u.GENERAL.CDW12 = srtCommandSet.dw12;
	pCmd->u.GENERAL.CDW13 = srtCommandSet.dw13;
	pCmd->u.GENERAL.CDW14 = srtCommandSet.dw14;
	pCmd->u.GENERAL.CDW15 = srtCommandSet.dw15;

	boRtnStatus = ::DeviceIoControl(hDeviceIOCTL, IOCTL_STORAGE_PROTOCOL_COMMAND, bTmpBuf, dwTmpBufSize, bTmpBuf, dwTmpBufSize, &dwRtnLength, NULL);
	if(boRtnStatus && (srtCommandSet.bProtocolField == PROTOCOL_DMA_IN))
		::CopyMemory(bIOBuf, ((PCHAR)pProtocolCmd + pProtocolCmd->DataToDeviceBufferOffset) + 0xD0, srtCommandSet.dwDataLength);

	this->dwCompletionQueueEntry[0] = 0xFFFFFFFF;
	this->dwCompletionQueueEntry[1] = 0xFFFFFFFF;
	this->dwCompletionQueueEntry[2] = 0xFFFFFFFF;
	this->dwCompletionQueueEntry[3] = 0xFFFFFFFF;

	::free(bTmpBuf);

	return boRtnStatus;
}

BOOL CShareFunctions::SendNVMeCmd(HANDLE hDeviceIOCTL, COMMAND_SET srtCommandSet, BYTE *bIOBuf, BYTE bBusType)
{
	BOOL boRtnStatus = FALSE;

	this->dwCompletionQueueEntry[0] = 0xFFFFFFFF;
	this->dwCompletionQueueEntry[1] = 0xFFFFFFFF;
	this->dwCompletionQueueEntry[2] = 0xFFFFFFFF;
	this->dwCompletionQueueEntry[3] = 0xFFFFFFFF;

	if(bBusType == BusTypeUsb)
		boRtnStatus = SendNVMeByUSB(hDeviceIOCTL, srtCommandSet, bIOBuf);
	else
		boRtnStatus = SendNVMeInbox(hDeviceIOCTL, srtCommandSet, bIOBuf);

	return boRtnStatus;
}

BOOL CShareFunctions::StrParsing(CString strValue, int iParsingMode, unsigned __int64 *ui64Value)
{
	BOOL boRtnStatus = FALSE;
	int iStrLength;
	char cStrContent[32] = {0};
	int i;
	unsigned __int64 ui64Tmp = 0;

	iStrLength = strValue.GetLength();
	if(iStrLength <= 0)
		return boRtnStatus;
	if((iParsingMode == PARSING_MODE_PATTERN) && (iStrLength > 8))
		return boRtnStatus;
	boRtnStatus = TRUE;
	*ui64Value = 0;
	::memcpy(cStrContent, strValue, iStrLength);
	for(i=0; i<iStrLength; i++)
	{
		if(iParsingMode == PARSING_MODE_DEC)
		{
			if(cStrContent[i] >= '0' && cStrContent[i] <= '9')
				*ui64Value = (*ui64Value * 10) + (cStrContent[i] - '0');
			else if((cStrContent[i] == 'k') || (cStrContent[i] == 'K'))
				*ui64Value = *ui64Value * 1024;
			else if((cStrContent[i] == 'm') || (cStrContent[i] == 'M'))
				*ui64Value = *ui64Value * 1024 * 1024;
			else if((cStrContent[i] == 'g') || (cStrContent[i] == 'G'))
				*ui64Value = *ui64Value * 1024 * 1024 * 1024;
			else if((cStrContent[i] == 't') || (cStrContent[i] == 'T'))
				*ui64Value = *ui64Value * 1024 * 1024 * 1024 * 1024;
			else
			{
				boRtnStatus = FALSE;
				break;
			}
		}
		else if((iParsingMode == PARSING_MODE_HEX) || (iParsingMode == PARSING_MODE_PATTERN))
		{
			if (cStrContent[i] >= '0' && cStrContent[i] <= '9')
				ui64Tmp = (ui64Tmp << 4) + (cStrContent[i] - '0');
			else if (cStrContent[i] >= 'a' && cStrContent[i] <= 'f')
				ui64Tmp = (ui64Tmp << 4) + (cStrContent[i] - 'a' + 10);
			else if (cStrContent[i] >= 'A' && cStrContent[i] <= 'F')
				ui64Tmp = (ui64Tmp << 4) + (cStrContent[i] - 'A' + 10);
			else
			{
				boRtnStatus = FALSE;
				break;
			}
		}
		else
		{
			boRtnStatus = FALSE;
			break;
		}
	}
	if((iParsingMode == PARSING_MODE_HEX) || (iParsingMode == PARSING_MODE_PATTERN))
		*ui64Value = ui64Tmp;
	if(boRtnStatus && (iParsingMode == PARSING_MODE_PATTERN))
	{
		if(iStrLength <= 2)
		{
			*ui64Value = (*ui64Value << 8) + ui64Tmp;
			*ui64Value = (*ui64Value << 8) + ui64Tmp;
			*ui64Value = (*ui64Value << 8) + ui64Tmp;
		}
		else if(iStrLength <= 4)
		{
			*ui64Value = (*ui64Value << 16) + ui64Tmp;
		}
	}
	return boRtnStatus;
}