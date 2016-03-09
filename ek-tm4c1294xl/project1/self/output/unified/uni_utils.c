/*------------------------------------------------------------------------------
uni_utils.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "uni_utils.h"



ulong   DateToLongUni(time  *ptm)
{
  uchar month = ptm->bMonth;
  uint year = 2000 + ptm->bYear;

  if (month > 2)
    month -= 3;
  else
  {
    month += 9;
    year--;
  }

  ulong c   = year / 100;
  ulong y  = year - 100 * c;
  ulong res = (146097 * c)/4 + (1461 * y)/4 + (153 * month + 2)/5 + ptm->bDay;

  return (res - 720000) * 86400l + (ptm->bHour * 60l + ptm->bMinute) * 60l + ptm->bSecond;
}
