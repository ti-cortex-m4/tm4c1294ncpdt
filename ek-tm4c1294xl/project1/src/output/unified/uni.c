/*------------------------------------------------------------------------------
UNI.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_settings.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_uni.h"
#include        "../../crc-16.h"
#include        "../../display/display.h"
#include        "../../keyboard/keyboard.h"
#include        "../../serial/ports.h"
#include        "../../flash/files.h"



file const              flObjectName = {FLS_OBJECT_NAME, &szObjectName, sizeof(szObjectName)};
file const              flCanalsName = {FLS_CANALS_NAME, &mpszCanalsName, sizeof(mpszCanalsName)};
file const              flGroupsName = {FLS_GROUPS_NAME, &mpszGroupsName, sizeof(mpszGroupsName)};

file const              flStrictUni = {FLS_STRICT_UNI, &boStrictUni, sizeof(boolean)};
file const              flMaxDelayUni = {FLS_MAX_DELAY_UNI, &bMaxDelayUni, sizeof(uchar)};
file const              flRepeatFlowUni = {FLS_REPEAT_FLOW_INI, &boRepeatFlowUni, sizeof(boolean)};
file const              flDsblPasswordUni = {FLS_DSBL_PASSWORD_INI, &boDsblPasswordUni, sizeof(boolean)};



void    InitUni(void)
{
  LoadFile(&flObjectName);
  LoadFile(&flCanalsName);
  LoadFile(&flGroupsName);

  LoadFile(&flStrictUni);

  LoadFile(&flMaxDelayUni);
  if ((bMaxDelayUni < 10) || (bMaxDelayUni > 250))
  {
    bMaxDelayUni = 60;
    SaveFile(&flMaxDelayUni);
  }

  LoadFile(&flRepeatFlowUni);

  LoadFile(&flDsblPasswordUni);

  uchar p;
  for (p=0; p<bPORTS; p++)
    mpbDelayUni[p] = 0;
}



void    ResetUni(void)
{
  memset(&szObjectName,  0, sizeof(szObjectName));
  sprintf(szObjectName, "object %u", wPrivate);

  SaveFile(&flObjectName);


  memset(&mpszCanalsName, 0, sizeof(mpszCanalsName));
  uchar c;
  for (c=0; c<bCANALS; c++)
    sprintf(mpszCanalsName[c], "canal %u", c+1);

  SaveFile(&flCanalsName);


  memset(&mpszGroupsName, 0, sizeof(mpszGroupsName));
  uchar g;
  for (g=0; g<bGROUPS; g++)
    sprintf(mpszGroupsName[g], "group %u", g+1);

  SaveFile(&flGroupsName);


  boStrictUni = TRUE;
  SaveFile(&flStrictUni);

  bMaxDelayUni = 60;
  SaveFile(&flMaxDelayUni);

  boRepeatFlowUni = FALSE;
  SaveFile(&flRepeatFlowUni);

  boDsblPasswordUni = FALSE;
  SaveFile(&flDsblPasswordUni);
}



void    DelayUni_1Hz(void)
{
  if (mpbDelayUni[0] > 0) mpbDelayUni[0]--;
  if (mpbDelayUni[1] > 0) mpbDelayUni[1]--;
  if (mpbDelayUni[2] > 0) mpbDelayUni[2]--;
  if (mpbDelayUni[3] > 0) mpbDelayUni[3]--;
}
