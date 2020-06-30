

    case DEV_SCALER_O_39P:
      Clear(); ShowPercent(66);

      cbRepeat = MaxRepeats();
      QueryScaler_Profile39();
      SetCurr(DEV_SCALER_I_39P);
      break;

    case DEV_SCALER_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+6);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            QueryScaler_Profile39();
            SetCurr(DEV_SCALER_I_39P);
          }
        } else {
          if (ReadScaler_Profile39()) {
            MakePause(DEV_RR_SCALER_O_39P);
          } else {
            Error39(220+0);
            ErrorProfile();
          }
        }
      } else {
        Error39(220+7);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          QueryScaler_Profile39();
          SetCurr(DEV_SCALER_I_39P);
        }
      }
      break;


    case DEV_RR_SCALER_O_39P:
      Clear(); ShowPercent(67);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_SCALER_I_39P);
      break;

    case DEV_RR_SCALER_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            RR_Profile39();
            SetCurr(DEV_RR_SCALER_I_39P);
          }
        } else {
          MakePause(DEV_INIT_39P);
        }  
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          RR_Profile39();
          SetCurr(DEV_RR_SCALER_I_39P);
        }
      }
      break;

