#ifndef SKIP_34

    case DEV_START_34P:
      if (fCurrCtrl == true)
        MakePause(DEV_PREVTIME_34P);
      else
        MakePause(DEV_POSTCORRECT_34P);
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
          //dwCorrectW = dwSecond2 - dwSecond1;

          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);
          if (dwDelta < GetCorrectLimit()) // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_34P); }
          else if (dwDelta < CORRECT_LIMIT_34) // простая коррекция
          {
            SetCorrectSecond34(dwDelta);
            ShowLo(szCorrectYes); DelayInf();
            MakePause(DEV_PREVCORRECT_34P);
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_PREVCORRECT_34P:
      cbRepeat = MaxRepeats();
      QueryCorrect34();
      SetCurr(DEV_CORRECT_34P);
      break;

    case DEV_CORRECT_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadCorrect34();
        MakePause(DEV_POSTCORRECT_34P);
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

    case DEV_POSTCORRECT_34P:
      MakePause(DEV_PREVOPEN_34P);
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
        if (ReadProfileClose34()) {
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
