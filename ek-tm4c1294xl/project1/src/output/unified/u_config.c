/*------------------------------------------------------------------------------
U_CONFIG.C


------------------------------------------------------------------------------*/
/*
#include        <string.h>
#include        "main.h"
#include        "xdata.h"
#include        "x_digitals.h"
#include        "queries2.h"
#include        "keyboard.h"
#include        "ports.h"
#include        "access.h"
#include        "memory.h"
#include        "engine.h"
#include        "sensors.h"
#include        "groups.h"
#include        "devices.h"
#include        "timedate.h"
#include        "nexttime.h"
#include        "rtc.h"
#include        "gps2.h"
#include        "postinput2.h"



#ifndef MODBUS

uchar           code    mpbDevicesMask[bDEVICES][8] = 
                        {
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF}, // 1
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF}, // 2
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x70,0xFF}, // 3
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 4
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 5
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 6
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 7
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF}, // 8
                          {0x00,0x00,0x00,0x00,0x00,0x3F,0x77,0x77}, // 9
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 10
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 11
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF}, // 12
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 13
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 14
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 15
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 16
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 17
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 18
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 19
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 20
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x0F,0xFF}, // 21
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 22
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 23
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 24
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0xFF}, // 25
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x07}, // 26
                        };



bit     IsDeviceAdded(uchar  ibDev)
{
uchar   i;

  if (GetDigitalDevice(ibDev) == 0) return 1;

  if (cbDevicesUni > 0)
  {
    for (i=0; i<cbDevicesUni; i++)
    {
      if( (mpdiDevicesUni[i].ibPort   == GetDigitalPort(ibDev)) &&
          (mpdiDevicesUni[i].ibPhone  == GetDigitalPhone(ibDev)) &&
          (mpdiDevicesUni[i].bDevice  == GetDigitalDevice(ibDev)) &&
          (mpdiDevicesUni[i].bAddress == GetDigitalAddress(ibDev)) ) return 1;
    }
  }

  return 0;
}


void    MakeDevicesUni(void) 
{
  memset(&mpdiDevicesUni, 0, sizeof(mpdiDevicesUni));
  cbDevicesUni = 0;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
    if (IsDeviceAdded(ibCan) == 0) 
       mpdiDevicesUni[cbDevicesUni++] = mpdiDigital[ibCan];
}


uchar   GetUsedCanals(void)
{
uchar   i=0;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
    if (GetDigitalDevice(ibCan) != 0)
      i++;

  return i;
}


uchar   GetUsedGroups(void)
{
uchar   i=0;

  for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)
    if (GetGroupsSize(ibGrp) > 0)
      i++;

  return i;
}


uchar   GetCanalsCount(uchar  ibDev)
{
uchar   i,j;

  j = 0;
  for (i=0; i<bCANALS; i++)
  {
    if( (mpdiDevicesUni[ibDev].ibPort   == GetDigitalPort(i)) &&
        (mpdiDevicesUni[ibDev].ibPhone  == GetDigitalPhone(i)) &&
        (mpdiDevicesUni[ibDev].bDevice  == GetDigitalDevice(i)) &&
        (mpdiDevicesUni[ibDev].bAddress == GetDigitalAddress(i)) ) j++;
  }

  return j; 
}


uchar   GetFirstCanalsNumber(uchar  ibDev)
{
uchar   i;

  for (i=0; i<bCANALS; i++)
  {
    if( (mpdiDevicesUni[ibDev].ibPort   == GetDigitalPort(i)) &&
        (mpdiDevicesUni[ibDev].ibPhone  == GetDigitalPhone(i)) &&
        (mpdiDevicesUni[ibDev].bDevice  == GetDigitalDevice(i)) &&
        (mpdiDevicesUni[ibDev].bAddress == GetDigitalAddress(i)) ) return i + 1;
  }

  return 0;
}


uchar   GetDeviceNumber(uchar  ibCan)
{
uchar   i;

  if (cbDevicesUni > 0)
  {
    for (i=0; i<cbDevicesUni; i++)
    {
      if( (mpdiDevicesUni[i].ibPort   == GetDigitalPort(ibCan)) &&
          (mpdiDevicesUni[i].ibPhone  == GetDigitalPhone(ibCan)) &&
          (mpdiDevicesUni[i].bDevice  == GetDigitalDevice(ibCan)) &&
          (mpdiDevicesUni[i].bAddress == GetDigitalAddress(ibCan)) ) return i + 1;
    }
  }

  return 0;
}



void    GetCorrectUni(void)
{
  InitPop(6);
  Pop(&tiAlt, sizeof(time));

  if (TrueTimeDate() == 1)
  {
    if ((tiCurr.bDay   != tiAlt.bDay)   ||
        (tiCurr.bMonth != tiAlt.bMonth) ||
        (tiCurr.bYear  != tiAlt.bYear))
      Result2(bUNI_BADTIME);
    else
    if (GetHouIndex() != (tiAlt.bHour*2 + tiAlt.bMinute/30))
      Result2(bUNI_BADTIME);
    else
    { 
      CorrectTime_Full(EVE_UNI_CORRECT);

      Result2(bUNI_OK);
    }
  }
  else Result2(bUNI_BADDATA);
}



void    GetCorrectionsUni(void)
{
  InitPushUni();
  for (ibCan=bInBuff6; ibCan<bInBuff6+bInBuff7; ibCan++)
  {
    if (ibCan == 0)
      PushInt((sint)(mpcwPosValueCurr[0] - mpcwNegValueCurr[0]));
    else if (ibCan == 1)
      PushInt((sint)(mpcwPosValuePrev[0] - mpcwNegValuePrev[0]));
    else
      PushInt(0);
  }
  Output2(2*(bInBuff7-bInBuff6));
}



void    GetOpenUni(void) 
{
uchar   i;

  memset(&mpbPassTwo, 0, sizeof(mpbPassTwo));

  for (i=0; i<8; i++) 
    mpbPassTwo[i] = InBuff(6+i) - 0x30;

  if ((memcmp(mpbPassOne, mpbPassTwo, 8) == 0) || SuperUser())
  {
    SetDelayUni();
    Result2(bUNI_GOODPASSWORD);
  }
  else
  {
    Result2(bUNI_BADPASSWORD);
  }
}



void    GetConfigUni(void) 
{
  MakeDevicesUni();

  InitPushUni();

  Push("ÑÝÌ+2 ", 6);
  PushCharDec2Txt(GetBuildDate_Day());
  PushChar('.');
  PushCharDec2Txt(GetBuildDate_Month());
  PushChar('.');
  PushCharDec2Txt(GetBuildDate_Year());
  PushChar(' ');

  PushCharDec2Txt(bMAXVERSION);
  PushChar('.');
  PushCharDec2Txt(bMINVERSION);
  PushChar('.');
  PushCharDec2Txt(GetBuildNumber() / 100);
  PushCharDec2Txt(GetBuildNumber() % 100);
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');

  Push(szObjectName, 32);

  PushInt(wPrivate / 0x10000);
  PushInt(wPrivate % 0x10000);

  PushInt(GetCODEChecksum());
  PushInt(GetUsedCanals());
  PushInt(GetUsedGroups());
  PushInt(bTARIFFS);
  PushInt(bDEVICES);
  PushInt(cbDevicesUni);
  PushInt(wOUTBUFF_SIZE);

  Output2(32+32+4+2+2+2+2+2+2+2);
}



void    GetSensorsUni(void) 
{
  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bDEVICES)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > bDEVICES + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();
    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      PushInt(ibCan);

      for (ibGrp=1; ibGrp<16; ibGrp++) 
        PushChar(msgDevices[ibCan][ibGrp]);

      PushChar(0);
    }
    Output2((uint)(2+16)*bInBuff9);
  }
}



void    GetDigitalsUni(void) 
{
uchar   i,j;

  MakeDevicesUni();

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > cbDevicesUni)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > cbDevicesUni + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();
    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      PushInt(ibCan);

      PushInt(mpdiDevicesUni[ibCan-1].bDevice);

      PushChar(0xFF);
      PushChar(0xFF);
      PushChar(0xFF);
      PushChar(0xFF);

      PushInt(mpdiDevicesUni[ibCan-1].bAddress);
      PushInt(GetCanalsCount(ibCan-1));
      PushInt(wHOURS);
      PushInt(GetFirstCanalsNumber(ibCan-1));

      PushChar(0);
      PushChar(0);
      PushChar(0);
      PushChar(0);
      PushChar(0);
      PushChar(0);

      PushChar(0);
      ibGrp = 0;
      if (boLoadMnt == TRUE) ibGrp |= 0x01;
      ibGrp |= 0x02;
      if (boLoadHou == TRUE) ibGrp |= 0x04;
      if (boEnableParam == TRUE) ibGrp |= 0x08;
      PushChar(ibGrp);

      j = mpdiDevicesUni[ibCan-1].bDevice - 1;
      for (i=0; i<8; i++)
        PushChar(mpbDevicesMask[j][i]);

      if (mpdiDevicesUni[ibCan-1].ibPhone == 0)
      {
        for (ibGrp=0; ibGrp<32; ibGrp++) PushChar(0);
      }
      else
      { 
        Push(&mpphPhones[ mpdiDevicesUni[ibCan-1].ibPhone - 1 ].szNumber, 13);
        for (ibGrp=0; ibGrp<32-13; ibGrp++) PushChar(0);
      }    
    }
  }
  Output2((uint)(2+2+4+2+2+2+2+6+2+8+32)*bInBuff9);
}



void    GetCanalsUni(void) 
{
  MakeDevicesUni();

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > bCANALS + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();
    for (ibCan=bInBuff7; ibCan<bInBuff7+bInBuff9; ibCan++)
    {
      PushInt(ibCan);

      PushInt(GetDeviceNumber(ibCan-1));
      PushInt(GetDigitalLine(ibCan-1)+1);

      reBuffA = mpreTransEng[ibCan-1];
      PushReal();

      reBuffA = mprePulseHou[ibCan-1];
      PushReal();

      reBuffA = mpreLosse[ibCan-1];
      PushReal();

      PushChar(GetDigitalLine(ibCan-1));

      ibGrp = 0;
      if (mpboEnblCan[ibCan-1] != TRUE) ibGrp |= 0x01;     
      PushChar(ibGrp);

      Push(mpszCanalsName[ibCan-1], 32);
    }
    Output2((uint)(2+2+2+4+4+4+1+1+32)*bInBuff9);
  }
}



void    GetGroupsUni(void) 
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > bGROUPS + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();

    for (ibGrp=bInBuff7-1; ibGrp<bInBuff7+bInBuff9-1; ibGrp++)
    {
      PushInt(ibGrp+1);

      for (ibCan=0; ibCan<128-16; ibCan++)
        PushChar(0);

      memset(&mpbGroupMaskUni, 0, sizeof(mpbGroupMaskUni));
      if (GetGroupsSize(ibGrp) > 0)
      {
        for (ibCan=0; ibCan<GetGroupsSize(ibGrp); ibCan++)
        {
          i = GetGroupsNodeCanal(ibGrp, ibCan);
          mpbGroupMaskUni[16-1 - (i / 4)] |= (0x01 << ((i % 4) * 2));

          if (GetGroupsNodeSign(ibGrp, ibCan) == 1)
            mpbGroupMaskUni[16-1 - (i / 4)] |= (0x02 << ((i % 4) * 2));   
        }
      }
      Push(mpbGroupMaskUni, sizeof(mpbGroupMaskUni));

      Push(mpszGroupsName[ibGrp], bNAME);
    }

    Output2((uint)(2+128+32)*bInBuff9);
  }
}

#endif
*/
