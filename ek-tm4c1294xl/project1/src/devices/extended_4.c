/*------------------------------------------------------------------------------
EXTENDED_4.C

 «начени€ счетчиков на Ќј„јЋќ мес€ца
------------------------------------------------------------------------------*/

#include        "../console.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_extended_4.h"
#include        "../serial/ports.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/digitals_messages.h"
#include        "../devices/devices.h"
#include        "../sensors/automatic_p.h"
#include        "../sensors/automatic3.h"
#include        "../time/rtc.h"
#include        "../time/timedate.h"
#include        "extended_4.h"



file const              flExt4Flag = {FLS_EXT_4_FLAG, &boExt4Flag, sizeof(boolean)};
file const              flExt4Months = {FLS_EXT_4_MONTHS, &bExt4Months, sizeof(uchar)};
file const              flExt4EnblCan = {FLS_EXT_4_ENBL_CAN, &mpboExt4EnblCan, sizeof(mpboExt4EnblCan)};


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
                        szBadEnabling[] = "*  запрещено    ",
                        szBadMode[]     = "*  нет данных   ";



void    InitExtended4(void)
{
  LoadFileBoolean(&flExt4Flag, FALSE);
  LoadFileChar(&flExt4Months, 0, 12, 4);
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
}


/*




void    InitExtended4(void) 
{ 
  if ((bExt4Months <= 0) || (bExt4Months > 12))
    bExt4Months = 4;
}



void    ResetExtended4(void) 
{ 
  boExt4Flag = boFalse;
  bExt4Months = 4;
  cwDayCan4 = 0;
  cwMonCan4 = 0;

  memset(&mpEnblCan4, boTrue, sizeof(mpEnblCan4));
  memset(&mpCntMonCan4_, 0, sizeof(mpCntMonCan4_));
}
*/


void    NextDayExtended4(void)
{ 
  cwDayCan4++;
//  memset(&mpCntMonCan4_[ibHardMon], 0, sizeof(value6)*bCANALS);
}



void    NextMonExtended4(void) 
{
  cwMonCan4++;
//  memset(&mpCntMonCan4_[ibHardMon], 0, sizeof(value6)*bCANALS);
}

