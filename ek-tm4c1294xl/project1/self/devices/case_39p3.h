

    case DEV_SCALER_O_39P:
      Clear(); ShowPercent(70);

      cbRepeat = MaxRepeats();
      QueryScaler_Profile39();
      SetCurr(DEV_SCALER_I_39P);
      break;

    case DEV_SCALER_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+19, QueryScaler_Profile39(), DEV_SCALER_I_39P)
        } else {
          if (ReadScaler_Profile39()) {
            MakePause(DEV_RR_SCALER_O_39P);
          } else {
            Error39(220+20);
            ErrorProfile();
          }
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+21, QueryScaler_Profile39(), DEV_SCALER_I_39P)
      }
      break;


    case DEV_RR_SCALER_O_39P:
      Clear(); ShowPercent(71);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_SCALER_I_39P);
      break;

    case DEV_RR_SCALER_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+22, RR_Profile39(), DEV_RR_SCALER_I_39P)
        } else {
          MakePause(DEV_INIT_39P);
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+23, RR_Profile39(), DEV_RR_SCALER_I_39P)
      }
      break;

