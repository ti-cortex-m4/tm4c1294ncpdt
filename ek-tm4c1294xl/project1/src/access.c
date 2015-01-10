/*------------------------------------------------------------------------------
ACCESS.C


------------------------------------------------------------------------------*/

#include        <string.h>
#include        "main.h"
#include        "keyboard.h"
#include        "mem_settings.h"



void    InitAccess(void)
{
// TODO	InitAccess
}



bool    SuperUser(void)
{
  return( (mpbPassTwo[0] == 2) &&
          (mpbPassTwo[1] == 6) &&
          (mpbPassTwo[2] == 1) &&
          (mpbPassTwo[3] == 1) &&
          (mpbPassTwo[4] == 3) &&
          (mpbPassTwo[5] == 7) &&
          (mpbPassTwo[6] == 9) &&
          (mpbPassTwo[7] == 1) );
}



void    ClearPassOne(void)
{
  memset(mpbPassOne, '\0', 10);
}


void    ClearPassTwo(void)
{
  memset(mpbPassTwo, '\0', 10);
}



bool    TrueKey(uchar  bKey)
{
  if (bKey > 13) return false;
  else
  {
    if ((enGlobal == GLB_WORK) && (bProgram == bSET_PASSWORD))
    {
      if ((bKey == bKEY_ENTER) && (SuperUser() == 0))
        return false;
    }

    if ((enGlobal != GLB_WORK) && (bProgram == bSET_SPEED))
    {
      if ((bKey != bKEY_PROGRAM) && (bKey != bKEY_ENTER))
        return false;
    }

    return true;
  }
}
