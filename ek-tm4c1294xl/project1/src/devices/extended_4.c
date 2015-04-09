/*------------------------------------------------------------------------------
EXTENDED_4.C

 Значения счетчиков на НАЧАЛО месяца
------------------------------------------------------------------------------*/

#include        "../console.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_extended_4.h"
#include        "../serial/ports.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/digitals_messages.h"
#include        "../devices/devices.h"
#include        "../sensors/automatic_p.h"
#include        "../sensors/automatic3.h"
#include        "../time/rtc.h"
#include        "../time/timedate.h"
#include        "extended_4.h"



file const              flExt4Flag = {FLS_EXT_4_FLAG, &boExt4Flag, sizeof(boolean)};
file const              flExt4Months = {FLS_EXT_4_MONTHS, &bExt4Months, sizeof(uchar)};



void    InitExtended4(void)
{
  LoadFileBoolean(&flExt4Flag, FALSE);
  LoadFileChar(&flExt4Months, 0, 12, 4);
}


void    ResetExtended4(void)
{ 
  boExt4Flag = FALSE;
  SaveFile(&flExt4Flag);

  bExt4Months = 4;
  SaveFile(&flExt4Months);
}
