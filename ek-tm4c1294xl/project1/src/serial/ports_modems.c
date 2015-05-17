/*------------------------------------------------------------------------------
PORTS_MODEMS.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../keyboard/keyboard.h"
#include "../keyboard/time/key_timedate.h"
#include "../hardware/watchdog.h"
#include "../digitals/wait_answer.h"
#include "../digitals/wait_query.h"
#include "../digitals/digitals_pause.h"
#include "../digitals/digitals_status.h"
#include "ports_modems.h"
#include "modems.h"
#include "ports.h"



serial  ModInput(uchar  bSecond, bool  fShow)
{
  MakeLongPause(DEV_MODEM_MANUAL, bSecond);
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWDT();
    ShowWaitAnswer(fShow);

    if (GetCurr() == DEV_MODEM_MANUAL) break;

    if ((mpSerial[ibPort] == SER_OVERFLOW) ||
        (mpSerial[ibPort] == SER_BADLINK)  ||
        (mpSerial[ibPort] == SER_POSTANSWER_MODEM) ||
        (mpSerial[ibPort] == SER_PAUSE)) break;

  }

  SetCurr(DEV_MODEM_MANUAL);
  HideCurrentTime(0);

  return( mpSerial[ibPort] );
}


bool    ModInputOK(uchar  bSecond)
{
  return( (ModInput(bSecond,0) == SER_POSTANSWER_MODEM) && (GetModemAnswer() == 0) );
}


bool    ModSerialOK(void)
{
  return( (mpSerial[ibPort] == SER_POSTANSWER_MODEM) && (GetModemAnswer() == 0) );
}