/*
void    MakeSimple4(void)
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
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines() == 1)
      {
        v6Buff = mpCntMonCan4_[ibMon][ibCan];

        if (mpboChannelsA[diPrev.ibLine] == boTrue)
        {
          v6Buff.bSelf = ST4_OK;
          v6Buff.reSelf = mpreChannelsB[diPrev.ibLine];
          ShowLo(szDataOK); DelayInf();
          if (ibCan == ibDig) bFlag4++;
        }
        else
        {
          v6Buff.bSelf = ST4_BADDIGITAL;
          v6Buff.reSelf = 0;
          ShowLo(szDataError); DelayInf();
        }

        v6Buff.tiSelf = *PGetCurrTimeDate();
        mpCntMonCan4_[ibMon][ibCan] = v6Buff;
      }
    }
  }
}


void    MakeCustom4(void)
{
uchar   i;

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  
  if (ReadCntMonCanFBuff(ibMon, ibDig) == 0) 
  { 
    ShowLo(szLinkError); DelayInf();
  }
  else
  { 
    ShowLo(szLinkOK); DelayInf();

    LoadCurrDigital(ibDig);      
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines() == 1)
      {
        v6Buff = mpCntMonCan4_[ibMon][ibCan];

        InitPop(15 + 15*ibCan);
        i = PopChar(); PopChar(); PopChar(); PopChar(); PopChar();
        PopReal();
        if (i == ST4_OK)
        {
          v6Buff.bSelf = i;
          v6Buff.reSelf = reBuffA;
          ShowLo(szDataOK); DelayInf();
          if (ibCan == ibDig) bFlag4++;
        }
        else
        {
          v6Buff.bSelf = i;
          v6Buff.reSelf = 0;
          ShowLo(szDataError); DelayInf();
        }

        v6Buff.tiSelf = *PGetCurrTimeDate();
        mpCntMonCan4_[ibMon][ibCan] = v6Buff;
      }
    }
  }
}


void    MakeExtended4(void)
{
uchar   i;

  if ((boExt4Flag == boTrue) && (mpEnblCan4[ibDig] == boTrue))
  {
    ShowHi(szExtended4); 
    Clear(); sprintf(szLo+3,"глубина: %bu", bExt4Months); DelayInf();

    bFlag4 = 0;
    for (i=0; i<bExt4Months; i++)
    {
      if (fKey == 1) break;

      ibMon = (bMONTHS + ibHardMon - i) % bMONTHS;

      v6Buff = mpCntMonCan4_[ibMon][ibDig];
      if (v6Buff.bSelf == ST4_OK) continue;

      Clear(); sprintf(szLo+3,"мес€ц: %-2bu",ibMon+1); DelayInf();

      (GetDigitalDevice(ibDig) != 6) ? MakeSimple4() : MakeCustom4();
    }

    Clear(); sprintf(szLo+3,"прин€то: %bu", bFlag4); DelayInf();

    ShowDigitalHi(); Clear();
  }
}



#ifndef MODBUS

void    PushData4(uchar  ibCanal, uchar  ibMonth)
{
  if (GetDigitalDevice(ibCanal) == 0)
  {
    PushChar(ST4_OK);
    PushInt(0xFF);
    PushInt(0xFF);
    reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal); PushReal();
    Push(&tiZero, sizeof(time));
  }
  else
  {
    v6Buff = mpCntMonCan4_[ibMonth][ibCanal]; 
    PushChar(v6Buff.bSelf);
    PushInt(0xFF);
    PushInt(0xFF);
    reBuffA = v6Buff.reSelf; PushReal();
    Push(&v6Buff.tiSelf, sizeof(time));
  }
}



void    OutExtended40(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));

    InitPushPtr();            
    wBuffD = 0;

    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
      {
        PushData4(i, InBuff(6));
        wBuffD += (1+2+2+4+6);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}



void    OutExtended401(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));

    InitPushPtr();            
    PushChar(boExt4Flag);
    PushChar(bExt4Months);
    PushInt(cwDayCan6);
    PushInt(cwMonCan6);
    wBuffD = 1+1+2+2;

    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
      {
        PushData4(i, InBuff(6));
        wBuffD += (1+2+2+4+6);
      }
    }

    OutptrOutBuff(wBuffD);
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

    InitPushPtr();            
    PushData4(InBuff(7), InBuff(6));
    OutptrOutBuff(1+2+2+4+6);
  }
}



void    OutExtended42(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if ((InBuff(6) >= bMONTHS) || (InBuff(7) >= bCANALS))
    Result(bRES_BADADDRESS);
  else
  {
    ibMon = InBuff(6);
    ibCan = InBuff(7);

    memset(&vaT, 0, sizeof(vaT));
    vaT.tiSelf = *PGetCurrTimeDate();

    if (GetDigitalDevice(ibCan) == 0) {
      if (LoadCntMon(ibMon) == 1) {  
        vaT.bSelf = ST4_OK;
        reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCan);
        vaT.reSelf = reBuffA;
      }
      else {  
        vaT.bSelf = ST4_BADFLASH;
        vaT.reSelf = 0;
      }

      InitPushPtr();            
      Push(&vaT, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else if (mpboEnblCan[ibCan] == boFalse) {
      vaT.bSelf = ST4_BADENABLING;
      vaT.reSelf = 0;

      InitPushPtr();            
      Push(&vaT, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else if (GetDigitalPhone(ibCan) != 0) {
      vaT.bSelf = ST4_BADPORT;
      vaT.reSelf = 0;

      InitPushPtr();            
      Push(&vaT, sizeof(value4));
      OutptrOutBuff(sizeof(value4));
    }
    else {
      SaveDisplay();

      ShowHi(szClear); 
      sprintf(szHi,"ћес€ц: %-2bu",ibMon+1); sprintf(szHi+14,"%2bu",ibCan+1);  
      Clear(); 

      i = ibPort;
      fAlt = ReadCntMonCan(ibMon,ibCan);
      ibPort = i;

      if (fAlt == 1) {
        vaT.bSelf = ST4_OK;
        vaT.reSelf = reBuffA;
      }
      else {
        vaT.bSelf = ST4_BADDIGITAL;
        vaT.reSelf = 0;
      }

      InitPushPtr();            
      Push(&vaT, sizeof(value4));
      OutptrOutBuff(sizeof(value4));

      LoadDisplay();
      NextPause();    // внимание !
    }     
  }
}



void    OutExtended43(void)
{
uchar   i;

  InitPushPtr();
  wBuffD = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      Push(&mpEnblCan4[i], sizeof(uchar));
      wBuffD += sizeof(uchar);
    }
  }

  OutptrOutBuff(wBuffD);
}

#endif


bit     ReadCntMonCanFCurr(uchar  ibMonth, uchar  ibCanal)
{
uchar   i;

  Clear();

  LoadCurrDigital(ibCanal);
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
    PushChar(ibMonth);         
    PushChar(ibCanal);         

    PckQueryIO(bHEADER+sizeof(value4)+2, 5+3+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  InitPop(bHEADER);
  bSpeciesCod = PopChar();
  PopChar(); PopChar(); PopChar(); PopChar(); 
  PopReal(); 
  Pop(&tiAlt, sizeof(time));   

  return(1);
}


bit     ReadCntMonCanFBuff(uchar  ibMonth, uchar  ibCanal)
{
uchar   i;

  Clear();

  LoadCurrDigital(ibCanal);
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
    PushChar(ibMonth);         

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
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  return(1);
}



void    ShowTimeDateF2(void)
{
  sprintf(szLo,"%02bu:%02bu %02bu.%02bu.%02bu",
                 tiAlt.bHour,
                 tiAlt.bMinute,
                 tiAlt.bDay,   
                 tiAlt.bMonth,
                 tiAlt.bYear);
}



void    ShowCntMonCanF2(void)
{
  switch (bSpeciesCod)
  {
    case ST4_NONE:         ShowLo(szNone);         break;
    case ST4_OK:           (ibZ == 0) ? ShowReal(&reBuffA) : ShowTimeDateF2(); break;    
    case ST4_BADDIGITAL:   ShowLo(szBadDigital);   break;
    case ST4_BADFLASH:     ShowLo(szBadFlash);     break;
    case ST4_BADPORT:      ShowLo(szBadPort);      break;
    case ST4_BADENABLING:  ShowLo(szBadEnabling);  break;
    default:               sprintf(szLo, "*  ошибка: %02bX", bSpeciesCod); break;
  }  
}



void    ShowExtended4(uchar  ibCanal, uchar  ibMonth)
{
  if (GetDigitalDevice(ibCanal) == 0)
  {
    LoadCntMon(ibMonth);

    v6Buff.bSelf = ST4_OK; 
    v6Buff.reSelf = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal);
    v6Buff.tiSelf = tiZero;
    bSpeciesCod = ST4_OK;
  }
  else
  {
    v6Buff = mpCntMonCan4_[ibMonth][ibCanal];
    bSpeciesCod = v6Buff.bSelf; 
  }

  reBuffA = v6Buff.reSelf;
  tiAlt = v6Buff.tiSelf;
  
  ShowCntMonCanF2();
}
 

*/
