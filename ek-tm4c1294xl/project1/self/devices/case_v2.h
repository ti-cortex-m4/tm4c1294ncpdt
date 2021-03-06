
#ifndef SKIP_V

    case DEV_START_V2:
      cbRepeat = MaxRepeats();
      QueryVersionV();
      SetCurr(DEV_VERSION_V2);
      break;

    case DEV_VERSION_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadVersionV() == false)
        {
          ShowHi(szBadVersion);
          DelayMsg(); ErrorProfile();
        }
        else
        {
          if (boHideMessages == false)
            MakeLongPause(DEV_POSTVERSION_V2, 1);
          else
            MakePause(DEV_POSTVERSION_V2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionV();
          SetCurr(DEV_VERSION_V2);
        }
      }
      break;


    case DEV_POSTVERSION_V2:
      cbCorrects = 0;

      if (fCurrCtrl == true)
        MakePause(DEV_POSTOPENCANAL_V2);
      else
        MakePause(DEV_POSTCORRECT_V2);
      break;

    case DEV_POSTOPENCANAL_V2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTimeV();
      SetCurr(DEV_TIME_V2);
      break;

    case DEV_TIME_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeV();
        MakePause(DEV_POSTTIME_V2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeV();
          SetCurr(DEV_TIME_V2);
        }
      }
      break;


    case DEV_POSTTIME_V2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_V2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_V2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;

    case DEV_CONTROL_V2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_V2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControlV(tiCurr);
        SetCurr(DEV_POSTOPENCANAL_V2);
      }
      break;


    case DEV_POSTCORRECT_V2:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryTimeV();
      SetCurr(DEV_VALUE_V2);
      break;

    case DEV_VALUE_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        dwTimeV = DateToHouIndex(ReadTimeV());
        MakePause(DEV_POSTVALUE_V2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeV();
          SetCurr(DEV_VALUE_V2);
        }
      }
      break;

    case DEV_POSTVALUE_V2:
      ShowPercent(75);
      InitHeaderV();

      cbRepeat = MaxRepeats();
      QueryHeaderV();
      SetCurr(DEV_HEADER_V2);
      break;

    case DEV_HEADER_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_V2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderV();
          SetCurr(DEV_HEADER_V2);
        }
      }
      break;

    case DEV_POSTHEADER_V2:
      if (ReadHeaderV() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_V2);
      break;

    case DEV_DATA_V2:
      cbRepeat = MaxRepeats();
      QueryHeaderV();
      SetCurr(DEV_HEADER_V2);
      break;

#endif
