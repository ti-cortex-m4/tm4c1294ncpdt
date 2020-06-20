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
#include "../sensors/sensor39/device39.h"
#include "../sensors/sensor39/query_engabs_39.h"
#include "../sensors/sensor39/current39.h"
#include "../sensors/sensor39/profile39_caller.h"
#include "../sensors/sensor39/hdlc_monitor.h"
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


    case DEV_MODEM_START:
      if ((exExtended == EXT_CURRENT_3MIN) && (diCurr.ibPhone != 0))
      {
        ShowLo(szPowerNo); DelayInf();
        cbWaitQuery = 3;
        NextCurrent();
      }
      else
      {
        fConnect = 0;
        if (StreamPortCan(diCurr.ibPort,ibDig) == 0)
        {
          fKeyOn = 0;
          MakePause(DEV_MODEM_STOP);

          AddModRecord(EVE_MODEM_ERROR);
        }
        else if (diCurr.ibPhone != 0)
          MakePause(DEV_MODEM_POSTSTART);
        else
          MakePause(DEV_MODEM_POSTCONNECT);
      }
      break;

    case DEV_MODEM_POSTSTART:
      cbRepeat = MaxRepeatsFixed();

      QueryModemBaud(1);
      MakeLongPause(DEV_MODEM_BAUD,1);

      AddDigRecord(EVE_MODEMCONNECT1);
      AddModRecord(EVE_MODEMBAUD);
      break;

    case DEV_MODEM_BAUD:
      if (ModSerialOK() == 1)
      {
        ShowLo(szBaudOK); DelayInf();
        mpcwBaud[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTBAUD);

        AddModRecord(EVE_MODEMBAUD_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTBAUD);
        else
        {
          cbRepeat--;
          ShowRepeat();

          QueryModemBaud(1);
          MakeLongPause(DEV_MODEM_BAUD,1);

          AddModRecord(EVE_MODEMBAUD_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTBAUD:
      cbRepeat = MaxRepeatsFixed();

      QueryModemCommon(1);
      MakeLongPause(DEV_MODEM_COMMON,1);

      AddModRecord(EVE_MODEMCOMMON1);
      break;

    case DEV_MODEM_COMMON:
      if (ModSerialOK() == 1)
      {
        ShowLo(szCommonOK); DelayInf();
        mpcwCommon[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCOMMON);

        AddModRecord(EVE_MODEMCOMMON1_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowRepeat();

          if (cbRepeat == MaxRepeatsFixed()-1)
          {
            QueryModemCommon(1);
            MakeLongPause(DEV_MODEM_COMMON,1);

            AddModRecord(EVE_MODEMCOMMON1_NEXT);
          }
          else
          {
            QueryModemEscape();
            MakeLongPause(DEV_MODEM_ONLINE,1);

            AddModRecord(EVE_MODEMESCAPE1_NEXT);
          }
        }
      }
      break;

    case DEV_MODEM_ONLINE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szEscapeOK); DelayInf();
        mpcwEscape[diCurr.ibPort]++;

        QueryModemHookOff();
        MakeLongPause(DEV_MODEM_POSTONLINE,1);

        AddModRecord(EVE_MODEMHOOKOFF1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowRepeat();

          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_POSTONLINE,1);

          AddModRecord(EVE_MODEMHOOKOFF1_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTONLINE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();
        mpcwHookOff[diCurr.ibPort]++;

        QueryModemCommon(1);
        MakeLongPause(DEV_MODEM_COMMON,1);

        AddModRecord(EVE_MODEMCOMMON2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowRepeat();

          QueryModemCommon(1);
          MakeLongPause(DEV_MODEM_COMMON,1);

          AddModRecord(EVE_MODEMCOMMON2_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCOMMON:
      if (boCustomModem == true)
        MakePause(DEV_MODEM_NORMAL);
      else
        MakePause(DEV_MODEM_POSTCUSTOM);
      break;

    case DEV_MODEM_NORMAL:
      cbRepeat = MaxRepeatsFixed();

      QueryModemCustom();
      MakeLongPause(DEV_MODEM_CUSTOM,1);

      AddModRecord(EVE_MODEMCUSTOM);
      break;

    case DEV_MODEM_CUSTOM:
      if (ModSerialOK() == 1)
      {
        ShowLo(szCustomOK); DelayInf();
        mpcwCustom[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCUSTOM);

        AddModRecord(EVE_MODEMCUSTOM_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowRepeat();

          QueryModemCustom();
          MakeLongPause(DEV_MODEM_CUSTOM,1);

          AddModRecord(EVE_MODEMCUSTOM_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCUSTOM:
      InitWaitAnswer();

      cbRepeat = MaxRepeatsFixed();

      fConnect = 1;
      QueryModemConnect();
      MakeLongPause(DEV_MODEM_CONNECT,bMaxConnect);

      AddModRecord(EVE_MODEMCONNECT);
      break;

    case DEV_MODEM_CONNECT:
      if ((mpSerial[ibPort] == SER_POSTANSWER_MODEM) && (ShowModemConnect() == 1))
      {
        ShowCanalNumber(ibDig);

        cbWaitOnline = 0;

        mpcwConnect[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCONNECT);

        AddDigRecord(EVE_MODEMCONNECT2);
        AddModRecord(EVE_MODEMCONNECT_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowRepeat();

          InitWaitAnswer();

          fConnect = 1;
          QueryModemConnect();
          MakeLongPause(DEV_MODEM_CONNECT, bMaxConnect);

          AddModRecord(EVE_MODEMCONNECT_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCONNECT:

      SkipFailure_BeforeExtended();

      if (exExtended == EXT_PROFILE_30MIN)
      {
        if (MakeExtended0() == 0) { fKeyOn = 0; MakePause(DEV_MODEM_STOP); break; }

        MakeExtended1();      if (SkipFailure_IsFailureMsg()) { fKeyOn = 0; MakePause(DEV_MODEM_STOP); break; }
        MakeExtended3(ibDig); if (SkipFailure_IsFailureMsg()) { fKeyOn = 0; MakePause(DEV_MODEM_STOP); break; }
        MakeExtended4();      if (SkipFailure_IsFailureMsg()) { fKeyOn = 0; MakePause(DEV_MODEM_STOP); break; }
        MakeExtended5();      if (SkipFailure_IsFailureMsg()) { fKeyOn = 0; MakePause(DEV_MODEM_STOP); break; }
        MakeExtended4T();     if (SkipFailure_IsFailureMsg()) { fKeyOn = 0; MakePause(DEV_MODEM_STOP); break; }
      }

      if ((exExtended == EXT_PROFILE_30MIN) && (boMntParams == false))
      {
        MakeExtended2();      if (SkipFailure_IsFailureMsg()) { fKeyOn = 0; MakePause(DEV_MODEM_STOP); break; }
      }

      if ((exExtended == EXT_CURRENT_3MIN) && (boMntParams == true))
      {
        MakeExtended2();      if (SkipFailure_IsFailureMsg()) { fKeyOn = 0; MakePause(DEV_MODEM_STOP); break; }
      }

      SkipFailure_AfterExtended();

      HideCurrTime(1);
      MakePause(GetNext());
      break;



    case DEV_MODEM_STOP:
      if (fKeyOn == 0)
        ShowCanalNumber(ibDig);
      else
        ShowHi(szManual);

      if ((diCurr.ibPhone != 0) && (fConnect == 1))
        MakePause(DEV_MODEM_POSTSTOP);
      else
        MakePause(DEV_MODEM_POSTBREAK);
      break;

    case DEV_MODEM_POSTSTOP:
      cbRepeat = MaxRepeatsFixed();

      QueryModemEscape();
      MakeLongPause(DEV_MODEM_ESCAPE,3);

      AddDigRecord(EVE_MODEMBREAK1);
      AddModRecord(EVE_MODEMESCAPE2);
      break;

    case DEV_MODEM_ESCAPE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szEscapeOK); DelayInf();

        mpcwEscape[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTESCAPE);

        AddModRecord(EVE_MODEMESCAPE2_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTESCAPE);
        else
        {
          cbRepeat--;
          ShowRepeat();

          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_PREVHOOKOFF,1);

          AddModRecord(EVE_MODEMHOOKOFF2_NEXT);
        }
      }
      break;

    case DEV_MODEM_PREVHOOKOFF:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();

        mpcwHookOff[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTHOOKOFF);

        AddModRecord(EVE_MODEMHOOKOFF2_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTESCAPE);
        else
        {
          cbRepeat--;
          ShowRepeat();

          QueryModemEscape();
          MakeLongPause(DEV_MODEM_ESCAPE,3);

          AddModRecord(EVE_MODEMESCAPE3_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTESCAPE:
      cbRepeat = MaxRepeatsFixed();

      QueryModemHookOff();
      MakeLongPause(DEV_MODEM_HOOKOFF,1);

      AddModRecord(EVE_MODEMHOOKOFF3);
      break;

    case DEV_MODEM_HOOKOFF:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();

        mpcwHookOff[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTHOOKOFF);

        AddDigRecord(EVE_MODEMBREAK2);
        AddModRecord(EVE_MODEMHOOKOFF3_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_BREAK);
        else
        {
          cbRepeat--;
          ShowRepeat();

          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_HOOKOFF,1);

          AddModRecord(EVE_MODEMHOOKOFF3_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTHOOKOFF:
      MakePause(DEV_MODEM_POSTBREAK);
      break;

    case DEV_MODEM_BREAK:
      ModemDTROff();
      mpcwDTROff[diCurr.ibPort]++;

      MakePause(DEV_MODEM_POSTBREAK);

      AddModRecord(EVE_MODEMDTROFF);
      break;

    case DEV_MODEM_POSTBREAK:
      fConnect = 0;
      mpSerial[diCurr.ibPort] = SER_BEGIN;
      if (fKeyOn == 1)
      {
        SetCurr(DEV_BEGIN);
        SetPause(DEV_BEGIN);

        Work(); OK();
      }
      else
      {
        if (exExtended == EXT_PROFILE_30MIN)
          NextProfile();
        else
          NextCheckup();
      }
      break;

#ifndef SKIP_A

    case DEV_START_A2:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpenA();
      SetCurr(DEV_OPENCANAL_A2);
      break;

    case DEV_OPENCANAL_A2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
      {
        if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_A2);
        else
          MakePause(DEV_POSTCORRECT_A2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenA();
          SetCurr(DEV_OPENCANAL_A2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_A2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTimeA();
      SetCurr(DEV_TIME_A2);
      break;

    case DEV_TIME_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueA = ReadTimeA();
        MakePause(DEV_POSTTIME_A2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeA();
          SetCurr(DEV_TIME_A2);
        }
      }
      break;


    case DEV_POSTTIME_A2:
      {
        ulong dwSecond1 = GetSecondIndex(tiValueA);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiValueA, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);

          if (dwDelta < GetCorrectLimit())                                        // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_A2); }
          else if (dwDelta < bMAJORCORRECT_A)                                     // простая коррекция
          {
            if (cbCorrects == 0)
            { ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_A2); }
            else
            {
              if (boManageTime == true)
              { ShowLo(szManageYes); DelayInf();  MakePause(DEV_MANAGE_A2); }
              else
              { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
            }
          }
          else if (dwDelta < wLIMITCORRECT_A)                                     // сложная коррекция
          {
            if (boManageTime == true)
            { ShowLo(szManageYes); DelayInf();  MakePause(DEV_MANAGE_A2); }
            else
            { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_A2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_A2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControlA();
        SetCurr(DEV_POSTCONTROL_A2);
      }
      break;

    case DEV_POSTCONTROL_A2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_A2);   // да !
        else
        {
          DelayOff(); // ErrorLink();
          cbRepeat--;

          QueryControlA();
          SetCurr(DEV_POSTCONTROL_A2);
        }
      }
      break;

    case DEV_MANAGE_A2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_A2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryManageA();
        SetCurr(DEV_POSTMANAGE_A2);
      }
      break;

    case DEV_POSTMANAGE_A2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_A2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryManageA();
          SetCurr(DEV_POSTMANAGE_A2);
        }
      }
      break;


    case DEV_POSTCORRECT_A2:
      Clear();

      cbRepeat = MaxRepeats();
      QueryTopA();
      SetCurr(DEV_TOP_A2);
      break;

    case DEV_TOP_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTopA();
        MakePause(DEV_POSTTOP_A2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTopA();
          SetCurr(DEV_TOP_A2);
        }
      }
      break;

    case DEV_POSTTOP_A2:
      cbIteration = 0;
      if (diCurr.bDevice == 1)
      {
        cbRepeat = MaxRepeats();
        QueryHeaderA();
        SetCurr(DEV_HEADER_A2);
      }
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeaderA_Plus(bBLOCKS_A);
        SetCurr(DEV_HEADER_A2PLUS);
      }
      break;

    case DEV_HEADER_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadHeaderA();
        MakePause(DEV_POSTHEADER_A2);
      }
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR1_A2);
/*
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA();
          SetCurr(DEV_HEADER_A2);
        }*/
      }
      break;

    case DEV_ERROR1_A2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bITERATIONS) ErrorProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryIdA();
        SetCurr(DEV_POSTERROR1_A2);
      }
      break;

    case DEV_POSTERROR1_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdA() == 1)
        {
          QueryHeaderA();
          SetCurr(DEV_HEADER_A2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR1_A2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdA();
          SetCurr(DEV_POSTERROR1_A2);
        }
      }
      break;

    case DEV_POSTHEADER_A2:
      cbIteration = 0;
      cbRepeat = MaxRepeats();
      QueryDataA();
      SetCurr(DEV_DATA_A2);
      break;

    case DEV_DATA_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTDATA_A2);
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR2_A2);
/*
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDataA();
          SetCurr(DEV_DATA_A2);
        }*/
      }
      break;

    case DEV_ERROR2_A2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bITERATIONS) ErrorProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryIdA();
        SetCurr(DEV_POSTERROR2_A2);
      }
      break;

    case DEV_POSTERROR2_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdA() == 1)
        {
          QueryDataA();
          SetCurr(DEV_DATA_A2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR2_A2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdA();
          SetCurr(DEV_POSTERROR2_A2);
        }
      }
      break;

    case DEV_POSTDATA_A2:
      cbIteration = 0;
      NewBoundsAbs16(iwMajor);
      if (ReadDataA() == 0)
        DoneProfile();
      else
      {
        (iwMajor == 0) ? (iwMajor = 8192/3 - 1) : (iwMajor--);

        cbRepeat = MaxRepeats();
        QueryHeaderA();
        SetCurr(DEV_HEADER_A2);
      }
      break;

    case DEV_HEADER_A2PLUS:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_DATA_A2PLUS);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
      break;

    case DEV_DATA_A2PLUS:
    {
      uchar i;
      for (i=0; i<bBLOCKS_A; i++)
        if (TestDataA_Plus(i) == 0) break;

      if (i != bBLOCKS_A)
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
      else
      {
        NewBoundsAbs16(iwMajor);
        for (i=0; i<bBLOCKS_A; i++)
        {
          if (ReadDataA_Plus(i) == 0) break;
          (iwMajor == 0) ? (iwMajor = 8192/3 - 1) : (iwMajor--);
        }

        if (i != bBLOCKS_A)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
    }
      break;

#endif

#ifndef SKIP_A

    case DEV_START_A3:
      cbRepeat = MaxRepeats();

      QueryOpenA();
      SetCurr(DEV_OPENCANAL_A3);             
      break;

    case DEV_OPENCANAL_A3:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenA();
          SetCurr(DEV_OPENCANAL_A3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_A3:
      cbRepeat = MaxRepeats();
      QueryEnergyA(0);
      SetCurr(DEV_ENERGY_A3);
      break;

    case DEV_ENERGY_A3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentA();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyA(0);
          SetCurr(DEV_ENERGY_A3);
        }
      } 
      break;

