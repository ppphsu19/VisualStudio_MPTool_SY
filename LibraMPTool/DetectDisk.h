#ifndef _DETECTDISK_H_
#define _DETECTDISK_H_

#include "StorageQuery.h"
#include "ShareFunctions.h"


#define MAX_DISKS 26
#define MAX_INFO_LEN 256
#define NVMe_IDENTIFY_BUFFER_SIZE 4096
#define DFP_RECEIVE_DRIVE_DATA 0x0007c088
#define IDE_ATA_IDENTIFY 0xEC

typedef struct
{
	BYTE bDiskBusType;
	int iPhysicalDiskIndex;
	CHAR cModelName[MAX_INFO_LEN];
	CHAR cSerialNumber[MAX_INFO_LEN];
	CHAR cFirmwareVersion[MAX_INFO_LEN];
	CHAR cDriveName[MAX_INFO_LEN];
	CHAR cFileSystem[MAX_INFO_LEN];
	CHAR cUSBBridgeSN[MAX_INFO_LEN];
	unsigned __int64 ui64LBA;
	int iSectorSize;
	int	iGBCapacity;
	CString strCapacity;
	int iFWMode;
	BOARD_INFO srtBoardInfo;
} DISKINFO;


class CDetectDisk  : public CShareFunctions
{
public:
	DISKINFO srtDiskInfo[MAX_DISKS];
	CHAR cExistDrive[MAX_DISKS];
	int	iDiskAmount;
	int iDriveAmount;

	void ScanDisks();

private:
	BYTE bTmpBridgeSN[MAX_INFO_LEN];
	BYTE bIdentifyDataSATA[IDENTIFY_BUFFER_SIZE];
	BYTE bIdentifyDataNVMe[NVMe_IDENTIFY_BUFFER_SIZE];
	PADMIN_IDENTIFY_CONTROLLER pIdCtrlr;

	void DetectDisks();
	void DetectDrives();
	BOOL DetectUSB(HANDLE hDeviceIOCTL);
	BOOL DetectSATA(HANDLE hDeviceIOCTL);
	BOOL DetectNVMeInbox(HANDLE hDeviceIOCTL);
	BOOL DetectNVMeOther(HANDLE hDeviceIOCTL);
	BYTE* FlipData(const BYTE* str, int pos, int flip, BYTE* buf);
	BOOL DecodeData(int iDiskIndex, HANDLE hDeviceIOCTL, int iBusType);
	BOOL GetDriveGeometryEx(int PhysicalNumber, DISK_GEOMETRY_EX *pdg);
	BOOL GetScsiPath(CString strPath, CString* strpRtnValue);
	BOOL GetFWMode(HANDLE hDeviceIOCTL, BYTE bBusType);
	BOOL GetBoardInfo(HANDLE hDeviceIOCTL, BYTE bBusType);
	BOOL DecodeBoardInfoData(BYTE* bDataBuf);
};

#endif