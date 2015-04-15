/*------------------------------------------------------------------------------
DEVICES_INIT.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_phones.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../keyboard/key_timedate.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_status.h"
#include        "../digitals/digitals_pause.h"
#include        "../digitals/digitals_messages.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/wait_answer.h"
#include        "../digitals/wait_query.h"
#include        "../digitals/current/current_run.h"
#include        "../digitals/profile/profile_run.h"
#include        "../digitals/checkup/checkup_run.h"
#include        "../digitals/max_repeats.h"
#include        "../special/recalc_def.h"
#include        "../special/defects.h"
#include        "../sensors/device_b.h"
#include        "../serial/ports.h"
#include        "../serial/ports_modems.h"
#include        "../serial/modems.h"
#include        "../serial/speeds_display.h"
#include        "../digitals/answer.h"
#include        "../digitals/limits.h"
#include        "../digitals/profile/refill.h"
#include        "../digitals/schedule/schedule.h"
#include        "../flash/files.h"
#include        "../flash/records.h"
#include        "../time/delay.h"
#include        "extended_1.h"
#include        "extended_4.h"
#include        "extended_4t.h"
#include        "extended_5.h"
#include        "extended_6.h"
#include        "extended_7.h"
#include        "devices_input.h"
#include        "devices_postinput.h"
#include        "devices_pause.h"
#include        "devices.h"
#include        "devices_init.h"



file const              flSeparateCan = {FLS_SEPARATE_CAN, &boSeparateCan, sizeof(boolean)};
file const              flShowMessages = {FLS_SHOW_MESSAGES, &boShowMessages, sizeof(boolean)};
file const              flHideMessages = {FLS_HIDE_MESSAGES, &boHideMessages, sizeof(boolean)};
file const              flControlTime = {FLS_CONTROL_TIME, &boControlTime, sizeof(boolean)};
file const              flManageTime = {FLS_MANAGE_TIME, &boManageTime, sizeof(boolean)};

file const              flKeysLevelB = {FLS_KEYS_LEVEL_B, &bKeysLevelB, sizeof(uchar)};
file const              flShortProfileC = {FLS_SHORT_PROFILE_C, &boShortProfileC, sizeof(boolean)};



void    InitDevices(void)
{
  LoadFile(&flSeparateCan);
  LoadFile(&flShowMessages);
  LoadFile(&flHideMessages);
  LoadFile(&flControlTime);
  LoadFile(&flManageTime);

  LoadFile(&flKeysLevelB);
  if ((bKeysLevelB < 1) || (bKeysLevelB > 2))
  {
    bKeysLevelB = 2;
    SaveFile(&flKeysLevelB);
  }

  LoadFile(&flShortProfileC);

//uchar   i,j;
//
//  if (GetLabelXDATA() == 0)
//  {
//    MakeDigitals();
//
//    for (i=0; i<bCANALS; i++) mpboBase[i] = FALSE;
//
//    for (i=0; i<bCANALS; i++) mpreEngFrac[i] = 0;
//
//    for (i=0; i<bCANALS; i++)
//      for (j=0; j<6; j++) mpreEngFracDigCan[i][j] = 0;
//  }

  SetCurr(DEV_BEGIN);
  SetPause(DEV_BEGIN);

  InitWaitAnswer();
  InitWaitQuery();
  cbWaitOnline = 0;

  fConnect = 0;
  InitConnectKey();

  ibPortPause = 0xFF;

  EnableAnswer();

  InitMaxRepeats();
  InitDef();
  InitDefects();
  InitLimits();
  InitRefill();
  InitSchedule();
  InitExtended1();
  InitExtended4();
  InitExtended4T();
  InitExtended5();
  InitExtended6();
  InitExtended7();
}


void    ResetDevices(void)
{
  boSeparateCan = FALSE;
  SaveFile(&flSeparateCan);

  boShowMessages = FALSE;
  SaveFile(&flShowMessages);

  boHideMessages = FALSE;
  SaveFile(&flHideMessages);

  boControlTime = TRUE;
  SaveFile(&flControlTime);

  boManageTime = TRUE;
  SaveFile(&flManageTime);

  bKeysLevelB = 2;
  SaveFile(&flKeysLevelB);

  boShortProfileC = FALSE;
  SaveFile(&flShortProfileC);

  ResetMaxRepeats();
  ResetDef();
  ResetDefects();
  ResetLimits();
  ResetRefill();
  ResetSchedule();
  ResetExtended1();
  ResetExtended4();
  ResetExtended4T();
  ResetExtended5();
  ResetExtended6();
  ResetExtended7();
}
