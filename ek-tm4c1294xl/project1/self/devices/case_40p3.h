

    case DEV_SCALER_O_40P:
      Clear(); ShowPercent(67);

      cbRepeat = MaxRepeats();
      QueryScaler_Profile40();
      SetCurr(DEV_SCALER_I_40P);
      break;

    case DEV_SCALER_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+19, QueryScaler_Profile40(), DEV_SCALER_I_40P)
        } else {
          if (ReadScaler_Profile40()) {
            MakePause(DEV_RR_SCALER_O_40P);
          } else {
            Error40(210+20);
            ErrorProfile();
          }
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+21, QueryScaler_Profile40(), DEV_SCALER_I_40P)
      }
      break;


    case DEV_RR_SCALER_O_40P:
      Clear(); ShowPercent(68);

      cbRepeat = MaxRepeats();
      RR_Profile40();
      SetCurr(DEV_RR_SCALER_I_40P);
      break;

    case DEV_RR_SCALER_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+22, RR_Profile40(), DEV_RR_SCALER_I_40P)
        } else {
          MakePause(DEV_INIT_40P);
        }  
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+23, RR_Profile40(), DEV_RR_SCALER_I_40P)
      }
      break;

