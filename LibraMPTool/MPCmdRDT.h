#ifndef _MPCMDRDT_H_
#define _MPCMDRDT_H_

#include "MPCmd.h"

class CMPCmdRDT : public CMPCmd
{
public:
	CMPCmdRDT();
	BOOL DoMPFlowFunc(int iPortIndex, HANDLE hDevice, CString strSN, BOOL boForceErase, STRUCT_PARAM* srtStructParam, BYTE bBusType, CLabel* lblInfo, CTextProgressCtrl* pgsPort) override;
	BOOL SendSetProductParamCmd(HANDLE hDevice, DWORD dwDataLength, BYTE* bDataBuf, BYTE bBusType) override;
};
#endif//_MPCMDRDT_H_

