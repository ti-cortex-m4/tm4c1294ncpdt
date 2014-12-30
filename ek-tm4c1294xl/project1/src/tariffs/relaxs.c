/*------------------------------------------------------------------------------
RELAXS.C

 Ïîäïðîãðàììû óïðàâëåíèÿ ïðàçäíèêàìè
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_tariffs.h"
#include        "../mem_program.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../timedate.h"
#include        "../rtc.h"
#include        "tariffs.h"



//                                           0123456789ABCDEF
static char const       szNoRelaxs[]      = " íåò ïðàçäíèêîâ ",
                        szRelaxHoliday[]  = " âûõîäíîé",
                        szRelaxWeekday[]  = " ðàáî÷èé ",
                        szRelaxError[]    = " îøèáêà !";



// ÷èòàåò êîëè÷åñòâî äíåé â ñïèñêå ïðàçäíèêîâ
uchar   GetRelaxSize(void)
{
  return( mpreRelaxs.bSize );
}


// çàïèñûâàåò êîëè÷åñòâî äíåé â ñïèñêå ïðàçäíèêîâ
void    SetRelaxSize(uchar  bSize)
{
  mpreRelaxs.bSize = bSize;
}



// ÷èòàåò äåíü èç ñïèñêà ïðàçäíèêîâ
void    GetRelaxDate(uchar  ibRelax)
{
  tiRelax = mpreRelaxs.mptiDate[ibRelax];
}


// çàïèñûâàåò äåíü â ñïèñîâ ïðàçäíèêîâ
void    SetRelaxDate(uchar  ibRelax)
{
  mpreRelaxs.mptiDate[ibRelax] = tiRelax;
}



// óñòàíîâêà ñïèñêà ïðàçäíèêîâ ïî óìîë÷àíèþ
void    DefaultRelaxs(void)
{
static char const  mpRelaxs[8*3] =
{ 1,  1,  2,
  2,  1,  2,
  7,  1,  2,
  8,  3,  2,
  1,  5,  2,
  9,  5,  2,
  7, 11,  2,
 25, 12,  2 };

  SetRelaxSize(0);

  ibZ = 0;
  for (ibX=0; ibX<sizeof(mpRelaxs)/3; ibX++)
  {
    tiRelax.bDay    = mpRelaxs[ibZ++];
    tiRelax.bMonth  = mpRelaxs[ibZ++];
    tiRelax.bSecond = mpRelaxs[ibZ++];  // òèï ïðàçäíèêà: áóäíè, ñóááîòà, âîñêðåñåíüå

    SetRelaxDate(ibX);
    SetRelaxSize(GetRelaxSize() + 1);
  }

  boSetRelaxs = boTrue; //boFalse;
}



// ñáðîñ ñïèñêà ïðàçäíèêîâ
void    ResetRelaxs(void)
{
  SetRelaxSize(0);
  boSetRelaxs = boTrue; //boFalse;

  boRelaxsFlag = boFalse;
  ibRelaxsTariff = 1;
}



// îïðåäåëÿåò òèï äíÿ íåäåëè
uchar   GetModeAlt(void)
{
uchar  i;

  if (bOldMode == 0)                    // áåç ó÷¸òà âûõîäíûõ è ïðàçäíè÷íûõ äíåé
    return(0);                          // áóäíè

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);

    if ((tiRelax.bDay   == tiAlt.bDay) &&
        (tiRelax.bMonth == tiAlt.bMonth)) 
      return(tiRelax.bSecond);          // òèï òåêóùåãî äíÿ îïðåäåëÿåòñÿ ïî ñïèñêó ïðàçäíèêîâ
  }

  i = Weekday();                        // òèï òåêóùåãî äíÿ îïðåäåëÿåòñÿ ïî êàëåíäàðþ

  if (i < 5)  return(0);                // áóäíè
  else 
  if (i == 5) return(1);                // ñóááîòà
  else        return(2);                // âîñêðåñåíüå
}
// òðåáóåò ïðåäâàðèòåëüíîé óñòàíîâêè ïåðåìåííîé tiAlt



// ïîêàçûâàåò òèï òåêóùåãî ðåæèìà
void    ShowModeName(uchar  ibMode)
{
  switch (ibMode)
  {
    case 1:  strcpy(szLo+7, szRelaxHoliday);  break;
    case 2:  strcpy(szLo+7, szRelaxWeekday);  break;
    default: strcpy(szLo+7, szRelaxError);    break;
  }
}



// ïîêàçûâàåò äàòó è òèï òåêóùåãî ïðàçäíèêà, åãî íîìåð è îáùåå êîëè÷åñòâî ïðàçäíèêîâ
void    ShowRelax(uchar  ibRelax)
{
  if (GetRelaxSize() > 0)
  {
    GetRelaxDate(ibRelax);
   
    sprintf(szLo," %2u.%02u",
                 tiRelax.bDay,
                 tiRelax.bMonth);

    ShowModeName(tiRelax.bSecond);

    sprintf(szHi+11,"%2u/%-2u",
                    ibRelax+1,
                    GetRelaxSize());    
  }
  else ShowLo(szNoRelaxs);    
}
