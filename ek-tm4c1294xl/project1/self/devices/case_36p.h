
#ifndef SKIP_36

    case DEV_START_36P:
//      if ((boControlQ == false) && (fCurrCtrl == true))
//        MakePause(DEV_PREVCORRECT_36P);
//      else
        MakePause(DEV_OPEN_36P);
      break;

    case DEV_PREVCORRECT_36P:
      if (tiCurr.bSecond < bMINORCORRECT_36) {
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
      if (IsSerial35())
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
      if (IsSerial35())
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
      if (IsSerial35())
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
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeProfile36();
      SetCurr35(DEV_TIME_36P);
      break;

    case DEV_TIME_36P:
      if (IsSerial35())
      {
        tiValue36 = ReadTime36();
        MakePause(DEV_POSTTIME_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeProfile36();
          SetCurr35(DEV_TIME_36P);
        }
      }
      break;

    case DEV_POSTTIME_36P:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateProfile36();
      SetCurr35(DEV_DATE_36P);
      break;

    case DEV_DATE_36P:
      if (IsSerial35())
      {
        tiValue36 = ReadDate36(tiValue36);
        dwValue36 = DateToHouIndex(tiValue36);
        MakePause(DEV_POSTDATE_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateProfile36();
          SetCurr35(DEV_DATE_36P);
        }
      }
      break;


    case DEV_POSTDATE_36P:
      if ((boControlQ != false) && (fCurrCtrl == true))
      {
        ulong dwSecond1 = GetSecondIndex(tiValue36);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiValue36, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_36P); }
          else if (GetCurrHouIndex() == (tiValue36.bHour*2 + tiValue36.bMinute/30)) // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_36P); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      else
        MakePause(DEV_POSTCORRECT_36P);
      break;


    case DEV_CONTROL_36P:
      cbRepeat = MaxRepeats();
      QueryControl36(tiCurr);
      SetCurr35(DEV_POSTCONTROL_36P);
      break;

    case DEV_POSTCONTROL_36P:
      if (IsSerial35())
        MakePause(DEV_POSTCORRECT_36P);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_36P);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl36(tiCurr);
          SetCurr35(DEV_POSTCONTROL_36P);
        }
      }
      break;


    case DEV_POSTCORRECT_36P:
      cwShutdown36 = 0;
      InitHeader36();

      ibLine36 = 0;
      if (SkipLine(ibDig, ibLine36) == true)
      {
        ReadHeader36_SkipLine(ibLine36);
        ibLine36++;
      }

      cbRepeat = MaxRepeats();
      QueryHeader36();
      SetCurr35(DEV_HEADER_36P);
      break;

    case DEV_HEADER_36P:
      if (IsSerial35())
      {
        if (IndexInBuff() == 3)                        // ���� ��� ��������� ������
        {
          if (cwShutdown36 >= GetMaxShutdown())        // ���� ������� ���� ��������� ������� �����
            DoneProfile();
          else
          {
            cwShutdown36 += 6;
            sprintf(szLo," ���������: %-4u   ",cwShutdown36);

            iwDigHou = (wHOURS+iwHardHou-wProfile36)%wHOURS;
            ShowProgressDigHou();

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else if (++wProfile36 > wHOURS)
              DoneProfile();
            else
              MakePause(DEV_DATA_36P);
          }
        }
        else
        {
          ReadHeader36();

          if (SkipLine(ibDig, ibLine36+1) == true)
          {
            ReadHeader36_SkipLine(ibLine36+1);
            ibLine36++;
          }

          cwShutdown36 = 0;                            // ���� ���� ��������� ������
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

        if (SkipLine(ibDig, ibLine36) == true)
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
