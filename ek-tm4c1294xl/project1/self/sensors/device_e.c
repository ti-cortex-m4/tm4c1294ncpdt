/*------------------------------------------------------------------------------
DEVICE_E!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../display/display.h"
#include "../digitals/digitals_display.h"
#include "../keyboard/time/key_timedate.h"
//#include        "xdata.h"
//#include        "display.h"
//#include        "timer0.h"
//#include        "lines.h"
//#include        "timedate.h"
//#include        "delay.h"
//#include        "beep.h"
//#include        "ports.h"
//#include        "engine.h"
//#include        "energy.h"
//#include        "special.h"
//#include        "nexttime.h"
//#include        "digitals.h"
//#include        "essential.h"
//#include        "sensors.h"
//#include        "watchdog.h"
//#include        "_timedate.h"



//#ifndef SKIP_E
/*
void    QueryBreakE(void)
{
  InitPush(0);
  PushChar(0x1A);          
  Query(0, 1, 1);

  DelayInf();
}



// посылка запроса на открытие канала св€зи дл€ сумматоров —Ёћ-2
void    QueryOpenE(void)
{
  InitPush(0);
  PushChar(0x1B);          
  PushChar('0'+diCurr.bAddress);            

  Query(1+1, 2, 1);
}


bit     ReadOpenE(void)
{
  return(InBuff(0) == diCurr.bAddress+'0');
}



void    QueryTimeE(void)
{
  InitPush(0);
  PushChar(0x1B);          
  PushChar('T');            

  Query(6+1, 2, 1);  
}


// чтение времени/даты дл€ сумматоров —Ёћ-2
void    ReadTimeAltE(void)
{
  InitPop(0);

  tiAlt.bSecond = FromBCD( PopChar() );
  tiAlt.bMinute = FromBCD( PopChar() );
  tiAlt.bHour   = FromBCD( PopChar() );
  tiAlt.bDay    = FromBCD( PopChar() );
  tiAlt.bMonth  = FromBCD( PopChar() );
  tiAlt.bYear   = FromBCD( PopChar() );
}


// чтение времени/даты дл€ сумматоров —Ёћ-2
void    ReadTimeDigE(void)
{
  InitPop(0);

  tiDig.bSecond = FromBCD( PopChar() );
  tiDig.bMinute = FromBCD( PopChar() );
  tiDig.bHour   = FromBCD( PopChar() );
  tiDig.bDay    = FromBCD( PopChar() );
  tiDig.bMonth  = FromBCD( PopChar() );
  tiDig.bYear   = FromBCD( PopChar() );
}



void    QueryCorrectE(void)
{
  InitPush(0);
  PushChar(0x1B);          
  PushChar('k');            

  Query(2+1, 2, 1);  
}


bit     ReadCorrectE(void)
{
  return((InBuff(0) == 'k') && (InBuff(1) == 0x55));
}



void    QueryDefectE(void)
{
  InitPush(0);
  PushChar(0x1B);          
  PushChar('^');            

  Query(48*16+1, 2, 1);                         
}


void    ReadDefectE(void)
{
uint    i;

  InitPop(0);
  for (i=0; i<48*16; i++) 
    mpbEsc_Def[i] = PopChar();
}


void    DefaultDefectE(void)
{
uint    i;

  for (i=0; i<48*16; i++) 
    mpbEsc_Def[i] = true;
}



void    QueryEnergyE(void)
{
  InitPush(0);
  PushChar(0x1B);          
  PushChar('L');            

  Query(1536+1, 2, 0);                          // опрашиваем с расширенными задержками
}


void    ReadEnergyE(void)
{
uint    i;

  HideCurrTime(1);                                

  InitPop(0);
  for (i=0; i<48*16; i++) 
  {
    wBuffD  = PopChar();
    wBuffD += PopChar()*0x100;

    mpwEsc_L[i] = wBuffD;
  }
}



void    QueryIndexE(void)
{
  InitPush(0);
  PushChar(0x1B);          
  PushChar('l');            

  Query(2+1, 2, 1);  
}


bit     ReadIndexE(uchar  chEsc, uchar  i)
{
  return( (InBuff(0) == chEsc) && (InBuff(1) == i) );
}



bit     MakeEnergyE(void)
{
uchar   i,j;

  // индекс получаса с опрошенного сумматора —Ёћ-2
  j = tiDig.bHour*2 + tiDig.bMinute/30;

  // врем€ на начало текущих суток
  tiDig.bHour   = 0;
  tiDig.bMinute = 0;

  // индекс на начало текущих суток
  if (SearchDefHouIndex() == 0) return(~fBreakRead);
  fBreakRead = 1;


  tiAlt = tiDig;
  dwHouIndex = DateToHouIndex();

  dwHouIndex -= (uint)48*ibMinor;
  HouIndexToDate(dwHouIndex);


  // индекс на начало требуемых суток
  for (i=0; i<ibMinor; i++)
    iwDigHou = (wHOURS+iwDigHou-48) % wHOURS;

  sprintf(szLo,"       %02u.%02u.%02u",tiAlt.bDay,tiAlt.bMonth,tiAlt.bYear);

  ShowProgressDigHou();

  for (i=0; i<48; i++)                          // читаем информацию по получасам
  {  
    ResetWatchdog();

    for (ibCan=0; ibCan<16; ibCan++)
      if (ibCan < bCHANNELS) mpwChannels[ibCan] = mpwEsc_L[(uint)i*16 + ibCan];


    tiAlt = tiCurr;
    dwBuffC = DateToHouIndex();

    if (dwHouIndex > dwBuffC) break;
    if (dwBuffC - dwHouIndex > wHOURS) break;

    HouIndexToDate(dwHouIndex);


    if ((tiAlt.bYear  == tiCurr.bYear)  &&      // проверка дл€ текущих суток
        (tiAlt.bMonth == tiCurr.bMonth) &&
        (tiAlt.bDay   == tiCurr.bDay))
    {
      if ((i >= GetHouIndex()) || (i > j)) break;
    }

    if (mpbEsc_Def[16*i + ibDig] == true)
      MakeSpecial();

    if (MakeStopHou(48) == 0) return(0);        // выход: граница опроса пройдена    

    if (++iwDigHou >= wHOURS) iwDigHou = 0;
    dwHouIndex++;
  }

  return(1);
}



// проверка на наличие брака по каналам в запрашиваемые сутки
bit     TestIndexE(void)
{
uchar   i;

  // текущие сутки опрашиваем всегда
  if (ibMinor == 0) return(1);

  // врем€ на начало текущих суток
  tiDig.bHour   = 0;
  tiDig.bMinute = 0;

  do 
  {
    ResetWatchdog();
    if (fKey == true) { fKey = 0; Beep(); }

    // индекс на начало требуемых суток
    iwDigHou = PrevDayIndex(ibMinor);

    // просматриваем все получасы требуемых суток
    for (i=0; i<48; i++)                          
    {  
      LoadImpHouSpec(iwDigHou,1); 

      // проверка на наличие брака дл€ всех каналов
      LoadCurrDigital(ibDig);      
      for (ibCan=0; ibCan<bCANALS; ibCan++)                           
      {
        LoadPrevDigital(ibCan);
        if (CompareCurrPrevLines() == 1)   
          if (*PGetCanInt(mpwImpHouCanSpec, ibCan) == 0xFFFF) return(1);
      }

      if (MakeStopHou(48) == 0) return(0);        // выход: граница опроса пройдена    

      if (++iwDigHou >= wHOURS) iwDigHou = 0;
    }

    sprintf(szLo," номер: %02u      ",ibMinor); DelayOff();
  } while (ibMinor++ < wHOURS/48);

  return(0);
}



// переход на нужные сутки/мес€ц назад с помощь команд Esc l/Esc v
bit     ReadAllIndexesE(uchar  chEsc, uchar  bMaximum)
{
uchar   i,j;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakE(); 

    if (bMaximum == 0) return(1);

    for (j=0; j<bMaximum; j++)
    {
      ResetWatchdog();
      if (fKey == true) { fKey = 0; Beep(); }

      InitPush(0);
      PushChar(0x1B);          
      PushChar(chEsc);            

      Query(2+1, 2, 1);  

      if (EscInput() != SER_GOODCHECK) break;
      else
      {
        sprintf(szLo," номер: %02u-%02u   ",bMaximum,j+1); DelayOff();

        if (ReadIndexE(chEsc,0) == 1)           // прекращаем опрос
          return(1);
        else if (ReadIndexE(chEsc,j+1) == 0)    // ошибка
          break;
        else if (j+1 == bMaximum)               // продолжаем опрос
          return(1);
      }
    }
  }

  return(0);
}
*/


void    ShowTimeOneE(uchar  ibCan)
{
  HideCurrTime(1);

  ShowCanalNumber(ibCan);
            
  sprintf(szLo,"ведущий %02u:%02u:%02u",
               tiCurr.bHour,
               tiCurr.bMinute,
               tiCurr.bSecond);
}


void    ShowTimeTwoE(time  ti)
{
	HideCurrTime(1);

  sprintf(szHi,"ведомый %02u:%02u:%02u",
               ti.bHour,
               ti.bMinute,
               ti.bSecond);

  sprintf(szLo,"ведущий %02u:%02u:%02u",
               tiCurr.bHour,
               tiCurr.bMinute,
               tiCurr.bSecond);
}

//#endif

