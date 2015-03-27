
#ifndef SKIP_B

    case DEV_START_B2:
      cbCorrects = 0;

      cbRepeat = bMINORREPEATS;
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B2);
      break;

    case DEV_OPENCANAL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
      {
        if (fCurrCtrl == 1)
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

      cbRepeat = bMINORREPEATS;
      QueryTimeB();
      SetCurr(DEV_TIME_B2);
      break;

    case DEV_TIME_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltB();
        ReadTimeDigB();
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
      uint iwDay1 = GetDayIndexMD(tiAlt.bMonth, tiAlt.bDay);                    // количество дней с начала года ведомого счётчика
      ulong dwSecond1 = GetSecondIndex(&tiAlt);                                 // количество секунд ведомого счётчика

      uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);                  // количество дней с начала года сумматора
      ulong dwSecond2 = GetSecondIndex(&tiCurr);                                // количество секунд сумматора

      if (iwDay1 != iwDay2)
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
      else
      {
        slong dwDelta = dwSecond1 - dwSecond2;
        ShowDeltaTime2(ibDig, dwDelta);

        dwDelta = (dwDelta < 0 ? -dwDelta : dwDelta);

        if (dwDelta < MinorCorrect())                                           // без коррекции
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
        else if (dwDelta < bMAJORCORRECT_B)                                     // простая коррекция
        {
          if (cbCorrects == 0)
          {
            bDeltaOld = (uchar)dwDelta;
            (boShowMessages == TRUE) ? DelayMsg() : DelayInf();
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
            else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))
            { ShowLo(szCorrectNext); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
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
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = bMINORREPEATS;
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
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = bMINORREPEATS;
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

      cbRepeat = bMINORREPEATS;
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

      cbRepeat = bMINORREPEATS;
      QueryTopB();
      SetCurr(DEV_TOP_B2);
      break;

    case DEV_TOP_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (TestVersionB710()) ReadTopBNew(); else ReadTopBOld();
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
      cbRepeat2 = 0;
      if (diCurr.bDevice == 2)
      {
        if (TestVersionB710())
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
        else
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
      }
      else
      {
        cbRepeat = bMINORREPEATS;
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

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else
      {
        cbRepeat = bMINORREPEATS;
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
      cbRepeat2 = 0;
      NewBoundsAbs(wBaseCurr);
      if (ReadHeaderB(0,0) == 0)
        DoneProfile();
      else
      {
        (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);

        cbRepeat = bMINORREPEATS;
        QueryHeaderB();
        SetCurr(DEV_HEADER_B2);
      }
      break;

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
        NewBoundsAbs(wBaseCurr);
        for (i=0; i<bBLOCKS_B; i++)
        {
          if (ReadHeaderB(i,1) == 0) break;
          (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
        }

        if (i != bBLOCKS_B)
          DoneProfile();
        else
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
    }
      break;

    case DEV_HEADER_B2NEXT:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2NEXT);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
      }
      break;

    case DEV_POSTHEADER_B2NEXT:
    {
        NewBoundsAbs2(dwBaseCurr);
        uchar i;
        for (i=0; i<17; i++)
        {
          if (ReadHeaderBNew(i,1) == 0) break;
          (dwBaseCurr == 0) ? (dwBaseCurr = 0x1FFF0) : (dwBaseCurr -= 0x0010);
        }

        if (i != 17)
          DoneProfile();
        else
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
    }
      break;

#endif
