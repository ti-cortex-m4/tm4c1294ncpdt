
#ifndef SKIP_38

    case DEV_START_38P:
       if (fCurrCtrl == true)
         MakePause(DEV_PREVTIME1_38P);
       else
        MakePause(DEV_PREVTIME2_38P);    
      break;


    // ������ ������� ��� ��������� ��������
    case DEV_PREVTIME1_38P:
      cbRepeat = MaxRepeats();
      QueryTime38();
      SetCurr(DEV_TIME1_38P);
      break;

    case DEV_TIME1_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue38 = ReadTime38();
        dwValue38 = DateToHouIndex(tiValue38);
        MakePause(DEV_POSTTIME1_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime38();
          SetCurr(DEV_TIME1_38P);
        }
      }
      break;

    case DEV_POSTTIME1_38P:
      {
        if (DifferentDay(tiValue38, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // ���� �� ���������, ��������� ����������
        else
        {
          ulong dwSecond1 = GetSecondIndex(tiValue38);
          ulong dwSecond2 = GetSecondIndex(tiCurr);
          
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);
          if (dwDelta < GetCorrectLimit()) {
            ShowLo(szCorrectNo); DelayInf();
            MakePause(DEV_PREVTIME2_38P); // ��� ���������
          }
          else if (GetCurrHouIndex() == (tiValue38.bHour*2 + tiValue38.bMinute/30))
          {
            if (boControlQ == false) {
              SetCorrectSecond38(dwSecond2 - dwSecond1);
              ShowLo(szCorrectYes); DelayInf();
              MakePause(DEV_PREVAUTHKEY1_38P); // ��������� �������
            } else {
              ShowLo(szManageYes); DelayInf();
              MakePause(DEV_PREVAUTHKEY2_38P); // ��������� �������
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;


// ������ ��������� �������
    case DEV_PREVAUTHKEY1_38P:
      cbRepeat = MaxRepeats();
      QueryAuthRequest38();
      SetCurr(DEV_AUTHKEY1_38P);
      break;

    case DEV_AUTHKEY1_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthRequest38();
        MakePause(DEV_POSTAUTHKEY1_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthRequest38();
          SetCurr(DEV_AUTHKEY1_38P);
        }
      }
      break;


    case DEV_POSTAUTHKEY1_38P:
      cbRepeat = MaxRepeats();
      QueryAuthResponse38();
      SetCurr(DEV_AUTHREQ1_38P);
      break;

    case DEV_AUTHREQ1_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bAuth = ReadAuthResponse38();
        if (bAuth == 0)
          MakePause(DEV_PREVCORRECT_38P);
        else {
          Clear(); sprintf(szLo+2,"������: %u ?",bAuth); DelayMsg();
          ErrorProfile();
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthResponse38();
          SetCurr(DEV_AUTHREQ1_38P);
        }
      }
      break;


    case DEV_PREVCORRECT_38P:
      cbRepeat = MaxRepeats();
      QueryCorrect38();
      SetCurr(DEV_CORRECT_38P);
      break;

    case DEV_CORRECT_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bCorrect = ReadCorrect38();
        if (bCorrect != 0) {
          Clear(); sprintf(szLo+1,"���������: %u ?",bCorrect); DelayMsg();
        }

        MakePause(DEV_PREVTIME2_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryCorrect38();
          SetCurr(DEV_CORRECT_38P);
        }
      }
      break;
// ����� ��������� �������

// ������ ��������� �������
    case DEV_PREVAUTHKEY2_38P:
      cbRepeat = MaxRepeats();
      QueryAuthRequest38();
      SetCurr(DEV_AUTHKEY2_38P);
      break;

    case DEV_AUTHKEY2_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadAuthRequest38();
        MakePause(DEV_POSTAUTHKEY2_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthRequest38();
          SetCurr(DEV_AUTHKEY2_38P);
        }
      }
      break;


    case DEV_POSTAUTHKEY2_38P:
      cbRepeat = MaxRepeats();
      QueryAuthResponse38();
      SetCurr(DEV_AUTHREQ2_38P);
      break;

    case DEV_AUTHREQ2_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bAuth = ReadAuthResponse38();
        if (bAuth == 0)
          MakePause(DEV_PREVMANAGE_38P);
        else {
          Clear(); sprintf(szLo+2,"������: %u ?",bAuth); DelayMsg();
          ErrorProfile();
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryAuthResponse38();
          SetCurr(DEV_AUTHREQ2_38P);
        }
      }
      break;


    case DEV_PREVMANAGE_38P:
      cbRepeat = MaxRepeats();
      QueryManage38();
      SetCurr(DEV_MANAGE_38P);
      break;

    case DEV_MANAGE_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        uchar bManage = ReadManage38();
        if (bManage != 0) {
          Clear(); sprintf(szLo+1,"���������: %u ?",bManage); DelayMsg();
        }

        MakePause(DEV_PREVTIME2_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryManage38();
          SetCurr(DEV_MANAGE_38P);
        }
      }
      break;
// ����� ��������� �������

// ������ ������� ��� ������ ��������
    case DEV_PREVTIME2_38P:
      cbRepeat = MaxRepeats();
      QueryTime38();
      SetCurr(DEV_TIME2_38P);
      break;

    case DEV_TIME2_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue38 = ReadTime38();
        dwValue38 = DateToHouIndex(tiValue38);
        MakePause(DEV_INITHEADER_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime38();
          SetCurr(DEV_TIME2_38P);
        }
      }
      break;


    case DEV_INITHEADER_38P:
      InitHeader38();
      MakePause(DEV_PAUSE_38P);
      break;

    case DEV_PAUSE_38P:
      {
        ulong dwSecNow = DateToSecIndex(tiCurr);
        ulong dwHou = DateToHouIndex(tiCurr);
        ulong dwSecPrev = DateToSecIndex(HouIndexToDate(dwHou));
        ulong dwSecNext = DateToSecIndex(HouIndexToDate(dwHou + 1));
        const char bGap = 30;
        bool f1 = (dwSecNext - dwSecNow < bGap);
        bool f2 = (dwSecNow - dwSecPrev < bGap);
        if (f1 || f2)
        {
          Clear();
          uchar bDelta = f1 ? bGap + (dwSecNext - dwSecNow) : bGap - (dwSecNow - dwSecPrev);
          sprintf(szLo+3, "�����: %u", bDelta);
          MakeLongPause(DEV_PAUSE_38P, 1);
        }
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeader38();
          SetCurr(DEV_HEADER_38P);
        }
      }
      break;

    case DEV_HEADER_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadData38() == false)
          DoneProfile();
        else
          MakePause(DEV_PAUSE_38P);
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

#endif
