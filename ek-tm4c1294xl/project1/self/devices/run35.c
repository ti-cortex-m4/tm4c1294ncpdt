/*------------------------------------------------------------------------------
run35.c


------------------------------------------------------------------------------*/

#include "../main.h"
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
#include "../sensors/device_a.h"
#include "../sensors/device_b.h"
#include "../sensors/device_b2.h"
#include "../sensors/device_b12.h"
#include "../sensors/sensor3/device_c.h"
#include "../sensors/sensor3/profile_c.h"
#include "../sensors/device_e.h"
#include "../sensors/device_k.h"
#include "../sensors/sensor21/device_p.h"
#include "../sensors/device_q.h"
#include "../sensors/device_s.h"
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
#include "run35.h"



extern  uchar                   cbCorrects;
extern  uchar                   ibDig;
extern  time                    tiDig;
extern  uchar                   cbRepeat;


device  GetCurr35Internal(void);
void    ErrorLink(void);



void    Run35(device  d)
{
  switch (d)
  {
  case DEV_START_35C:
    Clear(); ShowPercent(25);

    cbRepeat = MaxRepeats();
    QueryConfig35();
    SetCurr(DEV_CONFIG_35C);
    SetCurr35Internal(DEV_CONFIG_35C);
    break;

  case DEV_CONFIG_35C:
    if (mpSerial[ibPort] == SER_GOODCHECK)
    {
      ReadConfig35();
      MakePause(DEV_POSTCONFIG_35C);
    }
    else
    {
      if (cbRepeat == 0) ErrorCurrent();
      else
      {
        ErrorLink();
        cbRepeat--;

        QueryConfig35();
        SetCurr35(DEV_CONFIG_35C);
      }
    }
    break;

  case DEV_POSTCONFIG_35C:
    Clear(); ShowPercent(50);

    cbRepeat = MaxRepeats();
    QueryEngMon35(0);
    SetCurr35(DEV_ENERGY_35C);
    break;

  case DEV_ENERGY_35C:
    if (mpSerial[ibPort] == SER_GOODCHECK)
      ReadCurrent35();
    else
    {
      if (cbRepeat == 0) ErrorCurrent();
      else
      {
        ErrorLink();
        cbRepeat--;

        QueryEngMon35(0);
        SetCurr35(DEV_ENERGY_35C);
      }
    }
    break;


    case DEV_START_35P:
      cbRepeat = MaxRepeats();
      QueryVersion35();
      SetCurr35(DEV_VERSION_35P);
      break;

    case DEV_VERSION_35P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersion35();

        if (boHideMessages == false)
          MakeLongPause(DEV_POSTVERSION_35P, 1);
        else
          MakePause(DEV_POSTVERSION_35P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersion35();
          SetCurr35(DEV_VERSION_35P);
        }
      }
      break;


    case DEV_POSTVERSION_35P:
      cbCorrects = 0;

      if (fCurrCtrl == true)
        MakePause(DEV_POSTOPENCANAL_35P);
      else
        MakePause(DEV_POSTCORRECT_35P);
      break;

    case DEV_POSTOPENCANAL_35P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTime35();
      SetCurr35(DEV_TIME_35P);
      break;

    case DEV_TIME_35P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTime35();
        MakePause(DEV_POSTTIME_35P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime35();
          SetCurr35(DEV_TIME_35P);
        }
      }
      break;


    case DEV_POSTTIME_35P:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_35P); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_35P); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CONTROL_35P:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_35P);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControl35(tiCurr);
        SetCurr35(DEV_POSTOPENCANAL_35P);
      }
      break;


    case DEV_POSTCORRECT_35P:
      Clear(); ShowPercent(25);

      cbRepeat = MaxRepeats();
      QueryConfig35();
      SetCurr35(DEV_CONFIG_35P);
      break;

    case DEV_CONFIG_35P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfig35();
        MakePause(DEV_POSTCONFIG_35P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryConfig35();
          SetCurr35(DEV_CONFIG_35P);
        }
      }
      break;

    case DEV_POSTCONFIG_35P:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryTime35();
      SetCurr35(DEV_VALUE_35P);
      break;

    case DEV_VALUE_35P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueS = ReadTime35();
        dwValueS = DateToHouIndex(tiValueS);
        MakePause(DEV_POSTVALUE_35P);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime35();
          SetCurr35(DEV_VALUE_35P);
        }
      }
      break;

    case DEV_POSTVALUE_35P:
      Clear(); ShowPercent(75);

      InitHeader35();

      cbRepeat = MaxRepeats();
      QueryHeader35();
      SetCurr35(DEV_HEADER_35P);
      break;

    case DEV_HEADER_35P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_35P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader35();
          SetCurr35(DEV_HEADER_35P);
        }
      }
      break;

    case DEV_POSTHEADER_35P:
      if (ReadHeader35() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_35P);
      break;

    case DEV_DATA_35P:
      cbRepeat = MaxRepeats();
      QueryHeader35();
      SetCurr35(DEV_HEADER_35P);
      break;
  }
}

