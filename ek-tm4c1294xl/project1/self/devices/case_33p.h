#ifndef SKIP_33

    case DEV_START_33P:
      cbCorrects = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpen33();
      SetCurr(DEV_OPENCANAL_33P);
      break;

    case DEV_OPENCANAL_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpen33() == 0)
          ErrorProfile();
        else if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_33P);
        else
          MakePause(DEV_POSTCORRECT_33P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen33();
          SetCurr(DEV_OPENCANAL_33P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_33P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTime33();
      SetCurr(DEV_TIME_33P);
      break;

    case DEV_TIME_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiProfile33 = ReadTime33();
        MakePause(DEV_POSTTIME_33P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime33();
          SetCurr(DEV_TIME_33P);
        }
      }
      break;


    case DEV_POSTTIME_33P:
      {
        ulong dwSecond1 = GetSecondIndex(tiProfile33);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiProfile33, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_33P); }
          else if (GetCurrHouIndex() == (tiProfile33.bHour*2 + tiProfile33.bMinute/30))       // простая коррекция
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_33P);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CONTROL_33P:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_33P);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryControl33(tiCurr);
        SetCurr(DEV_POSTCONTROL_33P);
      }
      break;

    case DEV_POSTCONTROL_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_33P);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTCORRECT_33P); // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl33(tiCurr);
          SetCurr(DEV_POSTCONTROL_33P);
        }
      }
      break;


    case DEV_POSTCORRECT_33P:
      Clear();

      cbRepeat = GetMaxRepeats();
      QueryTop33();
      SetCurr(DEV_TOP_33P);
      break;

    case DEV_TOP_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTOP_33P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTop33();
          SetCurr(DEV_TOP_33P);
        }
      }
      break;

    case DEV_POSTTOP_33P:
      if (ReadTop33() == false) DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeader33();
        SetCurr(DEV_HEADER_33P);
      }
      break;

    case DEV_HEADER_33P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_33P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader33();
          SetCurr(DEV_HEADER_33P);
        }
      }
      break;

    case DEV_POSTHEADER_33P:
      if (ReadHeader33() == false)
        DoneProfile();
      else if (DecIndex33() == false)
        DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeader33();
        SetCurr(DEV_HEADER_33P);
      }
      break;

#endif
