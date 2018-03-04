/*------------------------------------------------------------------------------
ACCESS,C


------------------------------------------------------------------------------*/

#include  <string.h>
#include "main.h"
#include "keyboard/keyboard.h"
#include "memory/mem_settings.h"
#include "serial/ports.h"
#include "keyboard/key_speeds.h"



bool    SuperUser(void)
{
  return ((mpbPassTwo[0] == 2) &&
          (mpbPassTwo[1] == 6) &&
          (mpbPassTwo[2] == 1) &&
          (mpbPassTwo[3] == 1) &&
          (mpbPassTwo[4] == 3) &&
          (mpbPassTwo[5] == 7) &&
          (mpbPassTwo[6] == 9) &&
          (mpbPassTwo[7] == 1));
}



void    ClearPassOne(void)
{
  memset(mpbPassOne, '\0', 10);
}


void    ClearPassTwo(void)
{
  memset(mpbPassTwo, '\0', 10);
}



bool    ValidKey(uchar  bKey)
{
  if (bKey > 13)
    return false;
  else
  {
#ifndef NO_DISPLAY
    if ((enGlobal == GLB_WORK) && (wProgram == bSET_PASSWORD))
    {
      if ((bKey == bKEY_ENTER) && (SuperUser() == 0))
        return false;
    }
#endif

    if ((enGlobal != GLB_WORK) && (wProgram == bSET_SPEED))
    {
      if ((bKey != bKEY_PROGRAM) && (bKey != bKEY_ENTER))
        return ibPort != ibSetSpeedsPort;
    }

    return true;
  }
}
