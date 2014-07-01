#ifndef _EZ430_CHRONOS_CC_H_
#define _EZ430_CHRONOS_CC_H_

#include <stdio.h>
#include "gui2.h"

// TODO Calibration:
// Lay watch flat on table: x and y are 0, z is -50.

extern "C++" {

bool __cdecl BM_Reset();
bool __cdecl BM_GetCOM(unsigned char & bPortNb);
bool __cdecl BM_GetStatus(WORD & wStatus);
bool __cdecl BM_OpenCOM(char * strPortName, DWORD dwBaudrate = 115200, WORD wTimeout = 30, bool bRTS = false, bool bDTR = false);
void __cdecl BM_CloseCOM();

// SimpliciTI communications
bool __cdecl BM_SPL_GetData(DWORD& wData);
bool __cdecl BM_SPL_Start();
bool __cdecl BM_SPL_Stop();

// Sync Mode
bool __cdecl BM_SYNC_GetBufferStatus(WORD &);
bool __cdecl BM_SYNC_ReadBuffer(unsigned char *);
bool __cdecl BM_SYNC_Start();

// Blue Robin
bool __cdecl BM_BR_GetID(DWORD &);
bool __cdecl BM_BR_SetHeartrate(WORD);
bool __cdecl BM_BR_SetID(DWORD);
bool __cdecl BM_BR_Start();
bool __cdecl BM_BR_Stop();

// WBSL
bool __cdecl BM_WBSL_GetPacketStatus(DWORD &);
bool __cdecl BM_WBSL_GetStatus(DWORD &);
bool __cdecl BM_WBSL_Send_Data(unsigned char *,int,DWORD &);
bool __cdecl BM_WBSL_Start(void);
bool __cdecl BM_WBSL_Stop(void);

}

extern "C" void Ez_Init();

bool BM_OpenCOM(char portnum, DWORD dwBaudrate = 115200, WORD wTimeout = 30, bool bRTS = false, bool bDTR = false);


inline bool BM_OpenCOM(unsigned char portNb, DWORD dwBaudrate = 115200, WORD wTimeout = 30, bool bRTS = false, bool bDTR = false)
{
	char portname[16];
	sprintf_s(portname, "\\\\.\\COM%d", (int)portNb);
//	message(portname,portname);

	return BM_OpenCOM(portname, dwBaudrate, wTimeout, bRTS, bDTR);
}


#endif // _EZ430_CHRONOS_CC_H_