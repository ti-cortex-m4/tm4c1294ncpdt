

    case DEV_SCALER_O_39P:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryScaler39_Profile();
      SetCurr(DEV_SCALER_I_39P);
      break;

    case DEV_SCALER_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+6);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            QueryScaler39_Profile();
            SetCurr(DEV_SCALER_I_39P);
          }
        } else {
          ReadScaler39_Profile();
          MakePause(DEV_RR_SCALER_O_39P);
        }
      } else {
        Error39(220+7);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          QueryScaler39_Profile();
          SetCurr(DEV_SCALER_I_39P);
        }
      }
      break;


    case DEV_RR_SCALER_O_39P:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_RR_SCALER_I_39P);
      break;

    case DEV_RR_SCALER_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            Query39_RR_Profile();
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
          Query39_RR_Profile();
          SetCurr(DEV_RR_SCALER_I_39P);
        }
      }
      break;

