/*------------------------------------------------------------------------------
ENBL_HOURS.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_schedule.h"



void    SetEnblPrtHou(uchar  ibPrt, uchar  ibHou, bool  bo)
{
  mpboEnblPrtHou[ibPrt][ibHou] = bo;
}


bool GetEnblPrtHou(uchar  ibPrt, uchar  ibHou)
{
  return mpboEnblPrtHou[ibPrt][ibHou];
}
