

    case DEV_TIME_O_39P:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryTime39_Profile();
      SetCurr(DEV_TIME_I_39P);
      break;

    case DEV_TIME_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+6);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            QueryTime39_Profile();
            SetCurr(DEV_TIME_I_39P);
          }
        } else {
          ReadTime39_Profile();
          MakePause(DEV_RR_TIME_O_39P);
        }
      } else {
        Error39(220+7);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          QueryTime39_Profile();
          SetCurr(DEV_TIME_I_39P);
        }
      }
      break;


    case DEV_RR_TIME_O_39P:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_RR_TIME_I_39P);
      break;

    case DEV_RR_TIME_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            Query39_RR_Profile();
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
          Query39_RR_Profile();
          SetCurr(DEV_RR_TIME_I_39P);
        }
      }
      break;

