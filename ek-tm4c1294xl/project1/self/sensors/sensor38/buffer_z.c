/*------------------------------------------------------------------------------
buffer_z*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "include38.h"
#include "buffer_z.h"



#define         PROFILE38_SIZE 6


profile38       mpPrf38[PROFILE38_SIZE];
uchar           cbPrf38;
bool            fOveflow38;



void    InitBufferZ(void)
{
  memset(&mpPrf38, 0, sizeof(mpPrf38));
  cbPrf38 = 0;
  fOveflow38 = false;
}


void    AddBufferZ(time  ti, uint64_t  ddw)
{
  if (cbPrf38 < PROFILE38_SIZE)
  {
    mpPrf38[cbPrf38].fExists = true;
    mpPrf38[cbPrf38].tiTime = ti;
    mpPrf38[cbPrf38].ddwValue = ddw;

    cbPrf38++;
  }
  else
  {
    fOveflow38 = true;
  }
}



profile38 GetPrf38(uchar i)
{
  ASSERT(i < PROFILE38_SIZE);
  return mpPrf38[i];
}


uchar   GetPrfSize38(void)
{
  return cbPrf38;
}


uchar   GetPrfOveflow38(void)
{
  return fOveflow38;
}
