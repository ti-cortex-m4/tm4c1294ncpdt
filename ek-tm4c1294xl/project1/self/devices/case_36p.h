
#ifndef SKIP_U

    case DEV_START_U2:
      if ((boControlQ == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT_U2);
      else
        MakePause(DEV_OPEN_U2);
      break;

    case DEV_PREVCORRECT_U2:
      if (tiCurr.bSecond < bMINORCORRECT_U) {
        MakePause(DEV_CORRECT_U2);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT_U2);
      }
      break;

    case DEV_CORRECT_U2:
      ShowLo(szCorrectQ1);
      QueryCorrectU();
      SetCurr(DEV_OPEN_U2);
      break;

    case DEV_OPEN_U2:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U2);
      break;

    case DEV_OPENCANAL_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_U2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_U2:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionU();
      SetCurr(DEV_OPTION_U2);
      break;

    case DEV_OPTION_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_U2);
        else
          MakePause(DEV_POSTPASSWORD_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionU();
          SetCurr(DEV_OPTION_U2);
        }
      }
      break;

    case DEV_POSTOPTION_U2:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_U2);
      break;

    case DEV_PASSWORD_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_U2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_U2);
        }
      }
      break;

    case DEV_POSTPASSWORD_U2:
      if ((boControlQ != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_U2);
      else
        MakePause(DEV_POSTCORRECT_U2);
      break;

    case DEV_PREVTIME_U2:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_U2);
      break;

    case DEV_TIME_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_U2);
        }
      }
      break;

    case DEV_POSTTIME_U2:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_U2);
      break;

    case DEV_DATE_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_U2);
        }
      }
      break;


    case DEV_POSTDATE_U2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_U2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_U2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_U2:
      cbRepeat = MaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_U2);
      break;

    case DEV_POSTCONTROL_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_U2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_U2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_U2);
        }
      }
      break;


    case DEV_POSTCORRECT_U2:
      if (boPlcUFlag == false)
        MakePause(DEV_PREVHEADER_U2);
      else
      {
        Clear();
        sprintf(szLo+4, "блок: %u", bPlcUSize);
        MakeLongPause(DEV_PREVHEADER_U4, 1);
      }
      break;

    case DEV_PREVHEADER_U2:
      iwMajor = 0;
      InitHeaderU();

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == 1)
      {
        ReadHeaderU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = MaxRepeats();
      QueryHeaderU();
      SetCurr(DEV_HEADER_U2);
      break;

    case DEV_HEADER_U2:
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
              MakePause(DEV_DATA_U2);
          }
        }
        else
        {
          ReadHeaderU();

          if (SkipLine(ibDig, ibLineU+1) == 1)
          {
            ReadHeaderU_SkipLine(ibLineU+1);
            ibLineU++;
          }

          iwMajor = 0;                                  // если есть требуемая запись
          MakePause(DEV_POSTHEADER_U2);
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

          QueryHeaderU();
          SetCurr(DEV_HEADER_U2);
        }
      }
      break;

    case DEV_POSTHEADER_U2:
      if (++ibLineU < bMaxLineU)
      {
        cbRepeat = MaxRepeats();
        QueryHeaderU();
        SetCurr(DEV_HEADER_U2);
      }
      else
      {
        if (ReadDataU() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_U2);
      }
      break;

    case DEV_DATA_U2:
      if (wBaseCurr > wHOURS/48)
        DoneProfile();
      else
      {
        ibLineU = 0;

        if (SkipLine(ibDig, ibLineU) == 1)
        {
          ReadHeaderU_SkipLine(ibLineU);
          ibLineU++;
        }

        cbRepeat = MaxRepeats();
        QueryHeaderU();
        SetCurr(DEV_HEADER_U2);
      }
      break;

#endif
