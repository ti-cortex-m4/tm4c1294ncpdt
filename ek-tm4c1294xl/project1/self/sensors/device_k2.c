/*------------------------------------------------------------------------------
DEVICE_K2!C


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

static date             mpdaDatesK[45];



void	  QueryEnergyDayDatesK(void) 
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


void	  QueryEnergyMonDatesK(void) 
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



void  	ClearDatesK(void)
{
  cbDatesK = 0;
  memset(&mpdaDatesK, 0, sizeof(mpdaDatesK));
}



uchar   PopValueK(uchar  bCode) 
{
uchar   i,bT;

  i = 0;
  while (1) 
  {
    bT = PopChar() & 0x7F;
    if (bT == bCode) break;

    if ((bT >= '0') && (bT <= '9')) 
      i = i*10 + (bT-'0');
  }

  return i;
}


void	  PopDayK(void)
{
uchar   bT;

  daAlt.bDay   = 0;
  daAlt.bMonth = 0;
  daAlt.bYear  = 0;

  while (1) 
  {
    bT = PopChar() & 0x7F;

    if (bT == 0x0D) return;
    if (bT != '(') continue;

    daAlt.bDay   = PopValueK('.');
    daAlt.bMonth = PopValueK('.');
    daAlt.bYear  = PopValueK(')');
  }
}


void	  PopMonK(void)
{
uchar   bT;

  daAlt.bDay   = 0;
  daAlt.bMonth = 0;
  daAlt.bYear  = 0;

  while (1) 
  {
    bT = PopChar() & 0x7F;

    if (bT == 0x0D) return;
    if (bT != '(') continue;

    daAlt.bMonth = PopValueK('.');
    daAlt.bYear  = PopValueK(')');
  }
}



void	  ReadEnergyDayDatesK(void) 
{
uchar	i;

  InitPop(1);

  ClearDatesK();
  for (i=0; i<45; i++) 
  {
    PopDayK();
	  mpdaDatesK[cbDatesK++] = daAlt; 
  }
}


void	  ReadEnergyMonDatesK(void) 
{
uchar	i;

  InitPop(1);

  ClearDatesK();
  for (i=0; i<24; i++) 
  {
    PopMonK();
	  mpdaDatesK[cbDatesK++] = daAlt; 
  }
}



uchar	  IsDayAddedK(void)
{
uchar   i;

  if (boShowMessages == true) { Clear(); sprintf(szLo+0,"сутки %02bu.%02bu.%02bu",tiAlt.bDay,tiAlt.bMonth,tiAlt.bYear); DelayInf(); Clear(); }

  if (cbDatesK == 0)
  {
    return 0;
  }
  else
  {
    for (i=0; i<cbDatesK; i++)
    {
      daDig = mpdaDatesK[i];
      if ((daDig.bDay   == daAlt.bDay)   &&
          (daDig.bMonth == daAlt.bMonth) &&
          (daDig.bYear  == daAlt.bYear))
      {
        return i+1;
      }
    }

    return 0;
  }
}


uchar	  IsMonAddedK(void)
{
uchar   i;

  if (boShowMessages == true) { Clear(); sprintf(szLo+1,"мес€ц %02bu.%02bu",tiAlt.bMonth,tiAlt.bYear); DelayInf(); Clear(); }

  if (cbDatesK == 0)
  {
    return 0;
  }
  else
  {
    for (i=0; i<cbDatesK; i++)
    {
      daDig = mpdaDatesK[i];
      if ((daDig.bMonth == daAlt.bMonth) &&
          (daDig.bYear  == daAlt.bYear))
      {
        return i+1;
      }
    }

    return 0;
  }
}



void    ReadEnergyTariffK(uchar  ibLine, uchar  ibTariff)
{
uchar   i;

  InitPop(1);
  
  for (i=0; i<ibTariff+2; i++) PopRealK();

  mpreChannelsB[ibLine] = reBuffA;
  mpboChannelsA[ibLine] = true;

  reBuffA = mpreChannelsB[ibLine];
}