#endif

#ifndef SKIP_B

    case DEV_START_B2:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B2);
      break;

    case DEV_OPENCANAL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
      {
        if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_B2);
        else
          MakePause(DEV_POSTCORRECT_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_B2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTimeB();
      SetCurr(DEV_TIME_B2);
      break;

    case DEV_TIME_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueB = ReadTimeB();
        MakePause(DEV_POSTTIME_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeB();
          SetCurr(DEV_TIME_B2);
        }
      }
      break;


    case DEV_POSTTIME_B2:
      {
        ulong dwSecond1 = GetSecondIndex(tiValueB);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiValueB, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);

          if (dwDelta < GetCorrectLimit())                                        // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
          else if (dwDelta < bMAJORCORRECT_B)                                     // простая коррекция
          {
            if (cbCorrects == 0)
            {
              bDeltaOld = (uchar)dwDelta;
              (boShowMessages == true) ? DelayMsg() : DelayInf();
              ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_B2);
            }
            else
            {
              bDeltaNew = (uchar)dwDelta;
              if ((bDeltaNew < bDeltaOld) && (cbCorrects < 100))
              {
                bDeltaOld = bDeltaNew;
                cbCorrects++;
                MakePause(DEV_POSTOPENCANAL_B2);
              }
              else if (GetCurrHouIndex() == (tiValueB.bHour*2 + tiValueB.bMinute/30))
              { ShowLo(szCorrectNext); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
              else
              { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_B2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControlB();
        SetCurr(DEV_POSTCONTROL_B2);
      }
      break;

    case DEV_POSTCONTROL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_B2);   // да !
        else
        {
          DelayOff(); // ErrorLink();
          cbRepeat--;

          QueryControlB();
          SetCurr(DEV_POSTCONTROL_B2);
        }
      }
      break;
/*
    case DEV_MANAGE_B2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryManageB();
        SetCurr(DEV_POSTMANAGE_B2);
      }
      break;

    case DEV_POSTMANAGE_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_B2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryManageB();
          SetCurr(DEV_POSTMANAGE_B2);
        }
      }
      break;
*/

    case DEV_POSTCORRECT_B2:
      Clear();

      cbRepeat = MaxRepeats();
      QueryVersionB();
      SetCurr(DEV_VERSION_B2);
      break;

    case DEV_VERSION_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionB();
        MakePause(DEV_POSTVERSION_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionB();
          SetCurr(DEV_VERSION_B2);
        }
      }
      break;

    case DEV_POSTVERSION_B2:
      Clear();

      cbRepeat = MaxRepeats();
      QueryTopB();
      SetCurr(DEV_TOP_B2);
      break;

    case DEV_TOP_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (TestVersionB710()) ReadTopBNew(); else ReadTopBOld();
        MakePause(DEV_POSTTOP_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTopB();
          SetCurr(DEV_TOP_B2);
        }
      }
      break;

    case DEV_POSTTOP_B2:
      cbIteration = 0;
      if (diCurr.bDevice == 2)
      {
        if (TestVersionB710())
        {
          cbRepeat = MaxRepeats();
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
      }
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeaderB_Plus(bBLOCKS_B);
        SetCurr(DEV_HEADER_B2PLUS);
      }
      break;

    case DEV_HEADER_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2);
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_B2);
/*
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }*/
      }
      break;

    case DEV_ERROR_B2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bITERATIONS) ErrorProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryIdB();
        SetCurr(DEV_POSTERROR_B2);
      }
      break;

    case DEV_POSTERROR_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdB() == 1)
        {
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_B2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdB();
          SetCurr(DEV_POSTERROR_B2);
        }
      }
      break;

    case DEV_POSTHEADER_B2:
      cbIteration = 0;
      NewBoundsAbs16(wBaseCurr);
      if (ReadHeaderB(0,0) == 0)
        DoneProfile();
      else
      {
        (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);

        cbRepeat = MaxRepeats();
        QueryHeaderB();
        SetCurr(DEV_HEADER_B2);
      }
      break;

    case DEV_HEADER_B2PLUS:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2PLUS);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
      break;

    case DEV_POSTHEADER_B2PLUS:
    {
      uchar i;
      for (i=0; i<bBLOCKS_B; i++)
        if (TestHeaderB(i) == 0) break;

      if (i != bBLOCKS_B)
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
      else
      {
        NewBoundsAbs16(wBaseCurr);
        for (i=0; i<bBLOCKS_B; i++)
        {
          if (ReadHeaderB(i,1) == 0) break;
          (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
        }

        if (i != bBLOCKS_B)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
    }
      break;

    case DEV_HEADER_B2NEXT:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2NEXT);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
      }
      break;

    case DEV_POSTHEADER_B2NEXT:
    {
        NewBoundsAbs32(dwBaseCurr);
        uchar i;
        for (i=0; i<17; i++)
        {
          if (ReadHeaderBNew(i,1) == 0) break;
          (dwBaseCurr == 0) ? (dwBaseCurr = 0x1FFF0) : (dwBaseCurr -= 0x0010);
        }

        if (i != 17)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
    }
      break;

#endif

#ifndef SKIP_B

    case DEV_START_B3:
      cbRepeat = MaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B3);             
      break;

    case DEV_OPENCANAL_B3:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_B3:
      cbRepeat = MaxRepeats();
      QueryEnergyB(0);
      SetCurr(DEV_ENERGY_B3);
      break;

    case DEV_ENERGY_B3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentB();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyB(0);
          SetCurr(DEV_ENERGY_B3);
        }
      } 
      break;

#endif

#ifndef SKIP_B

    case DEV_START_B312:
      cbRepeat = MaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B312);             
      break;

    case DEV_OPENCANAL_B312:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B312);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B312);
        }
      }
      break;

    case DEV_POSTOPENCANAL_B312:
      cbRepeat = MaxRepeats();
      QueryEnergyB(0);
      SetCurr(DEV_ENERGY_B312);
      break;

    case DEV_ENERGY_B312:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentB12();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyB(0);
          SetCurr(DEV_ENERGY_B312);
        }
      } 
      break;

#endif

#ifndef SKIP_C

    case DEV_START_C2:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C2);
      break;

    case DEV_OPENCANAL_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
      {
        if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_C2);
        else
          MakePause(DEV_POSTCORRECT_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenC();
          SetCurr(DEV_OPENCANAL_C2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_C2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTimeC();
      SetCurr(DEV_TIME_C2);
      break;

    case DEV_TIME_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueC = ReadTimeC();
        MakePause(DEV_POSTTIME_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeC();
          SetCurr(DEV_TIME_C2);
        }
      }
      break;


    case DEV_POSTTIME_C2:
      {
        ulong dwSecond1 = GetSecondIndex(tiValueC);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiValueC, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_C2); }
          else if (GetCurrHouIndex() == (tiValueC.bHour*2 + tiValueC.bMinute/30)) // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_C2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CONTROL_C2:
      if (++cbCorrects > 3)
        MakePause(DEV_POSTCORRECT_C2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControlC();
        SetCurr(DEV_POSTCONTROL_C2);
      }
      break;

    case DEV_POSTCONTROL_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultC() == 1))
        MakePause(DEV_POSTOPENCANAL_C2);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTOPENCANAL_C2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlC();
          SetCurr(DEV_POSTCONTROL_C2);
        }
      }
      break;


    case DEV_POSTCORRECT_C2:
      cbRepeat = MaxRepeats();
      QueryVersionC();
      SetCurr(DEV_VERSION_C2);
      break;

    case DEV_VERSION_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionC();

        if (boHideMessages == false)
          MakeLongPause(DEV_POSTVERSION_C2, 1);
        else
          MakePause(DEV_POSTVERSION_C2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionC();
          SetCurr(DEV_VERSION_C2);
        }
      }
      break;

    case DEV_POSTVERSION_C2:
      cbRepeat = MaxRepeats();
      QueryTimeC();
      SetCurr(DEV_VALUE_C2);
      break;

    case DEV_VALUE_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueC = ReadTimeC();
        dwValueC = DateToHouIndex(tiValueC);
        MakePause(DEV_POSTVALUE_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeC();
          SetCurr(DEV_VALUE_C2);
        }
      }
      break;

    case DEV_POSTVALUE_C2:
