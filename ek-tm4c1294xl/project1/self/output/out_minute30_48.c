/*------------------------------------------------------------------------------
OUT_MINUTE30_48!C
                    

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
#include "out_minute30_48.h"



void    OutPowGrpHou48(void)
{
  if (bInBuff6 > wHOURS/48) { Result(bRES_BADADDRESS); return; }
  uint iwHhr = GetDayHhrIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHou(iwHhr) == false) { Result(bRES_BADFLASH); return; }

    if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
      PushFloat(0);
    else
      PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], bInBuff5, 2));

    wSize += sizeof(float);

    if (++iwHhr >= wHOURS) iwHhr = 0;
  }

  OutptrOutBuff(wSize);
}


void    OutImpCanHou48(void)
{
  if (bInBuff6 > wHOURS/48) { Result(bRES_BADADDRESS); return; }
  uint iwHhr = GetDayHhrIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHou(iwHhr) == false) { Result(bRES_BADFLASH); return; }

    if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
      PushInt(0);
    else
      PushInt( mpwImpHouCan[ PrevSoftHou() ][ bInBuff5 ] );

    wSize += sizeof(uint);

    if (++iwHhr >= wHOURS) iwHhr = 0;
  }

  OutptrOutBuff(wSize);
}



void    OutPowGrpHou48Ext(void)
{
  if (bInBuff6 > wHOURS/48) { Result(bRES_BADADDRESS); return; }
  uint iwHhr = GetDayHhrIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHou(iwHhr) == false) { Result(bRES_BADFLASH); return; }

    uchar g;
    for (g=0; g<bGROUPS; g++)
    {
      if ((InBuff(7 + g/8) & (0x80 >> g%8)) != 0)
      {
        if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
          PushFloat(0);
        else
          PushFloat(GetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], g, 2));

        wSize += sizeof(float);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
      }
    }

    if (++iwHhr >= wHOURS) iwHhr = 0;
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
  if (bInBuff6 > wHOURS/48) { Result(bRES_BADADDRESS); return; }
  uint iwHhr = GetDayHhrIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHhr) == false) { Result(bRES_BADFLASH); return; }

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

    if (++iwHhr >= wHOURS) iwHhr = 0;
  }

  OutptrOutBuff(wSize);
}


void    OutPowCanHou48Ext(void)
{
  if (bInBuff6 > wHOURS/48) { Result(bRES_BADADDRESS); return; }
  uint iwHhr = GetDayHhrIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHhr) == false) { Result(bRES_BADFLASH); return; }

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
      {
        if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
        {
          PushFloat(0);
        }
        else if (mpwImpHouCan[ PrevSoftHou() ][c] == 0xFFFF)
        {
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
          PushChar(0xFF);
        }
        else
        {
          PushFloat(GetCanHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], c, 2));
        }

        wSize += sizeof(float);
        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
      }
    }

    if (++iwHhr >= wHOURS) iwHhr = 0;
  }

  OutptrOutBuff(wSize);
}


void    OutDefCanHou48Ext(void)
{
  if (bInBuff6 > wHOURS/48) { Result(bRES_BADADDRESS); return; }
  uint iwHhr = GetDayHhrIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadImpHouFree(iwHhr) == false) { Result(bRES_BADFLASH); return; }

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
      {
        if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
          PushChar(0);
        else if (GetDigitalDevice(c) == 0)
          PushChar(1);
        else
          PushChar(mpwImpHouCan[ PrevSoftHou() ][ c ] != 0xFFFF);

        wSize += sizeof(uchar);
      }
    }

    if (++iwHhr >= wHOURS) iwHhr = 0;
  }

  OutptrOutBuff(wSize);
}
