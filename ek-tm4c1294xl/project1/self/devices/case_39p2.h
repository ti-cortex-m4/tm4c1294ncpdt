

    case DEV_TIME1_O_39P:
      MakePause(DEV_TIME2_O_39P); // TODO
/*
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",GetCounter_Correct39()+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTime_Profile39();
      SetCurr(DEV_TIME1_I_39P);
*/
      break;

    case DEV_TIME1_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+7, QueryTime_Profile39(), DEV_TIME1_I_39P)
        } else {
          ReadTime_Profile39();
          MakePause(DEV_RR_TIME1_O_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+8, QueryTime_Profile39(), DEV_TIME1_I_39P)
      }
      break;


    case DEV_RR_TIME1_O_39P:
//      Clear(); ShowPercent(65);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_TIME1_I_39P);
      break;

    case DEV_RR_TIME1_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+9, RR_Profile39(), DEV_RR_TIME1_I_39P)
        } else {
          MakePause(DEV_CORRECT_39P);
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+10, RR_Profile39(), DEV_RR_TIME1_I_39P)
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
          if (dwDelta < GetCorrectLimit())
          {
            ShowLo(szCorrectNo); DelayInf();
            MakePause(DEV_TIME2_O_39P); // без коррекции
          }
          else if (dwDelta < bMAJORCORRECT_39)
          {
            if (GetCounter_Correct39() == 0)
            {
              SaveFirstDelta_Current39(dwDelta);

              SetCorrectSecond39(dwSecondThis - dwSecondThat);
              ShowLo(szCorrectYes); DelayInf();
              MakePause(DEV_CORRECT_O_39P); // коррекция времени
            }
            else
            {
              if (CheckNextDelta_Current39(dwDelta))
              {
                SaveNextDelta_Current39();

                MakePause(DEV_TIME1_O_39P); // снова проверяем время
              }
              else if (GetCurrHouIndex() == (tmThat.bHour*2 + tmThat.bMinute/30))
              { ShowLo(szCorrectSkip); DelayInf(); MakePause(DEV_TIME2_O_39P); }
              else
              { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CORRECT_O_39P:
//      Clear(); ShowPercent(66);

      cbRepeat = MaxRepeats();
      QueryCorrect_Profile39();
      SetCurr(DEV_CORRECT_I_39P);
      break;

    case DEV_CORRECT_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+11, QueryCorrect_Profile39(), DEV_CORRECT_I_39P)
        } else {
          MakePause(DEV_RR_CORRECT_O_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+12, QueryCorrect_Profile39(), DEV_CORRECT_I_39P)
      }
      break;


    case DEV_RR_CORRECT_O_39P:
//      Clear(); ShowPercent(67);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_CORRECT_I_39P);
      break;

    case DEV_RR_CORRECT_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+13, RR_Profile39(), DEV_RR_CORRECT_I_39P)
        } else {
          MakePause(DEV_TIME1_O_39P); // снова проверяем время
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+14, RR_Profile39(), DEV_RR_CORRECT_I_39P)
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
          PROFILE39_REPEAT_OR_ERROR(220+15, QueryTime_Profile39(), DEV_TIME2_I_39P)
        } else {
          ReadTime_Profile39();
          MakePause(DEV_RR_TIME2_O_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+16, QueryTime_Profile39(), DEV_TIME2_I_39P)
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
          PROFILE39_REPEAT_OR_ERROR(220+17, RR_Profile39(), DEV_RR_TIME2_I_39P)
        } else {
          MakePause(DEV_SCALER_O_39P);
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+18, RR_Profile39(), DEV_RR_TIME2_I_39P)
      }
      break;
