/*------------------------------------------------------------------------------
KEYBOARD2.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "keyboard.h"
#include        "include/programs2.h"
#include        "keyboard2/key_gaps_flag.h"
#include        "keyboard2/key_gaps.h"



void    Keyboard2Program(void)
{
  switch (wProgram)
  {
    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_SetGaps();            break;

    default:                  NoProgram2();             break;
  }
}


void    Keyboard2Work(void)
{
  switch (wProgram)
  {
    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_GetGaps();            break;

    default:                  NoProgram2();             break;
  }
}


void    Keyboard2Reprogram(void)
{
  switch (wProgram)
  {
    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_SetGaps();            break;

    default:                  NoProgram2();             break;
  }
}