//      if (mpbHouCheck[ibDig] != 0)
//      {
//        Clear(); sprintf(szLo+2,"проверки: %bu",mpbHouCheck[ibDig]);
//        MakeLongPause(DEV_INIT_61_C2, 1);
//      }
//      else
      cbIteration = 0;
      if (boShortProfileC == false)
      {
        InitHeaderC6();

        StartReview();
        RestartReview();
        MakePause(DEV_DATA_6_C2);
      }
      else
      {
        InitHeaderC1();

        StartReview();
        RestartReview();
        MakePause(DEV_DATA_1_C2);
      }
      break;


    case DEV_DATA_6_C2:
      cbRepeat = MaxRepeats();
      QueryHeaderC6();
      SetCurr(DEV_HEADER_6_C2);
      break;

    case DEV_HEADER_6_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_6_C2);
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_6_C2);
      }
      break;

    case DEV_ERROR_6_C2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bITERATIONS) ErrorProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryIdC();
        SetCurr(DEV_POSTERROR_6_C2);
      }
      break;

    case DEV_POSTERROR_6_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC6();
          SetCurr(DEV_HEADER_6_C2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_6_C2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR_6_C2);
        }
      }
      break;

    case DEV_POSTHEADER_6_C2:
      cbIteration = 0;
      switch (ReadReviewC6()) {
        case REVIEW_REPEAT: {
          MakePause(DEV_DATA_6_C2);
          break;
        }
        case REVIEW_ID_REPEAT: {
          MakePause(DEV_ID_6_C2);
          break;
        }
        case REVIEW_SUCCESS: {
          if (ReadHeaderC6() == 0)
            DoneProfile();
          else {
            RestartReview();
            if (fReviewReadId == true)
              MakePause(DEV_ID_6_C2);
            else
              MakePause(DEV_DATA_6_C2);
          }
          break;
        }
        case REVIEW_ERROR: {
          ErrorProfile();
          break;
        }
        default: ASSERT(false);
      }
      break;

    case DEV_ID_6_C2:
      cbRepeat = MaxRepeats();
      QueryIdC();
      SetCurr(DEV_POSTID_6_C2);
      break;

    case DEV_POSTID_6_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadIdC() == 1))
        MakePause(DEV_DATA_6_C2);
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTID_6_C2);
        }
      }
      break;


    case DEV_DATA_1_C2:
      cbRepeat = MaxRepeats();
      QueryHeaderC1();
      SetCurr(DEV_HEADER_1_C2);
      break;

    case DEV_HEADER_1_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if ((IndexInBuff() == 6) && (InBuff(1) == 0x83) && (InBuff(2) == 0x24) && (InBuff(3) == 0x05)) // нет требуемой записи
        {
          MakePause(DEV_POSTHEADER_0_C2);
        }
        else // есть требуемая запись
        {
          MakePause(DEV_POSTHEADER_1_C2);
        }
      }
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_1_C2);
      }
      break;

    case DEV_ERROR_1_C2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bITERATIONS) ErrorProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryIdC();
        SetCurr(DEV_POSTERROR_1_C2);
      }
      break;

    case DEV_POSTERROR_1_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC1();
          SetCurr(DEV_HEADER_1_C2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_1_C2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR_1_C2);
        }
      }
      break;

    case DEV_POSTHEADER_0_C2:
      cbIteration = 0;
      switch (ReadReviewC1_Shutdown()) {
        case REVIEW_REPEAT: {
          MakePause(DEV_DATA_1_C2);
          break;
        }
        case REVIEW_ID_REPEAT: {
          MakePause(DEV_ID_1_C2);
          break;
        }
        case REVIEW_SUCCESS: {
          if (ReadHeaderC1_Shutdown() == 0)
            DoneProfile();
          else {
            RestartReview();
            if (fReviewReadId == true)
              MakePause(DEV_ID_1_C2);
            else
              MakePause(DEV_DATA_1_C2);
          }
          break;
        }
        case REVIEW_ERROR: {
          ErrorProfile();
          break;
        }
        default: ASSERT(false);
      }
      break;

      case DEV_POSTHEADER_1_C2:
        cbIteration = 0;
        switch (ReadReviewC1()) {
          case REVIEW_REPEAT: {
            MakePause(DEV_DATA_1_C2);
            break;
          }
          case REVIEW_ID_REPEAT: {
            MakePause(DEV_ID_1_C2);
            break;
          }
          case REVIEW_SUCCESS: {
            if (ReadHeaderC1() == 0)
              DoneProfile();
            else {
              RestartReview();
              if (fReviewReadId == true)
                MakePause(DEV_ID_1_C2);
              else
                MakePause(DEV_DATA_1_C2);
            }
            break;
          }
          case REVIEW_ERROR: {
            ErrorProfile();
            break;
          }
          default: ASSERT(false);
        }
        break;

    case DEV_ID_1_C2:
      cbRepeat = MaxRepeats();
      QueryIdC();
      SetCurr(DEV_POSTID_1_C2);
      break;

    case DEV_POSTID_1_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadIdC() == 1))
        MakePause(DEV_DATA_1_C2);
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTID_1_C2);
        }
      }
      break;

#endif

#ifndef SKIP_C

    case DEV_START_C3:
      cbRepeat = MaxRepeats();
      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C3);             
      break;

    case DEV_OPENCANAL_C3:
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
        MakePause(DEV_POSTOPENCANAL_C3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenC();
          SetCurr(DEV_OPENCANAL_C3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_C3:
      cbRepeat = MaxRepeats();
      QueryTimeC();                          
      SetCurr(DEV_TIME_C3);          
      break;

    case DEV_TIME_C3:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTIME_C3);
      else                                    
      {
        if (cbRepeat == 0) 
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeC();
          SetCurr(DEV_TIME_C3);
        }
      } 
      break;

    case DEV_POSTTIME_C3:
      tiOffs = ReadTimeC();

      cbRepeat = MaxRepeats();
      QueryEnergyAbsC();
      SetCurr(DEV_ENERGY_C3);
      break;

    case DEV_ENERGY_C3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentC();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyAbsC();
          SetCurr(DEV_ENERGY_C3);
        }
      } 
      break;

#endif

#ifndef SKIP_K

    case DEV_START_K2:
      if ((boControlK == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT2_K2);
      else
        MakePause(DEV_OPEN_K2);
      break;

    case DEV_PREVCORRECT2_K2:
      if (tiCurr.bSecond < bMINORCORRECT_K) {
        MakePause(DEV_CORRECT2_K2);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT2_K2);
      }
      break;

    case DEV_CORRECT2_K2:
      ShowLo(szCorrectQ1);
      QueryCorrectK();
      SetCurr(DEV_POSTCORRECT2_K2);
      break;

    case DEV_POSTCORRECT2_K2:
      //ShowLo(szCorrectQ2);
      MakePause(DEV_OPEN_K2);
      break;

    case DEV_OPEN_K2:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_K2);
      break;

    case DEV_OPENCANAL_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_K2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_K2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_K2:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionK();
      SetCurr(DEV_OPTION_K2);
      break;

    case DEV_OPTION_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_K2);
        else
          MakePause(DEV_POSTPASSWORD_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_K2);
        }
      }
      break;

    case DEV_POSTOPTION_K2:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_K2);
      break;

    case DEV_PASSWORD_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_K2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_K2);
        }
      }
      break;

    case DEV_POSTPASSWORD_K2:
      if ((boControlK != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_K2);
      else
        MakePause(DEV_POSTCORRECT_K2);
      break;

    case DEV_PREVTIME_K2:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_K2);
      break;

    case DEV_TIME_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_K2);
        }
      }
      break;

    case DEV_POSTTIME_K2:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_K2);
      break;

    case DEV_DATE_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_K2);
        }
      }
      break;


    case DEV_POSTDATE_K2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_K2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_K2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_K2:
      cbRepeat = MaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_K2);
      break;

    case DEV_POSTCONTROL_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_K2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_K2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_K2);
        }
      }
      break;


    case DEV_POSTCORRECT_K2:
      iwMajor = 0;
      ibMinor = 0;

      wBaseCurr = 0;
      tiDigPrev = tiCurr;

      cbRepeat = MaxRepeats();
      QueryHeaderK();
      SetCurr(DEV_HEADER_K2);
      break;

    case DEV_HEADER_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 10)                        // если нет требуемой записи
        {
          if (iwMajor >= 480)                           // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            uchar h;
            for (h=0; h<48; h++)
            {
              wBaseCurr++;

              sprintf(szLo," выключено: %-4u   ",++iwMajor);

              iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
              ShowProgressDigHou();
            }

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_K2);
          }
        }
        else
        {
          ReadHeaderK(ibMinor);

          iwMajor = 0;                                  // если есть требуемая запись
          MakePause(DEV_POSTHEADER_K2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderK();
          SetCurr(DEV_HEADER_K2);
        }
      }
      break;

    case DEV_POSTHEADER_K2:
      if (++ibMinor < ibMinorMax)
      {
        cbRepeat = MaxRepeats();
        QueryHeaderK();
        SetCurr(DEV_HEADER_K2);
      }
      else
      {
        ibMinor = 0;
        if (ReadDataK() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_K2);
      }
      break;

    case DEV_DATA_K2:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeaderK();
        SetCurr(DEV_HEADER_K2);
      }
      break;

#endif

#ifndef SKIP_K

    case DEV_START_K3:
      ShowPercent(50);
      ibMinor = 0;

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_K3);
      break;

    case DEV_OPENCANAL_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_K3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_K3:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionK();
      SetCurr(DEV_OPTION_K3);
      break;

    case DEV_OPTION_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_K3);
        }
      }
      break;

    case DEV_POSTOPTION_K3:
      ShowPercent(52+ibMinor);

      cbRepeat = MaxRepeats();
      QueryEnergySpecK(ibMinor);
      SetCurr(DEV_ENERGY_K3);
      break;

    case DEV_ENERGY_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecK(ibMinor);
          SetCurr(DEV_ENERGY_K3);
        }
      }
      break;

    case DEV_POSTENERGY_K3:
      ReadEnergyK(ibMinor);

      if ((diCurr.bDevice == 14) ||
          (diCurr.bDevice == 17))
        ReadCurrentK(1);
      else
      {
        if (++ibMinor < 4)
          MakePause(DEV_POSTOPTION_K3);
        else
          ReadCurrentK(4);
      }
      break;

#endif

