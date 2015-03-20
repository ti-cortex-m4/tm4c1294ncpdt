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


/*
void    InitUni(void)
{
uchar   i;

  for (i=0; i<bPORTS; i++)
    mpbDelayUni[i] = 0;  

  if ((bMaxDelayUni < 10) || (bMaxDelayUni > 250)) bMaxDelayUni = 60;
}



void    ResetUni(void)
{
uchar   i;

  memset(&szObjectName,  0, sizeof(szObjectName));
  memset(&mpszCanalsName, 0, sizeof(mpszCanalsName));
  memset(&mpszGroupsName, 0, sizeof(mpszGroupsName));

  sprintf(&szObjectName, "object %u", wPrivate);

  for (i=0; i<bCANALS; i++)
    sprintf(mpszCanalsName[i], "canal %bu", i+1);

  for (i=0; i<bGROUPS; i++)
    sprintf(mpszGroupsName[i], "group %bu", i+1);

  boStrictUni = boTrue;

  bMaxDelayUni = 60;

  boRepeatFlowUni = boFalse;
}



void    DelayUni(void)
{
  if (mpbDelayUni[0] > 0) mpbDelayUni[0]--;
  if (mpbDelayUni[1] > 0) mpbDelayUni[1]--;
  if (mpbDelayUni[2] > 0) mpbDelayUni[2]--;

#ifdef  UPGRADE
  if (mpbDelayUni[3] > 0) mpbDelayUni[3]--;
#endif
}
*/
