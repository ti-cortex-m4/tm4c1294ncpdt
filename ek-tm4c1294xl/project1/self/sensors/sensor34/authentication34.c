/*------------------------------------------------------------------------------
authentication34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "authentication34.h"



static  uchar           mpbAuthKey[16];
static  uchar           mpbAuthRequest[16];



void    QueryAuthKey(void)
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


void    ReadAuthKey(void)
{
  InitPop(4);

  uchar i;
  for (i=0; i<16; i++) {
    mpbAuthKey[i] = PopChar();
  }
}



void    MakeAuthRequest(void)
{
  uchar mpbPass[16];

  memset(&mpbPass, 0, sizeof(mpbPass));

  if (boEnblKeys != true)
  {
    mpbPass[0] = '1';
    mpbPass[1] = '1';
    mpbPass[2] = '1';
    mpbPass[3] = '1';
    mpbPass[4] = '1';
    mpbPass[5] = '1';
  }
  else
  {
    line ln = mpphKeys[ibDig];

    uchar i;
    for (i=0; i<bLINE_SIZE; i++)
    {
      if (ph.szLine[i] == 0) break;
      mpbPass[i] = ph.szLine[i];
    }
  }

  HashMD5(mpbPass, strlen(mpbPass), md5Out);
}



void    QueryAuthRequest(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x65);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x09);
  PushChar(0x12);

  PushIntLtl(1); // уровень доступа: 1,2

  uchar i;
  for (i=0; i<16; i++) {
    PushChar(mpbAuthRequest[i]);
  }

  QueryIO(3+3+2, 7+2+16+2);
}


bool    ReadAuthRequest(void)
{
  return (InBuff(1) & 0x80) != 0;
}
