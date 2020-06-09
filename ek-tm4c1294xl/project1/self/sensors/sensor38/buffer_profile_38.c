/*------------------------------------------------------------------------------
buffer_profile_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "include38.h"
#include "buffer_profile_38.h"



#define         PROFILE38_SIZE 6


profile38       mpPrf38[PROFILE38_SIZE];
uchar           cbPrfSize38;
bool            fPrfOveflow38;



void    InitPrfBuff38(void)
{
  memset(&mpPrf38, 0, sizeof(mpPrf38));
  cbPrfSize38 = 0;
  fPrfOveflow38 = false;
}


void    AddPrfBuff38(time  ti, uint64_t  ddw)
{
  if (cbPrfSize38 < PROFILE38_SIZE)
  {
    mpPrf38[cbPrfSize38].fExists = true;
    mpPrf38[cbPrfSize38].tiTime = ti;
    mpPrf38[cbPrfSize38].ddwValue = ddw;

    cbPrfSize38++;
  }
  else
  {
    fPrfOveflow38 = true;
  }
}



profile38 GetPrf38(uchar i)
{
  ASSERT(i < PROFILE38_SIZE);
  return mpPrf38[i];
}


uchar   GetPrfSize38(void)
{
  return cbPrfSize38;
}


bool    GetPrfOveflow38(void)
{
  return fPrfOveflow38;
}
