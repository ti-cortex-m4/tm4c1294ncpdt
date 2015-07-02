/*------------------------------------------------------------------------------
WATCHDOG.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/watchdog.h"
#include "../memory/mem_program.h"
#include "watchdog.h"



void    InitWDT(void)
{
  if (boEnblWDT == true)
    EnableWDT();
}


void    EnableWDT(void)
{
#ifdef ENABLE_WATCHDOG



#endif
}


void    DisableWDT(void)
{
#ifdef ENABLE_WATCHDOG



#endif
}


void    ResetWDT(void)
{
#ifdef ENABLE_WATCHDOG



#endif
}


bool    IsResetWDT(void)
{
  return false;
}

