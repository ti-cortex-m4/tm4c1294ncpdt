/*------------------------------------------------------------------------------
OUT_FLASH.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_ports.h"
#include        "../ports.h"
#include        "../queries.h"
#include        "../delay.h"



void    OutFlashPage(void) {
    if ((bInBuff5 == 0xFF) && (bInBuff6 == 0xFF))
    {
//          memset(&mpbOutBuff0, '\0', wPAGE_SIZE);
/*
      InitPushPtr();

      PushInt(cwWrnBusy);
      PushInt(cwWrnCompare);
      PushInt(cwWrnPageErase);
      PushInt(cwWrnPageRead);
      PushInt(cwWrnPageWrite);
      PushInt(cwErrCompare);
      PushInt(cwErrPageErase);
      PushInt(cwErrPageRead);
      PushInt(cwErrPageWrite);

      PushChar(bUINT);
      PushChar(bIMPULSE);
      PushChar(bPOWER);
      PushChar(bREAL);

      PushInt(wFLA_BEGIN);
      PushInt(wFLA_PRIVATE);
      PushInt(wFLA_LABEL);
      PushInt(wFLA_IMPHOUCAN);
      PushInt(wFLA_IMPDAYCAN);
      PushInt(wFLA_IMPMONCAN);
      PushInt(wFLA_POWDAYGRP);
      PushInt(wFLA_POWMONGRP);
      PushInt(wFLA_CNTMONCAN);
      PushInt(wFLA_END);

      PushInt(0);
      PushInt(0);
      PushInt(0);

      PushInt(cwWrnResetWDT);

      PushInt(GetCODEChecksum());
      PushInt(wPrivate);
      PushChar(bLogical);

      PushInt(wFLA_KEYRECORD);
      PushInt(wFLA_SYSRECORD);
      PushInt(wFLA_DIGRECORD);
      PushInt(wFLA_IMPRECORD);

      PushInt(wRECORDS);
      PushChar(bRECORD_BLOCK);
      PushChar(bRECORD_SIZE);

      PushLong(&cdwKeyRecord);
      PushLong(&cdwSysRecord);
      PushLong(&cdwDigRecord);
      PushLong(&cdwImpRecord);

      PushLong(&cdwSeconds);
      PushLong(&cdwMinutes1);
      PushLong(&cdwMinutes3);
      PushLong(&cdwMinutes30);
      PushInt(cwDays);
      PushInt(cwMonths);
      PushInt(cwYears);

      PushInt(0);
      PushInt(0);

      PushInt(wFLA_MODRECORD);
      PushLong(&cdwModRecord);

      PushInt(wFLA_POWDAYGRP2);
      PushInt(wFLA_CNTMONCAN2);

      PushInt(wFLA_PH2RECORD);
      PushLong(&cdwPh2Record);

      PushInt(wFLA_DEFDAYCAN);
      PushInt(wFLA_DEFMONCAN);

      PushInt(wFLA_DIAGRAM);
      PushInt(wFLA_CNTDAYCAN7);

      PushInt(wRECORDS2);
      PushInt(wRECORD2_SIZE);

      PushInt(wFLA_AUXILIARY);
      PushLong(&cdwAuxRecord);
      PushInt(wPAGES);

      OutptrOutBuff(wPAGE_SIZE);
*/
    }
    else
    if (bInBuff5*0x100 + bInBuff6 <= wFLA_END)
    {
      wPageIn = bInBuff5*0x100 + bInBuff6;

      if (SafePageRead() == 1)
        Outptr(&mpbPageIn, wPAGE_SIZE);
      else
        Result(bRES_BADFLASH);
    }
    else Result(bRES_BADADDRESS);

}
