/*------------------------------------------------------------------------------
UNI.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_uni.h"
#include "../../kernel/crc-16.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../nvram/cache.h"
#include "uni.h"



cache const             chObjectName = {OBJECT_NAME, &szObjectName, sizeof(szObjectName)};
cache const             chCanalsName = {CANALS_NAME, &mpszCanalsName, sizeof(mpszCanalsName)};
cache const             chGroupsName = {GROUPS_NAME, &mpszGroupsName, sizeof(mpszGroupsName)};

cache const             chStrictUni = {STRICT_UNI, &boStrictUni, sizeof(bool)};
cache const             chMaxDelayUni = {MAX_DELAY_UNI, &bMaxDelayUni, sizeof(uchar)};
cache const             chRepeatFlowUni = {REPEAT_FLOW_INI, &boRepeatFlowUni, sizeof(bool)};
cache const             chEnblPasswUni = {ENBL_PASS_INI, &boEnblPassUni, sizeof(bool)};



void    InitUni(void)
{
	LoadCache(&chObjectName);
  LoadCache(&chCanalsName);
  LoadCache(&chGroupsName);

  LoadCache(&chStrictUni);

  LoadCache(&chMaxDelayUni);
  if ((bMaxDelayUni < 10) || (bMaxDelayUni > 250))
  {
    bMaxDelayUni = 60;
    SaveCache(&chMaxDelayUni);
  }

  LoadCache(&chRepeatFlowUni);

  LoadCache(&chEnblPasswUni);

  uchar p;
  for (p=0; p<bPORTS; p++)
    mpbDelayUni[p] = 0;
}



void    ResetUni(void)
{
  memset(&szObjectName,  0, sizeof(szObjectName));

  sprintf(szObjectName, "object %u", wPrivate);

  SaveCache(&chObjectName);


  memset(&mpszCanalsName, 0, sizeof(mpszCanalsName));

  uchar c;
  for (c=0; c<bCANALS; c++)
    sprintf(mpszCanalsName[c], "canal %u", c+1);

  SaveCache(&chCanalsName);


  memset(&mpszGroupsName, 0, sizeof(mpszGroupsName));

  uchar g;
  for (g=0; g<bGROUPS; g++)
    sprintf(mpszGroupsName[g], "group %u", g+1);

  SaveCache(&chGroupsName);


  boStrictUni = true;
  SaveCache(&chStrictUni);

  bMaxDelayUni = 60;
  SaveCache(&chMaxDelayUni);

  boRepeatFlowUni = false;
  SaveCache(&chRepeatFlowUni);

  boEnblPassUni = true;
  SaveCache(&chEnblPasswUni);
}



void    DelayUni_1Hz(void)
{
  if (mpbDelayUni[0] > 0) mpbDelayUni[0]--;
  if (mpbDelayUni[1] > 0) mpbDelayUni[1]--;
  if (mpbDelayUni[2] > 0) mpbDelayUni[2]--;
  if (mpbDelayUni[3] > 0) mpbDelayUni[3]--;
}