#ifndef SKIP_P

    case DEV_START_P2:
      ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenP();
      SetCurr(DEV_OPENCANAL_P2);
    break;

    case DEV_OPENCANAL_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTOPENCANAL_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenP();
          SetCurr(DEV_OPENCANAL_P2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_P2:
      ShowPercent(60);

      cbRepeat = MaxRepeats();
      QueryModeP();
      SetCurr(DEV_MODE_P2);
    break;

    case DEV_MODE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTMODE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryModeP();
          SetCurr(DEV_MODE_P2);
        }
      }
      break;

    case DEV_POSTMODE_P2:
      ShowPercent(70);

      cbRepeat = MaxRepeats();
      QueryPasswordP();
      SetCurr(DEV_PASSWORD_P2);
    break;

    case DEV_PASSWORD_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPASSWORD_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordP();
          SetCurr(DEV_PASSWORD_P2);
        }
      }
      break;

    case DEV_POSTPASSWORD_P2:
      ShowPercent(80);

      cbRepeat = MaxRepeats();
      QueryTimeP();
      SetCurr(DEV_TIME_P2);
      break;

    case DEV_TIME_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeP();

        if (boControlTime == true)
          MakePause(DEV_POSTTIME_P2);
        else
          MakePause(DEV_POSTCORRECT_P2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeP();
          SetCurr(DEV_TIME_P2);
        }
      }
      break;

    case DEV_POSTTIME_P2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (dwSecond1 == dwSecond2)
        {
          MakePause(DEV_POSTCORRECT_P2);
        }
        else if (dwSecond1 > dwSecond2)
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dw = dwSecond1 - dwSecond2;
          if (dw > 5) dw = 5;
          iwMajor = dw % 0x10000;

          Clear(); sprintf(szLo+1,"коррекция: -%u с", iwMajor); DelayInf();
          iwMajor |= 0x8000;

          cbRepeat = MaxRepeats();
          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dw = dwSecond2 - dwSecond1;
          if (dw > 5) dw = 5;
          iwMajor = dw % 0x10000;

          Clear(); sprintf(szLo+1,"коррекция: +%u с", iwMajor); DelayInf();

          cbRepeat = MaxRepeats();
          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
      }
      break;

    case DEV_CORRECT_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        Clear();
        MakePause(DEV_POSTCORRECT_P2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
      }
      break;

    case DEV_POSTCORRECT_P2:
      ShowPercent(90);

      cbRepeat = MaxRepeats();
      QueryRegisterP();
      SetCurr(DEV_REGISTER_P2);
      break;

    case DEV_REGISTER_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadRegisterP();
        if (ibMinorMax == 0)
          ErrorProfile();
        else
          MakePause(DEV_POSTREGISTER_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRegisterP();
          SetCurr(DEV_REGISTER_P2);
        }
      }
      break;

    case DEV_POSTREGISTER_P2:
      Setup1P();

      cbRepeat = MaxRepeats();
      QuerySetValueP(); // возвращает (ERR5), если прошло более 6 минут после команды Р2
      SetCurr(DEV_SETVALUE_P2);
      break;

    case DEV_SETVALUE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTSETVALUE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QuerySetValueP();
          SetCurr(DEV_SETVALUE_P2);
        }
      }
      break;

    case DEV_POSTSETVALUE_P2:
      cbRepeat = MaxRepeats();
      QueryGetValueP();
      SetCurr(DEV_GETVALUE_P2);
      break;

    case DEV_GETVALUE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadGetValueP();
        MakePause(DEV_POSTGETVALUE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryGetValueP();
          SetCurr(DEV_GETVALUE_P2);
        }
      }
      break;

    case DEV_POSTGETVALUE_P2:
      cbRepeat = MaxRepeats();
      QueryProfileP();
      SetCurr(DEV_PROFILE_P2);
      break;

    case DEV_PROFILE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPROFILE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileP();
          SetCurr(DEV_PROFILE_P2);
        }
      }
      break;

    case DEV_POSTPROFILE_P2:
      ReadProfileP(tiDig);
      if ((++wBaseCurr > wBaseLast) || (bBreakEls == 1))
      {
        Setup2P();
        if (((MakeStopHou(0) == 0) || (iwMajor > 10)) && (iwDigHou != 0xFFFF))
        {
          DoneProfile();
        }
        else
        {
          if (BreakP())
          {
            DoneProfile();
          }
          else
          {
            NewBoundsAbs16(ibMinor++);

            if (cwSecondLockoutP > 60)
            {
              cbRepeat = MaxRepeats();
              QueryRepasswordP();
              SetCurr(DEV_REPASSWORD_P2);
            }
            else
            {
              cbRepeat = MaxRepeats();
              QuerySetValueP();
              SetCurr(DEV_SETVALUE_P2);
            }
          }
        }
      }
      else
      {
        cbRepeat = MaxRepeats();
        QueryProfileP();
        SetCurr(DEV_PROFILE_P2);
      }
      break;

    case DEV_REPASSWORD_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTREPASSWORD_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRepasswordP();
          SetCurr(DEV_REPASSWORD_P2);
        }
      }
      break;

    case DEV_POSTREPASSWORD_P2:
      cbRepeat = MaxRepeats();
      QuerySetValueP();
      SetCurr(DEV_SETVALUE_P2);
      break;

#endif

#ifndef SKIP_P

    case DEV_START_P3:
      ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenP();
      SetCurr(DEV_OPENCANAL_P3);
    break;

    case DEV_OPENCANAL_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTOPENCANAL_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenP();
          SetCurr(DEV_OPENCANAL_P3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_P3:
      ShowPercent(60);

      cbRepeat = MaxRepeats();
      QueryModeP();
      SetCurr(DEV_MODE_P3);
    break;

    case DEV_MODE_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTMODE_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryModeP();
          SetCurr(DEV_MODE_P3);
        }
      }
      break;

    case DEV_POSTMODE_P3:
      ShowPercent(70);

      cbRepeat = MaxRepeats();
      QueryPasswordP();
      SetCurr(DEV_PASSWORD_P3);
    break;

    case DEV_PASSWORD_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPASSWORD_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordP();
          SetCurr(DEV_PASSWORD_P3);
        }
      }
      break;

    case DEV_POSTPASSWORD_P3:
      ShowPercent(80);

      cbRepeat = MaxRepeats();
      QueryRegisterP();
      SetCurr(DEV_REGISTER_P3);
      break;

    case DEV_REGISTER_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadRegisterP();
        MakePause(DEV_POSTREGISTER_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRegisterP();
          SetCurr(DEV_REGISTER_P3);
        }
      }
      break;

    case DEV_POSTREGISTER_P3:
      ShowPercent(90);

      cbRepeat = MaxRepeats();
      QueryEngAbsP(0);
      SetCurr(DEV_ENERGY0_P3);
      break;

    case DEV_ENERGY0_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEngAbsP(0);
        MakePause(DEV_POSTENERGY0_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsP(0);
          SetCurr(DEV_ENERGY0_P3);
        }
      }
      break;

    case DEV_POSTENERGY0_P3:
      ShowPercent(91);

      cbRepeat = MaxRepeats();
      QueryEngAbsP(1);
      SetCurr(DEV_ENERGY1_P3);
      break;

    case DEV_ENERGY1_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEngAbsP(1);

        ReadCurrentP();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsP(1);
          SetCurr(DEV_ENERGY1_P3);
        }
      }
      break;

#endif

#ifndef SKIP_Q

    case DEV_START_Q2:
      if ((boControlQ == false) && (fCurrCtrl == true))
      {
        ShowLo(szCorrectQ1);
        QueryCorrectQ();
        SetCurr(DEV_CORRECT_Q2);
      }
      else MakePause(DEV_OPEN_Q2);
      break;

    case DEV_CORRECT_Q2:
      ShowLo(szCorrectQ2);
      MakePause(DEV_OPEN_Q2);
      break;

    case DEV_OPEN_Q2:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_Q2);
      break;

    case DEV_OPENCANAL_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_Q2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_Q2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_Q2:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q2);
      break;

    case DEV_OPTION_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_Q2);
        else
          MakePause(DEV_POSTPASSWORD_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionQ();
          SetCurr(DEV_OPTION_Q2);
        }
      }
      break;

    case DEV_POSTOPTION_Q2:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_Q2);
      break;

    case DEV_PASSWORD_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_Q2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_Q2);
        }
      }
      break;

    case DEV_POSTPASSWORD_Q2:
      if ((boControlQ != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_Q2);
      else
        MakePause(DEV_POSTCORRECT_Q2);
      break;

    case DEV_PREVTIME_Q2:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_Q2);
      break;

    case DEV_TIME_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_Q2);
        }
      }
      break;

    case DEV_POSTTIME_Q2:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_Q2);
      break;

    case DEV_DATE_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_Q2);
        }
      }
      break;


    case DEV_POSTDATE_Q2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_Q2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_Q2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_Q2:
      cbRepeat = MaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_Q2);
      break;

    case DEV_POSTCONTROL_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_Q2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_Q2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_Q2);
        }
      }
      break;


    case DEV_POSTCORRECT_Q2:
      iwMajor = 0;
      ibLineQ = 0;

      InitHeaderQ();

      cbRepeat = MaxRepeats();
      QueryHeaderQ();
      SetCurr(DEV_HEADER_Q2);
      break;

    case DEV_HEADER_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 10)                        // если нет требуемой записи
        {
          if (iwMajor >= 480)                           // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            uchar h;
            for (h=0; h<48; h++)
            {
              wBaseCurr++;

              sprintf(szLo," выключено: %-4u   ",++iwMajor);

              iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
              ShowProgressDigHou();
            }

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_Q2);
          }
        }
        else
        {
          ReadHeaderQ(ibLineQ);

          iwMajor = 0;                                  // если есть требуемая запись
          MakePause(DEV_POSTHEADER_Q2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderQ();
          SetCurr(DEV_HEADER_Q2);
        }
      }
      break;

    case DEV_POSTHEADER_Q2:
      if (++ibLineQ < MAX_LINE_Q)
      {
        cbRepeat = MaxRepeats();
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      else
      {
        ibLineQ = 0;
        if (ReadDataQ() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_Q2);
      }
      break;

    case DEV_DATA_Q2:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      break;

#endif


#ifndef SKIP_Q

    case DEV_START_Q3:
      ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_Q3);
      break;

    case DEV_OPENCANAL_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_Q3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_Q3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_Q3:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q3);
      break;

    case DEV_OPTION_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_Q3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_Q3);
        }
      }
      break;

    case DEV_POSTOPTION_Q3:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryEnergySpecQ();
      SetCurr(DEV_ENERGY_Q3);
      break;

    case DEV_ENERGY_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyQ();
        ReadCurrentQ();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecQ();
          SetCurr(DEV_ENERGY_Q3);
        }
      }
      break;

#endif

#ifndef SKIP_S

    case DEV_START_S2:
      cbRepeat = MaxRepeats();
      QueryVersionS();
      SetCurr(DEV_VERSION_S2);
      break;

    case DEV_VERSION_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionS();

        if (boHideMessages == false)
          MakeLongPause(DEV_POSTVERSION_S2, 1);
        else
          MakePause(DEV_POSTVERSION_S2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionS();
          SetCurr(DEV_VERSION_S2);
        }
      }
      break;


    case DEV_POSTVERSION_S2:
      cbCorrects = 0;

      if (fCurrCtrl == true)
        MakePause(DEV_POSTOPENCANAL_S2);
      else
        MakePause(DEV_POSTCORRECT_S2);
      break;

    case DEV_POSTOPENCANAL_S2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTimeS();
      SetCurr(DEV_TIME_S2);
      break;

    case DEV_TIME_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeS();
        MakePause(DEV_POSTTIME_S2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeS();
          SetCurr(DEV_TIME_S2);
        }
      }
      break;


    case DEV_POSTTIME_S2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_S2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_S2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CONTROL_S2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_S2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControlS(tiCurr);
        SetCurr(DEV_POSTOPENCANAL_S2);
      }
      break;


    case DEV_POSTCORRECT_S2:
      Clear(); ShowPercent(25);

      cbRepeat = MaxRepeats();
      QueryConfigS();
      SetCurr(DEV_CONFIG_S2);
      break;

    case DEV_CONFIG_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfigS();
        MakePause(DEV_POSTCONFIG_S2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryConfigS();
          SetCurr(DEV_CONFIG_S2);
        }
      }
      break;

    case DEV_POSTCONFIG_S2:
      ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryTimeS();
      SetCurr(DEV_VALUE_S2);
      break;

    case DEV_VALUE_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueS = ReadTimeS();
        dwValueS = DateToHouIndex(tiValueS);
        MakePause(DEV_POSTVALUE_S2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeS();
          SetCurr(DEV_VALUE_S2);
        }
      }
      break;

    case DEV_POSTVALUE_S2:
      ShowPercent(75);
      InitHeaderS();

      cbRepeat = MaxRepeats();
      QueryHeaderS();
      SetCurr(DEV_HEADER_S2);
      break;

    case DEV_HEADER_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_S2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderS();
          SetCurr(DEV_HEADER_S2);
        }
      }
      break;

    case DEV_POSTHEADER_S2:
      if (ReadHeaderS() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_S2);
      break;

    case DEV_DATA_S2:
      cbRepeat = MaxRepeats();
      QueryHeaderS();
      SetCurr(DEV_HEADER_S2);
      break;

#endif

#ifndef SKIP_S

    case DEV_START_S3:
      ShowPercent(25);

      cbRepeat = MaxRepeats();
      QueryConfigS();
      SetCurr(DEV_CONFIG_S3);
      break;

    case DEV_CONFIG_S3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfigS();
        MakePause(DEV_POSTCONFIG_S3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryConfigS();
          SetCurr(DEV_CONFIG_S3);
        }
      }
      break;

    case DEV_POSTCONFIG_S3:
      ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryEngMonS(0);
      SetCurr(DEV_ENERGY_S3);
      break;

    case DEV_ENERGY_S3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentS();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngMonS(0);
          SetCurr(DEV_ENERGY_S3);
        }
      }
      break;

#endif

