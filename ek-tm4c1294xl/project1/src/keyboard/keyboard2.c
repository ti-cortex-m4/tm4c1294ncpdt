/*------------------------------------------------------------------------------
KEYBOARD2.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../include/programs2.h"
#include        "keyboard.h"
#include        "key_gaps_flag.h"
#include        "key_gaps.h"
#include        "digitals/key_hide_messages.h"
#include        "digitals/key_max_repeats.h"
#include        "unified/key_strict_uni.h"
#include        "unified/key_dsbl_password_uni.h"
#include        "unified/key_max_delay_uni.h"
#include        "unified/key_repeat_flow_uni.h"



void    Keyboard2Program(void)
{
  switch (wProgram)
  {
    case wSET_HIDE_MESSAGES:  key_SetHideMessages();    break;

    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_SetGaps();            break;

    case wSET_MAX_REPEATS:    key_SetMaxRepeats();      break;

    case wSET_STRICT_UNI:         key_SetStrictUni();        break;
    case wSET_DSBL_PASSWORD_UNI:  key_SetDsblPasswordUni();  break;
    case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
    case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

    default:                  NoProgram2();             break;
  }
}


void    Keyboard2Work(void)
{
  switch (wProgram)
  {
    case wSET_HIDE_MESSAGES:  key_SetHideMessages();    break;

    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_GetGaps();            break;

    case wSET_MAX_REPEATS:    key_SetMaxRepeats();      break;

    case wSET_STRICT_UNI:         key_SetStrictUni();        break;
    case wSET_DSBL_PASSWORD_UNI:  key_SetDsblPasswordUni();  break;
    case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
    case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

    default:                  NoProgram2();             break;
  }
}


void    Keyboard2Reprogram(void)
{
  switch (wProgram)
  {
    case wSET_HIDE_MESSAGES:  key_SetHideMessages();    break;

    case wSET_GAPS_FLAG:      key_SetGapsFlag();        break;
    case wSET_GAPS:           key_SetGaps();            break;

    case wSET_MAX_REPEATS:    key_SetMaxRepeats();      break;

    case wSET_STRICT_UNI:         key_SetStrictUni();        break;
    case wSET_DSBL_PASSWORD_UNI:  key_SetDsblPasswordUni();  break;
    case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
    case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

    default:                  NoProgram2();             break;
  }
}

