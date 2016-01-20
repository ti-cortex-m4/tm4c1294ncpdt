#ifndef SKIP_N31

    case DEV_START_G2:
      cbCorrects = 0;

      cbRepeat = bMINORREPEATS;
      QueryOpenG();
      SetCurr(DEV_OPENCANAL_G2);
      break;

    case DEV_OPENCANAL_G2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpenG() == 0)
          ErrorProfile();
        else if (fCurrCtrlHou == 1)
          MakePause(DEV_POSTOPENCANAL_G2);
        else
          MakePause(DEV_POSTCORRECT_G2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenG();
          SetCurr(DEV_OPENCANAL_G2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_G2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1bu",cbCorrects+1); DelayInf();

      cbRepeat = bMINORREPEATS;
      QueryTimeG();
      SetCurr(DEV_TIME_G2);
      break;

    case DEV_TIME_G2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltG();
        ReadTimeDigG();
        MakePause(DEV_POSTTIME_G2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeG();
          SetCurr(DEV_TIME_G2);
        }
      }
      break;


    case DEV_POSTTIME_G2:
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

        if (dwBuffC < bMINORCORRECT_G)                                          // без коррекции
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_G2); }
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // простая коррекция
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_G2);  }
        else
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
      }
      break;

    case DEV_CONTROL_G2:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_G2);
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryControlG();
        SetCurr(DEV_POSTCONTROL_G2);
      }
      break;

    case DEV_POSTCONTROL_G2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_G2);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTCORRECT_G2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlG();
          SetCurr(DEV_POSTCONTROL_G2);
        }
      }
      break;


    case DEV_POSTCORRECT_G2:
      Clear();

      cbRepeat = bMINORREPEATS;
      QueryTopG();
      SetCurr(DEV_TOP_G2);
      break;

    case DEV_TOP_G2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTOP_G2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTopG();
          SetCurr(DEV_TOP_G2);
        }
      }
      break;

    case DEV_POSTTOP_G2:
      if (ReadTopG() == 0) DoneProfile();
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryHeaderG();
        SetCurr(DEV_HEADER_G2);
      }
      break;

    case DEV_HEADER_G2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_G2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderG();
          SetCurr(DEV_HEADER_G2);
        }
      }
      break;

    case DEV_POSTHEADER_G2:
      if (ReadHeaderG() == 0)
        DoneProfile();
      else if (DecIndexG() == 0)
        DoneProfile();
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryHeaderG();
        SetCurr(DEV_HEADER_G2);
      }
      break;

#endif
