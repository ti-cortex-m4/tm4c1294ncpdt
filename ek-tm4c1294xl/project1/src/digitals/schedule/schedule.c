/*------------------------------------------------------------------------------
SCHEDULE.C


------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "../../memory/mem_schedule.h"
#include    "../../flash/files.h"
#include    "enbl_hours.h"
#include    "schedule.h"



file const              flEnblPrtHou = {FLS_ENBL_PRT_HOU, &mpboEnblPrtHou, sizeof(mpboEnblPrtHou)};

file const              flCtrlHou = {FLS_CTRL_HOU, &mpboCtrlHou, sizeof(mpboCtrlHou)};

file const              flRecalcHou = {FLS_RECALC_HOU, &mpboRecalcHou, sizeof(mpboRecalcHou)};
file const              flRecalcAlways = {FLS_RECALC_ALWAYS, &boRecalcAlways, sizeof(boolean)};



void    InitSchedule(void)
{
  LoadFile(&flEnblPrtHou);

  LoadFile(&flCtrlHou);

  LoadFile(&flRecalcHou);
  LoadFile(&flRecalcAlways);
}


void    ResetSchedule(void)
{
  uchar p;
  uchar h;
  for (p=0; p<bPORTS; p++)
    for (h=0; h<48; h++)
      SetEnblPrtHou(p, h, TRUE);

  SaveFile(&flEnblPrtHou);


  for (h=0; h<48; h++)
    mpboCtrlHou[h] = FALSE;

   mpboCtrlHou[42] = TRUE;

   SaveFile(&flCtrlHou);


   for (h=0; h<48; h++)
      mpboRecalcHou[h] = FALSE;

   mpboRecalcHou[1] = TRUE;

   SaveFile(&flRecalcHou);


   boRecalcAlways = TRUE;
   SaveFile(&flRecalcAlways);
}
