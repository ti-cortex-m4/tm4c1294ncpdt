/*------------------------------------------------------------------------------
ENBL_HOURS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"



void    SetEnblPrtHou(uchar  ibPrt, uchar  ibHou, boolean  bo)
{
  mpboEnblPrtHou[ibPrt][ibHou] = bo;
}


boolean GetEnblPrtHou(uchar  ibPrt, uchar  ibHou)
{
  return mpboEnblPrtHou[ibPrt][ibHou];
}
