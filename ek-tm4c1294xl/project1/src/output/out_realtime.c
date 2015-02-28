/*------------------------------------------------------------------------------
 OUT_REALTIME.C


 ------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../serial/ports.h"
#include        "../realtime/realtime.h"



void    OutRealtime(void)
{
	InitPushCRC();

	PushTime(&tiCurr);
	PushTime(&tiPrev);

	PushChar(fSeason);
	PushChar(fSummer);
	PushChar(fWinter);

	PushChar(fActive);

	PushInt(ibSoftMnt);
	PushInt(0);
	PushInt(ibSoftHou);
	PushInt(iwHardHou);
	PushInt(ibSoftDay);
	PushInt(ibHardDay);
	PushInt(ibSoftMon);
	PushInt(ibHardMon);

	PushLong(cdwSeconds);
	PushLong(cdwMinutes1);
	PushLong(cdwMinutes3);
	PushLong(cdwMinutes30);
	PushInt(cwDays);
	PushInt(cwMonths);
	PushInt(cwYears);

	Output((6 + 6) + (1 + 1 + 1) + 1 + ((2 + 2) + (2 + 2) + (2 + 2) + (2 + 2)) + (4 + 4 + 4 + 4 + 2 + 2 + 2));
}
