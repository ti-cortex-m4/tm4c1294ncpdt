/*------------------------------------------------------------------------------
link_up_reset.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/restart.h"
#include "../hardware/hardware_restart.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "link_up_reset.h"



static volatile lur_t   enLinkUpReset;
static volatile uchar   cbLinkUpReset;



static bool isEnabled(void)
{
  return fLinkUpResetFlag == true;
}


void InitLinkUpReset(void)
{
  enLinkUpReset = LUR_LINK_UNKNOWN;

  if ((wLinkUpResetTimeout >= 1) && (wLinkUpResetTimeout <= 60))
    cbLinkUpReset = wLinkUpResetTimeout;
  else
    cbLinkUpReset = 5;
}


void LinkUpReset_LinkUp(void)
{
  if (isEnabled() && (enLinkUpReset == LUR_LINK_DOWN))
  {
    CONSOLE("link status: up \n");

    enLinkUpReset = LUR_LINK_UP;
    cbLinkUpReset = 5;
  }
}


void LinkUpReset_LinkDown(void)
{
  if (isEnabled())
  {
    CONSOLE("link status: down \n");
    enLinkUpReset = LUR_LINK_DOWN;
  }
}


void LinkUpReset_1Hz(void)
{
  if (isEnabled() && (enLinkUpReset == LUR_LINK_UP) && (cbLinkUpReset > 0))
  {
    CONSOLE("link status: decrement \n");
    cbLinkUpReset--;
  }
}


void RunLinkUpReset(void)
{
  if (isEnabled() && (cbLinkUpReset == 0))
  {
    WARNING("link status: restart \n");

    cwLinkUpResetCount++;
    SaveEntity(&enLinkUpResetCount);

    DelayMilliSecond(100);

    if (fLinkUpResetMode == false)
      Restart();
    else
      HardwareRestart();
  }
}
