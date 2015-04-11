/*------------------------------------------------------------------------------
DEVICE_F.C


------------------------------------------------------------------------------*/

#include        "../main.h"
//#include        "../memory/mem_settings.h"
//#include        "../memory/mem_digitals.h"
//#include        "../memory/mem_current.h"
//#include        "../memory/mem_factors.h"
//#include        "../memory/mem_realtime.h"
//#include        "../memory/mem_energy_spec.h"
//#include        "../memory/mem_profile.h"
//#include        "../memory/mem_limits.h"
//#include        "../display/display.h"
//#include        "../keyboard/key_timedate.h"
//#include        "../time/timedate.h"
//#include        "../time/calendar.h"
//#include        "../time/delay.h"
#include        "../serial/ports_stack.h"
//#include        "../serial/ports_devices.h"
//#include        "../serial/ports_common.h"
//#include        "../devices/devices.h"
//#include        "../devices/devices_time.h"
//#include        "../digitals/current/current_run.h"
//#include        "../digitals/digitals_messages.h"
//#include        "../digitals/limits.h"
//#include        "../digitals/profile/refill.h"
//#include        "../special/special.h"
//#include        "../flash/records.h"
//#include        "../energy.h"
#include        "device_f.h"


/*
#ifndef SKIP_F
*/
// переход в ведомый режим дл€ сумматоров —Ёћ+2
void    QueryBreakF(void)
{
  InitPush(0);
  PushChar(0x1A);          
  Query(0, 1, 1);

  Delay(50);
}


