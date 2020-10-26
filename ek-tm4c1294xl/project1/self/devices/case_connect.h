
    case DEV_MODEM_START:
      if ((exExtended == EXT_CURRENT_3MIN) && (diCurr.ibPhone != 0))
      {
        ShowLo(szPowerNo); DelayInf();
        cbWaitQuery = 3;
        NextCurrent();
      }
      else
      {
        MonitorString("\n DEV_MODEM_START fConnect = 0");
        fConnect = 0;
        if (StreamPortCan(diCurr.ibPort,ibDig) == 0)
        {
          fKeyOn = 0;
          MakePause(DEV_MODEM_STOP);

          AddModRecord(EVE_MODEM_ERROR);
        }
        else if (IsModemConnect())
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

      MonitorString("\n DEV_MODEM_POSTCUSTOM fConnect = 1");

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

          MonitorString("\n DEV_MODEM_CONNECT fConnect = 1");

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

      if (IsModemDisconnect())
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
      MonitorString("\n DEV_MODEM_POSTBREAK fConnect = 0");

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
