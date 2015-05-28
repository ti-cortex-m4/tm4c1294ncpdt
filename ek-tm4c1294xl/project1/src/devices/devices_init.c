/*------------------------------------------------------------------------------
DEVICES_INIT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_phones.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../keyboard/time/key_timedate.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_status.h"
#include "../digitals/digitals_pause.h"
#include "../digitals/digitals_messages.h"
#include "../digitals/digitals_display.h"
#include "../digitals/wait_answer.h"
#include "../digitals/wait_query.h"
#include "../digitals/current/current_run.h"
#include "../digitals/profile/profile_run.h"
#include "../digitals/checkup/checkup_run.h"
#include "../digitals/max_repeats.h"
#include "../special/recalc_def.h"
#include "../special/defects.h"
#include "../sensors/device_b.h"
#include "../serial/ports.h"
#include "../serial/ports_modems.h"
#include "../serial/modems.h"
#include "../serial/speeds_display.h"
#include "../digitals/answer.h"
#include "../digitals/profile/refill.h"
#include "../digitals/schedule/schedule.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "../time/delay.h"
#include "../digitals/extended/extended_1.h"
#include "../digitals/extended/extended_4.h"
#include "../digitals/extended/extended_4t.h"
#include "../digitals/extended/extended_5.h"
#include "../digitals/extended/extended_6.h"
#include "../digitals/extended/extended_7.h"
#include "devices_input.h"
#include "devices_postinput.h"
#include "devices_pause.h"
#include "devices.h"
#include "devices_init.h"



file const              flSeparateCan = {SEPARATE_CAN, &boSeparateCan, sizeof(bool)};
file const              flShowMessages = {SHOW_MESSAGES, &boShowMessages, sizeof(bool)};
file const              flHideMessages = {HIDE_MESSAGES, &boHideMessages, sizeof(bool)};
file const              flControlTime = {CONTROL_TIME, &boControlTime, sizeof(bool)};
file const              flManageTime = {MANAGE_TIME, &boManageTime, sizeof(bool)};

file const              flKeysLevelB = {KEYS_LEVEL_B, &bKeysLevelB, sizeof(uchar)};
file const              flShortProfileC = {SHORT_PROFILE_C, &boShortProfileC, sizeof(bool)};



void    InitDevices1(void)
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

  InitMaxRepeats();
  InitDef();
  InitDefects();
  InitRefill();
  InitSchedule();
  InitExtended1();
  InitExtended4();
  InitExtended4T();
  InitExtended5();
  InitExtended6();
  InitExtended7();
}


void    InitDevices2(void)
{
//uchar   i,j;
//
//  if (GetLabelXDATA() == 0)
//  {
//    MakeDigitals();
//
//    for (i=0; i<bCANALS; i++) mpboBase[i] = false;
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
}


void    ResetDevices(bool  fFull)
{
  boSeparateCan = false;
  SaveFile(&flSeparateCan);

  boShowMessages = false;
  SaveFile(&flShowMessages);

  boHideMessages = false;
  SaveFile(&flHideMessages);

  boControlTime = true;
  SaveFile(&flControlTime);

  boManageTime = true;
  SaveFile(&flManageTime);

  bKeysLevelB = 2;
  SaveFile(&flKeysLevelB);

  boShortProfileC = false;
  SaveFile(&flShortProfileC);

  ResetMaxRepeats();
  ResetDef();
  ResetDefects();
  ResetRefill();
  ResetSchedule();
  ResetExtended1();
  ResetExtended4(fFull);
  ResetExtended4T(fFull);
  ResetExtended5(fFull);
  ResetExtended6(fFull);
  ResetExtended7();
}
