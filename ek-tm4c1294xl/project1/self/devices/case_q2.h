
#ifndef SKIP_Q

    case DEV_START_Q2:
      if ((boControlQ == false) && (fCurrCtrl == true))
      {
        ShowLo(szCorrectQ1);
        QueryCorrectQ();
        SetCurr(DEV_CORRECT_Q2);
      }
      else MakePause(DEV_OPEN_Q2);
      break;

    case DEV_CORRECT_Q2:
      ShowLo(szCorrectQ2);
      MakePause(DEV_OPEN_Q2);
      break;

    case DEV_OPEN_Q2:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_Q2);
      break;

    case DEV_OPENCANAL_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_Q2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_Q2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_Q2:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q2);
      break;

    case DEV_OPTION_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_Q2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionQ();
          SetCurr(DEV_OPTION_Q2);
        }
      }
      break;

    case DEV_POSTOPTION_Q2:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_Q2);
      break;

    case DEV_PASSWORD_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if ((boControlQ != false) && (fCurrCtrl == true))
          MakePause(DEV_POSTPASSWORD_Q2);
        else
          MakePause(DEV_POSTCORRECT_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_Q2);
        }
      }
      break;

    case DEV_POSTPASSWORD_Q2:
      ShowPercent(53);

      cbRepeat = GetMaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_Q2);
      break;

    case DEV_TIME_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_Q2);
        }
      }
      break;

    case DEV_POSTTIME_Q2:
      ShowPercent(54);

      cbRepeat = GetMaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_Q2);
      break;

    case DEV_DATE_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_Q2);
        }
      }
      break;

/*
    case DEV_POSTDATE_Q2:
      wBuffD  = GetDayIndex();              // количество дней с начала года ведомого счётчика
      dwBuffC = GetSecondIndex();           // количество секунд ведомого счётчика

      tiAlt = tiCurr;                       // текущие время/дата сумматора

      if (wBuffD != GetDayIndex())
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
      else
      {
        if (dwBuffC > GetSecondIndex())                                         // необходима коррекция времени ведомого счётчика назад
          ShowDeltaNeg();
        else
          ShowDeltaPos();

        if (dwBuffC < bMINORCORRECT_K)                                          // без коррекции
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_Q2); }
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // простая коррекция
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_Q2); }
        else
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
      }
      break;


    case DEV_CONTROL_Q2:
      cbRepeat = GetMaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_Q2);
      break;

    case DEV_POSTCONTROL_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_Q2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_Q2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_Q2);
        }
      }
      break;


    case DEV_POSTCORRECT_Q2:
      iwMajor = 0;
      ibMinor = 0;

      InitHeaderQ();

      cbRepeat = GetMaxRepeats();
      QueryHeaderQ();
      SetCurr(DEV_HEADER_Q2);
      break;

    case DEV_HEADER_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 10)                        // если нет требуемой записи
        {
          if (iwMajor >= 480)                           // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            for (i=0; i<48; i++)
            {
              wBaseCurr++;

              sprintf(szLo," выключено: %-4u   ",++iwMajor);

              iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
              ShowProgressDigHou();
            }

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_Q2);
          }
        }
        else
        {
          ReadHeaderQ();

          iwMajor = 0;                                  // если есть требуемая запись
          MakePause(DEV_POSTHEADER_Q2);
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

          QueryHeaderQ();
          SetCurr(DEV_HEADER_Q2);
        }
      }
      break;

    case DEV_POSTHEADER_Q2:
      if (++ibMinor < ibMinorMax)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      else
      {
        ibMinor = 0;
        if (ReadDataQ() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_Q2);
      }
      break;

    case DEV_DATA_Q2:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      break;
*/
#endif

