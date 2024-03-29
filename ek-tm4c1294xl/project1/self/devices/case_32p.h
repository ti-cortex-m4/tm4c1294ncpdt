#ifndef SKIP_32

    case DEV_START_32P:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpen32();
      SetCurr(DEV_OPENCANAL_32P);
      break;

    case DEV_OPENCANAL_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpen32() == 0)
          ErrorProfile();
        else if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_32P);
        else
          MakePause(DEV_POSTCORRECT_32P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen32();
          SetCurr(DEV_OPENCANAL_32P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_32P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTime32();
      SetCurr(DEV_TIME_32P);
      break;

    case DEV_TIME_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiProfile32 = ReadTime32();
        MakePause(DEV_POSTTIME_32P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime32();
          SetCurr(DEV_TIME_32P);
        }
      }
      break;


    case DEV_POSTTIME_32P:
      {
        ulong dwSecond1 = GetSecondIndex(tiProfile32);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiProfile32, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_32P); }
          else if (GetCurrHouIndex() == (tiProfile32.bHour*2 + tiProfile32.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_32P);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;

    case DEV_CONTROL_32P:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_32P);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControl32(tiCurr);
        SetCurr(DEV_POSTCONTROL_32P);
      }
      break;

    case DEV_POSTCONTROL_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_32P);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTCORRECT_32P); // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl32(tiCurr);
          SetCurr(DEV_POSTCONTROL_32P);
        }
      }
      break;


    case DEV_POSTCORRECT_32P:
      Clear();

      cbRepeat = MaxRepeats();
      QueryTop32();
      SetCurr(DEV_TOP_32P);
      break;

    case DEV_TOP_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTOP_32P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTop32();
          SetCurr(DEV_TOP_32P);
        }
      }
      break;

    case DEV_POSTTOP_32P:
      if (ReadTop32() == false) DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader32();
        SetCurr(DEV_HEADER_32P);
      }
      break;

    case DEV_HEADER_32P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_32P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader32();
          SetCurr(DEV_HEADER_32P);
        }
      }
      break;

    case DEV_POSTHEADER_32P:
      if (ReadHeader32() == false)
        DoneProfile();
      else if (DecIndex32() == false)
        DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader32();
        SetCurr(DEV_HEADER_32P);
      }
      break;

#endif
