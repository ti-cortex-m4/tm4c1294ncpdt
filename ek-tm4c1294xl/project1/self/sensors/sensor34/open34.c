/*------------------------------------------------------------------------------
open34.c


------------------------------------------------------------------------------*/
/*
#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "auth34.h"
#include "open34.h"



static bool QueryAuthKey34_Full(void)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryAuthKey34();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == MaxRepeats()) return false;
  ShowPercent(10);

  ReadAuthKey34();

  return true;
}


static bool QueryAuthReq34_Full(void)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    DelayOff();
    QueryAuthReq34();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == MaxRepeats()) return false;
  ShowPercent(20);

  ReadAuthReq34();

  return true;
}



bool    QueryOpen34_Full(void)
{
  if (QueryAuthKey34_Full() == false)
    return false;

  if (QueryAuthReq34_Full() == false)
    return false;

  return true;
}
*/
