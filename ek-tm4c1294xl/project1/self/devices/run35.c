
#ifndef SKIP_35

    case DEV_START_35P:
      cbRepeat = MaxRepeats();
      QueryVersion35();
      SetCurr35(DEV_VERSION_35P);
      break;

    case DEV_VERSION_35P:
      if (mpSerial[ibPort] == SER_PAUSE) // SER_GOODCHECK
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
      if (mpSerial[ibPort] == SER_PAUSE) // SER_GOODCHECK
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
      if (mpSerial[ibPort] == SER_PAUSE) // SER_GOODCHECK
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
      if (mpSerial[ibPort] == SER_PAUSE) // SER_GOODCHECK
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
      if (mpSerial[ibPort] == SER_PAUSE) // SER_GOODCHECK
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
