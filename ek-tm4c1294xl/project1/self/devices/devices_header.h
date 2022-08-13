/*------------------------------------------------------------------------------
DEVICES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../main_devices.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_params.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_current.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_limits.h"
#include "../memory/mem_phones.h"
#include "../memory/mem_flow.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../keyboard/time/key_timedate.h"
#include "../realtime/realtime.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_status.h"
#include "../digitals/digitals_pause.h"
#include "../digitals/digitals_messages.h"
#include "../digitals/digitals_display.h"
#include "../digitals/wait_answer.h"
#include "../digitals/wait_query.h"
#include "../digitals/current/current_run.h"
#include "../digitals/profile/profile_run.h"
#include "../digitals/profile/profile_link.h"
#include "../digitals/checkup/checkup_run.h"
#include "../digitals/params/params2.h"
#include "../digitals/max_repeats.h"
#include "../digitals/correct_limit.h"
#include "../digitals/max_shutdown.h"
#include "../digitals/review/review.h"
#include "../digitals/review/review_core.h"
#include "../special/recalc_def.h"
#include "../special/defects.h"
#include "../sensors/sensor1/device_a.h"
#include "../sensors/sensor2/device_b.h"
#include "../sensors/sensor2/device_b2.h"
#include "../sensors/sensor2/device_b12.h"
#include "../sensors/sensor3/device_c.h"
#include "../sensors/sensor3/profile_c.h"
#include "../sensors/device_e.h"
#include "../sensors/device_k.h"
#include "../sensors/sensor21/device_p.h"
#include "../sensors/device_q.h"
#include "../sensors/sensor24/device_s.h"
#include "../sensors/sensor26/device_u.h"
#include "../sensors/sensor26/device_u_plc.h"
#include "../sensors/device_v.h"
#include "../sensors/device_w.h"
#include "../sensors/unpack_w.h"
#include "../sensors/sensor31/device31.h"
#include "../sensors/sensor31/profile31.h"
#include "../sensors/sensor31/procedure31.h"
#include "../sensors/sensor32/device32.h"
#include "../sensors/sensor32/profile32.h"
#include "../sensors/sensor33/device33.h"
#include "../sensors/sensor33/profile33.h"
#include "../sensors/sensor34/device34.h"
#include "../sensors/sensor34/time34.h"
#include "../sensors/sensor34/auth34.h"
#include "../sensors/sensor34/profile34.h"
#include "../sensors/sensor35/include35.h"
#include "../sensors/sensor35/device35.h"
#include "../sensors/sensor35/io35.h"
#include "../sensors/sensor35/postinput35.h"
#include "../sensors/sensor35/status35.h"
#include "../sensors/sensor35/profile35.h"
#include "../sensors/sensor36/device36.h"
#include "../sensors/sensor36/io36.h"
#include "../sensors/sensor36/current36.h"
#include "../sensors/sensor36/profile36.h"
#include "../sensors/sensor38/device38.h"
#include "../sensors/sensor38/current38.h"
#include "../sensors/sensor38/profile38.h"
#include "../sensors/sensor38/auth38.h"
#include "../sensors/sensor38/time38.h"
#include "../sensors/sensor39/dlms.h"
#include "../sensors/sensor39/current39_wrapper.h"
#include "../sensors/sensor39/profile39.h"
#include "../sensors/sensor39/correct39_wrapper.h"
#include "../sensors/sensor39/profile39_wrapper.h"
#include "../sensors/sensor39/hdlc_monitor.h"
#include "../sensors/sensor39/error39.h"
#include "../serial/ports.h"
#include "../serial/ports_modems.h"
#include "../serial/modems.h"
#include "../serial/speeds_display.h"
#include "../serial/monitor.h"
#include "../digitals/dsbl_answer.h"
#include "../digitals/limits.h"
#include "../digitals/digitals_display.h"
#include "../digitals/skip_failure.h"
#include "../digitals/extended/extended_0.h"
#include "../digitals/extended/extended_1.h"
#include "../digitals/extended/extended_3.h"
#include "../digitals/extended/extended_4.h"
#include "../digitals/extended/extended_4t.h"
#include "../digitals/extended/extended_5.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/delay.h"
#include "devices_input.h"
#include "devices_postinput.h"
#include "devices_pause.h"
#include "devices_init.h"
#include "devices_include.h"
#include "devices.h"



// счётчик повторов
uchar                   cbRepeat, cbIteration;

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



void    ShowRepeat(void)
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


void    ShowProfileTime(time  ti)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", ti.bHour,ti.bDay,ti.bMonth,ti.bYear);
}



bool    MakeStopHou(uint  wAdd)
{
  if (((wHOURS+iwHardHou-iwDigHou) % wHOURS) < (mpcwStopCan[ibDig]+wAdd))
  {
    NewBoundsRel((wHOURS+iwHardHou-iwDigHou) % wHOURS);
    return true;
  }
  else
  {
    NewLimits(); // переход границы со стороны сумматора
    return false;
  }
}


bool    MakeStopHou2(uint  wAdd, uint  wRel)
{
  if (((wHOURS+iwHardHou-iwDigHou) % wHOURS) < (mpcwStopCan[ibDig]+wAdd))
  {
    NewBoundsRel(wRel);
    return true;
  }
  else
  {
    NewLimits(); // переход границы со стороны сумматора
    return false;
  }
}



void    ErrorLink(void)
{
  IncProfileLinkWrn(diCurr.ibPort, GetCurrHouIndex());

  ShowLo(szNoLink);
  sprintf(szLo+14,"%2u",cbRepeat); DelayInf();
}



void    RunDevices(void)
{
  if (fFlow == 1) return;

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
      sprintf(szLo+13,"%3u",cbWaitAnswer); HideCurrTime(1);
      break;

#ifndef SKIP_E
    case DEV_ENERGY_E2:
      cbWaitQuery = bMAXWAITQUERY;
      sprintf(szLo+13,"%3bu",cbWaitAnswer); HideCurrTime(1);
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

