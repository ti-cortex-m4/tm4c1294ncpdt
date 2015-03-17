/*------------------------------------------------------------------------------
KEYBOARD2.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../include/programs2.h"
#include        "keyboard.h"
#include        "key_gaps_flag.h"
#include        "key_gaps.h"
#include        "digitals/key_max_repeats.h"



void    Keyboard2Program(void)
{
  switch (wProgram)
  {
    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_SetGaps();            break;

    case wSET_MAX_REPEATS:    key_SetMaxRepeats();      break;

    default:                  NoProgram2();             break;
  }
}


void    Keyboard2Work(void)
{
  switch (wProgram)
  {
    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_GetGaps();            break;

    case wSET_MAX_REPEATS:    key_SetMaxRepeats();      break;

    default:                  NoProgram2();             break;
  }
}


void    Keyboard2Reprogram(void)
{
  switch (wProgram)
  {
    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_SetGaps();            break;

    case wSET_MAX_REPEATS:    key_SetMaxRepeats();      break;

    default:                  NoProgram2();             break;
  }
}

