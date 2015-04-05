/*------------------------------------------------------------------------------
DEVICES.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_profile.h"
#include        "../memory/mem_energy_spec.h"
#include        "../memory/mem_limits.h"
#include        "../memory/mem_phones.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../keyboard/key_timedate.h"
#include        "../realtime/realtime.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_status.h"
#include        "../digitals/digitals_pause.h"
#include        "../digitals/digitals_messages.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/wait_answer.h"
#include        "../digitals/wait_query.h"
#include        "../digitals/current/current_run.h"
#include        "../digitals/profile/profile_run.h"
#include        "../digitals/checkup/checkup_run.h"
#include        "../digitals/params/params2.h"
#include        "../digitals/max_repeats.h"
#include        "../digitals/correct_limit.h"
#include        "../special/recalc_def.h"
#include        "../special/defects.h"
#include        "../sensors/device_a.h"
#include        "../sensors/device_b.h"
#include        "../sensors/device_b2.h"
#include        "../sensors/device_b12.h"
#include        "../sensors/device_c.h"
#include        "../serial/ports.h"
#include        "../serial/ports_modems.h"
#include        "../serial/modems.h"
#include        "../serial/speeds_display.h"
#include        "../digitals/answer.h"
#include        "../digitals/limits.h"
#include        "../digitals/digitals_display.h"
#include        "../flash/files.h"
#include        "../flash/records.h"
#include        "../time/timedate.h"
#include        "../time/delay.h"
#include        "devices_input.h"
#include        "devices_postinput.h"
#include        "devices_pause.h"
#include        "devices_init.h"
#include        "extended_1.h"
#include        "devices.h"



// счётчик повторов
uchar                   cbRepeat, cbRepeat2;

// счётчик коррекций времени
uchar                   cbCorrects;

// признак прекращения опроса профиля нагрузки
//bit                     fBreakRead;

// индекс текущего цифрового счетчика
uchar                   ibDig;

//
time                    tiDig, tiDigPrev;

// вид опроса счётчиков
extended                exExtended;

// признак нахождени в режимах connect модема
bool                    fConnect;

// счетчик
uchar                   cbWaitOnline;

// признак разрыва соединеия при нажатии кнопки
bool                    fKeyOn;



void    ShowProgressRepeat(void)
{
  Clear();
  sprintf(szLo+3,"повтор: %u",cbRepeat); DelayInf();
}


void    ShowProgressDigHou(void)
{
  uint i = (ulong)100*((wHOURS+iwHardHou-iwDigHou)%wHOURS)/mpcwStopCan[ibDig];
  if (i > 100) i = 100;

  ShowProgress(12,i);
}


bool    MakeStopHou(uint  wAdd)
{
  if (((wHOURS+iwHardHou-iwDigHou) % wHOURS) < (mpcwStopCan[ibDig]+wAdd))
  {
    NewBoundsRel((wHOURS+iwHardHou-iwDigHou) % wHOURS);
    return(1);
  }
  else
  {
    NewLimits(); // переход границы со стороны сумматора
    return(0);
  }
}


void    ErrorLink(void)
{
  ShowLo(szNoLink);
  sprintf(szLo+14,"%2u",cbRepeat); DelayInf();
}



void    RunDevices(void)
{
  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;


  if ((fConnect == 1) && (wProgram != 0))
  {
    if ((cbWaitOnline > 0) && (cbWaitOnline % 10 == 5))
    {
      SaveDisplay();
      ShowHi(szManual); Clear();

      if (cbWaitOnline <= bMAXWAITONLINE)
        sprintf(szLo,"  осталось: %u c ",(uchar)(bMAXWAITONLINE-cbWaitOnline));
      else
        sprintf(szLo,"окончились: %u c ",(uchar)bMAXWAITONLINE);

      DelayMsg();
      LoadDisplay();

      if (cbWaitOnline > bMAXWAITONLINE) KeyBreakConnect();
    }
  }



  switch (GetPause())
  {
#ifndef SKIP_E
    case DEV_OPENCANAL_E2:
#endif

    case DEV_MODEM_CONNECT:
      cbWaitQuery = bMAXWAITQUERY;
      sprintf(szLo+13,"%3u",cbWaitAnswer); HideCurrentTime(1);
      break;

#ifndef SKIP_E
    case DEV_ENERGY_E2:
      cbWaitQuery = bMAXWAITQUERY;
      sprintf(szLo+13,"%3bu",cbWaitAnswer); HideCurrentTime(1);
      if (IndexInBuff() > 0) sprintf(szLo," прием: %-4u ",IndexInBuff());
      break;
#endif
  }


  if ((mpSerial[ibPort] == SER_INPUT_MASTER))
  {
    DevicesInput();
  }

  if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
  {
    DevicesPostInput();
  }

  else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
           (mpSerial[ibPort] == SER_BADLINK)  ||
           (mpSerial[ibPort] == SER_POSTANSWER_MODEM)  ||
           (mpSerial[ibPort] == SER_PAUSE))
  {
    DevicesPause();
  }
  else return;



  switch (GetCurr())
  {
    case DEV_PAUSE:
      if (mpSerial[ibPort] == SER_POSTANSWER_MODEM)
        SetCurr(GetPause());
      break;

