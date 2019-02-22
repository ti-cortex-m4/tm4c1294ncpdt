/*------------------------------------------------------------------------------
time34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "time34.h"



static time             tmCurr34;


void    SetTimeCurr34(time tm)
{
  tmCurr34 = tm;
}


time    GetTimeCurr34(void)
{
  return tmCurr34;
}



void    QueryTime34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x09);

  QueryIO(3+18+2, 6+2);
}


time    ReadTime34(void)
{
  InitPop(3);
  return UnixTimeToTimeFromGMT34(PopLongLtl());
}



void    QueryCorrectTime34(int32_t  dwSecond)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x65);
  PushChar(0x00);
  PushChar(0x4F);
  PushChar(0x00);
  PushChar(0x04);
  PushChar(0x08);

  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);

  PushLongLtl(dwSecond);

  QueryIO(3+3+2, 7+4+4+2);
}


bool    ReadCorrectTime34(void)
{
  return (InBuff(1) & 0x80) == 0;
}
