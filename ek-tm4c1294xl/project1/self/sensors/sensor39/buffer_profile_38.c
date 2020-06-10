/*------------------------------------------------------------------------------
buffer_profile_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "include39.h"
#include "buffer_profile_38.h"



static profile39    mpBuffPrf38[PROFILE39_SIZE];
static uchar        cbBuffPrfSize38;
static bool         fBuffPrfOveflow38;



void    InitBuffPrf38(void)
{
  memset(&mpBuffPrf38, 0, sizeof(mpBuffPrf38));
  cbBuffPrfSize38 = 0;
  fBuffPrfOveflow38 = false;
}


void    AddBuffPrf38(time  tiTime, uint64_t  ddwValue)
{
  if (cbBuffPrfSize38 < PROFILE39_SIZE)
  {
    uchar i = cbBuffPrfSize38;
    ASSERT(i < PROFILE39_SIZE);
    mpBuffPrf38[i].fExists = true;
    mpBuffPrf38[i].tiTime = tiTime;
    mpBuffPrf38[i].ddwValue = ddwValue;

    cbBuffPrfSize38++;
  }
  else
  {
    fBuffPrfOveflow38 = true;
  }
}



profile39 GetBuffPrf38(uchar  i)
{
  ASSERT(i < PROFILE39_SIZE);
  return mpBuffPrf38[i];
}


uchar   GetBuffPrfSize38(void)
{
  return cbBuffPrfSize38;
}


bool    GetBuffPrfOveflow38(void)
{
  return fBuffPrfOveflow38;
}
