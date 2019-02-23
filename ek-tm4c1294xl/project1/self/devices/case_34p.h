#ifndef SKIP_34

    case DEV_START_34P:
      if (fCurrCtrl == true)
        MakePause(DEV_PREVTIME_34P);
      else
        MakePause(DEV_PREVOPEN_34P);
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
            MakePause(DEV_PREVOPEN_34P); // без коррекции
          }
          else if (GetCurrHouIndex() == GetTimeCurrIndex34())
          {
            if (dwDelta < CORRECT_LIMIT_34) {
              SetCorrectSecond34(dwSecond1 - dwSecond2);
              ShowLo(szCorrectYes); DelayInf();
              MakePause(DEV_PREVAUTH1KEY_34P); // коррекция времени
            } else {
              ShowLo(szManageYes); DelayInf();
              MakePause(DEV_PREVAUTH2KEY_34P); // установка времени
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

// начало коррекции времени

    case DEV_PREVAUTH1KEY_34P:
      cbRepeat = MaxRepeats();
      QueryAuthKey34();
      SetCurr(DEV_AUTH1KEY_34P);
      break;

    case DEV_AUTH1KEY_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthKey34();
        MakePause(DEV_POSTAUTH1KEY_34P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthKey34();
          SetCurr(DEV_AUTH1KEY_34P);
        }
      }
      break;


    case DEV_POSTAUTH1KEY_34P:
      cbRepeat = MaxRepeats();
      QueryAuthReq34();
      SetCurr(DEV_AUTH1REQ_34P);
      break;

    case DEV_AUTH1REQ_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadAuthReq())
          MakePause(DEV_PREVCORRECT_34P);
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
          SetCurr(DEV_AUTH1REQ_34P);
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
        if (InBuff(2) == 0x05)
          MakePause(DEV_PREVAUTH2KEY_34P); // нельзя корректировать время, можно установить время
        else
          MakePause(DEV_PREVOPEN_34P);
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

    case DEV_PREVAUTH2KEY_34P:
      cbRepeat = MaxRepeats();
      QueryAuthKey34();
      SetCurr(DEV_AUTH2KEY_34P);
      break;

    case DEV_AUTH2KEY_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthKey34();
        MakePause(DEV_POSTAUTH2KEY_34P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthKey34();
          SetCurr(DEV_AUTH2KEY_34P);
        }
      }
      break;


    case DEV_POSTAUTH2KEY_34P:
      cbRepeat = MaxRepeats();
      QueryAuthReq34();
      SetCurr(DEV_AUTH2REQ_34P);
      break;

    case DEV_AUTH2REQ_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadAuthReq())
          MakePause(DEV_PREVMANAGE_34P);
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
          SetCurr(DEV_AUTH2REQ_34P);
        }
      }
      break;


    case DEV_PREVMANAGE_34P:
      cbRepeat = MaxRepeats();
      QueryManage34();
      SetCurr(DEV_MANAGE_34P);
      break;

    case DEV_MANAGE_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadManage34();
        MakePause(DEV_PREVOPEN_34P);
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
