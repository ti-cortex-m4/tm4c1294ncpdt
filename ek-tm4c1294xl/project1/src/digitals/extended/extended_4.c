/*------------------------------------------------------------------------------
EXTENDED_4.C

 «начени€ счетчиков на конец мес€цев из буфера с дозапросом (oтчет є52 от 21.11.2009)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_extended_6.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_pause.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/digitals_messages.h"
#include "../../devices/devices.h"
#include "../../sensors/device_f.h"
#include "../../sensors/automatic_p.h"
#include "../../sensors/automatic2.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../engine.h"
#include "../../energy2.h"
#include "extended_4.h"



file const              flExt4Flag = {EXT_4_FLAG, &boExt4Flag, sizeof(boolean)};
file const              flExt4Months = {EXT_4_MONTHS, &bExt4Months, sizeof(uchar)};
file const              flExt4EnblCan = {EXT_4_ENBL_CAN, &mpboExt4EnblCan, sizeof(mpboExt4EnblCan)};


//                                         0123456789ABCDEF
static char const       szExtended4[]   = "ќпрос данных: 4 ",
                        szLinkOK[]      = "   ответ: есть  ",
                        szLinkError[]   = "   ответ: нет   ",
                        szDataOK[]      = "  данные: есть  ",
                        szDataError[]   = "  данные: нет   ",
                        szNone[]        = "*    пусто      ",
                        szBadDigital[]  = "*   ошибка !    ",
                        szBadFlash[]    = "* flash error   ",
                        szBadPort[]     = "*    модем      ",
                        szBadEnabling[] = "*  запрещено    ";



static uchar            bFlag4;
static uchar            bStatus;



boolean SaveExt4Values(uchar  ibMon)
{
  return SaveBuff(EXT_4_MON_VALUES + ibMon*VALUE4_CAN_PAGES, &mpCntMonCan4, sizeof(mpCntMonCan4));
}


boolean LoadExt4Values(uchar  ibMon)
{
  return LoadBuff(EXT_4_MON_VALUES + ibMon*VALUE4_CAN_PAGES, &mpCntMonCan4, sizeof(mpCntMonCan4));
}



void    InitExtended4(void)
{
  LoadFileBoolean(&flExt4Flag, FALSE);
  LoadFileChar(&flExt4Months, 1, 12, 4);
  LoadFile(&flExt4EnblCan);
}


void    ResetExtended4(void)
{ 
  boExt4Flag = FALSE;
  SaveFile(&flExt4Flag);

  bExt4Months = 4;
  SaveFile(&flExt4Months);


  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpboExt4EnblCan[c] = TRUE;
  }

  SaveFile(&flExt4EnblCan);


  memset(&mpCntMonCan4, 0, sizeof(mpCntMonCan4));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveExt4Values(m);
  }


  cwDayCan4 = 0;
  cwMonCan4 = 0;
}



void    NextDayExtended4(void)
{ 
  cwDayCan4++;

  memset(&mpCntMonCan4, 0, sizeof(mpCntMonCan4));
  SaveExt4Values(ibHardMon);
}



void    NextMonExtended4(void) 
{
  cwMonCan4++;

  memset(&mpCntMonCan4, 0, sizeof(mpCntMonCan4));
  SaveExt4Values(ibHardMon);
}



static void MakeDevices(uchar  ibMon)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  if (ReadCntMonCan(ibMon, ibDig) == 0) 
  { 
    ShowLo(szLinkError); DelayInf();
  }
  else
  { 
    ShowLo(szLinkOK); DelayInf();

    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        value6 vl = mpCntMonCan4[c];

        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          vl.bSelf = ST4_OK;
          vl.reSelf = mpreChannelsB[diPrev.ibLine];
          ShowLo(szDataOK); DelayInf();
          if (c == ibDig) bFlag4++;
        }
        else
        {
          vl.bSelf = ST4_BADDIGITAL;
          vl.reSelf = 0;
          ShowLo(szDataError); DelayInf();
        }

        vl.tiSelf = *GetCurrTimeDate();
        mpCntMonCan4[c] = vl;
      }
    }
  }
}


static void MakeDevice6(uchar  ibMon)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  if (ReadCntMonCanFBuff(ibMon, ibDig) == 0) 
  { 
    ShowLo(szLinkError); DelayInf();
  }
  else
  { 
    ShowLo(szLinkOK); DelayInf();

    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
      	value6 vl = mpCntMonCan4[c];

        InitPop(15 + 15*c);
        status st = (status) PopChar();
        PopChar(); PopChar(); PopChar(); PopChar();
        real re = PopFloat();

        if (st == ST4_OK)
        {
          vl.bSelf = st;
          vl.reSelf = re;
          ShowLo(szDataOK); DelayInf();
          if (c == ibDig) bFlag4++;
        }
        else
        {
          vl.bSelf = st;
          vl.reSelf = 0;
          ShowLo(szDataError); DelayInf();
        }

        vl.tiSelf = *GetCurrTimeDate();
        mpCntMonCan4[c] = vl;
      }
    }
  }
}


void    MakeExtended4(void)
{
  if ((boExt4Flag == TRUE) && (mpboExt4EnblCan[ibDig] == TRUE))
  {
    ShowHi(szExtended4); 
    Clear(); sprintf(szLo+3,"глубина: %u", bExt4Months);
    DelayInf();

    bFlag4 = 0;

    uchar m;
    for (m=0; m<bExt4Months; m++)
    {
      if (fKey == true) break;

      uchar ibMon = (bMONTHS + ibHardMon - m) % bMONTHS;
      LoadExt4Values(ibMon);

      value6 vl = mpCntMonCan4[ibDig];
      if (vl.bSelf == ST4_OK) continue;

      Clear(); sprintf(szLo+3,"мес€ц: %-2u",ibMon+1); DelayInf();

      (GetDigitalDevice(ibDig) != 6) ? MakeDevices(ibMon) : MakeDevice6(ibMon);

      SaveExt4Values(ibMon);
    }

    Clear(); sprintf(szLo+3,"прин€то: %u", bFlag4); DelayInf();

    ShowCanalNumber(ibDig);
    Clear();
  }
}



void    PushData4(uchar  ibCan, uchar  ibMon)
{
  if (GetDigitalDevice(ibCan) == 0)
  {
    PushChar(ST4_OK);
    PushInt(0xFF);
    PushInt(0xFF);
    PushFloat(mpreCntMonCan[ PrevSoftMon() ][ibCan]);
    PushTime(tiZero);
  }
  else
  {
  	value6 va = mpCntMonCan4[ibCan];
    PushChar(va.bSelf);
    PushInt(0xFF);
    PushInt(0xFF);
    PushFloat(va.reSelf);
    PushTime(va.tiSelf);
  }
}



void    OutExtended40(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));
    LoadExt4Values(InBuff(6));

    InitPushPtr();            
    uint wSize = 0;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        PushData4(c, InBuff(6));
        wSize += (1+2+2+4+6);
      }
    }

    OutptrOutBuff(wSize);
  }
}



void    OutExtended401(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));
    LoadExt4Values(InBuff(6));

    InitPushPtr();            
    PushChar(boExt4Flag);
    PushChar(bExt4Months);
    PushInt(cwDayCan6);
    PushInt(cwMonCan6);
    uint wSize = 1+1+2+2;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        PushData4(c, InBuff(6));
        wSize += (1+2+2+4+6);
      }
    }

    OutptrOutBuff(wSize);
  }
}



void    OutExtended41(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if ((InBuff(6) >= bMONTHS) || (InBuff(7) >= bCANALS))
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));
    LoadExt4Values(InBuff(6));

    InitPushPtr();            
    PushData4(InBuff(7), InBuff(6));
    OutptrOutBuff(1+2+2+4+6);
  }
}



void    OutExtended42(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if ((InBuff(6) >= bMONTHS) || (InBuff(7) >= bCANALS))
    Result(bRES_BADADDRESS);
  else
  {
    uchar ibMon = InBuff(6);
    uchar ibCan = InBuff(7);

    value4 va;
    memset(&va, 0, sizeof(va));
    va.tiSelf = *GetCurrTimeDate();

    if (GetDigitalDevice(ibCan) == 0)
    {
      if (LoadCntMon(ibMon) == 1)
      {
        va.bSelf = ST4_OK;
        va.reSelf = mpreCntMonCan[ PrevSoftMon() ][ibCan];
      }
      else
      {
        va.bSelf = ST4_BADFLASH;
        va.reSelf = 0;
      }

      InitPushPtr();            
      Push(&va, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else if (mpboEnblCan[ibCan] == FALSE)
    {
      va.bSelf = ST4_BADENABLING;
      va.reSelf = 0;

      InitPushPtr();            
      Push(&va, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else if (GetDigitalPhone(ibCan) != 0)
    {
      va.bSelf = ST4_BADPORT;
      va.reSelf = 0;

      InitPushPtr();            
      Push(&va, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else
    {
      SaveDisplay();

      ShowHi(szClear); 
      sprintf(szHi,"ћес€ц: %-2u",ibMon+1); sprintf(szHi+14,"%2u",ibCan+1);
      Clear(); 

      uchar p = ibPort;
      bool f = ReadCntMonCan(ibMon,ibCan);
      ibPort = p;

      if (f == 1)
      {
        va.bSelf = ST4_OK;
        va.reSelf = reBuffA;
      }
      else
      {
        va.bSelf = ST4_BADDIGITAL;
        va.reSelf = 0;
      }

      InitPushPtr();            
      Push(&va, sizeof(value4));
      OutptrOutBuff(sizeof(value4));

      LoadDisplay();
      NextPause(); // внимание !
    }     
  }
}



void    OutExtended43(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      Push(&mpboExt4EnblCan[c], sizeof(uchar));
      wSize += sizeof(uchar);
    }
  }

  OutptrOutBuff(wSize);
}



bool    ReadCntMonCanFCurr(uchar  ibMon, uchar  ibCan)
{
uchar   i;

  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  Clear(); 

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();

    InitPushPck();
    PushChar(diCurr.bAddress);          
    PushChar(0);

    PushChar((5+3+2) % 0x100);
    PushChar((5+3+2) / 0x100);

    PushChar(0xFF);
    PushChar(bEXT_GETEXTENDED42);         
    PushChar(ibMon);         
    PushChar(ibCan);         

    PckQueryIO(bHEADER+sizeof(value4)+2, 5+3+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  InitPop(bHEADER);
  bStatus = PopChar();
  PopChar(); PopChar(); PopChar(); PopChar(); 
  PopFloat(); 
  Pop(&tiAlt, sizeof(time));   

  return(1);
}


bool    ReadCntMonCanFBuff(uchar  ibMon, uchar  ibCan)
{
uchar   i;

  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  Clear(); 

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();

    InitPushPck();
    PushChar(diCurr.bAddress);          
    PushChar(0);

    PushChar((5+10+2) % 0x100);
    PushChar((5+10+2) / 0x100);

    PushChar(0xFF);
    PushChar(bEXT_GETEXTENDED40);         
    PushChar(ibMon);         

    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);

    PckQueryIO(bHEADER+sizeof(value4)*bCANALS+2, 5+10+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  return(1);
}



void    ShowTimeDateF2(void)
{
  sprintf(szLo,"%02u:%02u %02u.%02u.%02u",
                 tiAlt.bHour,
                 tiAlt.bMinute,
                 tiAlt.bDay,   
                 tiAlt.bMonth,
                 tiAlt.bYear);
}



void    ShowCntMonCanF2(void)
{
  switch (bStatus)
  {
    case ST4_NONE:         ShowLo(szNone);         break;
    case ST4_OK:           (ibZ == 0) ? ShowFloat(reBuffA) : ShowTimeDateF2(); break;
    case ST4_BADDIGITAL:   ShowLo(szBadDigital);   break;
    case ST4_BADFLASH:     ShowLo(szBadFlash);     break;
    case ST4_BADPORT:      ShowLo(szBadPort);      break;
    case ST4_BADENABLING:  ShowLo(szBadEnabling);  break;
    default:               sprintf(szLo, "*  ошибка: %02X", bStatus); break;
  }  
}



void    ShowExtended4(uchar  ibCan, uchar  ibMon)
{
  value6 va;

  if (GetDigitalDevice(ibCan) == 0)
  {
    LoadCntMon(ibMon);

    va.bSelf = ST4_OK; 
    va.reSelf = mpreCntMonCan[ PrevSoftMon() ][ibCan];
    va.tiSelf = tiZero;
    bStatus = ST4_OK;
  }
  else
  {
    LoadExt4Values(ibMon);

    va = mpCntMonCan4[ibCan];
    bStatus = va.bSelf;
  }

  reBuffA = va.reSelf;
  tiAlt = va.tiSelf;

  ShowCntMonCanF2();
}

