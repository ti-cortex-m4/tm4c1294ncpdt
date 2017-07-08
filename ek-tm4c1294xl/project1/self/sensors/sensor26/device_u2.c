/*------------------------------------------------------------------------------
DEVICE_U2.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../device_k.h"
#include "../device_q.h"
#include "device_u2.h"



static uchar            cbDatesU;

static date             mpdtDatesU[128];



void    QueryEnergyDayDatesU(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('D');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+128*17+2, n+8+1, 128);
}


void    QueryEnergyMonDatesU(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('M');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+36*14+2, n+8+1, 36);
}



void    ClearDatesU(void)
{
  cbDatesU = 0;
  memset(&mpdtDatesU, 0, sizeof(mpdtDatesU));
}



uchar   PopValueU(uchar  bCode)
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


date    PopDayDateU(void)
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

    dt.bDay   = PopValueU('.');
    dt.bMonth = PopValueU('.');
    dt.bYear  = PopValueU(')');
  }
}


date    PopMonDateU(void)
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

    dt.bMonth = PopValueU('.');
    dt.bYear  = PopValueU(')');
  }
}



void    ReadEnergyDayDatesU(void)
{
  InitPop(1);

  ClearDatesU();

  uchar i;
  for (i=0; i<128; i++)
  {
    mpdtDatesU[cbDatesU++] = PopDayDateU();
  }
}


void    ReadEnergyMonDatesU(void)
{
  InitPop(1);

  ClearDatesU();

  uchar	i;
  for (i=0; i<36; i++)
  {
    mpdtDatesU[cbDatesU++] = PopMonDateU();
  }
}



uchar    IsDayAddedU(date  dt)
{
  if (boShowMessages == true) { Clear(); sprintf(szLo+0,"сутки %02u.%02u.%02u",dt.bDay,dt.bMonth,dt.bYear); DelayInf(); Clear(); }

  if (cbDatesU == 0)
  {
    return 0;
  }
  else
  {
    uchar i;
    for (i=0; i<cbDatesU; i++)
    {
      date mp = mpdtDatesU[i];
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


uchar    IsMonAddedU(date  dt)
{
  if (boShowMessages == true) { Clear(); sprintf(szLo+1,"мес€ц %02u.%02u",dt.bMonth,dt.bYear); DelayInf(); Clear(); }

  if (cbDatesU == 0)
  {
    return 0;
  }
  else
  {
    uchar i;
    for (i=0; i<cbDatesU; i++)
    {
      date mp = mpdtDatesU[i];
      if ((mp.bMonth == dt.bMonth) &&
          (mp.bYear  == dt.bYear))
      {
        return i+1;
      }
    }

    return 0;
  }
}



void    ReadEnergyTariffU(uchar  ibLine, uchar  ibTrf)
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
