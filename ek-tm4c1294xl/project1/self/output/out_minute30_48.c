/*------------------------------------------------------------------------------
OUT_MINUTE30_48.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../energy.h"
#include "../energy2.h"
#include "../digitals/digitals.h"
#include "../digitals/sensors.h"
#include "../digitals/current/current.h"



void    OutPowGrpHou48Ext(void)
{
float   re;

  uint iwHou = GetDayHouIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHou(iwHou) == false) { Result(bRES_BADFLASH); return; }
    else
    {
      uchar g;
      for (g=0; g<bGROUPS; g++)
      {
        if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
        {
          if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
            re = 0;
          else
            re = GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], g, 2);

          PushFloat(re);

          wSize += sizeof(float);
          if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        }
      }
    }

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  OutptrOutBuff(wSize);
}


void    PushImpHouCan(uint  wT, uchar  ibCan)
{
  if ((IsPulseCanal(ibCan) || IsSpecCurrent(GetDigitalDevice(ibCan))) && (wT == 0xFFFF)) wT = 0;
  PushInt(wT);
}


void    OutImpCanHou48Ext(void)
{
  uint iwHou = GetDayHouIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHou) == false) { Result(bRES_BADFLASH); return; }
    else
    {
      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
        {
          if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
            PushInt(0);
          else
            PushImpHouCan( mpwImpHouCan[ PrevSoftHou() ][ c ], c );

          wSize += sizeof(uint);
          if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        }
      }
    }

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  OutptrOutBuff(wSize);
}


void    OutPowCanHou48Ext(void)
{
float   re;

  uint iwHou = GetDayHouIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHou) == false) { Result(bRES_BADFLASH); return; }
    else
    {
      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
        {
          if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
          {
            re = 0;
            PushFloat(re);
          }
          else
          if (mpwImpHouCan[ PrevSoftHou() ][c] == 0xFFFF)
          {
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
          }
          else
          {
            re = GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], c, 2);
            PushFloat(re);
          }

          wSize += sizeof(float);
          if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        }
      }
    }

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  OutptrOutBuff(wSize);
}


void    OutDefCanHou48Ext(void)
{
  uint iwHou = PrevDayIndex(bInBuff6);

  InitPushPtr();
  uint wBuffD = 0;

  uchar j;
  for (j=0; j<48; j++)
  {
    if (LoadImpHouFree(iwHou) == 0) break;
    else
    {
      uchar i;
      for (i=0; i<bCANALS; i++)
      {
        if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0)
        {
          if ((bInBuff6 == 0) && (j > GetHouIndex()))
            PushChar(0);
          else if (GetDigitalDevice(i) == 0)
            PushChar(1);
          else
            PushChar(*PGetCanInt(mpwImpHouCan[ PrevSoftHou() ], i) != 0xFFFF);

          wBuffD += sizeof(uchar);
        }
      }
    }

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  if (j == 48)
    OutptrOutBuff(wBuffD);
  else
    Result(bRES_BADFLASH);
}