#ifndef SKIP_U

    case DEV_START_U2:
      if ((boControlQ == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT_U2);
      else
        MakePause(DEV_OPEN_U2);
      break;

    case DEV_PREVCORRECT_U2:
      if (tiCurr.bSecond < bMINORCORRECT_U) {
        MakePause(DEV_CORRECT_U2);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT_U2);
      }
      break;

    case DEV_CORRECT_U2:
      ShowLo(szCorrectQ1);
      QueryCorrectU();
      SetCurr(DEV_OPEN_U2);
      break;

    case DEV_OPEN_U2:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U2);
      break;

    case DEV_OPENCANAL_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_U2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_U2:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionU();
      SetCurr(DEV_OPTION_U2);
      break;

    case DEV_OPTION_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_U2);
        else
          MakePause(DEV_POSTPASSWORD_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionU();
          SetCurr(DEV_OPTION_U2);
        }
      }
      break;

    case DEV_POSTOPTION_U2:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_U2);
      break;

    case DEV_PASSWORD_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_U2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_U2);
        }
      }
      break;

    case DEV_POSTPASSWORD_U2:
      if ((boControlQ != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_U2);
      else
        MakePause(DEV_POSTCORRECT_U2);
      break;

    case DEV_PREVTIME_U2:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_U2);
      break;

    case DEV_TIME_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_U2);
        }
      }
      break;

    case DEV_POSTTIME_U2:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_U2);
      break;

    case DEV_DATE_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_U2);
        }
      }
      break;


    case DEV_POSTDATE_U2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_U2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_U2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_U2:
      cbRepeat = MaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_U2);
      break;

    case DEV_POSTCONTROL_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_U2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_U2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_U2);
        }
      }
      break;


    case DEV_POSTCORRECT_U2:
      if (boPlcUFlag == false)
        MakePause(DEV_PREVHEADER_U2);
      else
      {
        Clear();
        sprintf(szLo+4, "блок: %u", bPlcUSize);
        MakeLongPause(DEV_PREVHEADER_U4, 1);
      }
      break;

    case DEV_PREVHEADER_U2:
      iwMajor = 0;
      InitHeaderU();

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == true)
      {
        ReadHeaderU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = MaxRepeats();
      QueryHeaderU();
      SetCurr(DEV_HEADER_U2);
      break;

    case DEV_HEADER_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 3)                        // если нет требуемой записи
        {
          if (iwMajor >= 31)                           // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            sprintf(szLo," выключено: %-4u   ",++iwMajor);

            iwDigHou = (wHOURS+iwHardHou-wBaseCurr*48)%wHOURS;
            ShowProgressDigHou();

            NewBoundsAbs16(++wBaseCurr);

            if (wBaseCurr >= wHOURS/48)
              DoneProfile();
            else if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_U2);
          }
        }
        else
        {
          ReadHeaderU();

          if (SkipLine(ibDig, ibLineU+1) == true)
          {
            ReadHeaderU_SkipLine(ibLineU+1);
            ibLineU++;
          }

          iwMajor = 0;                                  // если есть требуемая запись
          MakePause(DEV_POSTHEADER_U2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderU();
          SetCurr(DEV_HEADER_U2);
        }
      }
      break;

    case DEV_POSTHEADER_U2:
      if (++ibLineU < bMaxLineU)
      {
        cbRepeat = MaxRepeats();
        QueryHeaderU();
        SetCurr(DEV_HEADER_U2);
      }
      else
      {
        if (ReadDataU() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_U2);
      }
      break;

    case DEV_DATA_U2:
      if (wBaseCurr > wHOURS/48)
        DoneProfile();
      else
      {
        ibLineU = 0;

        if (SkipLine(ibDig, ibLineU) == true)
        {
          ReadHeaderU_SkipLine(ibLineU);
          ibLineU++;
        }

        cbRepeat = MaxRepeats();
        QueryHeaderU();
        SetCurr(DEV_HEADER_U2);
      }
      break;

#endif

#ifndef SKIP_U

    case DEV_START_U3:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U3);
      break;

    case DEV_OPENCANAL_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_U3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_U3:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionU();
      SetCurr(DEV_OPTION_U3);
      break;

    case DEV_OPTION_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_U3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_U3);
        }
      }
      break;

    case DEV_POSTOPTION_U3:
      Clear(); ShowPercent(52);

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == true)
      {
        ReadEngU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = MaxRepeats();
      QueryEngSpecU(ibLineU);
      SetCurr(DEV_ENERGY_U3);
      break;

    case DEV_ENERGY_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEngU(ibLineU);

        if (SkipLine(ibDig, ibLineU+1) == true)
        {
          ReadEngU_SkipLine(ibLineU+1);
          ibLineU++;
        }

        uchar bMaxLine = GetMaxLineU(ibDig);
        if (++ibLineU < bMaxLine)
        {
          Clear(); ShowPercent(52+ibLineU);
          QueryEngSpecU(ibLineU);
          SetCurr(DEV_ENERGY_U3);
        }
        else
          ReadCurrentU(bMaxLine);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngSpecU(ibLineU);
          SetCurr(DEV_ENERGY_U3);
        }
      }
      break;

#endif

#ifndef SKIP_U

    case DEV_PREVHEADER_U4:
      iwMajor = 0;
      InitHeaderU_Plc();

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == true)
      {
        ReadHeaderU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = MaxRepeats();
      QueryHeaderU_Plc();
      SetCurr(DEV_HEADER_U4);
      break;

    case DEV_HEADER_U4:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 3)                        // если нет требуемой записи
        {
          if (iwMajor >= wPlcUShutdown)                // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            iwMajor += bPlcUSize;
            sprintf(szLo," выключено: %-4u   ",iwMajor);

            wBaseCurr += bPlcUSize;
            iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
            ShowProgressDigHou();

            if (wBaseCurr >= wHOURS)
              DoneProfile();
            else if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_U4);
          }
        }
        else
        {
          ReadHeaderU_Plc();

          if (SkipLine(ibDig, ibLineU+1) == true)
          {
            ReadHeaderU_SkipLine(ibLineU+1);
            ibLineU++;
          }

          iwMajor = 0;                                  // если есть требуемая запись
          MakePause(DEV_POSTHEADER_U4);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderU_Plc();
          SetCurr(DEV_HEADER_U4);
        }
      }
      break;

    case DEV_POSTHEADER_U4:
      if (++ibLineU < bMaxLineU)
      {
        cbRepeat = MaxRepeats();
        QueryHeaderU_Plc();
        SetCurr(DEV_HEADER_U4);
      }
      else
      {
        if (ReadDataU_Plc() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_U4);
      }
      break;

    case DEV_DATA_U4:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        ibLineU = 0;

        if (SkipLine(ibDig, ibLineU) == true)
        {
          ReadHeaderU_SkipLine(ibLineU);
          ibLineU++;
        }

        cbRepeat = MaxRepeats();
        QueryHeaderU_Plc();
        SetCurr(DEV_HEADER_U4);
      }
      break;

#endif

#ifndef SKIP_V

    case DEV_START_V2:
      cbRepeat = MaxRepeats();
      QueryVersionV();
      SetCurr(DEV_VERSION_V2);
      break;

    case DEV_VERSION_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadVersionV() == false)
        {
          ShowHi(szBadVersion);
          DelayMsg(); ErrorProfile();
        }
        else
        {
          if (boHideMessages == false)
            MakeLongPause(DEV_POSTVERSION_V2, 1);
          else
            MakePause(DEV_POSTVERSION_V2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionV();
          SetCurr(DEV_VERSION_V2);
        }
      }
      break;


    case DEV_POSTVERSION_V2:
      cbCorrects = 0;

      if (fCurrCtrl == true)
        MakePause(DEV_POSTOPENCANAL_V2);
      else
        MakePause(DEV_POSTCORRECT_V2);
      break;

    case DEV_POSTOPENCANAL_V2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTimeV();
      SetCurr(DEV_TIME_V2);
      break;

    case DEV_TIME_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeV();
        MakePause(DEV_POSTTIME_V2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeV();
          SetCurr(DEV_TIME_V2);
        }
      }
      break;


    case DEV_POSTTIME_V2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_V2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_V2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CONTROL_V2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_V2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControlV(tiCurr);
        SetCurr(DEV_POSTOPENCANAL_V2);
      }
      break;


    case DEV_POSTCORRECT_V2:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryTimeV();
      SetCurr(DEV_VALUE_V2);
      break;

    case DEV_VALUE_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        dwTimeV = DateToHouIndex(ReadTimeV());
        MakePause(DEV_POSTVALUE_V2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeV();
          SetCurr(DEV_VALUE_V2);
        }
      }
      break;

    case DEV_POSTVALUE_V2:
      ShowPercent(75);
      InitHeaderV();

      cbRepeat = MaxRepeats();
      QueryHeaderV();
      SetCurr(DEV_HEADER_V2);
      break;

    case DEV_HEADER_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_V2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderV();
          SetCurr(DEV_HEADER_V2);
        }
      }
      break;

    case DEV_POSTHEADER_V2:
      if (ReadHeaderV() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_V2);
      break;

    case DEV_DATA_V2:
      cbRepeat = MaxRepeats();
      QueryHeaderV();
      SetCurr(DEV_HEADER_V2);
      break;

#endif

#ifndef SKIP_V

    case DEV_START_V3:
      cbRepeat = MaxRepeats();
      QueryEngAbsV();
      SetCurr(DEV_ENERGY_V3);
      break;

    case DEV_ENERGY_V3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentV();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsV();
          SetCurr(DEV_ENERGY_V3);
        }
      }
      break;

#endif

#ifndef SKIP_W

    case DEV_START_W2:
      ShowPercent(50);

      if (fCurrCtrl == true)
        MakePause(DEV_PREVTIME_W2);
      else
        MakePause(DEV_POSTCORRECT_W2); // read profiles
      break;


    case DEV_PREVOPENCANAL_W2:
      cbRepeat = MaxRepeats();
      QueryOpenW();
      SetCurr(DEV_OPENCANAL_W2);
      break;

    case DEV_OPENCANAL_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_W2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenW();
          SetCurr(DEV_OPENCANAL_W2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_W2:
      Clear();
      ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionW();
      SetCurr(DEV_OPTION_W2);
      break;


    case DEV_OPTION_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_W2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionW();
          SetCurr(DEV_OPTION_W2);
        }
      }
      break;

    case DEV_POSTOPTION_W2:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryPasswordW();
      SetCurr(DEV_PASSWORD_W2);
      break;

    case DEV_PASSWORD_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_CONTROL_W2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordW();
          SetCurr(DEV_PASSWORD_W2);
        }
      }
      break;


    case DEV_PREVTIME_W2:
      cbRepeat = MaxRepeats();
      QueryTimeW();
      SetCurr(DEV_TIME_W2);
      break;

    case DEV_TIME_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiProfileW = ReadTimeW();
        MakePause(DEV_POSTTIME_W2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeC();
          SetCurr(DEV_TIME_W2);
        }
      }
      break;

    case DEV_POSTTIME_W2:
      {
        ulong dwSecond1 = GetSecondIndex(tiProfileW);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiProfileW, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          dwCorrectW = dwSecond2 - dwSecond1;

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit()) // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_W2); }
          else if (GetCurrHouIndex() == (tiProfileW.bHour*2 + tiProfileW.bMinute/30)) // простая коррекция
          {
            ShowLo(szCorrectYes); DelayInf();

            if (boControlW)
              MakePause(DEV_PREVOPENCANAL_W2);
            else
              MakePause(DEV_GETCORRECT_W2);
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_GETCORRECT_W2:
      cbRepeat = MaxRepeats();
      QueryGetCorrectW();
      SetCurr(DEV_POSTGETCORRECT_W2);
      break;

    case DEV_POSTGETCORRECT_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadGetCorrectW();
        MakeLongPause(DEV_SETCORRECT_W2,1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryGetCorrectW();
          SetCurr(DEV_POSTGETCORRECT_W2);
        }
      }
      break;

    case DEV_SETCORRECT_W2:
      cbRepeat = MaxRepeats();
      QuerySetCorrectW(dwCorrectW);
      SetCurr(DEV_POSTSETCORRECT_W2);
      break;

    case DEV_POSTSETCORRECT_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakeLongPause(DEV_POSTCORRECT_W2,1);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QuerySetCorrectW(dwCorrectW);
          SetCurr(DEV_POSTSETCORRECT_W2);
        }
      }
      break;


    case DEV_CONTROL_W2:
      cbRepeat = MaxRepeats();
      QueryControlW(tiCurr);
      SetCurr(DEV_POSTCONTROL_W2);
      break;

    case DEV_POSTCONTROL_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakeLongPause(DEV_POSTCORRECT_W2,1);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlC();
          SetCurr(DEV_POSTCONTROL_W2);
        }
      }
      break;


    case DEV_POSTCORRECT_W2: // read profiles
      QueryCloseW();

      InitProfileW();
      MakePause(DEV_PREVPROFILE_W2);
      break;

    case DEV_PREVPROFILE_W2:
      cbRepeat = MaxRepeats();
      QueryProfileW();
      SetCurr(DEV_PROFILE_W2);
      break;

    case DEV_PROFILE_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (DoneProfileW())
          DoneProfile();
        else
          MakePause(DEV_POSTPROFILE_W2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileW();
          SetCurr(DEV_PROFILE_W2);
        }
      }
      break;

    case DEV_POSTPROFILE_W2:
      if (ReadProfileW() == false)
        DoneProfile();
      else
      {
        if (++wProfileW >= wHOURS)
          DoneProfile();
        else
          MakePause(DEV_PREVPROFILE_W2);
      }
      break;

