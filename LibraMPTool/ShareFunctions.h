#ifndef _SHAREFUNCTIONS_H_
#define _SHAREFUNCTIONS_H_
#include "nvme.h"
#include <tlhelp32.h>
#include <afxmt.h>
#include <shlwapi.h>

#pragma comment(lib,"Shlwapi.lib")

#define LogFolderName _T("Log")
#define BinFolderName _T("Bin")
#define ConfigFolderName _T("Config")
#define ConfigFileType _T("*.ini")
#define SysIniFileName _T("System.ini")
#define SYSStructFileName _T("SYS.set")
#define RDTStructFileName _T("RDT.set")
#define FlashMappingFile _T("FlashMapping.ini")

#define FLASH_VENDOR_MICRON _T("Micron")

#define PHYSICAL_DRIVE_PATH _T("\\\\.\\PhysicalDrive")
#define CMD_TIMEOUT 10

#define MAX_FLASH_AMOUNT 100

#define MP_MAJOR_VERSION 0x0001
#define MP_MINOR_VERSION 0x0001
#define MAX_ITEM_AMOUNT 1024

#define STORAGE_PROTOCOL_COMMAND_LENGTH_NVME 0x40
#define STORAGE_PROTOCOL_COMMAND_FLAG_ADAPTER_REQUEST 0x80000000
#define STORAGE_PROTOCOL_STRUCTURE_VERSION 0x1
#define STORAGE_PROTOCOL_SPECIFIC_NVME_ADMIN_COMMAND    0x01
#define STORAGE_PROTOCOL_SPECIFIC_NVME_NVM_COMMAND      0x02
#define IOCTL_STORAGE_PROTOCOL_COMMAND CTL_CODE(IOCTL_STORAGE_BASE, 0x04F0, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

#define MAX_QUEUE_DEPTH 1024
#define SYS_MAX_LENGTH 128*1024

#define TOOL_NAME_INFO_OFFSET 0
#define LBA_INFO_OFFSET 16
#define LOOP_INFO_OFFSET 32
#define DATE_TIME_INFO_OFFSET 48

#define CDB_LENGTH 12
#define OPERATION_CODE 0xA1
#define PROTOCOL_SET_PAYLOAD 0
#define PROTOCOL_NON_DATA 1
#define PROTOCOL_DMA_IN 2
#define PROTOCOL_DMA_OUT 3
#define PROTOCOL_RESPONSE_INFO 15
#define TO_SERVICE_ADMIN_PROTOCOL_FIELD 0
#define PCIE_POWER_OFF 1
#define PCIE_POWER_ON 2
#define INITIAL_PCIE_PRSTN_HIGH 3
#define INITIAL_PCIE_PRSTN_BY_583 4
#define MCU_RESET 5
#define NVME_NORMAL_SHUTDOWN 6
#define BRIDGE_DATA_LENGTH 512

#define PARSING_MODE_DEC 1
#define PARSING_MODE_HEX 2
#define PARSING_MODE_PATTERN 3

#define PARTITION_AP _T("diskpart.exe")
#define SETUPINFO_CLEAN _T("CleanPartition")
#define SETUPINFO_EXTENSION _T("sc")
#define CleanPartitionTimeout 60


typedef struct
{
	BYTE bEpoStar;
	CString strConfigFile;
	CString strPortSN[MP_MAX_DISKS];
} SYSTEM_PARAM;

typedef struct
{
	CString strType;
	CString strPartNumber;
	CString strID;
	WORD wDieCapacityGb;
	BYTE bLunPerTarget;
	BYTE bPlanePerLun;
	WORD wBlkPerPlane;
	WORD wPagePerBlk;
	WORD wPageSize;
	CString strBinPath;
} FLASH_MAPPING;

typedef struct
{
	WORD wOffset;
	BYTE bLength;
	CString strName;
	BOOL boType;
	BOOL boDisplay;
	CString strValue;
} ITEM_PARAM;

typedef struct
{
	DWORD dwStructVersion;
	WORD wItemAmount;
	ITEM_PARAM srtItemParam[MAX_ITEM_AMOUNT];
} STRUCT_PARAM;

typedef struct
{
	BYTE bSNRule;
	CString strBeginSN;
	CString strEndSN;
	CString strSNMask;
	DWORD dwSNResetCount;
	DWORD dwSNPassCount;
	DWORD dwSNFailCount;
} SERIAL_NUMBER_PARAM;

