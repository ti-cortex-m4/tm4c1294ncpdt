
#ifndef SKIP_W

    case DEV_START_W2:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
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
      ShowPercent(51);

      cbRepeat = GetMaxRepeats();
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

      cbRepeat = GetMaxRepeats();
      QueryPasswordW();
      SetCurr(DEV_PASSWORD_W2);
      break;

    case DEV_PASSWORD_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (fCurrCtrl == true)
          MakePause(DEV_PREVTIME_W2);
        else
          MakePause(DEV_POSTCORRECT_W2);
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
      cbRepeat = GetMaxRepeats();
      QueryTimeW_Profile();
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
        uint iwDay1 = GetDayIndexMD(tiProfileW.bMonth, tiProfileW.bDay);
        ulong dwSecond1 = GetSecondIndex(tiProfileW);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          dwCorrectW = dwSecond2 - dwSecond1;

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit()) // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_W2); }
          else if (GetCurrHouIndex() == (tiProfileW.bHour*2 + tiProfileW.bMinute/30)) // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_GETCORRECT_W2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_GETCORRECT_W2:
      cbRepeat = GetMaxRepeats();
      QueryGetCorrectW();
      SetCurr(DEV_POSTGETCORRECT_W2);
      break;

    case DEV_POSTGETCORRECT_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uint w = ReadGetCorrectW();
        if (w <= 1800)
          MakeLongPause(DEV_SETCORRECT_W2,1);
        else
          MakeLongPause(DEV_CONTROL_W2,1);
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
      cbRepeat = GetMaxRepeats();
      QuerySetCorrectW(dwCorrectW);
      SetCurr(DEV_POSTSETCORRECT_W2);
      break;

    case DEV_POSTSETCORRECT_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_W2);
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
      cbRepeat = GetMaxRepeats();
      QueryControlW(tiCurr);
      SetCurr(DEV_POSTCONTROL_W2);
      break;

    case DEV_POSTCONTROL_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_W2);
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

    case DEV_POSTCORRECT_W2:
      ErrorProfile();
      break;

#endif
