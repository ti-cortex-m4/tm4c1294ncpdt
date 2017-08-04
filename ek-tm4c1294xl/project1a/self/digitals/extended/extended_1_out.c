/*------------------------------------------------------------------------------
EXTENDED_1_OUT!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../display/display.h"
#include "../../serial/ports.h"
#include "../../realtime/realtime.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_pause.h"
#include "../../sensors/automatic2.h"
#include "../../digitals/extended/extended_6.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../energy.h"
#include "../../energy2.h"
#include "extended_1.h"
#include "extended_1_out.h"



void    OutEscS_Value(bool  fDouble)
{
  SaveDisplay();
  ShowHi(szClear); sprintf(szHi,"Порт %u: CRC%03u",ibPort+1,bInBuff5); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      sprintf(szHi+14,"%2u",c+1);

      double db;
      if (GetDigitalDevice(c) == 0)
      {
        db = GetCntCurrImp(c);
        mptiEsc_S[c] = *GetCurrTimeDate();
      }
      else if (mpboEnblCan[c] == false)
      {
        db = 0;
        mptiEsc_S[c] = *GetCurrTimeDate();
      }
      else if ((boExtendedEscS == true) || (GetDigitalPhone(c) != 0))
        db = mpdbEsc_S[c];
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == true)
          db = mpdbChannelsC[diCurr.ibLine];
        else
        {
          uchar p = ibPort;
          double2 db2 = ReadCntCurrCan(c);
          ibPort = p;

          if (!db2.fValid) db = 0; else db = db2.dbValue;
        }

        mptiEsc_S[c] = *GetCurrTimeDate();
      }

      wSize += PushFloatOrDouble(db, fDouble);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause(); // внимание !
}


void    OutEscU_Value(void)
{
  SaveDisplay();
  ShowHi(szClear); sprintf(szHi,"Порт %u: CRC%03u",ibPort+1,bInBuff5); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      sprintf(szHi+14,"%2u",c+1);

      time ti1, ti2;
      if (GetDigitalDevice(c) == 0)
      {
        ti1 = *GetCurrTimeDate();
        ti2 = ti1;
      }
      else if (mpboEnblCan[c] == false)
      {
        ti1 = tiZero;
        ti2 = ti1;
      }
      else if ((boExtendedEscU == true) || (GetDigitalPhone(c) != 0))
      {
        ti1 = mptiEsc_U1[c];
        ti2 = mptiEsc_U2[c];
      }
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == true)
          ti1 = tiChannelC;
        else
        {
          uchar p = ibPort;
          time2 ti2 = ReadTimeCan(c);
          ibPort = p;

          if (!ti2.fValid) ti1 = tiZero; else ti1 = ti2.tiValue;
        }

        ti2 = *GetCurrTimeDate();
      }

      wSize += PushTime(ti1);
      wSize += PushTime(ti2);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause(); // внимание !
}


void    OutEscV_Value(bool  fDouble)
{
  SaveDisplay();
  ShowHi(szClear); sprintf(szHi,"Порт %u: CRC%03u",ibPort+1,bInBuff5); Clear();

  uchar ibMon = ibHardMon;

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      sprintf(szHi+14,"%2u",c+1);

      double db;
      if (GetDigitalDevice(c) == 0)
      {
        if (LoadCntMon(ibMon) == true)
          db = mpdbCntMonCan[ PrevSoftMon() ][c];
        else
          db = GetDoubleNAN();

        mptiEsc_V[c] = *GetCurrTimeDate();
      }
      else if (SupportedExtended6(c))
      {
        db = mpCntBoxCan6[c].dbValue;
      }
      else if (mpboEnblCan[c] == false)
      {
        db = 0;
        mptiEsc_V[c] = *GetCurrTimeDate();
      }
      else if ((boExtendedEscV == true) || (GetDigitalPhone(c) != 0))
        db = mpdbEsc_V[c];
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == true)
          db = mpdbChannelsC[diCurr.ibLine];
        else
        {
          uchar p = ibPort;
          double2 db2 = ReadCntMonCan(ibMon, c);
          ibPort = p;

          if (!db2.fValid) db = 0; else db = db2.dbValue;
        }

        mptiEsc_V[c] = *GetCurrTimeDate();
      }

      wSize += PushFloatOrDouble(db, fDouble);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause(); // внимание !
}



void    OutEscS_Time(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      wSize += PushTime(mptiEsc_S[c]);
    }
  }

  OutptrOutBuff(wSize);      
}


void    OutEscV_Time(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      if (SupportedExtended6(c))
      {
        wSize += PushTime(mpCntBoxCan6[c].tiUpdate);
      }
      else
      {
        wSize += PushTime(mptiEsc_V[c]);
      }
    }
  }

  OutptrOutBuff(wSize);      
}
