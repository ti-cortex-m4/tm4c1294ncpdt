/*------------------------------------------------------------------------------
authentication34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
//#include "unix_time_gmt34.h"
//#include "device34.h"
#include "authentication34.h"



static  uchar           mpbAuthRequest[16];



void    QueryAuthRequest(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x08);

  QueryIO(3+81+2, 6+2);
}


void    ReadAuthRequest(void)
{
  InitPop(4);

  uchar i;
  for (i=0; i<16; i++) {
    mpbAuthRequest[i] = PopChar();
  }
}
