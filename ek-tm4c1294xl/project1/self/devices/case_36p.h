
#ifndef SKIP_U

    case DEV_START_36P:
      if ((boControlQ == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT_36P);
      else
        MakePause(DEV_OPEN_36P);
      break;

    case DEV_PREVCORRECT_36P:
      if (tiCurr.bSecond < bMINORCORRECT_U) {
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
      if (mpSerial[ibPort] == SER_GOODCHECK)
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
      if (mpSerial[ibPort] == SER_GOODCHECK)
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
      if (mpSerial[ibPort] == SER_GOODCHECK)
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
      if ((boControlQ != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_36P);
      else
        MakePause(DEV_POSTCORRECT_36P);
      break;

    case DEV_PREVTIME_36P:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeSpec36();
      SetCurr35(DEV_TIME_36P);
      break;

    case DEV_TIME_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTime36();
        MakePause(DEV_POSTTIME_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpec36();
          SetCurr35(DEV_TIME_36P);
        }
      }
      break;

    case DEV_POSTTIME_36P:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateSpec36();
      SetCurr35(DEV_DATE_36P);
      break;

    case DEV_DATE_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDate36(tiDig);
        MakePause(DEV_POSTDATE_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpec36();
          SetCurr35(DEV_DATE_36P);
        }
      }
      break;


    case DEV_POSTDATE_36P:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_36P); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_36P); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_36P:
      cbRepeat = MaxRepeats();
      QueryControl36();
      SetCurr35(DEV_POSTCONTROL_36P);
      break;

    case DEV_POSTCONTROL_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_36P);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_36P);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl36();
          SetCurr35(DEV_POSTCONTROL_36P);
        }
      }
      break;


    case DEV_POSTCORRECT_36P:
      if (boPlcUFlag == false)
        MakePause(DEV_PREVHEADER_36P);
      else
      {
        Clear();
        sprintf(szLo+4, "блок: %u", bPlcUSize);
        MakeLongPause(DEV_PREVHEADER_U4, 1);
      }
      break;

    case DEV_PREVHEADER_36P:
      iwMajor = 0;
      InitHeader36();

      ibLine36 = 0;
      if (SkipLine(ibDig, ibLine36) == 1)
      {
        ReadHeader36_SkipLine(ibLine36);
        ibLine36++;
      }

      cbRepeat = MaxRepeats();
      QueryHeader36();
      SetCurr35(DEV_HEADER_36P);
      break;

    case DEV_HEADER_36P:
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
              MakePause(DEV_DATA_36P);
          }
        }
        else
        {
          ReadHeader36();

          if (SkipLine(ibDig, ibLine36+1) == 1)
          {
            ReadHeader36_SkipLine(ibLine36+1);
            ibLine36++;
          }

          iwMajor = 0;                                  // если есть требуемая запись
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

        if (SkipLine(ibDig, ibLine36) == 1)
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
