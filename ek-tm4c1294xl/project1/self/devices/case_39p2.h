

    case DEV_TIME_O_39P:
      Clear(); ShowPercent(64);

      cbRepeat = MaxRepeats();
      QueryTime_Profile39();
      SetCurr(DEV_TIME_I_39P);
      break;

    case DEV_TIME_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+6);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            QueryTime_Profile39();
            SetCurr(DEV_TIME_I_39P);
          }
        } else {
          ReadTime_Profile39();
          MakePause(DEV_RR_TIME_O_39P);
        }
      } else {
        Error39(220+7);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          QueryTime_Profile39();
          SetCurr(DEV_TIME_I_39P);
        }
      }
      break;


    case DEV_RR_TIME_O_39P:
      Clear(); ShowPercent(65);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_TIME_I_39P);
      break;

    case DEV_RR_TIME_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            RR_Profile39();
            SetCurr(DEV_RR_TIME_I_39P);
          }
        } else {
          MakePause(DEV_2_TIME_O_39P);
        }  
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          RR_Profile39();
          SetCurr(DEV_RR_TIME_I_39P);
        }
      }
      break;


    case DEV_CORRECT1_38P:
      {
        if (DifferentDay(tiValue39, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // даты не совпадают, коррекция невозможна
        else
        {
          ulong dwSecond1 = GetSecondIndex(tiValue39);
          ulong dwSecond2 = GetSecondIndex(tiCurr);
          
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);
          if (dwDelta < GetCorrectLimit()) {
            ShowLo(szCorrectNo); DelayInf();
            MakePause(DEV_2_TIME_O_39P); // без коррекции
          }
          else if (GetCurrHouIndex() == (tiValue39.bHour*2 + tiValue39.bMinute/30))
          {
            SetCorrectSecond38(dwSecond2 - dwSecond1);
            ShowLo(szCorrectYes); DelayInf();
            MakePause(DEV_CORRECT2_38P); // коррекция времени
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;

    case DEV_CORRECT2_38P:


    case DEV_2_TIME_O_39P:
      Clear(); ShowPercent(64);

      cbRepeat = MaxRepeats();
      QueryTime_Profile39();
      SetCurr(DEV_2_TIME_I_39P);
      break;

    case DEV_2_TIME_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+6);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            QueryTime_Profile39();
            SetCurr(DEV_2_TIME_I_39P);
          }
        } else {
          ReadTime_Profile39();
          MakePause(DEV_2_RR_TIME_O_39P);
        }
      } else {
        Error39(220+7);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          QueryTime_Profile39();
          SetCurr(DEV_2_TIME_I_39P);
        }
      }
      break;


    case DEV_2_RR_TIME_O_39P:
      Clear(); ShowPercent(65);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_2_RR_TIME_I_39P);
      break;

    case DEV_2_RR_TIME_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            RR_Profile39();
            SetCurr(DEV_2_RR_TIME_I_39P);
          }
        } else {
          MakePause(DEV_2_SCALER_O_39P);
        }  
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          RR_Profile39();
          SetCurr(DEV_2_RR_TIME_I_39P);
        }
      }
      break;
