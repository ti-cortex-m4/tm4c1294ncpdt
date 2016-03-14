/*------------------------------------------------------------------------------
uni_utils.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "uni_utils.h"



ulong   DateToLongUni(time  *pti)
{
  uchar month = pti->bMonth;
  uint year = 2000 + pti->bYear;

  if (month > 2)
    month -= 3;
  else
  {
    month += 9;
    year--;
  }

  ulong c = year / 100;
  ulong y = year - 100 * c;
  ulong res = (146097 * c)/4 + (1461 * y)/4 + (153 * month + 2)/5 + pti->bDay;

  return (res - 720000) * 86400l + (pti->bHour * 60l + pti->bMinute) * 60l + pti->bSecond;
}
