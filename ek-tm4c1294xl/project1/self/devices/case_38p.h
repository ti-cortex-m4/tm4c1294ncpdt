
#ifndef SKIP_38

    case DEV_START_38P:
      MakePause(DEV_PREVTIME_38P);
      break;


/*
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

*/
    case DEV_PREVTIME_38P:
      cbRepeat = MaxRepeats();
      QueryTime38();
      SetCurr(DEV_TIME_38P);
      break;

    case DEV_TIME_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue38 = ReadTime38();
        dwValue38 = DateToHouIndex(tiValue38);
        MakePause(DEV_POSTTIME_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime38();
          SetCurr(DEV_TIME_38P);
        }
      }
      break;


    case DEV_POSTTIME_38P:
      InitHeader38();

      cbRepeat = MaxRepeats();
      QueryHeader38();
      SetCurr(DEV_HEADER_38P);
      break;

    case DEV_HEADER_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadData38() == false)
          DoneProfile();
        else
          MakePause(DEV_DATA_38P);
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

    case DEV_DATA_38P:
      cbRepeat = MaxRepeats();
      QueryHeader38();
      SetCurr(DEV_HEADER_38P);
      break;

#endif
