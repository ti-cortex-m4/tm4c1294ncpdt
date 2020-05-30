
#ifndef SKIP_38

    case DEV_START_38P:
//      if ((boControlQ == false) && (fCurrCtrl == true))
//        MakePause(DEV_PREVCORRECT_38P);
//      else
        MakePause(DEV_OPEN_38P);
      break;

    case DEV_PREVCORRECT_38P:
      if (tiCurr.bSecond < bMINORCORRECT_38) {
        MakePause(DEV_CORRECT_38P);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT_38P);
      }
      break;

    case DEV_CORRECT_38P:
      ShowLo(szCorrectQ1);
      QueryCorrect38();
      SetCurr(DEV_OPEN_38P);
      break;

    case DEV_OPEN_38P:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpen38();
      SetCurr(DEV_OPENCANAL_38P);
      break;

    case DEV_OPENCANAL_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpen38();
        MakeLongPause(DEV_POSTOPENCANAL_38P, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen38();
          SetCurr(DEV_OPENCANAL_38P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_38P:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOption38();
      SetCurr(DEV_OPTION_38P);
      break;

    case DEV_OPTION_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPassword38())
          MakePause(DEV_POSTOPTION_38P);
        else
          MakePause(DEV_POSTPASSWORD_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOption38();
          SetCurr(DEV_OPTION_38P);
        }
      }
      break;

    case DEV_POSTOPTION_38P:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryPassword38();
      SetCurr(DEV_PASSWORD_38P);
      break;

    case DEV_PASSWORD_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_38P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPassword38();
          SetCurr(DEV_PASSWORD_38P);
        }
      }
      break;

    case DEV_POSTPASSWORD_38P:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeProfile38();
      SetCurr(DEV_TIME_38P);
      break;

    case DEV_TIME_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue38 = ReadTime38();
        MakePause(DEV_POSTTIME_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeProfile38();
          SetCurr(DEV_TIME_38P);
        }
      }
      break;

    case DEV_POSTTIME_38P:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateProfile38();
      SetCurr(DEV_DATE_38P);
      break;

    case DEV_DATE_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue38 = ReadDate38(tiValue38);
        dwValue38 = DateToHouIndex(tiValue38);
        MakePause(DEV_POSTDATE_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateProfile38();
          SetCurr(DEV_DATE_38P);
        }
      }
      break;


    case DEV_POSTDATE_38P:
      if ((boControlQ != false) && (fCurrCtrl == true))
      {
        ulong dwSecond1 = GetSecondIndex(tiValue38);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiValue38, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_38P); }
          else if (GetCurrHouIndex() == (tiValue38.bHour*2 + tiValue38.bMinute/30)) // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_38P); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      else
        MakePause(DEV_POSTCORRECT_38P);
      break;


    case DEV_CONTROL_38P:
      cbRepeat = MaxRepeats();
      QueryControl38(tiCurr);
      SetCurr(DEV_POSTCONTROL_38P);
      break;

    case DEV_POSTCONTROL_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_38P);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_38P);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl38(tiCurr);
          SetCurr(DEV_POSTCONTROL_38P);
        }
      }
      break;


    case DEV_POSTCORRECT_38P:
      cwShutdown38 = 0;
      InitHeader38();

      ibLine38 = 0;
      if (SkipLine(ibDig, ibLine38) == true)
      {
        ReadHeader38_SkipLine(ibLine38);
        ibLine38++;
      }

      cbRepeat = MaxRepeats();
      QueryHeader38();
      SetCurr(DEV_HEADER_38P);
      break;

    case DEV_HEADER_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 3)                        // если нет требуемой записи
        {
          if (cwShutdown38 >= GetMaxShutdown())        // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            cwShutdown38 += 6;
            sprintf(szLo," выключено: %-4u   ",cwShutdown38);

            iwDigHou = (wHOURS+iwHardHou-wProfile38)%wHOURS;
            ShowProgressDigHou();

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else if (++wProfile38 > wHOURS)
              DoneProfile();
            else
              MakePause(DEV_DATA_38P);
          }
        }
        else
        {
          ReadHeader38();

          if (SkipLine(ibDig, ibLine38+1) == true)
          {
            ReadHeader38_SkipLine(ibLine38+1);
            ibLine38++;
          }

          cwShutdown38 = 0;                            // если есть требуемая запись
          MakePause(DEV_POSTHEADER_38P);
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

          QueryHeader38();
          SetCurr(DEV_HEADER_38P);
        }
      }
      break;

    case DEV_POSTHEADER_38P:
      if (++ibLine38 < bMaxLine38)
      {
        cbRepeat = MaxRepeats();
        QueryHeader38();
        SetCurr(DEV_HEADER_38P);
      }
      else
      {
        if (ReadData38() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_38P);
      }
      break;

    case DEV_DATA_38P:
      if (wBaseCurr > wHOURS/48)
        DoneProfile();
      else
      {
        ibLine38 = 0;

        if (SkipLine(ibDig, ibLine38) == true)
        {
          ReadHeader38_SkipLine(ibLine38);
          ibLine38++;
        }

        cbRepeat = MaxRepeats();
        QueryHeader38();
        SetCurr(DEV_HEADER_38P);
      }
      break;

#endif
