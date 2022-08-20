
#ifndef SKIP_B

    case DEV_START_B2:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B2);
      break;

    case DEV_OPENCANAL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
      {
        if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_B2);
        else
          MakePause(DEV_POSTCORRECT_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_B2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTimeB();
      SetCurr(DEV_TIME_B2);
      break;

    case DEV_TIME_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueB = ReadTimeB();
        MakePause(DEV_POSTTIME_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeB();
          SetCurr(DEV_TIME_B2);
        }
      }
      break;


    case DEV_POSTTIME_B2:
      {
        ulong dwSecond1 = GetSecondIndex(tiValueB);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiValueB, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);

          if (dwDelta < GetCorrectLimit())                                        // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
          else if (dwDelta < bMAJORCORRECT_B)                                     // простая коррекция
          {
            if (cbCorrects == 0)
            {
              bDeltaOld = (uchar)dwDelta;
              (boShowMessages == true) ? DelayMsg() : DelayInf();
              ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_B2);
            }
            else
            {
              bDeltaNew = (uchar)dwDelta;
              if ((bDeltaNew < bDeltaOld) && (cbCorrects < 100))
              {
                bDeltaOld = bDeltaNew;
                cbCorrects++;
                MakePause(DEV_POSTOPENCANAL_B2);
              }
              else if (GetCurrHouIndex() == (tiValueB.bHour*2 + tiValueB.bMinute/30))
              { ShowLo(szCorrectSkip); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
              else
              { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_B2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControlB();
        SetCurr(DEV_POSTCONTROL_B2);
      }
      break;

    case DEV_POSTCONTROL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_B2);   // да !
        else
        {
          DelayOff(); // ErrorLink();
          cbRepeat--;

          QueryControlB();
          SetCurr(DEV_POSTCONTROL_B2);
        }
      }
      break;
/*
    case DEV_MANAGE_B2:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = MaxRepeats();
        QueryManageB();
        SetCurr(DEV_POSTMANAGE_B2);
      }
      break;

    case DEV_POSTMANAGE_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_B2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryManageB();
          SetCurr(DEV_POSTMANAGE_B2);
        }
      }
      break;
*/

    case DEV_POSTCORRECT_B2:
      Clear();

      cbRepeat = MaxRepeats();
      QueryVersionB();
      SetCurr(DEV_VERSION_B2);
      break;

    case DEV_VERSION_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionB();
        MakePause(DEV_POSTVERSION_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionB();
          SetCurr(DEV_VERSION_B2);
        }
      }
      break;

    case DEV_POSTVERSION_B2:
      Clear();

      cbRepeat = MaxRepeats();
      QueryTopB();
      SetCurr(DEV_TOP_B2);
      break;

    case DEV_TOP_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (TestVersionB710()) ReadTopBx17(); else ReadTopBOld();
        MakePause(DEV_POSTTOP_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTopB();
          SetCurr(DEV_TOP_B2);
        }
      }
      break;

    case DEV_POSTTOP_B2:
      cbIteration = 0;
      if (diCurr.bDevice == 2)
      {
        if (TestVersionB710())
        {
          cbRepeat = MaxRepeats();
          QueryHeaderBx17();
          SetCurr(DEV_HEADER_B2x17);
        }
        else
        {
          if (boShortProfileB)
          {
            ShowLo(szProfile2x1); DelayInf();

            cbRepeat = MaxRepeats();
            QueryHeaderB();
            SetCurr(DEV_HEADER_B2);
          }
          else
          {
            ShowLo(szProfile2x16); DelayInf();

            cbRepeat = MaxRepeats();
            QueryHeaderBx16();
            SetCurr(DEV_HEADER_B2x16);
          }
        }
      }
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeaderB_Plus(bBLOCKS_B);
        SetCurr(DEV_HEADER_B2PLUS);
      }
      break;

    case DEV_HEADER_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2);
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_B2);
/*
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }*/
      }
      break;

    case DEV_ERROR_B2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bITERATIONS) ErrorProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryIdB();
        SetCurr(DEV_POSTERROR_B2);
      }
      break;

    case DEV_POSTERROR_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdB() == 1)
        {
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_B2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdB();
          SetCurr(DEV_POSTERROR_B2);
        }
      }
      break;

    case DEV_POSTHEADER_B2:
      cbIteration = 0;
      NewBoundsAbs16(wBaseCurr);
      if (ReadHeaderB(0,0) == 0)
        DoneProfile();
      else
      {
        (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);

        cbRepeat = MaxRepeats();
        QueryHeaderB();
        SetCurr(DEV_HEADER_B2);
      }
      break;


    // ПРТ-М230
    case DEV_HEADER_B2PLUS:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2PLUS);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
      break;

    case DEV_POSTHEADER_B2PLUS:
    {
      uchar i;
      for (i=0; i<bBLOCKS_B; i++)
        if (TestHeaderB(i) == 0) break;

      if (i != bBLOCKS_B)
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
      else
      {
        NewBoundsAbs16(wBaseCurr);
        for (i=0; i<bBLOCKS_B; i++)
        {
          if (ReadHeaderB(i,1) == 0) break;
          (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
        }

        if (i != bBLOCKS_B)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
    }
      break;


    // Меркурий-233 блоками по 17 получасов
    case DEV_HEADER_B2x17:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2x17);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBx17();
          SetCurr(DEV_HEADER_B2x17);
        }
      }
      break;

    case DEV_POSTHEADER_B2x17:
      {
        NewBoundsAbs32(dwBaseCurr);

        uchar i;
        for (i=0; i<17; i++)
        {
          if (ReadHeaderBx17(i,1) == 0) break;
          (dwBaseCurr == 0) ? (dwBaseCurr = 0x1FFF0) : (dwBaseCurr -= 0x0010);
        }

        if (i != 17)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderBx17();
          SetCurr(DEV_HEADER_B2x17);
        }
      }
      break;


    // Меркурий-230 блоками по 16 получасов
    case DEV_HEADER_B2x16:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2x16);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBx16();
          SetCurr(DEV_HEADER_B2x16);
        }
      }
      break;

    case DEV_POSTHEADER_B2x16:
      {
        NewBoundsAbs16(dwBaseCurr);

        uchar i;
        for (i=0; i<PROFILE2X16_SIZE; i++)
        {
          if (ReadHeaderBx16(i,1) == 0) break;
          (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
        }

        if (i != PROFILE2X16_SIZE)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderBx16();
          SetCurr(DEV_HEADER_B2x16);
        }
      }
      break;

#endif
