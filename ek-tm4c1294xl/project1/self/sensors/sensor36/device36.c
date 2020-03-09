/*------------------------------------------------------------------------------
DEVICE36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "device36.h"



void    QueryTime36(void)
{
  Query36();
}


time    ReadTime36(void)
{
  time ti;

  ti.bSecond = 0;

  return ti;
}
