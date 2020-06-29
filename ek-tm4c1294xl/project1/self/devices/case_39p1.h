
#ifndef SKIP_39

    case DEV_START_39P:
      MakePause(DEV_DISC_O_39P);
      break;


    case DEV_DISC_O_39P:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      Query39_DISC_Profile();
      SetCurr(DEV_DISC_I_39P);
      break;

    case DEV_DISC_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_SNRM_O_39P);
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          Query39_DISC_Profile();
          SetCurr(DEV_DISC_I_39P);
        }
      }
      break;


    case DEV_SNRM_O_39P:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      Query39_SNRM();
      SetCurr(DEV_SNRM_I_39P);
      break;

    case DEV_SNRM_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_AARQ_O_39P);
      } else {
        Error39(220+1);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          Query39_SNRM();
          SetCurr(DEV_SNRM_I_39P);
        }
      }
      break;


    case DEV_AARQ_O_39P:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      Query39_AARQ_Profile();
      SetCurr(DEV_AARQ_I_39P);
      break;

    case DEV_AARQ_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+2);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            Query39_AARQ_Profile();
            SetCurr(DEV_AARQ_I_39P);
          }
        } else {
          MakePause(DEV_RR_AARQ_O_39P);
        }  
      } else {
        Error39(220+3);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          Query39_AARQ_Profile();
          SetCurr(DEV_AARQ_I_39P);
        }
      }
      break;


    case DEV_RR_AARQ_O_39P:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_RR_AARQ_I_39P);
      break;

    case DEV_RR_AARQ_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            Query39_RR_Profile();
            SetCurr(DEV_RR_AARQ_I_39P);
          }
        } else {
          Error39(220+0);
          MakePause(DEV_TIME_O_39P);
        }  
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          Query39_RR_Profile();
          SetCurr(DEV_RR_AARQ_I_39P);
        }
      }
      break;
