
#ifndef SKIP_41

    case DEV_START_41P:
//       if (fCurrCtrl == true)
//         MakePause(DEV_PREVTIME1_41P);
//       else
        MakePause(DEV_PREVTIME2_41P);
      break;


    // чтение времени для коррекции времения
    case DEV_PREVTIME1_41P:
      cbRepeat = MaxRepeats();
      QueryTime38();
      SetCurr(DEV_TIME1_41P);
      break;

    case DEV_TIME1_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue41 = ReadTime38();
        dwValue41 = DateToHouIndex(tiValue41);
        MakePause(DEV_POSTTIME1_41P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime38();
          SetCurr(DEV_TIME1_41P);
        }
      }
      break;

    case DEV_POSTTIME1_41P:
      {
        if (DifferentDay(tiValue41, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // даты не совпадают, коррекция невозможна
        else
        {
          ulong dwSecond1 = GetSecondIndex(tiValue41);
          ulong dwSecond2 = GetSecondIndex(tiCurr);
          
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);
          if (dwDelta < GetCorrectLimit()) {
            ShowLo(szCorrectNo); DelayInf();
            MakePause(DEV_PREVTIME2_41P); // без коррекции
          }
          else if (GetCurrHouIndex() == (tiValue41.bHour*2 + tiValue41.bMinute/30))
          {
            if (boControlQ == false) {
              SetCorrectSecond38(dwSecond2 - dwSecond1);
              ShowLo(szCorrectYes); DelayInf();
              MakePause(DEV_PREVAUTHKEY1_41P); // коррекция времени
            } else {
              ShowLo(szManageYes); DelayInf();
              MakePause(DEV_PREVAUTHKEY2_41P); // установка времени
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


// начало коррекции времени
    case DEV_PREVAUTHKEY1_41P:
      cbRepeat = MaxRepeats();
      QueryAuthRequest38();
      SetCurr(DEV_AUTHKEY1_41P);
      break;

    case DEV_AUTHKEY1_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthRequest38();
        MakePause(DEV_POSTAUTHKEY1_41P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthRequest38();
          SetCurr(DEV_AUTHKEY1_41P);
        }
      }
      break;


    case DEV_POSTAUTHKEY1_41P:
      cbRepeat = MaxRepeats();
      QueryAuthResponse38();
      SetCurr(DEV_AUTHREQ1_41P);
      break;

    case DEV_AUTHREQ1_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bAuth = ReadAuthResponse38();
        if (bAuth == 0)
          MakePause(DEV_PREVCORRECT_41P);
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
          SetCurr(DEV_AUTHREQ1_41P);
        }
      }
      break;


    case DEV_PREVCORRECT_41P:
      cbRepeat = MaxRepeats();
      QueryCorrect38();
      SetCurr(DEV_CORRECT_41P);
      break;

    case DEV_CORRECT_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bCorrect = ReadCorrect38();
        if (bCorrect != 0) {
          Clear(); sprintf(szLo+1,"коррекция: %u ?",bCorrect); DelayMsg();
        }

        MakePause(DEV_PREVTIME2_41P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryCorrect38();
          SetCurr(DEV_CORRECT_41P);
        }
      }
      break;
// конец коррекции времени

// начало установки времени
    case DEV_PREVAUTHKEY2_41P:
      cbRepeat = MaxRepeats();
      QueryAuthRequest38();
      SetCurr(DEV_AUTHKEY2_41P);
      break;

    case DEV_AUTHKEY2_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthRequest38();
        MakePause(DEV_POSTAUTHKEY2_41P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthRequest38();
          SetCurr(DEV_AUTHKEY2_41P);
        }
      }
      break;


    case DEV_POSTAUTHKEY2_41P:
      cbRepeat = MaxRepeats();
      QueryAuthResponse38();
      SetCurr(DEV_AUTHREQ2_41P);
      break;

    case DEV_AUTHREQ2_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bAuth = ReadAuthResponse38();
        if (bAuth == 0)
          MakePause(DEV_PREVMANAGE_41P);
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
          SetCurr(DEV_AUTHREQ2_41P);
        }
      }
      break;


    case DEV_PREVMANAGE_41P:
      cbRepeat = MaxRepeats();
      QueryManage38();
      SetCurr(DEV_MANAGE_41P);
      break;

    case DEV_MANAGE_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bManage = ReadManage38();
        if (bManage != 0) {
          Clear(); sprintf(szLo+1,"установка: %u ?",bManage); DelayMsg();
        }

        MakePause(DEV_PREVTIME2_41P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryManage38();
          SetCurr(DEV_MANAGE_41P);
        }
      }
      break;
// конец установки времени

// чтение времени для чтения профилей
    case DEV_PREVTIME2_41P:
      cbRepeat = MaxRepeats();
      QueryTime38();
      SetCurr(DEV_TIME2_41P);
      break;

    case DEV_TIME2_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue41 = ReadTime38();
        dwValue41 = DateToHouIndex(tiValue41);
        MakePause(DEV_INITHEADER_41P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime38();
          SetCurr(DEV_TIME2_41P);
        }
      }
      break;


    case DEV_INITHEADER_41P:
      InitHeader41();
      MakePause(DEV_PAUSE_41P);
      break;

    case DEV_PAUSE_41P:
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
          MakeLongPause(DEV_PAUSE_41P, 1);
        }
        else
        {
          ClearRepeatProfile41();

          cbRepeat = MaxRepeats();
          QueryHeader41(0);
          SetCurr(DEV_HEADER_41P);
        }
      }
      break;

    case DEV_HEADER_41P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 14)
        {
          if (NextRepeatProfile41())
            QueryHeader41(0);
          else
            ErrorProfile();
        }
        else
        {
          if (ReadData41(0) == false)
            DoneProfile();
          else if (cwShutdown41 >= GetMaxShutdown())
            DoneProfile();
          else
            MakePause(DEV_PAUSE_41P);
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

          QueryHeader41(0);
          SetCurr(DEV_HEADER_41P);
        }
      }
      break;

#endif
