
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

/*
    case DEV_START_38P:
      MakePause(DEV_PREVAUTHKEY_38P);
      break;


    case DEV_PREVAUTHKEY_38P:
      cbRepeat = MaxRepeats();
      QueryAuthKey38();
      SetCurr(DEV_AUTHKEY_38P);
      break;

    case DEV_AUTHKEY_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthKey38();
        MakePause(DEV_POSTAUTHKEY_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthKey38();
          SetCurr(DEV_AUTHKEY_38P);
        }
      }
      break;


    case DEV_POSTAUTHKEY_38P:
      cbRepeat = MaxRepeats();
      QueryAuthReq38();
      SetCurr(DEV_AUTHREQ_38P);
      break;

    case DEV_AUTHREQ_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadAuthReq38())
          MakePause(DEV_POSTSTART_38P);
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

          QueryAuthReq38();
          SetCurr(DEV_AUTHREQ_38P);
        }
      }
      break;
*/
    case DEV_POSTTIME1_38P:
      {
        ulong dwSecond1 = GetSecondIndex(GetTimeCurr38());
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(GetTimeCurr38(), tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);
          if (dwDelta < GetCorrectLimit()) {
            ShowLo(szCorrectNo); DelayInf();
            MakePause(DEV_PREVINIT_38P); // без коррекции
          }
          else if (GetCurrHouIndex() == GetTimeCurrIndex38())
          {
            if (dwDelta < CORRECT_LIMIT_38) {
              SetCorrectSecond38(dwSecond2 - dwSecond1);
              ShowLo(szCorrectYes); DelayInf();
              MakePause(DEV_PREVCORRECT_38P); // коррекция времени
            } else {
              ShowLo(szManageYes); DelayInf();
              MakePause(DEV_PREVMANAGE_38P); // установка времени
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;
/*
// начало коррекции времени

    case DEV_PREVCORRECT_38P:
      cbRepeat = MaxRepeats();
      QueryCorrect38();
      SetCurr(DEV_CORRECT_38P);
      break;

    case DEV_CORRECT_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadCorrect38();
        if (InBuff(2) == 0x05) {
          ShowLo(szManageYes); DelayInf();
          MakePause(DEV_PREVMANAGE_38P); // нельзя корректировать время, можно установить время
        } else {
          MakePause(DEV_PREVINIT_38P);
        }
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

    case DEV_PREVMANAGE_38P:
      cbRepeat = MaxRepeats();
      QueryManage38();
      SetCurr(DEV_MANAGE_38P);
      break;

    case DEV_MANAGE_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadManage38();
        MakePause(DEV_PREVINIT_38P);
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
*/
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
        MakePause(DEV_POSTTIME2_38P);
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


    case DEV_POSTTIME2_38P:
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