typedef struct
{
	BOOL boDDRTest;
	BOOL boFlashTest;
	BOOL boSPITest;
	BOOL boThermalTest;
	BOOL boEfuseTest;
} QUICK_TEST_PARAM;

typedef struct
{
	CString strConfigType;
	BYTE bCapacityMethod;
	BOOL boForceErase;
	BYTE bQuickTest;
} OTHER_SETTING;

typedef struct
{
	int iChannelNum;
	int iBankNum;
	BYTE bFlashID[8];
} BOARD_INFO;

typedef struct
{
	BYTE bOpcode;
	DWORD dwNSID;
	DWORD dw10;
	DWORD dw11;
	DWORD dw12;
	DWORD dw13;
	DWORD dw14;
	DWORD dw15;
	BYTE bVendorControl;
	DWORD dwDataLength;
	BYTE bProtocolField;
	ULONG ulTimeout;
} COMMAND_SET;

//typedef enum _STORAGE_PROTOCOL_TYPE
//{
//    ProtocolTypeUnknown = 0x00,
//    ProtocolTypeScsi,
//    ProtocolTypeAta,
//    ProtocolTypeNvme,
//    ProtocolTypeSd,
//    ProtocolTypeProprietary = 0x7E,
//    ProtocolTypeMaxReserved = 0x7F
//} STORAGE_PROTOCOL_TYPE, *PSTORAGE_PROTOCOL_TYPE;

//typedef struct _STORAGE_PROTOCOL_COMMAND
//{
//
//    DWORD Version;
//    DWORD Length;
//
//    STORAGE_PROTOCOL_TYPE  ProtocolType;
//    DWORD Flags;
//
//    DWORD ReturnStatus;
//    DWORD ErrorCode;
//
//    DWORD CommandLength;
//    DWORD ErrorInfoLength;
//    DWORD DataToDeviceTransferLength;
//    DWORD DataFromDeviceTransferLength;
//
//    DWORD TimeOutValue;
//
//    DWORD ErrorInfoOffset;
//    DWORD DataToDeviceBufferOffset;
//    DWORD DataFromDeviceBufferOffset;
//
//    DWORD CommandSpecific;
//    DWORD Reserved0;
//
//    DWORD FixedProtocolReturnData;
//    DWORD Reserved1[3];
//
//    BYTE  Command[ANYSIZE_ARRAY];
//
//} STORAGE_PROTOCOL_COMMAND, *PSTORAGE_PROTOCOL_COMMAND;

typedef union
{

    struct
    {
        USHORT  P           : 1;

        USHORT  SC          : 8;
        USHORT  SCT         : 3;
        USHORT  Reserved    : 2;
        USHORT  M           : 1;
        USHORT  DNR         : 1;
    } DUMMYSTRUCTNAME;

    USHORT AsUshort;

} NVME_COMMAND_STATUS, *PNVME_COMMAND_STATUS;

typedef struct
{

    ULONGLONG           ErrorCount;
    USHORT              SQID;
    USHORT              CMDID;
    NVME_COMMAND_STATUS Status;

    struct
    {
        USHORT  Byte        : 8;
        USHORT  Bit         : 3;
        USHORT  Reserved    : 5;
    } ParameterErrorLocation;

    ULONGLONG           Lba;
    ULONG               NameSpace;

    UCHAR               VendorInfoAvailable;

    UCHAR               Reserved0[3];

    ULONGLONG           CommandSpecificInfo;

    UCHAR               Reserved1[24];

} NVME_ERROR_INFO_LOG, *PNVME_ERROR_INFO_LOG;

typedef union
{

    struct
    {
        ULONG   CNS      : 2;
        ULONG   Reserved : 30;
    } DUMMYSTRUCTNAME;

    ULONG AsUlong;

} NVME_CDW10_IDENTIFY, *PNVME_CDW10_IDENTIFY;
//
// Command Dword 0
//
typedef union
{
	//LSB
	ULONG OPC       : 8;
	ULONG FUSE      : 2;
	ULONG Reserved0 : 5;
	ULONG PSDT      : 1;
	ULONG CID       : 16;
	//MSB
    ULONG AsUlong;

} NVME_COMMAND_DWORD0, *PNVME_COMMAND_DWORD0;
//
// NVMe command data structure
//
typedef struct
{
    //
    // Common fields for all commands
    //
    NVME_COMMAND_DWORD0 CDW0;
    ULONG               NSID;
    ULONG               Reserved0[2];
    ULONGLONG           MPTR;
    ULONGLONG           PRP1;
    ULONGLONG           PRP2;

    //
    // Command independent fields from CDW10 to CDW15
    //
    union
    {

        //
        // General Command data fields
        //
        struct
        {
            ULONG   CDW10;
            ULONG   CDW11;
            ULONG   CDW12;
            ULONG   CDW13;
            ULONG   CDW14;
            ULONG   CDW15;
        } GENERAL;

        //
        // Admin Command: Identify
        //
        struct
        {
            NVME_CDW10_IDENTIFY CDW10;
            ULONG   CDW11;
            ULONG   CDW12;
            ULONG   CDW13;
            ULONG   CDW14;
            ULONG   CDW15;
        } IDENTIFY;
    } u;

} NVME_COMMAND, *PNVME_COMMAND;

