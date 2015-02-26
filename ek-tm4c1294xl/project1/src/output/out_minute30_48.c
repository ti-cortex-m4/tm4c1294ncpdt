/*------------------------------------------------------------------------------
OUT_MINUTE30_48.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../serial/ports.h"
#include        "../realtime/realtime.h"
#include        "../energy.h"
#include        "../energy2.h"
#include        "../digitals/digitals.h"
#include        "../digitals/sensors.h"
#include        "../digitals/current.h"



void    OutPowGrpHou48Ext(void)
{
uchar   g, h;
uint    w, iwHou;
real    re;

  iwHou = GetDayHouIndex(bInBuff6);

  InitPushPtr();
  w = 0;

  for (h=0; h<48; h++)
  {
    if (LoadImpHou(iwHou) == FALSE) break; // TODO
    else
    {
      for (g=0; g<bGROUPS; g++)
      {
        if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
        {
          if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
            re = 0;
          else
            re = GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], g, 2);

          PushReal(re);

          w += sizeof(real);
          if (w >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        }
      }
    }

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  if (h == 48)
    OutptrOutBuff(w);
  else
    Result(bRES_BADFLASH);
}


void    PushImpHouCan(uint  wT, uchar  ibCan)
{
  if ((IsPulseCanal(ibCan) || IsSpecCurrent(GetDigitalDevice(ibCan))) && (wT == 0xFFFF)) wT = 0;
  PushInt(wT);
}


void    OutImpCanHou48Ext(void)
{
uchar   c, h;
uint    w, iwHou;

  iwHou = GetDayHouIndex(bInBuff6);

  InitPushPtr();
  w = 0;

  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHou) == FALSE) break; // TODO
    else
    {
      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
        {
          if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
            PushInt(0);
          else
            PushImpHouCan( mpwImpHouCan[ PrevSoftHou() ][ c ], c );

          w += sizeof(uint);
          if (w >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        }
      }
    }

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  if (h == 48)
    OutptrOutBuff(w);
  else
    Result(bRES_BADFLASH);
}


void    OutPowCanHou48Ext(void)
{
uchar   c, h;
uint    w, iwHou;
real    re;

  iwHou = GetDayHouIndex(bInBuff6);

  InitPushPtr();
  w = 0;

  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHou) == FALSE) break; // TODO
    else
    {
      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
        {
          if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
          {
            re = 0;
            PushReal(re);
          }
          else
          if (GetCanInt(mpwImpHouCan[ PrevSoftHou() ], c) == 0xFFFF)
          {
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
          }
          else
          {
            re = GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], c, 2);
            PushReal(re);
          }

          w += sizeof(real);
          if (w >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
        }
      }
    }

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  if (h == 48)
    OutptrOutBuff(w);
  else
    Result(bRES_BADFLASH);
}
