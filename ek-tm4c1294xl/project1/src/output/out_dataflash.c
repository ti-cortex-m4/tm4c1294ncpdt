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
  for (i=0; i<1000; i++) PushChar(0);

  InitPushCRC();

  PUSH_ENUM(DF_BEGIN)

  PUSH_ENUM(DF_PRIVATE)
  PUSH_ENUM(DF_GLOBAL)
  PUSH_ENUM(DF_LOGICAL)

  PUSH_ENUM(DF_GROUPS)

  PUSH_ENUM(DF_PUBLIC_TARIFFS)
  PUSH_ENUM(DF_TARIFFS_MODE)

  PUSH_ENUM(DF_DAY_ZONE)

  PUSH_ENUM(DF_ZONES_POW)
  PUSH_ENUM(DF_ZONES_ENG)

  PUSH_ENUM(DF_PERIOD_POW)
  PUSH_ENUM(DF_PERIOD_ENG)

  PUSH_ENUM(DF_RELAXS_FLAG)
  PUSH_ENUM(DF_RELAXS_TARIFF)
  PUSH_ENUM(DF_RELAXS)

  PUSH_ENUM(DF_GAPS_FLAG)
  PUSH_ENUM(DF_GAPS)

  PUSH_ENUM(DF_TRANS_ENG)
  PUSH_ENUM(DF_TRANS_CNT)
  PUSH_ENUM(DF_PULSE_HOU)
  PUSH_ENUM(DF_PULSE_MNT)

  PUSH_ENUM(DF_COUNT)
  PUSH_ENUM(DF_LOSSE)
  PUSH_ENUM(DF_LEVEL)

  PUSH_ENUM(DF_DIGITALS)

  PUSH_ENUM(DF_IMPHOUCAN)
  PUSH_ENUM(DF_IMPDAYCAN)
  PUSH_ENUM(DF_IMPMONCAN)
  PUSH_ENUM(DF_POWDAYGRP)
  PUSH_ENUM(DF_POWMONGRP)
  PUSH_ENUM(DF_CNTMONCAN)

  PUSH_ENUM(DF_END)

  Output(1000);
}