typedef struct _SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER
{
	SCSI_PASS_THROUGH_DIRECT sptd;
	ULONG             Filler;
	UCHAR             ucSenseBuf[32];
} SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, *PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER;

class CShareFunctions
{
public:
	DWORD dwCompletionQueueEntry[4];

	void WriteLog(CString strWriteInfo, CString strFileName, BOOL boClean);
	CString GetErrorMessage(DWORD dwErrorCode);

	void ShowTestResult(SERIAL_NUMBER_PARAM* srtSNParam, CLabel* lblResult);

	int GetDiskCapacity(int iChannel, int iBank, BYTE bLunPerTarget, WORD wDieCapacityGb);
	unsigned __int64 GetLBNValue(int iCapacityGB);

	unsigned __int64 GetStrValue(CString strValue);
	void GetStrValueFunc(CString strValue, char cFindKey, int iDataLength, BYTE* bValueBuf);

	void GetSysIniFile(CString strRootDirectoryPath, SYSTEM_PARAM* srtSysParam);
	void SaveSysIniFile(CString strRootDirectoryPath, SYSTEM_PARAM* srtSysParam);

	void GetConfigFiles(CString strRootDirectoryPath, CString strBoardType, CString strBinPath, BOOL boRDTFlag, int* iFileCount, CComboBox* cmbConfigList);
	BOOL GetStructItems(CString strRootDirectoryPath, BOOL boRDTFlag, STRUCT_PARAM* srtStructParam);
	void GetProductionParam(CString strRootDirectoryPath, CString strBinPath, CString strFileName, STRUCT_PARAM* srtStructParam, SERIAL_NUMBER_PARAM* srtSNParam, QUICK_TEST_PARAM* srtQuickTestParam, OTHER_SETTING* srtOtherParam);
	void GetProductionParamValuesFromFile(CString fileFullName, STRUCT_PARAM* srtStructParam);
	void SaveProductionParam(CString strRootDirectoryPath, CString strBinPath, CString strFileName, STRUCT_PARAM* srtStructParam, SERIAL_NUMBER_PARAM* srtSNParam, FLASH_MAPPING* srtFlashParam, QUICK_TEST_PARAM* srtQuickTestParam, OTHER_SETTING* srtOtherParam, BOOL boNewFile);
	BOOL GetFlashParam(CString strRootDirectoryPath, CString strVendor, CString strFlashID, FLASH_MAPPING* srtFlashParam);

	BOOL CheckAPProcess(CString strTerminateProcessName);
	void SetDeletePartitionSetupInfo(int iPhysicalIndex);
	void DeleteSetupInfo(int iPhysicalIndex);
	void RunDeletePartitionSetupFunc(int iPhysicalIndex);
	BOOL SendNVMeCmd(HANDLE hDeviceIOCTL, COMMAND_SET srtCommandSet, BYTE* bIOBuf, BYTE bBusType);

	BOOL StrParsing(CString strValue, int iParsingMode, unsigned __int64 *ui64Value);

private:
	CSemaphore mutex;

	BOOL USBBridgeCmd(HANDLE hDeviceIOCTL, BOOL bAdmin, BYTE Protocol, DWORD dwTransferLength, BYTE bDataInOut, ULONG ulTimeout, BYTE* bIOBuf);
	BOOL SendNVMeByUSB(HANDLE hDeviceIOCTL, COMMAND_SET srtCommandSet, BYTE* bIOBuf);
	BOOL SendNVMeInbox(HANDLE hDeviceIOCTL, COMMAND_SET srtCommandSet, BYTE* bIOBuf);

};
#endif