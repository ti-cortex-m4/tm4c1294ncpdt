/*------------------------------------------------------------------------------
DEVICE_K2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "device_k.h"
#include "device_k2.h"



static uchar            cbDatesK;

static date             mpdtDatesK[45];



void    QueryEnergyDayDatesK(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('D');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+45*17+2, 15+8+1, 45);
}


void    QueryEnergyMonDatesK(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('M');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+24*14+2, 15+8+1, 24);
}



void    QueryEnergyDayK(uchar  ibLine, uchar  bDay)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('D');
  PushChar1Bcc('0');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar2Bcc(bDay);
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+10+1, 6);
}


void    QueryEnergyMonK(uchar  ibLine, uchar  bMon)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('M');
  PushChar1Bcc('0');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar2Bcc(bMon);
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+10+1, 6);
}



void    ClearDatesK(void)
{
  cbDatesK = 0;
  memset(&mpdtDatesK, 0, sizeof(mpdtDatesK));
}



uchar   PopValueK(uchar  bCode) 
{
  uchar i = 0;
  while (true)
  {
    uchar b = PopChar() & 0x7F;
    if (b == bCode) break;

    if ((b >= '0') && (b <= '9'))
      i = i*10 + (b-'0');
  }

  return i;
}


date    PopDayDateK(void)
{
  date dt;
  dt.bDay   = 0;
  dt.bMonth = 0;
  dt.bYear  = 0;

  while (true)
  {
    uchar b = PopChar() & 0x7F;

    if (b == 0x0D) return dt;
    if (b != '(') continue;

    dt.bDay   = PopValueK('.');
    dt.bMonth = PopValueK('.');
    dt.bYear  = PopValueK(')');
  }
}


date    PopMonDateK(void)
{
  date dt;
  dt.bDay   = 0;
  dt.bMonth = 0;
  dt.bYear  = 0;

  while (true)
  {
    uchar b = PopChar() & 0x7F;

    if (b == 0x0D) return dt;
    if (b != '(') continue;

    dt.bMonth = PopValueK('.');
    dt.bYear  = PopValueK(')');
  }
}



void    ReadEnergyDayDatesK(void)
{
  InitPop(1);

  ClearDatesK();

  uchar i;
  for (i=0; i<45; i++) 
  {
    mpdtDatesK[cbDatesK++] = PopDayDateK();
  }
}


void    ReadEnergyMonDatesK(void)
{
  InitPop(1);

  ClearDatesK();

  uchar	i;
  for (i=0; i<24; i++) 
  {
    mpdtDatesK[cbDatesK++] = PopMonDateK();
  }
}



uchar    IsDayAddedK(date  dt)
{
  if (boShowMessages == true) { Clear(); sprintf(szLo+0,"сутки %02u.%02u.%02u",dt.bDay,dt.bMonth,dt.bYear); DelayInf(); Clear(); }

  if (cbDatesK == 0)
  {
    return 0;
  }
  else
  {
    uchar i;
    for (i=0; i<cbDatesK; i++)
    {
      date mp = mpdtDatesK[i];
      if ((mp.bDay   == dt.bDay)   &&
          (mp.bMonth == dt.bMonth) &&
          (mp.bYear  == dt.bYear))
      {
        return i+1;
      }
    }

    return 0;
  }
}


uchar    IsMonAddedK(date  dt)
{
  if (boShowMessages == true) { Clear(); sprintf(szLo+1,"мес€ц %02u.%02u",dt.bMonth,dt.bYear); DelayInf(); Clear(); }

  if (cbDatesK == 0)
  {
    return 0;
  }
  else
  {
    uchar i;
    for (i=0; i<cbDatesK; i++)
    {
      date mp = mpdtDatesK[i];
      if ((mp.bMonth == dt.bMonth) &&
          (mp.bYear  == dt.bYear))
      {
        return i+1;
      }
    }

    return 0;
  }
}



void    ReadEnergyTariffK(uchar  ibLine, uchar  ibTrf)
{
double db;

  InitPop(1);
  
  uchar i;
  for (i=0; i<ibTrf+2; i++)
  {
    db = PopDoubleK();
  }

  mpdbChannelsC[ibLine] = db;
  mpboChannelsA[ibLine] = true;
}
