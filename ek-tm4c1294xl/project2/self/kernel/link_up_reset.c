/*------------------------------------------------------------------------------
link_up_reset.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/restart.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "link_up_reset.h"



static volatile lur_t   enLinkUpReset;
static volatile uchar   cbLinkUpReset;



static bool isEnabled(void)
{
  return true;
}


void InitLinkUpReset(void)
{
  enLinkUpReset = LUR_LINK_UNKNOWN;
  cbLinkUpReset = 5;
}


void LinkUpReset_LinkUp(void)
{
  if (enLinkUpReset == LUR_LINK_DOWN)
  {
    enLinkUpReset = LUR_LINK_UP;
    cbLinkUpReset = 5;
  }
}


void LinkUpReset_LinkDown(void)
{
  enLinkUpReset = LUR_LINK_DOWN;
}


void LinkUpReset_1Hz(void)
{
  if ((enLinkUpReset == LUR_LINK_UP) && (cbLinkUpReset > 0))
  {
    cbLinkUpReset--;
  }
}


void RunLinkUpReset(void)
{
  if (cbLinkUpReset == 0)
  {
    WARNING("link up restart \n");

    cwLinkUpResetCount++;
    SaveEntity(&enLinkUpResetCount);

    DelayMilliSecond(100);
    Restart();
  }
}
