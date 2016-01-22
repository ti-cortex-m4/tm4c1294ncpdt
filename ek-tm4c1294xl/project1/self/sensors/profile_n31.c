/*------------------------------------------------------------------------------
PROFILE_N31.C


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../memory/mem_digitals.h"
//#include "../memory/mem_current.h"
//#include "../memory/mem_factors.h"
////#include "../memory/mem_realtime.h"
////#include "../memory/mem_energy_spec.h"
////#include "../memory/mem_profile.h"
////#include "../memory/mem_limits.h"
//#include "../serial/ports.h"
//#include "../serial/ports_devices.h"
////#include "../serial/monitor.h"
//#include "../display/display.h"
////#include "../keyboard/time/key_timedate.h"
////#include "../time/timedate.h"
//#include "../time/delay.h"
//#include "../devices/devices.h"
////#include "../devices/devices_time.h"
//#include "../digitals/current/current_run.h"
////#include "../digitals/limits.h"
//#include "../digitals/digitals_messages.h"
////#include "../special/special.h"
//#include "automatic_n31.h"
#include "device_n31.h"
#include "profile_n31.h"



#ifndef SKIP_N31

time                    tiProfileN31;


/*
// чтение энергии дл€ счЄтчика Ёнерги€-9
bit     ReadEnergyAllG(void)
{
  ReadPackTimeDigG();

  if ((tiDig.bSecond == 0) &&
      (tiDig.bMinute == 0) &&
      (tiDig.bHour   == 0) &&
      (tiDig.bDay    == 0) &&
      (tiDig.bMonth  == 0) &&
      (tiDig.bYear   == 0)) return(0);

  return(1);
}



// переход на предыдущую запись
bit     DecIndexG(void)
{
  if (wBaseLast == wBaseCurr)
  {
    if (wOffsCurr != 0) wOffsCurr--; else return(0);
  }
  else
  {
    if (wOffsCurr != 0) wOffsCurr--; else wOffsCurr = wBaseLast-1;
  }

  return(1);
}



// посылка запроса на чтение вершины массива дл€ счЄтчика Ёнерги€-9
void    QueryTopG(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  if (ExtVersionCod())
    PushCharCod(0x0B);
  else
    PushCharCod(0x0A);

  PushCharCod(0x00);
  PushCharCod(0x00);

  CodQueryIO(3+13+1, 3+3+1);
}


// чтение вершины массива дл€ счЄтчика Ёнерги€-9
bit     ReadTopG(void)
{
  InitPop(3);

  PopChar();
  PopChar();

  if (ExtVersionCod())
  {
    wBaseCurr = PopIntExtG();                   // индекс текущей записи
    wBaseLast = PopIntExtG();                   // количество записей
  }
  else
  {
    wBaseCurr = PopChar()*0x100 + PopChar();    // индекс текущей записи
    wBaseLast = PopChar()*0x100 + PopChar();    // количество записей
  }

  wOffsCurr = wBaseCurr;

  sprintf(szLo,"  %5u:%-5u   ",wBaseLast,wBaseCurr); DelayInf();

  return( DecIndexG() );
}



// посылка запроса на чтение заголовка часового блока дл€ счЄтчика Ёнерги€-9
void    QueryHeaderG(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  if (ExtVersionCod())
    PushCharCod(0x0E);
  else
    PushCharCod(0x19);

  PushCharCod(wOffsCurr / 0x100);
  PushCharCod(wOffsCurr % 0x100);

  if (ExtVersionCod())
    CodQueryIO(3+102+1, 3+3+1);
  else
    CodQueryIO(3+24+1, 3+3+1);
}


// чтение заголовка часового блока дл€ счЄтчика Ёнерги€-9
bit     ReadHeaderG(void)
{
  NoShowTime(1);

  if (ExtVersionCod())
  {
    MakeCRC13InBuff(3, 100);
    if (wCRC != InBuff(103) + InBuff(104)*0x100)
    {
      sprintf(szLo,"   ошибки: %-4u    ",++iwMajor);
      return(iwMajor < 48);
    }
  }

/ *
  MakeCRC12InBuff(3, 24);
  if (wCRC != 0) { sprintf(szLo," выключено: %-4u   ",++iwMajor); return(iwMajor < 48); }
* /

  ReadPackTimeDigG();
  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",
          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if ((tiDig.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }


  if (SearchDefHouIndex() == 0) return(++iwMajor < 48);
  iwMajor = 0;


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // врем€ записи должно соответсвовать началу получасового блока

  tiAlt = tiCurr;
  dwBuffC = DateToHouIndex();

  dwBuffC -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  HouIndexToDate(dwBuffC);


  ShowProgressDigHou();
  reBuffB = mprePulseHou[ibDig];

  if (ExtVersionCod()) InitPop(3+4+4*6*3);
  for (ibCan=0; ibCan<6; ibCan++)
  {
    if (ExtVersionCod())
      PopRealExtG();
    else
      PopRealG();

    mpreEngFracDigCan[ibDig][ibCan] += reBuffA;

    if (tiDig.bMinute % 30 == 0)
    {
      wBuffD = (uint)(mpreEngFracDigCan[ibDig][ibCan]*reBuffB);
      mpwChannels[ibCan] = wBuffD;

      mpreEngFracDigCan[ibDig][ibCan] -= (real)wBuffD/reBuffB;
    }
  }

  MakePrevHou();
  return(MakeStopHou(0));
}
*/

#endif
