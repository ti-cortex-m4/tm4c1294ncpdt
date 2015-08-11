/*------------------------------------------------------------------------------
SCHEDULE.C


------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "../../memory/mem_schedule.h"
#include    "../../nvram/cache.h"
#include    "enbl_hours.h"
#include    "schedule.h"



cache const             chEnblPrtHou = {ENBL_PRT_HOU, &mpboEnblPrtHou, sizeof(mpboEnblPrtHou)};

cache const             chCtrlHou = {CTRL_HOU, &mpboCtrlHou, sizeof(mpboCtrlHou)};

cache const             chRecalcHou = {RECALC_HOU, &mpboRecalcHou, sizeof(mpboRecalcHou)};
cache const             chRecalcAlways = {RECALC_ALWAYS, &boRecalcAlways, sizeof(bool)};



void    InitSchedule(void)
{
  LoadCache(&chEnblPrtHou);

  LoadCache(&chCtrlHou);

  LoadCache(&chRecalcHou);
  LoadCache(&chRecalcAlways);
}


void    ResetSchedule(void)
{
  uchar p;
  uchar h;
  for (p=0; p<bPORTS; p++)
    for (h=0; h<48; h++)
      SetEnblPrtHou(p, h, true);

  SaveCache(&chEnblPrtHou);


  for (h=0; h<48; h++)
    mpboCtrlHou[h] = false;

   mpboCtrlHou[42] = true;

   SaveCache(&chCtrlHou);


   for (h=0; h<48; h++)
      mpboRecalcHou[h] = false;

   mpboRecalcHou[1] = true;

   SaveCache(&chRecalcHou);


   boRecalcAlways = true;
   SaveCache(&chRecalcAlways);
}
