

    case DEV_TIME_O_39P:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryTime39_Profile();
      SetCurr(DEV_TIME_I_39P);
      break;

    case DEV_TIME_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+0);
          ErrorProfile();
        } else {
          ReadTime39_Profile();
          MakePause(DEV_RR_TIME_O_39P);
        }
      } else {
        Error39(220+0);
        ErrorProfile();
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
          ErrorProfile();
        } else {
          MakePause(DEV_INIT_39P);
        }  
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;

