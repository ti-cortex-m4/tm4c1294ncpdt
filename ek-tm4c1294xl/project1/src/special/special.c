/*------------------------------------------------------------------------------
SPECIAL.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_profile.h"
#include        "../display/display.h"
#include        "../impulses/energy_spec.h"
#include        "../time/delay.h"
#include        "../energy.h"
#include        "calc.h"
#include        "special.h"



//                                          0123456789ABCDEF
static char const       szSpecialBegin[] = " подготовка...  ",
                        szSpecialEnd[]   = " завершение...  ";



bool    IsDefect(uchar  ibCan)
{
  LoadImpHouSpec(iwDigHou,1);
  return(GetCanInt(mpwImpHouCanSpec, ibCan) == 0xFFFF);
}



bool    IsOpenSpecial(void)
{
  return(fLoadDay || fLoadMon);
}


void    OpenSpecial(void)
{
  ShowLo(szSpecialBegin);
  DelayInf(); Clear();

  OpenCalc();
}


void    MakeSpecial(void)
{
  if (IsDefect(ibDig) || IsDouble(ibDig))
  {
    cwHouRead++;
    sprintf(szLo," %02u:%02u",tiAlt.bHour,tiAlt.bMinute);

    CalcTimeDate(1,1);


    MakeAllPrevTariffs();

    CalcDigCanals();

    fLoadMem = 0;
    CalcAllGroups(1);
  }
}


void    CloseSpecial(void)
{
  ShowLo(szSpecialEnd);
  DelayInf(); Clear();

  CloseCalc(1,1);
}