#endif

#ifndef SKIP_W

    case DEV_START_W3:
      ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenW();
      SetCurr(DEV_OPENCANAL_W3);
      break;

    case DEV_OPENCANAL_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_W3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenW();
          SetCurr(DEV_OPENCANAL_W3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_W3:
      ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionW();
      SetCurr(DEV_OPTION_W3);
      break;

    case DEV_OPTION_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ibLineW = 0;
        MakePause(DEV_POSTOPTION_W3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionW();
          SetCurr(DEV_OPTION_W3);
        }
      }
      break;

    case DEV_POSTOPTION_W3:
      ShowPercent(52+ibLineW);

      cbRepeat = MaxRepeats();
      QueryEngAbsW_Current(ibLineW);
      SetCurr(DEV_ENERGY_W3);
      break;

    case DEV_ENERGY_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_W3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsW_Current(ibLineW);
          SetCurr(DEV_ENERGY_W3);
        }
      }
      break;

    case DEV_POSTENERGY_W3:
      ReadEngW(ibLineW);

      if (++ibLineW < MAX_LINE_W)
        MakePause(DEV_POSTOPTION_W3);
      else
        ReadCurrentW();
      break;

#endif
#ifndef SKIP_31

    case DEV_START_31P:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpen31();
      SetCurr(DEV_OPENCANAL_31P);
      break;

    case DEV_OPENCANAL_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpen31() == 0)
          ErrorProfile();
        else if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_31P);
        else
          MakePause(DEV_POSTCORRECT_31P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen31();
          SetCurr(DEV_OPENCANAL_31P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_31P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTime31();
      SetCurr(DEV_TIME_31P);
      break;

    case DEV_TIME_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiProfile31 = ReadTime31();
        MakePause(DEV_POSTTIME_31P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime31();
          SetCurr(DEV_TIME_31P);
        }
      }
      break;


    case DEV_POSTTIME_31P:
      {
        ulong dwSecond1 = GetSecondIndex(tiProfile31);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiProfile31, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_31P); }
          else if (GetCurrHouIndex() == (tiProfile31.bHour*2 + tiProfile31.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_31P);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CONTROL_31P:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_31P);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControl31(tiCurr);
        SetCurr(DEV_POSTCONTROL_31P);
      }
      break;

    case DEV_POSTCONTROL_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_31P);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTCORRECT_31P); // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl31(tiCurr);
          SetCurr(DEV_POSTCONTROL_31P);
        }
      }
      break;


    case DEV_POSTCORRECT_31P:
      Clear();

      cbRepeat = MaxRepeats();
      QueryTop31();
      SetCurr(DEV_TOP_31P);
      break;

    case DEV_TOP_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTOP_31P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTop31();
          SetCurr(DEV_TOP_31P);
        }
      }
      break;

    case DEV_POSTTOP_31P:
      if (ReadTop31() == false) DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader31();
        SetCurr(DEV_HEADER_31P);
      }
      break;

    case DEV_HEADER_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_31P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader31();
          SetCurr(DEV_HEADER_31P);
        }
      }
      break;

    case DEV_POSTHEADER_31P:
      if (ReadHeader31() == false)
        DoneProfile();
      else if (DecIndex31() == false)
        DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader31();
        SetCurr(DEV_HEADER_31P);
      }
      break;

#endif
#ifndef SKIP_31

    case DEV_START_31C:
      cbRepeat = MaxRepeats();
      QueryOpen31();
      SetCurr(DEV_OPENCANAL_31C);
      break;

    case DEV_OPENCANAL_31C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpen31() == false)
          ErrorCurrent();
        else
          MakePause(DEV_POSTOPENCANAL_31C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen31();
          SetCurr(DEV_OPENCANAL_31C);
        }
      }
      break;

    case DEV_POSTOPENCANAL_31C:
      cbRepeat = MaxRepeats();
      QueryEngAbs31();
      SetCurr(DEV_ENERGY_31C);
      break;

    case DEV_ENERGY_31C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrent31();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs31();
          SetCurr(DEV_ENERGY_31C);
        }
      }
      break;

#endif
#ifndef SKIP_32

    case DEV_START_32P:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpen32();
      SetCurr(DEV_OPENCANAL_32P);
      break;

    case DEV_OPENCANAL_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpen32() == 0)
          ErrorProfile();
        else if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_32P);
        else
          MakePause(DEV_POSTCORRECT_32P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen32();
          SetCurr(DEV_OPENCANAL_32P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_32P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTime32();
      SetCurr(DEV_TIME_32P);
      break;

    case DEV_TIME_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiProfile32 = ReadTime32();
        MakePause(DEV_POSTTIME_32P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime32();
          SetCurr(DEV_TIME_32P);
        }
      }
      break;


    case DEV_POSTTIME_32P:
      {
        ulong dwSecond1 = GetSecondIndex(tiProfile32);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiProfile32, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_32P); }
          else if (GetCurrHouIndex() == (tiProfile32.bHour*2 + tiProfile32.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_32P);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CONTROL_32P:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_32P);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControl32(tiCurr);
        SetCurr(DEV_POSTCONTROL_32P);
      }
      break;

    case DEV_POSTCONTROL_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_32P);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTCORRECT_32P); // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl32(tiCurr);
          SetCurr(DEV_POSTCONTROL_32P);
        }
      }
      break;


    case DEV_POSTCORRECT_32P:
      Clear();

      cbRepeat = MaxRepeats();
      QueryTop32();
      SetCurr(DEV_TOP_32P);
      break;

    case DEV_TOP_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTOP_32P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTop32();
          SetCurr(DEV_TOP_32P);
        }
      }
      break;

    case DEV_POSTTOP_32P:
      if (ReadTop32() == false) DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader32();
        SetCurr(DEV_HEADER_32P);
      }
      break;

    case DEV_HEADER_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_32P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader32();
          SetCurr(DEV_HEADER_32P);
        }
      }
      break;

    case DEV_POSTHEADER_32P:
      if (ReadHeader32() == false)
        DoneProfile();
      else if (DecIndex32() == false)
        DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader32();
        SetCurr(DEV_HEADER_32P);
      }
      break;

#endif
#ifndef SKIP_33

    case DEV_START_33P:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpen33();
      SetCurr(DEV_OPENCANAL_33P);
      break;

    case DEV_OPENCANAL_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpen33() == 0)
          ErrorProfile();
        else if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_33P);
        else
          MakePause(DEV_POSTCORRECT_33P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen33();
          SetCurr(DEV_OPENCANAL_33P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_33P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTime33();
      SetCurr(DEV_TIME_33P);
      break;

    case DEV_TIME_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiProfile33 = ReadTime33();
        MakePause(DEV_POSTTIME_33P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime33();
          SetCurr(DEV_TIME_33P);
        }
      }
      break;


    case DEV_POSTTIME_33P:
      {
        ulong dwSecond1 = GetSecondIndex(tiProfile33);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiProfile33, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_33P); }
          else if (GetCurrHouIndex() == (tiProfile33.bHour*2 + tiProfile33.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_33P);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CONTROL_33P:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_33P);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControl33(tiCurr);
        SetCurr(DEV_POSTCONTROL_33P);
      }
      break;

    case DEV_POSTCONTROL_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_33P);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTCORRECT_33P); // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl33(tiCurr);
          SetCurr(DEV_POSTCONTROL_33P);
        }
      }
      break;


    case DEV_POSTCORRECT_33P:
      Clear();

      cbRepeat = MaxRepeats();
      QueryTop33();
      SetCurr(DEV_TOP_33P);
      break;

    case DEV_TOP_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTOP_33P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTop33();
          SetCurr(DEV_TOP_33P);
        }
      }
      break;

    case DEV_POSTTOP_33P:
      if (ReadTop33() == false) DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader33();
        SetCurr(DEV_HEADER_33P);
      }
      break;

    case DEV_HEADER_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_33P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader33();
          SetCurr(DEV_HEADER_33P);
        }
      }
      break;

    case DEV_POSTHEADER_33P:
      if (ReadHeader33() == false)
        DoneProfile();
      else if (DecIndex33() == false)
        DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader33();
        SetCurr(DEV_HEADER_33P);
      }
      break;

#endif
#ifndef SKIP_34

    case DEV_START_34C:
      cbRepeat = MaxRepeats();
      QueryEngAbs34();
      SetCurr(DEV_ENERGY_34C);
      break;

    case DEV_ENERGY_34C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrent34();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs34();
          SetCurr(DEV_ENERGY_34C);
        }
      }
      break;

