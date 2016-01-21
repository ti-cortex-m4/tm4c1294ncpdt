#ifndef SKIP_N31
/*
    case DEV_START_N31P:
      cbCorrects = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpenN31();
      SetCurr(DEV_OPENCANAL_N31P);
      break;

    case DEV_OPENCANAL_N31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpenN31() == 0)
          ErrorProfile();
        else if (fCurrCtrlHou == 1)
          MakePause(DEV_POSTOPENCANAL_N31P);
        else
          MakePause(DEV_POSTCORRECT_N31P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenN31();
          SetCurr(DEV_OPENCANAL_N31P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_N31P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1bu",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeN31();
      SetCurr(DEV_TIME_N31P);
      break;

    case DEV_TIME_N31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltN31();
        ReadTimeDigN31();
        MakePause(DEV_POSTTIME_N31P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeN31();
          SetCurr(DEV_TIME_N31P);
        }
      }
      break;


    case DEV_POSTTIME_N31P:
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
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_N31P); }
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // простая коррекция
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_N31P);  }
        else
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
      }
      break;

    case DEV_CONTROL_N31P:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_N31P);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryControlN31();
        SetCurr(DEV_POSTCONTROL_N31P);
      }
      break;

    case DEV_POSTCONTROL_N31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_N31P);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTCORRECT_N31P);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlN31();
          SetCurr(DEV_POSTCONTROL_N31P);
        }
      }
      break;


    case DEV_POSTCORRECT_N31P:
      Clear();

      cbRepeat = GetMaxRepeats();
      QueryTopN31();
      SetCurr(DEV_TOP_N31P);
      break;

    case DEV_TOP_N31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTOP_N31P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTopN31();
          SetCurr(DEV_TOP_N31P);
        }
      }
      break;

    case DEV_POSTTOP_N31P:
      if (ReadTopN31() == 0) DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderN31();
        SetCurr(DEV_HEADER_N31P);
      }
      break;

    case DEV_HEADER_N31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_N31P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderN31();
          SetCurr(DEV_HEADER_N31P);
        }
      }
      break;

    case DEV_POSTHEADER_N31P:
      if (ReadHeaderN31() == 0)
        DoneProfile();
      else if (DecIndexN31() == 0)
        DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderN31();
        SetCurr(DEV_HEADER_N31P);
      }
      break;
*/
#endif
