
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
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionW();
      SetCurr(DEV_OPTION_W2);
      break;

    case DEV_OPTION_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (fCurrCtrl == true)
          MakePause(DEV_PREVTIME_W2);
        else
          MakePause(DEV_POSTCORRECT_W2); // ?
      }
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
        if (cbRepeat == 0)
          ErrorProfile();
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
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_W2); }
          else if (GetCurrHouIndex() == (tiValueC.bHour*2 + tiValueC.bMinute/30)) // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_W2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;
/*
    case DEV_CONTROL_W2:
      if (++cbCorrects > 3)
        MakePause(DEV_POSTCORRECT_W2);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryControlC();
        SetCurr(DEV_POSTCONTROL_W2);
      }
      break;

    case DEV_POSTCONTROL_W2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultC() == 1))
        MakePause(DEV_POSTOPENCANAL_W2);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTOPENCANAL_W2);   // да !
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
      cbRepeat = GetMaxRepeats();
      QueryVersionC();
      SetCurr(DEV_VERSION_W2);
      break;

    case DEV_VERSION_W2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionC();

        if (boHideMessages == false)
          MakeLongPause(DEV_POSTVERSION_W2, 1);
        else
          MakePause(DEV_POSTVERSION_W2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionC();
          SetCurr(DEV_VERSION_W2);
        }
      }
      break;

    case DEV_POSTVERSION_W2:
      cbRepeat = GetMaxRepeats();
      QueryTimeC();
      SetCurr(DEV_VALUE_W2);
      break;
*/
#endif
