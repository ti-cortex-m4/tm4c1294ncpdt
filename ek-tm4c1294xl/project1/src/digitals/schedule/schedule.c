/*------------------------------------------------------------------------------
SCHEDULE.C


------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "../../memory/mem_schedule.h"
#include    "../../flash/files.h"
#include    "../../nvram/cache.h"
#include    "enbl_hours.h"
#include    "schedule.h"



file const              flEnblPrtHou = {ENBL_PRT_HOU, &mpboEnblPrtHou, sizeof(mpboEnblPrtHou)};

file const              flCtrlHou = {CTRL_HOU, &mpboCtrlHou, sizeof(mpboCtrlHou)};

file const              flRecalcHou = {RECALC_HOU, &mpboRecalcHou, sizeof(mpboRecalcHou)};
cache const             chRecalcAlways = {RECALC_ALWAYS, &boRecalcAlways, sizeof(bool)};



void    InitSchedule(void)
{
  LoadFile(&flEnblPrtHou);

  LoadFile(&flCtrlHou);

  LoadFile(&flRecalcHou);
  LoadCache(&chRecalcAlways);
}


void    ResetSchedule(void)
{
  uchar p;
  uchar h;
  for (p=0; p<bPORTS; p++)
    for (h=0; h<48; h++)
      SetEnblPrtHou(p, h, true);

  SaveFile(&flEnblPrtHou);


  for (h=0; h<48; h++)
    mpboCtrlHou[h] = false;

   mpboCtrlHou[42] = true;

   SaveFile(&flCtrlHou);


   for (h=0; h<48; h++)
      mpboRecalcHou[h] = false;

   mpboRecalcHou[1] = true;

   SaveFile(&flRecalcHou);


   boRecalcAlways = true;
   SaveCache(&chRecalcAlways);
}
