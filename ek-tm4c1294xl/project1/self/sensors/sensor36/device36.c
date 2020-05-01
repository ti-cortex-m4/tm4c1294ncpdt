/*------------------------------------------------------------------------------
DEVICE36!C

Энергомера СЕ301 NNCL2, СЕ303 NNCL2
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "io36.h"
#include "../device_k.h"
#include "../device_q.h"
#include "device36.h"



void    QueryClose36(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('B');
  PushChar1Bcc('0');
  PushChar1Bcc(0x03);

  BccQuery36(0, 4+1, 0);
  DelayOff();
}



void    QueryOpen36(void)
{
  uchar n = PushAddress1Bcc();

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query36(1000, n+2, 1);
}


void    ReadOpen36(void)
{
  Clear();
  InitPop(1);

  uchar i;
  for (i=0; i<16; i++)
  {
    uchar b = PopChar0Bcc();

    if ((b == '\r') || (b == '\n')) break;
    szLo[i] = b;
  }
}



void    QueryOption36(void)
{
uchar   i;

  InitPush(0);
  PushChar1Bcc(0x06);

  switch (mppoPorts[ diCurr.ibPort ].ibBaud)
  {
    case 0:  i = '2'; break;
    case 1:  i = '3'; break;
    case 2:  i = '4'; break;
    case 3:  i = '5'; break;
    case 4:  i = '6'; break;
    default: i = '7'; break;
  }

  PushChar1Bcc('0');
  PushChar1Bcc(i);
  PushChar1Bcc('1');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  cbHeaderBcc = 1;
  cwInBuffBcc = 0;
  Query36(1000, 4+2, 1);
}



void    QueryTime36(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1000+1+17+2, n+8+1, 0);
}


time    ReadTime36(void)
{
  InitPop(7);

  time ti;
  ti.bHour   = PopChar2Bcc(); PopChar();
  ti.bMinute = PopChar2Bcc(); PopChar();
  ti.bSecond = PopChar2Bcc(); PopChar();

  return ti;
}



void    QueryDate36(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1000+1+20+2, n+8+1, 0);
}


time    ReadDate36(time  ti)
{
  InitPop(7+3);

  ti.bDay   = PopChar2Bcc(); PopChar();
  ti.bMonth = PopChar2Bcc(); PopChar();
  ti.bYear  = PopChar2Bcc(); PopChar();

  return ti;
}



void    QueryEngAbs36(uchar  ibLine)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1000+1+6*28+2, n+8+1, 6);
}


void    QueryEngDay36(uchar  ibLine, time  ti)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('D');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar2Bcc(ti.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bYear);
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1000+1+6*28+2, n+16+1, 6);
}


void    QueryEngMon36(uchar  ibLine, time  ti)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('M');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar2Bcc(ti.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bYear);
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1000+1+6*28+2, n+13+1, 6);
}


void    ReadEng36(uchar  ibLine)
{
  InitPop(1);

  mpdbChannelsC[ibLine] = PopDoubleQ();
}


void    ReadEng36_SkipLine(uchar  ibLine)
{
  mpdbChannelsC[ibLine] = 0;
}


void    ReadEngTariff36(uchar  ibLine, uchar  ibTrf)
{
double db;

  InitPop(1);

  uchar i;
  for (i=0; i<ibTrf+2; i++)
  {
    db = PopDoubleQ();
  }

  mpdbChannelsC[ibLine] = db;
  mpboChannelsA[ibLine] = true;
}