#endif
#ifndef SKIP_34

    case DEV_START_34P:
      MakePause(DEV_PREVAUTHKEY_34P);
      break;


    case DEV_PREVAUTHKEY_34P:
      cbRepeat = MaxRepeats();
      QueryAuthKey34();
      SetCurr(DEV_AUTHKEY_34P);
      break;

    case DEV_AUTHKEY_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthKey34();
        MakePause(DEV_POSTAUTHKEY_34P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthKey34();
          SetCurr(DEV_AUTHKEY_34P);
        }
      }
      break;


    case DEV_POSTAUTHKEY_34P:
      cbRepeat = MaxRepeats();
      QueryAuthReq34();
      SetCurr(DEV_AUTHREQ_34P);
      break;

    case DEV_AUTHREQ_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadAuthReq34())
          MakePause(DEV_POSTSTART_34P);
        else
          ErrorProfile();
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthReq34();
          SetCurr(DEV_AUTHREQ_34P);
        }
      }
      break;


    case DEV_POSTSTART_34P:
      if (fCurrCtrl == true)
        MakePause(DEV_PREVTIME_34P);
      else
        MakePause(DEV_PREVINIT_34P);
      break;


    case DEV_PREVTIME_34P:
      cbRepeat = MaxRepeats();
      QueryTime34();
      SetCurr(DEV_TIME_34P);
      break;

    case DEV_TIME_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        SetTimeCurr34(ReadTime34());
        MakePause(DEV_POSTTIME_34P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime34();
          SetCurr(DEV_TIME_34P);
        }
      }
      break;

    case DEV_POSTTIME_34P:
      {
        ulong dwSecond1 = GetSecondIndex(GetTimeCurr34());
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(GetTimeCurr34(), tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);
          if (dwDelta < GetCorrectLimit()) {
            ShowLo(szCorrectNo); DelayInf();
            MakePause(DEV_PREVINIT_34P); // без коррекции
          }
          else if (GetCurrHouIndex() == GetTimeCurrIndex34())
          {
            if (dwDelta < CORRECT_LIMIT_34) {
              SetCorrectSecond34(dwSecond2 - dwSecond1);
              ShowLo(szCorrectYes); DelayInf();
              MakePause(DEV_PREVCORRECT_34P); // коррекция времени
            } else {
              ShowLo(szManageYes); DelayInf();
              MakePause(DEV_PREVMANAGE_34P); // установка времени
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

// начало коррекции времени

    case DEV_PREVCORRECT_34P:
      cbRepeat = MaxRepeats();
      QueryCorrect34();
      SetCurr(DEV_CORRECT_34P);
      break;

    case DEV_CORRECT_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadCorrect34();
        if (InBuff(2) == 0x05) {
          ShowLo(szManageYes); DelayInf();
          MakePause(DEV_PREVMANAGE_34P); // нельзя корректировать время, можно установить время
        } else {
          MakePause(DEV_PREVINIT_34P);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryCorrect34();
          SetCurr(DEV_CORRECT_34P);
        }
      }
      break;

// конец коррекции времени

// начало установки времени

    case DEV_PREVMANAGE_34P:
      cbRepeat = MaxRepeats();
      QueryManage34();
      SetCurr(DEV_MANAGE_34P);
      break;

    case DEV_MANAGE_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadManage34();
        MakePause(DEV_PREVINIT_34P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryManage34();
          SetCurr(DEV_MANAGE_34P);
        }
      }
      break;

// конец установки времени

    case DEV_PREVINIT_34P:
      cbRepeat = MaxRepeats();
      QueryProfileClose34();
      SetCurr(DEV_INIT_34P);
      break;

    case DEV_INIT_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_PREVOPEN_34P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileClose34();
          SetCurr(DEV_INIT_34P);
        }
      }
      break;


    case DEV_PREVOPEN_34P:
      InitProfileOpen34();

      cbRepeat = MaxRepeats();
      QueryProfileOpen34();
      SetCurr(DEV_OPEN_34P);
      break;

    case DEV_OPEN_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_PREVREAD_34P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileOpen34();
          SetCurr(DEV_OPEN_34P);
        }
      }
      break;

    case DEV_PREVREAD_34P:
      InitProfileRead34();

      cbRepeat = MaxRepeats();
      QueryProfileRead34();
      SetCurr(DEV_READ_34P);
      break;

    case DEV_READ_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        if (ReadProfileRead34()) {
          cbRepeat = MaxRepeats();
          QueryProfileRead34();
          SetCurr(DEV_READ_34P);
        } else {
          MakePause(DEV_PREVCLOSE_34P);
        }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileRead34();
          SetCurr(DEV_READ_34P);
        }
      }
      break;

    case DEV_PREVCLOSE_34P:
      cbRepeat = MaxRepeats();
      QueryProfileClose34();
      SetCurr(DEV_CLOSE_34P);
      break;

    case DEV_CLOSE_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        if (ReadProfileClose34_Safe()) {
          cbRepeat = MaxRepeats();
          QueryProfileOpen34();
          SetCurr(DEV_OPEN_34P);
        } else {
          DoneProfile();
        }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileClose34();
          SetCurr(DEV_CLOSE_34P);
        }
      }
      break;

#endif

#ifndef SKIP_35

    case DEV_RUN_WAIT_35:
      MonitorString("\t run: wait");

      Query35Internal(250, 0, NNCL2_DATA_GET);
      SetCurr(DEV_RUN_DATA_GET_35);
      break;

    case DEV_RUN_BREAK_35:
      MonitorString("\t run: break");

      if (exExtended == EXT_CURRENT_3MIN)
        ErrorCurrent();
      else
        ErrorProfile();
      break;

    case DEV_RUN_DATA_GET_35:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MonitorString("\t run: good data");

        SetSerial35(SER_GOODCHECK);
        MakePause(GetCurr35Internal());
      }
      else
      {
        MonitorString("\t run: bad data");

        SetSerial35(SER_BADCHECK);
        MakePause(GetCurr35Internal());
      }
      break;



    case DEV_START_35C:
      Clear(); ShowPercent(25);

      cbRepeat = MaxRepeats();
      QueryConfig35();
      SetCurr35(DEV_CONFIG_35C);
      break;

    case DEV_CONFIG_35C:
      if (IsSerial35())
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
      if (IsSerial35())
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

#endif

#ifndef SKIP_35

    case DEV_START_35P:
      cbRepeat = MaxRepeats();
      QueryVersion35();
      SetCurr35(DEV_VERSION_35P);
      break;

    case DEV_VERSION_35P:
      if (IsSerial35())
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
      if (IsSerial35())
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
      if (IsSerial35())
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
      if (IsSerial35())
      {
        tiValue35 = ReadTime35();
        dwValue35 = DateToHouIndex(tiValue35);
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
      if (IsSerial35())
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

#endif

#ifndef SKIP_36

    case DEV_RUN_WAIT_36:
      MonitorString("\t run: wait");

      Query36Internal(false, 1000, 0, 0, NNCL2_DATA_GET);
      SetCurr(DEV_RUN_DATA_GET_36);
      break;

    case DEV_RUN_BREAK_36:
      MonitorString("\t run: break");

      if (exExtended == EXT_CURRENT_3MIN)
        ErrorCurrent();
      else
        ErrorProfile();
      break;

    case DEV_RUN_DATA_GET_36:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MonitorString("\t run: good data");

        SetSerial35(SER_GOODCHECK);
        MakePause(GetCurr35Internal());
      }
      else
      {
        MonitorString("\t run: bad data");

        SetSerial35(SER_BADCHECK);
        MakePause(GetCurr35Internal());
      }
      break;



    case DEV_START_36C:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpen36();
      SetCurr35(DEV_OPENCANAL_36C);
      break;

    case DEV_OPENCANAL_36C:
      if (IsSerial35())
        MakePause(DEV_POSTOPENCANAL_36C);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen36();
          SetCurr35(DEV_OPENCANAL_36C);
        }
      }
      break;

    case DEV_POSTOPENCANAL_36C:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOption36();
      SetCurr35(DEV_OPTION_36C);
      break;

    case DEV_OPTION_36C:
      if (IsSerial35())
        MakePause(DEV_POSTOPTION_36C);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOption36();
          SetCurr35(DEV_OPTION_36C);
        }
      }
      break;

    case DEV_POSTOPTION_36C:
      Clear(); ShowPercent(52);

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == true)
      {
        ReadEng36_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = MaxRepeats();
      QueryEngCurrent36(ibLineU);
      SetCurr35(DEV_ENERGY_36C);
      break;

    case DEV_ENERGY_36C:
      if (IsSerial35())
      {
        ReadEng36(ibLineU);

        if (SkipLine(ibDig, ibLineU+1) == true)
        {
          ReadEng36_SkipLine(ibLineU+1);
          ibLineU++;
        }

        uchar bMaxLine = GetMaxLine36(ibDig);
        if (++ibLineU < bMaxLine)
        {
          Clear(); ShowPercent(52+ibLineU);
          QueryEngCurrent36(ibLineU);
          SetCurr35(DEV_ENERGY_36C);
        }
        else
          ReadCurrent36(bMaxLine);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngCurrent36(ibLineU);
          SetCurr35(DEV_ENERGY_36C);
        }
      }
      break;

#endif

#ifndef SKIP_36

    case DEV_START_36P:
//      if ((boControlQ == false) && (fCurrCtrl == true))
//        MakePause(DEV_PREVCORRECT_36P);
//      else
        MakePause(DEV_OPEN_36P);
      break;

    case DEV_PREVCORRECT_36P:
      if (tiCurr.bSecond < bMINORCORRECT_36) {
        MakePause(DEV_CORRECT_36P);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT_36P);
      }
      break;

    case DEV_CORRECT_36P:
      ShowLo(szCorrectQ1);
      QueryCorrect36();
      SetCurr35(DEV_OPEN_36P);
      break;

    case DEV_OPEN_36P:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpen36();
      SetCurr35(DEV_OPENCANAL_36P);
      break;

    case DEV_OPENCANAL_36P:
      if (IsSerial35())
      {
        ReadOpen36();
        MakeLongPause(DEV_POSTOPENCANAL_36P, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen36();
          SetCurr35(DEV_OPENCANAL_36P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_36P:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOption36();
      SetCurr35(DEV_OPTION_36P);
      break;

    case DEV_OPTION_36P:
      if (IsSerial35())
      {
        if (HasPassword36())
          MakePause(DEV_POSTOPTION_36P);
        else
          MakePause(DEV_POSTPASSWORD_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOption36();
          SetCurr35(DEV_OPTION_36P);
        }
      }
      break;

    case DEV_POSTOPTION_36P:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryPassword36();
      SetCurr35(DEV_PASSWORD_36P);
      break;

    case DEV_PASSWORD_36P:
      if (IsSerial35())
        MakePause(DEV_POSTPASSWORD_36P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPassword36();
          SetCurr35(DEV_PASSWORD_36P);
        }
      }
      break;

    case DEV_POSTPASSWORD_36P:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeProfile36();
      SetCurr35(DEV_TIME_36P);
      break;

    case DEV_TIME_36P:
      if (IsSerial35())
      {
        tiValue36 = ReadTime36();
        MakePause(DEV_POSTTIME_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeProfile36();
          SetCurr35(DEV_TIME_36P);
        }
      }
      break;

    case DEV_POSTTIME_36P:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateProfile36();
      SetCurr35(DEV_DATE_36P);
      break;

    case DEV_DATE_36P:
      if (IsSerial35())
      {
        tiValue36 = ReadDate36(tiValue36);
        dwValue36 = DateToHouIndex(tiValue36);
        MakePause(DEV_POSTDATE_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateProfile36();
          SetCurr35(DEV_DATE_36P);
        }
      }
      break;


    case DEV_POSTDATE_36P:
      if ((boControlQ != false) && (fCurrCtrl == true))
      {
        ulong dwSecond1 = GetSecondIndex(tiValue36);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiValue36, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_36P); }
          else if (GetCurrHouIndex() == (tiValue36.bHour*2 + tiValue36.bMinute/30)) // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_36P); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      else
        MakePause(DEV_POSTCORRECT_36P);
      break;


    case DEV_CONTROL_36P:
      cbRepeat = MaxRepeats();
      QueryControl36(tiCurr);
      SetCurr35(DEV_POSTCONTROL_36P);
      break;

    case DEV_POSTCONTROL_36P:
      if (IsSerial35())
        MakePause(DEV_POSTCORRECT_36P);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_36P);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl36(tiCurr);
          SetCurr35(DEV_POSTCONTROL_36P);
        }
      }
      break;


    case DEV_POSTCORRECT_36P:
      cwShutdown36 = 0;
      InitHeader36();

      ibLine36 = 0;
      if (SkipLine(ibDig, ibLine36) == true)
      {
        ReadHeader36_SkipLine(ibLine36);
        ibLine36++;
      }

      cbRepeat = MaxRepeats();
      QueryHeader36();
      SetCurr35(DEV_HEADER_36P);
      break;

    case DEV_HEADER_36P:
      if (IsSerial35())
      {
        if (IndexInBuff() == 3)                        // если нет требуемой записи
        {
          if (cwShutdown36 >= GetMaxShutdown())        // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            cwShutdown36 += 6;
            sprintf(szLo," выключено: %-4u   ",cwShutdown36);

            iwDigHou = (wHOURS+iwHardHou-wProfile36)%wHOURS;
            ShowProgressDigHou();

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else if (++wProfile36 > wHOURS)
              DoneProfile();
            else
              MakePause(DEV_DATA_36P);
          }
        }
        else
        {
          ReadHeader36();

          if (SkipLine(ibDig, ibLine36+1) == true)
          {
            ReadHeader36_SkipLine(ibLine36+1);
            ibLine36++;
          }

          cwShutdown36 = 0;                            // если есть требуемая запись
          MakePause(DEV_POSTHEADER_36P);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader36();
          SetCurr35(DEV_HEADER_36P);
        }
      }
      break;

    case DEV_POSTHEADER_36P:
      if (++ibLine36 < bMaxLine36)
      {
        cbRepeat = MaxRepeats();
        QueryHeader36();
        SetCurr35(DEV_HEADER_36P);
      }
      else
      {
        if (ReadData36() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_36P);
      }
      break;

    case DEV_DATA_36P:
      if (wBaseCurr > wHOURS/48)
        DoneProfile();
      else
      {
        ibLine36 = 0;

        if (SkipLine(ibDig, ibLine36) == true)
        {
          ReadHeader36_SkipLine(ibLine36);
          ibLine36++;
        }

        cbRepeat = MaxRepeats();
        QueryHeader36();
        SetCurr35(DEV_HEADER_36P);
      }
      break;

