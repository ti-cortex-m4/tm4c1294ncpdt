
#ifndef SKIP_K

    case DEV_START_K2:
      if ((boControlK == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT2_K2);
      else
        MakePause(DEV_OPEN_K2);
      break;

    case DEV_PREVCORRECT2_K2:
      if (tiCurr.bSecond < bMINORCORRECT_K) {
        MakePause(DEV_CORRECT2_K2);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT2_K2);
      }
      break;

    case DEV_CORRECT2_K2:
      ShowLo(szCorrectQ1);
      QueryCorrectK();
      SetCurr(DEV_POSTCORRECT2_K2);
      break;

    case DEV_POSTCORRECT2_K2:
      //ShowLo(szCorrectQ2);
      MakePause(DEV_OPEN_K2);
      break;

    case DEV_OPEN_K2:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_K2);
      break;

    case DEV_OPENCANAL_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_K2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_K2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_K2:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionK();
      SetCurr(DEV_OPTION_K2);
      break;

    case DEV_OPTION_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_K2);
        else
          MakePause(DEV_POSTPASSWORD_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_K2);
        }
      }
      break;

    case DEV_POSTOPTION_K2:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_K2);
      break;

    case DEV_PASSWORD_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_K2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_K2);
        }
      }
      break;

    case DEV_POSTPASSWORD_K2:
      if ((boControlK != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_K2);
      else
        MakePause(DEV_POSTCORRECT_K2);
      break;

    case DEV_PREVTIME_K2:
      ShowPercent(53);

      cbRepeat = GetMaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_K2);
      break;

    case DEV_TIME_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_K2);
        }
      }
      break;

    case DEV_POSTTIME_K2:
      ShowPercent(54);

      cbRepeat = GetMaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_K2);
      break;

    case DEV_DATE_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_K2);
        }
      }
      break;


    case DEV_POSTDATE_K2:
      {
        uint iwDay1 = GetDayIndexMD(tiDig.bMonth, tiDig.bDay);
        ulong dwSecond1 = GetSecondIndex(tiDig);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_K2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_K2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_K2:
      cbRepeat = GetMaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_K2);
      break;

    case DEV_POSTCONTROL_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_K2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_K2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_K2);
        }
      }
      break;


    case DEV_POSTCORRECT_K2:
      iwMajor = 0;
      ibMinor = 0;

      wBaseCurr = 0;
      tiDigPrev = tiCurr;

      cbRepeat = GetMaxRepeats();
      QueryHeaderK();
      SetCurr(DEV_HEADER_K2);
      break;

    case DEV_HEADER_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 10)                        // если нет требуемой записи
        {
          if (iwMajor >= 480)                           // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            uchar h;
            for (h=0; h<48; h++)
            {
              wBaseCurr++;

              sprintf(szLo," выключено: %-4u   ",++iwMajor);

              iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
              ShowProgressDigHou();
            }

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_K2);
          }
        }
        else
        {
          ReadHeaderK();

          iwMajor = 0;                                  // если есть требуемая запись
          MakePause(DEV_POSTHEADER_K2);
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

          QueryHeaderK();
          SetCurr(DEV_HEADER_K2);
        }
      }
      break;

    case DEV_POSTHEADER_K2:
      if (++ibMinor < ibMinorMax)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderK();
        SetCurr(DEV_HEADER_K2);
      }
      else
      {
        ibMinor = 0;
        if (ReadDataK() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_K2);
      }
      break;

    case DEV_DATA_K2:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderK();
        SetCurr(DEV_HEADER_K2);
      }
      break;

#endif
