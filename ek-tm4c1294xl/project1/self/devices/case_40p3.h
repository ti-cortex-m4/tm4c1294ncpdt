

    case DEV_SCALER_O_40P:
      Clear(); ShowPercent(67);

      cbRepeat = MaxRepeats();
      QueryScaler_Profile39();
      SetCurr(DEV_SCALER_I_40P);
      break;

    case DEV_SCALER_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(210+19, QueryScaler_Profile39(), DEV_SCALER_I_40P)
        } else {
          if (ReadScaler_Profile39()) {
            MakePause(DEV_RR_SCALER_O_40P);
          } else {
            Error40(210+20);
            ErrorProfile();
          }
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+21, QueryScaler_Profile39(), DEV_SCALER_I_40P)
      }
      break;


    case DEV_RR_SCALER_O_40P:
      Clear(); ShowPercent(68);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_SCALER_I_40P);
      break;

    case DEV_RR_SCALER_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(210+22, RR_Profile39(), DEV_RR_SCALER_I_40P)
        } else {
          MakePause(DEV_INIT_40P);
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+23, RR_Profile39(), DEV_RR_SCALER_I_40P)
      }
      break;
