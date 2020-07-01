

    case DEV_TIME1_O_39P:
      Clear(); ShowPercent(64);

      cbRepeat = MaxRepeats();
      QueryTime_Profile39();
      SetCurr(DEV_TIME1_I_39P);
      break;

    case DEV_TIME1_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+6, QueryTime_Profile39(), DEV_TIME1_I_39P)
        } else {
          ReadTime_Profile39();
          MakePause(DEV_RR_TIME1_O_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+7, QueryTime_Profile39(), DEV_TIME1_I_39P)
      }
      break;


    case DEV_RR_TIME1_O_39P:
      Clear(); ShowPercent(65);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_TIME1_I_39P);
      break;

    case DEV_RR_TIME1_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+0, RR_Profile39(), DEV_RR_TIME1_I_39P)
        } else {
          MakePause(DEV_CORRECT_39P);
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+0, RR_Profile39(), DEV_RR_TIME1_I_39P)
      }
      break;


    case DEV_CORRECT_39P:
      {
        time tmThat = GetTime_Profile39();
        if (DifferentDay(tmThat, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // даты не совпадают, коррекция невозможна
        else
        {
          ulong dwSecondThat = GetSecondIndex(tmThat);
          ulong dwSecondThis = GetSecondIndex(tiCurr);
          
          ShowDigitalDeltaTime(ibDig, dwSecondThat, dwSecondThis);

          ulong dwDelta = AbsLong(dwSecondThat - dwSecondThis);
          if (dwDelta < GetCorrectLimit()) {
            ShowLo(szCorrectNo); DelayInf();
            MakePause(DEV_TIME2_O_39P); // без коррекции
          }
          else if (GetCurrHouIndex() == (tmThat.bHour*2 + tmThat.bMinute/30))
          {
            SetCorrectSecond39(dwSecondThis - dwSecondThat);
            ShowLo(szCorrectYes); DelayInf();
            MakePause(DEV_CORRECT_O_39P); // коррекция времени
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CORRECT_O_39P:
      Clear(); ShowPercent(66);

      cbRepeat = MaxRepeats();
      QueryTime_Profile39();
      SetCurr(DEV_CORRECT_I_39P);
      break;

    case DEV_CORRECT_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+6, QueryTime_Profile39(), DEV_CORRECT_I_39P)
        } else {
          ReadTime_Profile39();
          MakePause(DEV_RR_TIME1_O_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+7, QueryTime_Profile39(), DEV_CORRECT_I_39P)
      }
      break;


    case DEV_RR_CORRECT_O_39P:
      Clear(); ShowPercent(67);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_CORRECT_I_39P);
      break;

    case DEV_RR_CORRECT_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+0, RR_Profile39(), DEV_RR_CORRECT_I_39P)
        } else {
          MakePause(DEV_TIME2_O_39P);
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+0, RR_Profile39(), DEV_RR_CORRECT_I_39P)
      }
      break;


    case DEV_TIME2_O_39P:
      Clear(); ShowPercent(68);

      cbRepeat = MaxRepeats();
      QueryTime_Profile39();
      SetCurr(DEV_TIME2_I_39P);
      break;

    case DEV_TIME2_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+6, QueryTime_Profile39(), DEV_TIME2_I_39P)
        } else {
          ReadTime_Profile39();
          MakePause(DEV_RR_TIME2_O_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+7, QueryTime_Profile39(), DEV_TIME2_I_39P)
      }
      break;


    case DEV_RR_TIME2_O_39P:
      Clear(); ShowPercent(69);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_TIME2_I_39P);
      break;

    case DEV_RR_TIME2_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+0, RR_Profile39(), DEV_RR_TIME2_I_39P)
        } else {
          MakePause(DEV_SCALER_O_39P);
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+0, RR_Profile39(), DEV_RR_TIME2_I_39P)
      }
      break;