/*
// проверка сетевого адреса дл€ сумматоров —Ёћ+2
bit     ReadAddressF(void)
{
  return(InBuff(0) == diCurr.bAddress);
}


// проверка результата операции дл€ сумматоров —Ёћ+2
bit     ReadResultF(void)
{
  TestResult(InBuff(5));
  return(ReadAddressF() && (InBuff(5) == 0));
}



// запрос на времени/даты дл€ сумматоров —Ёћ+2
void    QueryTimeF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (0+7) % 0x100 );
  PushChar( (0+7) / 0x100 );

  PushChar(bINQ_GETCURRTIME);         

  PckQueryIO(sizeof(time)+7, 0+7);
}


// чтение времени/даты дл€ сумматоров —Ёћ+2
void    ReadTimeAltF(void)
{
  InitPop(5);

  tiAlt.bSecond = PopChar();
  tiAlt.bMinute = PopChar();
  tiAlt.bHour   = PopChar();
  tiAlt.bDay    = PopChar();
  tiAlt.bMonth  = PopChar();
  tiAlt.bYear   = PopChar();
}



void    QueryIdF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);
  PushChar(0);

  PushChar( (0+7) % 0x100 );
  PushChar( (0+7) / 0x100 );

  PushChar(bINQ_GETLOGICAL);

  PckQueryIO(2+7, 0+7);
}


bit     ReadIdF(void)
{
  InitPop(0);
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;
  if (PopChar() != ((2+7) % 0x100)) return 0;
  if (PopChar() != ((2+7) / 0x100)) return 0;
  if (PopChar() != bINQ_GETLOGICAL) return 0;
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;

  return 1;
}



// запрос на чтение реальных показаний счЄтчиков дл€ сумматоров —Ёћ+2
void    QueryRealExtendedF(uchar  bQuery)
{
uchar   i;

  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (1+bCANALS/8+7) % 0x100 );
  PushChar( (1+bCANALS/8+7) / 0x100 );

  PushChar(0xFF);
  PushChar(bQuery);         

  for (i=0; i<bCANALS/8; i++) 
    PushChar(0xFF);

  PckQueryIO(bHEADER+sizeof(real)*bCANALS+2, 1+bCANALS/8+7);
}


// чтение реальных показаний счЄтчиков дл€ сумматоров —Ёћ+2
void    ReadRealExtendedF(void)
{
uchar   i;

  InitPop(bHEADER);

  for (i=0; i<bCANALS; i++)
  {
    PopReal();

    SetCanReal(mpreChannelsB, i);
    mpboChannelsA[i] = boTrue;
  }

  reBuffA = *PGetCanReal(&mpreChannelsB, diCurr.ibLine);
}



// запрос на чтение коэффициентов дл€ сумматоров —Ёћ+2
void    QueryKoeffF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (1+7) % 0x100 );
  PushChar( (1+7) / 0x100 );

  PushChar(bINQ_GETKOEFF);         
  PushChar(diCurr.ibLine);          

  PckQueryIO(sizeof(real)*4+7, 1+7);
}


// чтение коэффициентов дл€ сумматоров —Ёћ+2
void    ReadKoeffF(void)
{
  InitPop(5);

  PopReal();
  SetCanReal(mpreTransEng,ibDig);
  PopReal();
  SetCanReal(mpreTransCnt,ibDig);
  PopReal();
  SetCanReal(mprePulseHou,ibDig);
  PopReal();
  SetCanReal(mprePulseMnt,ibDig);
}



// посылка запроса на коррекцию времени дл€ сумматора —Ёћ+2
void    QueryControlF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (7+7) % 0x100 );
  PushChar( (7+7) / 0x100 );

  PushChar(0xFF);       
  PushChar(bEXT_CORRECT2);         

  PushChar( tiCurr.bSecond );
  PushChar( tiCurr.bMinute );
  PushChar( tiCurr.bHour   );
  PushChar( tiCurr.bDay    );
  PushChar( tiCurr.bMonth  );
  PushChar( tiCurr.bYear   );

  PckQueryIO(1+7, 7+7);
}



void    QueryHeaderF(void)
{
uchar   i;

  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (1+bCANALS/8+7) % 0x100 );
  PushChar( (1+bCANALS/8+7) / 0x100 );

  PushChar(0xFF);
  PushChar(bEXT_GETSTOPCAN);

  for (i=0; i<bCANALS/8; i++) 
    PushChar(0xFF);

  PckQueryIO(bHEADER+sizeof(uint)*bCANALS+2, 1+bCANALS/8+7);
}


void    ReadHeaderF(void)
{
  InitPop(bHEADER);
    
  for (ibCan=0; ibCan<bCANALS; ibCan++)
    mpwChannels[ibCan] = PopChar()*0x100 + PopChar();


  Clear(); sprintf(szLo+1,"%04u",mpcwStopCan[ibDig]);

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      if (mpcwStopCan[ibCan] < mpwChannels[diPrev.ibLine])
        mpcwStopCan[ibCan] = mpwChannels[diPrev.ibLine];

      if (ibCan == ibDig) sprintf(szLo+6,"%04u",mpwChannels[diPrev.ibLine]);
    }
  }

  sprintf(szLo+11,"%04u",mpcwStopCan[ibDig]); DelayMsg();
}


void    InitEnergyF(void)
{
  if (!UseBounds())
    iwMajor = 0;
  else 
  {
    iwMajor = mpcwStartRelCan[ibDig];
    sprintf(szLo," начало %04u:%02bu ",iwMajor,(uchar)(iwMajor/48 + 1));
    DelayMsg();
  }
}


void    QueryEnergyF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (4+7) % 0x100 );
  PushChar( (4+7) / 0x100 );

  PushChar(0xFF);       
  PushChar(bEXT_GETIMPCANHOU);         

  PushChar( iwMajor / 0x100 );
  PushChar( iwMajor % 0x100 );

  PushChar(bBLOCKS_F);

  PckQueryIO(bHEADER+bBLOCKS_F*(sizeof(time)+sizeof(uint)*bCANALS)+2, 4+7);
}


bit     ReadEnergyF(uchar  ibBlock)
{
  NoShowTime(1);                                        // запрещаем автоматическое отображение времени
  

  InitPop(bHEADER+ibBlock*(sizeof(time)+sizeof(uint)*bCANALS));

  tiDig.bSecond = PopChar();                            // врем€/дата часового блока
  tiDig.bMinute = PopChar();
  tiDig.bHour   = PopChar();
  tiDig.bDay    = PopChar();
  tiDig.bMonth  = PopChar();
  tiDig.bYear   = PopChar();

  sprintf(szLo," %02bu:%02bu %02bu.%02bu.%02bu",        // показываем врем€/дату часового блока
          tiDig.bHour,tiDig.bMinute, tiDig.bDay,tiDig.bMonth,tiDig.bYear);
  

  tiAlt = tiDig;
  if (SearchDefHouIndex() == 0) return(0);              // выход: часовой блок не имеетс€ в массиве получасового брака
  
  ShowProgressDigHou();      

    
  for (ibCan=0; ibCan<bCANALS; ibCan++)                 // читаем количество импульсов по каналам
    mpwChannels[ibCan] = PopChar()*0x100 + PopChar();

  tiAlt = tiDig;
  MakePrevHou();  
  return(MakeStopHou(0));
}



void    QueryCurrentF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (4+4) % 0x100 );
  PushChar( (4+4) / 0x100 );

  PushChar(0xFF);       
  PushChar(bEXT_GETIMPCANMNT);         

  PckQueryIO(bHEADER+sizeof(uint)*bCANALS+2, 4+4);
}


void    ReadCurrentF(void)
{
uchar   i;

  InitPop(bHEADER);

  for (i=0; i<bCANALS; i++)
  {
    dwBuffC = (ulong)(PopChar()*0x100 + PopChar());
    SetCanLong(mpdwChannelsB, i);
  }


  ShowLo(szPowerOK); Delay(200);

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      mpboReadyCan[ibCan] = boTrue;

      dwBuffC = mpdwChannelsB[ diPrev.ibLine ];
      mpwImpMntCan[ (bMINUTES+ibSoftMnt-1) % bMINUTES ][ibCan] = (uint)dwBuffC;
    }
  }

  NextCurrent();
}

#endif
*/
