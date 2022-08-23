

    case DEV_TIME1_O_40P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8, "%1u", GetCounter_Correct40()+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTime_Profile40();
      SetCurr(DEV_TIME1_I_40P);
      break;

    case DEV_TIME1_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+7, QueryTime_Profile40(), DEV_TIME1_I_40P)
        } else {
          ReadTime_Profile40();
          MakePause(DEV_RR_TIME1_O_40P);
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+8, QueryTime_Profile40(), DEV_TIME1_I_40P)
      }
      break;


    case DEV_RR_TIME1_O_40P:
      cbRepeat = MaxRepeats();
      RR_Profile40();
      SetCurr(DEV_RR_TIME1_I_40P);
      break;

    case DEV_RR_TIME1_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+9, RR_Profile40(), DEV_RR_TIME1_I_40P)
        } else {
          MakePause(DEV_CORRECT_40P);
        }  
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+10, RR_Profile40(), DEV_RR_TIME1_I_40P)
      }
      break;


    case DEV_CORRECT_40P:
      {
        time tmThat = GetTime_Profile40();
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
            MakePause(DEV_TIME2_O_40P); // без коррекции
          }
          else if (dwDelta < wLIMITCORRECT_40)
          {
            if (GetCounter_Correct40() == 0)
            {
              SaveFirstDelta_Current40(dwDelta);

              SetCorrectSecond40(dwSecondThis - dwSecondThat);
              ShowLo(szCorrectYes); DelayInf();
              MakePause(DEV_CORRECT_O_40P); // коррекция времени
            }
            else
            {
              if (CheckNextDelta_Current40(dwDelta))
              {
                SaveNextDelta_Current40();

                MakeLongPause(DEV_TIME1_O_40P, 1); // снова проверяем время
              }
              else if (GetCurrHouIndex() == (tmThat.bHour*2 + tmThat.bMinute/30))
              { ShowLo(szCorrectSkip); DelayInf(); MakePause(DEV_TIME2_O_40P); }
              else
              { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CORRECT_O_40P:
      cbRepeat = MaxRepeats();
      QueryCorrect_Profile40();
      SetCurr(DEV_CORRECT_I_40P);
      break;

    case DEV_CORRECT_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+11, QueryCorrect_Profile40(), DEV_CORRECT_I_40P)
        } else {
          MakePause(DEV_RR_CORRECT_O_40P);
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+12, QueryCorrect_Profile40(), DEV_CORRECT_I_40P)
      }
      break;


    case DEV_RR_CORRECT_O_40P:
      cbRepeat = MaxRepeats();
      RR_Profile40();
      SetCurr(DEV_RR_CORRECT_I_40P);
      break;

    case DEV_RR_CORRECT_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+13, RR_Profile40(), DEV_RR_CORRECT_I_40P)
        } else {
          MakeLongPause(DEV_TIME1_O_40P, 1); // снова проверяем время
        }  
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+14, RR_Profile40(), DEV_RR_CORRECT_I_40P)
      }
      break;


    case DEV_TIME2_O_40P:
      Clear(); ShowPercent(65);

      cbRepeat = MaxRepeats();
      QueryTime_Profile40();
      SetCurr(DEV_TIME2_I_40P);
      break;

    case DEV_TIME2_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+15, QueryTime_Profile40(), DEV_TIME2_I_40P)
        } else {
          ReadTime_Profile40();
          MakePause(DEV_RR_TIME2_O_40P);
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+16, QueryTime_Profile40(), DEV_TIME2_I_40P)
      }
      break;


    case DEV_RR_TIME2_O_40P:
      Clear(); ShowPercent(66);

      cbRepeat = MaxRepeats();
      RR_Profile40();
      SetCurr(DEV_RR_TIME2_I_40P);
      break;

    case DEV_RR_TIME2_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+17, RR_Profile40(), DEV_RR_TIME2_I_40P)
        } else {
          MakePause(DEV_SCALER_O_40P);
        }  
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+18, RR_Profile40(), DEV_RR_TIME2_I_40P)
      }
      break;
