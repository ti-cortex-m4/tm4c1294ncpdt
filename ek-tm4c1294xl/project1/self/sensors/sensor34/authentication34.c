/*------------------------------------------------------------------------------
authentication34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "authentication34.h"



static  uchar           mpbAuthRequest[16];
static  uchar           mpbAuthResponse[16];



void    QueryAuthRequest(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x08);

  QueryIO(3+16+2, 6+2);
}


void    ReadAuthRequest(void)
{
  InitPop(4);

  uchar i;
  for (i=0; i<16; i++) {
    mpbAuthRequest[i] = PopChar();
  }
}




void    QueryAuthResponse(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x65);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x09);
  PushChar(0x12);

  PushIntLtl(1);

  uchar i;
  for (i=0; i<16; i++) {
      PushChar(mpbAuthResponse[i]);
  }

  QueryIO(3+3+2, 7+2+16+2);
}


bool    ReadAuthResponse(void)
{
  return (InBuff(1) & 0x80) != 0;
}