#endif

#ifndef SKIP_38

    case DEV_START_38C:
      Clear();

      cbRepeat = MaxRepeats();
      QueryEngAbs38();
      SetCurr(DEV_ENERGY_38C);
      break;

    case DEV_ENERGY_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrent38();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs38();
          SetCurr(DEV_ENERGY_38C);
        }
      }
      break;

#endif

#ifndef SKIP_38

    case DEV_START_38P:
       if (fCurrCtrl == true)
         MakePause(DEV_PREVTIME1_38P);
       else
        MakePause(DEV_PREVTIME2_38P);    
      break;


    // чтение времени для коррекции времения
    case DEV_PREVTIME1_38P:
      cbRepeat = MaxRepeats();
      QueryTime38();
      SetCurr(DEV_TIME1_38P);
      break;

    case DEV_TIME1_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue38 = ReadTime38();
        dwValue38 = DateToHouIndex(tiValue38);
        MakePause(DEV_POSTTIME1_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime38();
          SetCurr(DEV_TIME1_38P);
        }
      }
      break;

    case DEV_POSTTIME1_38P:
      {
        if (DifferentDay(tiValue38, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // даты не совпадают, коррекция невозможна
        else
        {
          ulong dwSecond1 = GetSecondIndex(tiValue38);
          ulong dwSecond2 = GetSecondIndex(tiCurr);
          
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);
          if (dwDelta < GetCorrectLimit()) {
            ShowLo(szCorrectNo); DelayInf();
            MakePause(DEV_PREVTIME2_38P); // без коррекции
          }
          else if (GetCurrHouIndex() == (tiValue38.bHour*2 + tiValue38.bMinute/30))
          {
            if (boControlQ == false) {
              SetCorrectSecond38(dwSecond2 - dwSecond1);
              ShowLo(szCorrectYes); DelayInf();
              MakePause(DEV_PREVAUTHKEY1_38P); // коррекция времени
            } else {
              ShowLo(szManageYes); DelayInf();
              MakePause(DEV_PREVAUTHKEY2_38P); // установка времени
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


// начало коррекции времени
    case DEV_PREVAUTHKEY1_38P:
      cbRepeat = MaxRepeats();
      QueryAuthRequest38();
      SetCurr(DEV_AUTHKEY1_38P);
      break;

    case DEV_AUTHKEY1_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthRequest38();
        MakePause(DEV_POSTAUTHKEY1_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthRequest38();
          SetCurr(DEV_AUTHKEY1_38P);
        }
      }
      break;


    case DEV_POSTAUTHKEY1_38P:
      cbRepeat = MaxRepeats();
      QueryAuthResponse38();
      SetCurr(DEV_AUTHREQ1_38P);
      break;

    case DEV_AUTHREQ1_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bAuth = ReadAuthResponse38();
        if (bAuth == 0)
          MakePause(DEV_PREVCORRECT_38P);
        else {
          Clear(); sprintf(szLo+2,"пароль: %u ?",bAuth); DelayMsg();
          ErrorProfile();
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthResponse38();
          SetCurr(DEV_AUTHREQ1_38P);
        }
      }
      break;


    case DEV_PREVCORRECT_38P:
      cbRepeat = MaxRepeats();
      QueryCorrect38();
      SetCurr(DEV_CORRECT_38P);
      break;

    case DEV_CORRECT_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bCorrect = ReadCorrect38();
        if (bCorrect != 0) {
          Clear(); sprintf(szLo+1,"коррекция: %u ?",bCorrect); DelayMsg();
        }

        MakePause(DEV_PREVTIME2_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryCorrect38();
          SetCurr(DEV_CORRECT_38P);
        }
      }
      break;
// конец коррекции времени

// начало установки времени
    case DEV_PREVAUTHKEY2_38P:
      cbRepeat = MaxRepeats();
      QueryAuthRequest38();
      SetCurr(DEV_AUTHKEY2_38P);
      break;

    case DEV_AUTHKEY2_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthRequest38();
        MakePause(DEV_POSTAUTHKEY2_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthRequest38();
          SetCurr(DEV_AUTHKEY2_38P);
        }
      }
      break;


    case DEV_POSTAUTHKEY2_38P:
      cbRepeat = MaxRepeats();
      QueryAuthResponse38();
      SetCurr(DEV_AUTHREQ2_38P);
      break;

    case DEV_AUTHREQ2_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bAuth = ReadAuthResponse38();
        if (bAuth == 0)
          MakePause(DEV_PREVMANAGE_38P);
        else {
          Clear(); sprintf(szLo+2,"пароль: %u ?",bAuth); DelayMsg();
          ErrorProfile();
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthResponse38();
          SetCurr(DEV_AUTHREQ2_38P);
        }
      }
      break;


    case DEV_PREVMANAGE_38P:
      cbRepeat = MaxRepeats();
      QueryManage38();
      SetCurr(DEV_MANAGE_38P);
      break;

    case DEV_MANAGE_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bManage = ReadManage38();
        if (bManage != 0) {
          Clear(); sprintf(szLo+1,"установка: %u ?",bManage); DelayMsg();
        }

        MakePause(DEV_PREVTIME2_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryManage38();
          SetCurr(DEV_MANAGE_38P);
        }
      }
      break;
// конец установки времени

// чтение времени для чтения профилей
    case DEV_PREVTIME2_38P:
      cbRepeat = MaxRepeats();
      QueryTime38();
      SetCurr(DEV_TIME2_38P);
      break;

    case DEV_TIME2_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue38 = ReadTime38();
        dwValue38 = DateToHouIndex(tiValue38);
        MakePause(DEV_INITHEADER_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime38();
          SetCurr(DEV_TIME2_38P);
        }
      }
      break;


    case DEV_INITHEADER_38P:
      InitHeader38();
      MakePause(DEV_PAUSE_38P);
      break;

    case DEV_PAUSE_38P:
      {
        ulong dwSecNow = DateToSecIndex(tiCurr);
        ulong dwHou = DateToHouIndex(tiCurr);
        ulong dwSecPrev = DateToSecIndex(HouIndexToDate(dwHou));
        ulong dwSecNext = DateToSecIndex(HouIndexToDate(dwHou + 1));
        const char bGap = 30;
        bool f1 = (dwSecNext - dwSecNow < bGap);
        bool f2 = (dwSecNow - dwSecPrev < bGap);
        if (f1 || f2)
        {
          Clear();
          uchar bDelta = f1 ? bGap + (dwSecNext - dwSecNow) : bGap - (dwSecNow - dwSecPrev);
          sprintf(szLo+3, "пауза: %u", bDelta);
          MakeLongPause(DEV_PAUSE_38P, 1);
        }
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeader38();
          SetCurr(DEV_HEADER_38P);
        }
      }
      break;

    case DEV_HEADER_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadData38() == false)
          DoneProfile();
        else
          MakePause(DEV_PAUSE_38P);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader38();
          SetCurr(DEV_HEADER_38P);
        }
      }
      break;

#endif

#ifndef SKIP_39

    case DEV_START_39C:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      Query39_DISC_Current();
      SetCurr(DEV_DISC_39C);
      break;

    case DEV_DISC_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_POSTDISC_39C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_DISC_Current();
          SetCurr(DEV_DISC_39C);
        }
      }
      break;


    case DEV_POSTDISC_39C:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      Query39_SNRM();
      SetCurr(DEV_SNRM_39C);
      break;

    case DEV_SNRM_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_POSTSNRM_39C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_SNRM();
          SetCurr(DEV_SNRM_39C);
        }
      }
      break;


    case DEV_POSTSNRM_39C:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      Query39_AARQ_Current();
      SetCurr(DEV_OPEN2_39C);
      break;

    case DEV_OPEN2_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateIframe_Current())
          ErrorCurrent();
        else
          MakePause(DEV_POSTOPEN2_39C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_AARQ_Current();
          SetCurr(DEV_OPEN2_39C);
        }
      }
      break;


    case DEV_POSTOPEN2_39C:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      Query39_RR_Current();
      SetCurr(DEV_RR1_39C);
      break;

    case DEV_RR1_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Current())
          ErrorCurrent();
        else
          MakePause(DEV_POSTRR1_39C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_RR_Current();
          SetCurr(DEV_RR1_39C);
        }
      }
      break;


    case DEV_POSTRR1_39C:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryEngAbs39_Current();
      SetCurr(DEV_ENGABS_39C);
      break;

    case DEV_ENGABS_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateIframe_Current())
          ErrorCurrent();
        else {
          SaveCurrent39();
          MakePause(DEV_POSTENGABS_39C);
        }
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs39_Current();
          SetCurr(DEV_ENGABS_39C);
        }
      }
      break;


    case DEV_POSTENGABS_39C:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Current();
      SetCurr(DEV_RR2_39C);
      break;

    case DEV_RR2_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateSframe_Current())
          ErrorCurrent();
        else {
          ReadCurrent39();
        }
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_RR_Current();
          SetCurr(DEV_RR2_39C);
        }
      }
      break;

#endif

#ifndef SKIP_39

    case DEV_START_39P:
      MakePause(DEV_1_39P);
      break;


    case DEV_1_39P:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      Query39_DISC_Profile();
      SetCurr(DEV_2_39P);
      break;

    case DEV_2_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_3_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_3_39P:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      Query39_SNRM();
      SetCurr(DEV_4_39P);
      break;

    case DEV_4_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_5_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_5_39P:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      Query39_AARQ_Profile();
      SetCurr(DEV_6_39P);
      break;

    case DEV_6_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateIframe_Profile())
          ErrorProfile();
        else
          MakePause(DEV_7_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_7_39P:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_8_39P);
      break;

    case DEV_8_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Profile())
          ErrorProfile();
        else
          MakePause(DEV_9_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_9_39P:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryTime39_Profile();
      SetCurr(DEV_10_39P);
      break;

    case DEV_10_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateIframe_Profile())
          ErrorProfile();
        else {
          ReadTime39_Profile();
          MakePause(DEV_11_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_11_39P:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_12_39P);
      break;

    case DEV_12_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Profile())
          ErrorProfile();
        else
          MakePause(DEV_13_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_13_39P:
      InitProfile39_Profile();
      MakePause(DEV_13a_39P);
      break;


    case DEV_13a_39P:
      cbRepeat = MaxRepeat39();
      QueryProfile39_Profile();
      SetCurr(DEV_14_39P);
      break;

    case DEV_14_39P:
      Read1_Profile();
      MakePause(DEV_15_39P);
      break;

    case DEV_15_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK)  {
        Read1_Profile();
        if (!LastSegmentDMLS()) {
          MakePause(DEV_16_39P);
        } else {          
          MakePause(DEV_18_39P);
        }
      } else {
        ErrorProfile();
      } 
      break;


    case DEV_16_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_17_39P);
      break;

    case DEV_17_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          ErrorProfile();
        } else {
          Read2_Profile();
          MakePause(DEV_15_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_18_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_19_39P);
      break;

    case DEV_19_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          ErrorProfile();
        } else {
          Read3_Profile();
          if (UseBlocks_Profile()) {
            QueryNextBlock39_Profile();
            MakePause(DEV_20_39P);
          } else {
            MakePause(DEV_25_39P);
          }
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_20_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK)  {
        Read4_Profile();
        if (!LastSegmentDMLS()) {
          MakePause(DEV_21_39P);
        } else {          
          MakePause(DEV_23_39P);
        }
      } else {
        ErrorProfile();
      } 
      break;


    case DEV_21_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_22_39P);
      break;

    case DEV_22_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          ErrorProfile();
        } else {
          Read5_Profile();
          MakePause(DEV_20_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_23_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_24_39P);
      break;

    case DEV_24_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          ErrorProfile();
        } else {
          MakePause(DEV_25_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_25_39P:
      if (FinishProfile39_Profile())
        MakePause(DEV_13a_39P);
      else
        DoneProfile();
      break;

#endif
  }

}
