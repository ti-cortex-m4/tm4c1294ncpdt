/*------------------------------------------------------------------------------
OUT_DATAFLASH.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../serial/ports.h"
#include        "../include/flash.h"



#define PUSH_ENUM(value) PushString(#value); PushString("="); PushIntAsString(value); PushChar(0x0D); PushChar(0x0A);



void    OutDataFlashMap(void)
{
uint    i;

  InitPushCRC();
  for (i=0; i<2000; i++) PushChar(0);

  InitPushCRC();

  PUSH_ENUM(FLS_BEGIN)

  PUSH_ENUM(FLS_PRIVATE)
  PUSH_ENUM(FLS_GLOBAL)
  PUSH_ENUM(FLS_LOGICAL)

  PUSH_ENUM(FLS_GROUPS)

  PUSH_ENUM(FLS_PUBLIC_TARIFFS)
  PUSH_ENUM(FLS_TARIFFS_MODE)

  PUSH_ENUM(FLS_DAY_ZONE)

  PUSH_ENUM(FLS_ZONES_POW)
  PUSH_ENUM(FLS_ZONES_ENG)

  PUSH_ENUM(FLS_PERIOD_POW)
  PUSH_ENUM(FLS_PERIOD_ENG)

  PUSH_ENUM(FLS_RELAXS_FLAG)
  PUSH_ENUM(FLS_RELAXS_TARIFF)
  PUSH_ENUM(FLS_RELAXS)

  PUSH_ENUM(FLS_GAPS_FLAG)
  PUSH_ENUM(FLS_GAPS)

  PUSH_ENUM(FLS_TRANS_ENG)
  PUSH_ENUM(FLS_TRANS_CNT)
  PUSH_ENUM(FLS_PULSE_HOU)
  PUSH_ENUM(FLS_PULSE_MNT)

  PUSH_ENUM(FLS_COUNT)
  PUSH_ENUM(FLS_LOSSE)
  PUSH_ENUM(FLS_LEVEL)

  PUSH_ENUM(FLS_DIGITALS)

  PUSH_ENUM(FLS_IMPHOUCAN)
  PUSH_ENUM(FLS_IMPDAYCAN)
  PUSH_ENUM(FLS_IMPMONCAN)
  PUSH_ENUM(FLS_POWDAYGRP)
  PUSH_ENUM(FLS_POWMONGRP)
  PUSH_ENUM(FLS_CNTMONCAN)

  PUSH_ENUM(FLS_IMPHOUCAN_BUFF)
  PUSH_ENUM(FLS_IMPDAYCAN_BUFF)
  PUSH_ENUM(FLS_IMPMONCAN_BUFF)
  PUSH_ENUM(FLS_IMPABSCAN_BUFF)
  PUSH_ENUM(FLS_POWDAYGRP_BUFF)
  PUSH_ENUM(FLS_POWMONGRP_BUFF)
  PUSH_ENUM(FLS_CNTMONCAN_BUFF)

  PUSH_ENUM(FLS_PTRMNT)
  PUSH_ENUM(FLS_PTRHOU)
  PUSH_ENUM(FLS_PTRDAY)
  PUSH_ENUM(FLS_PTRMON)

  PUSH_ENUM(FLS_TICURR)

  PUSH_ENUM(FLS_END)

  Output(2000);
}
