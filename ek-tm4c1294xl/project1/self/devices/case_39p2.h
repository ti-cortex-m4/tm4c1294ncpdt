

    case DEV_TIME_O_39P:
      Clear(); ShowPercent(54);

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
      Clear(); ShowPercent(55);

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
          MakePause(DEV_SCALER_O_39P);
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

