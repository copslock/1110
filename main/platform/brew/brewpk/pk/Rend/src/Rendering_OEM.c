//**************************************************************
//Copyright (C), 2008-2008, AnyLook Co., Ltd.
//File name:    Rendering_OEM.c
//Author:       AnyLook
//Version:      1.0
//Date:      2009/01/09
//Description:
//    Rendering Src file
//Others: 
//Function List: 
//<Name>        <desc>
//Simple        
//History: 
//<author>      <time>      <version >  <desc>
// AnyLook    2009/01/09       1.0       build this moudle  
//**************************************************************
#include "AEE.h"
#include "AEEShell.h"
#include "AEEStdLib.h"
#include "AEE_OEM.h"
#include "AEE_OEMDispatch.h"
#include "Rendering_Config.h"
#include "Rendering_OEM.h"
#include "AEEIDIB.h"
#include "OEMHeap.h"
#include "disp.h"

#define RELEASEIF(p) do { if (p) { IQI_Release((IQueryInterface*)(p)); p = 0; } } while (0)

extern void Rendering_TimerCB(void *pUser);
int Rendering_StartTimer(int ms, void *pUser)
{
    return AEE_SetSysTimer(ms, Rendering_TimerCB, pUser);;
}

int Rendering_CancelTemer(void *pUser)
{
    return AEE_CancelTimer(Rendering_TimerCB, pUser);
}

boolean Rendering_DevAvaild(void)
{
    AEEDeviceInfo Info;
    
	AEE_GetDeviceInfo(&Info);
    
#if (REND_PLATFORMID != 0)
	if(Info.dwPlatformID != REND_PLATFORMID)
	{
		return FALSE;
	}
#endif
	return TRUE;
}

void Rendering_UpdateDev(void *pBmpBuf, int nSize, int dx, int dy, int nPitch, int nDepth, int nScheme)
{
    disp_update(pBmpBuf,
                dx,
                0, 0,
                dy, dx,
                0, 0);
}

void *Rendering_Malloc(int nSize)
{
    return sys_malloc(nSize);
}

void Rendering_Free(void *pBuf)
{
    sys_free(pBuf);
}

