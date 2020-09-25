#ifndef _MPCMD_H_
#define _MPCMD_H_
#include <sys/stat.h>
#include "TextProgressCtrl.h"
#include "ShareFunctions.h"

#define FW_Mode_BK_Color RGB(0x8E, 0x8E, 0x8E)
#define FW_Mode_Text_Color RGB(0xFF, 0xFF, 0xFF)
#define Progress_BK_Color RGB(0xAD, 0xAD, 0xAD)
#define Success_BK_Color RGB(0x00, 0xBB, 0x00)
#define Fail_BK_Color RGB(0xCE, 0x00, 0x00)

#define FW_MODE_ROM 1
#define FW_MODE_BNR 2
#define FW_MODE_RDT 3
#define FW_MODE_SYS 4

#define DOWNLOAD_IMAGE_MAX_LENGTH 0x10000
#define FIX_DATA_LENGTH 4096
#define FIX_FLASH_ID_LENGTH 512
#define TIMEOUT_CHECK_PROGRESS_STATUS 180
#define TIMEOUT_CHECK_CHANGE_MODE 180


typedef struct
{
	WORD wFileAmount;
} CONFIG_FILE_PARAM;

typedef struct
{
	HWND hWndMPInfo;
	int iPortIndex;
	int iDiskPhysicalIndex;
	BYTE bDiskBusType;
	BOOL boPartitionFlag;
	CLabel* m_lblInfo;
	CLabel* m_lblFWMode;
	CTextProgressCtrl* m_pgsPort;
	LPVOID pCmdClass;
	STRUCT_PARAM* srtStructParam;
	QUICK_TEST_PARAM* srtQuickTestParam;
	CString strMPSN;
	DWORD* dwSNPassCount;
	DWORD* dwSNFailCount;
	BOOL boForceErase;
	BYTE bQuickTest;
} MP_THREAD_PARAM;

typedef struct
{
	unsigned __int64 ui64CurrentSN;
	unsigned __int64 ui64BeginSN;
	unsigned __int64 ui64EndSN;
} SN_INFO;

class CMPCmd : public CShareFunctions
{
public:
	CString strLogFilePath;
	CString strFWState[4];
	CString strResult[2];
	int iCmdAmount[MP_MAX_DISKS];
	int iCmdCurrent[MP_MAX_DISKS];

	BOOL ConfirmDiskFlashID();
	void SetFilePath(CString strRootDirectoryPath, CString strBinPath);
	BOOL CheckImage(CString* strErrorMsg);
	void SetMPMsg(int iPortIndex, CString strMsg, CLabel* lblInfo, CTextProgressCtrl* pgsPort);
	BOOL WaitAPProcessDone(int iPortIndex, int iTimeoutSecond, CLabel* lblInfo);
	BOOL DeletePartitionFunc(int iPortIndex, int iPhysicalIndex, int iTimeoutSecond, CLabel* lblInfo);
	BOOL DoSysMode2RomModeFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort);
	BOOL DoRomMode2BnrModeFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort);
	BOOL DoQuickTestFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, QUICK_TEST_PARAM* srtQuickTestParam, CLabel* lblInfo, CTextProgressCtrl* pgsPort);
	virtual BOOL DoMPFlowFunc(int iPortIndex, HANDLE hDevice, CString strSN, BOOL boForceErase, STRUCT_PARAM* srtStructParam, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort);
	BOOL DoBurMode2SysModeFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort);

protected:
	COMMAND_SET srtCommandSet;
	CString strBurnerPath;
	CString strRDTPath;
	CString strSBLPath;
	CString strSYSPath;
	CString strRootDirectoryPath;
	BYTE* bImageBuf;

	//non data
	BOOL SendAPKeyCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendEraseScanCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendFactoryScanCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendRunDownloadImageCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendProgramSBLCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendProgramFWCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendCheckCapacityCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendPreserveBBTandErCntInfo(HANDLE hDevice, BYTE bBusType);
	BOOL SendDDRTestCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendFlashRWTestCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendSPIRWTestCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendThermalSensorTestCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendCheckEfuseTestCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendJump2ROMModeCmd(HANDLE hDevice, int iSelectMode, BYTE bBusType);
	BOOL SendIDPageEraseCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendPreserveRDTCmd(HANDLE hDevice, BYTE bBusType);
	//write
	BOOL SendDownloadImageCmd(HANDLE hDevice, BYTE b64KBIndex, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	virtual BOOL SendSetProductParamCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	//read
	BOOL SendGetBoardInfoCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	BOOL SendGetProgressStatusCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	BOOL SendGetBadBlockTableCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	BOOL SendGetCapacityCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	BOOL SendGetFlashIDCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	BOOL SendScanFlashIDCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	BOOL SendGetFWModeCmd(HANDLE hDevice, BYTE* bFWMode, BYTE bBusType);
	BOOL SendGetErrorCodeAndStatusCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType);
	//power
	BOOL SendPowerOffCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendPowerOnCmd(HANDLE hDevice, BYTE bBusType);
	BOOL SendResetBy583Cmd(HANDLE hDevice, BYTE bBusType);

	BOOL GetFlashIDFunc(HANDLE hDevice, BYTE bBusType);
	BOOL DownloadImageFunc(HANDLE hDevice, CString strFilePath, BYTE bBusType);
	BOOL SetProductParamFunc(HANDLE hDevice, CString strSN, STRUCT_PARAM* srtParam, BYTE bBusType);
	BOOL GetProgressStatusFunc(int iPortIndex, HANDLE hDevice, BYTE bBusType, int iTimeoutSeconds, CLabel* lblInfo);
	BOOL CheckDiskReady(HANDLE hDevice, BYTE bBusType, int iTimeoutSeconds);
};
#endif
UINT Thread_MPFlowFunc(LPVOID pParam);