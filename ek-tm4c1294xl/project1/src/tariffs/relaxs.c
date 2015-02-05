/*------------------------------------------------------------------------------
RELAXS.C

 Подпрограммы управления праздниками
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../timedate.h"
#include        "../rtc.h"
#include        "tariffs.h"



//                                           0123456789ABCDEF
static char const       szNoRelaxs[]      = " нет праздников ",
                        szRelaxHoliday[]  = " выходной",
                        szRelaxWeekday[]  = " рабочий ",
                        szRelaxError[]    = " ошибка !";



// читает количество дней в списке праздников
uchar   GetRelaxSize(void)
{
  return( mpreRelaxs.bSize );
}


// записывает количество дней в списке праздников
void    SetRelaxSize(uchar  bSize)
{
  mpreRelaxs.bSize = bSize;
}



// читает день из списка праздников
void    GetRelaxDate(uchar  ibRelax)
{
  tiRelax = mpreRelaxs.mptiDate[ibRelax];
}


// записывает день в списов праздников
void    SetRelaxDate(uchar  ibRelax)
{
  mpreRelaxs.mptiDate[ibRelax] = tiRelax;
}



// установка списка праздников по умолчанию
void    DefaultRelaxs(void)
{
static uchar const  mpRelaxs[8*3] =
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
    tiRelax.bSecond = mpRelaxs[ibZ++];  // тип праздника: будни, суббота, воскресенье

    SetRelaxDate(ibX);
    SetRelaxSize(GetRelaxSize() + 1);
  }

  boSetRelaxs = true; //false;
}



// сброс списка праздников
void    ResetRelaxs(void)
{
  SetRelaxSize(0);
  boSetRelaxs = true; //false;

  boRelaxsFlag = false;
  ibRelaxsTariff = 1;
}



// определяет тип дня недели
uchar   GetModeAlt(void)
{
uchar  i;

  if (bOldTariffsMode == 0)                    // без учёта выходных и праздничных дней
    return(0);                          // будни

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);

    if ((tiRelax.bDay   == tiAlt.bDay) &&
        (tiRelax.bMonth == tiAlt.bMonth)) 
      return(tiRelax.bSecond);          // тип текущего дня определяется по списку праздников
  }

  i = Weekday();                        // тип текущего дня определяется по календарю

  if (i < 5)  return(0);                // будни
  else 
  if (i == 5) return(1);                // суббота
  else        return(2);                // воскресенье
}
// требует предварительной установки переменной tiAlt



// показывает тип текущего режима
void    ShowModeName(uchar  ibMode)
{
  switch (ibMode)
  {
    case 1:  strcpy(szLo+7, szRelaxHoliday);  break;
    case 2:  strcpy(szLo+7, szRelaxWeekday);  break;
    default: strcpy(szLo+7, szRelaxError);    break;
  }
}



// показывает дату и тип текущего праздника, его номер и общее количество праздников
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
