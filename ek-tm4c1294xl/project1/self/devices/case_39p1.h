
#ifndef SKIP_39

    case DEV_START_39P:
      MakePause(DEV_DISC_O_39P);
      break;


    case DEV_DISC_O_39P:
      Clear(); ShowPercent(60);

      cbRepeat = MaxRepeats();
      DISC_Profile39();
      SetCurr(DEV_DISC_I_39P);
      break;

    case DEV_DISC_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_SNRM_O_39P);
      } else {
        Error39(220+0);
        PROFILE_REPEAT_OR_ERROR(DISC_Profile39(), DEV_DISC_I_39P)
      }
      break;


    case DEV_SNRM_O_39P:
      Clear(); ShowPercent(61);

      cbRepeat = MaxRepeats();
      Query39_SNRM();
      SetCurr(DEV_SNRM_I_39P);
      break;

    case DEV_SNRM_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_AARQ_O_39P);
      } else {
        Error39(220+1);
        PROFILE_REPEAT_OR_ERROR(Query39_SNRM(), DEV_SNRM_I_39P)
      }
      break;


    case DEV_AARQ_O_39P:
      Clear(); ShowPercent(62);

      cbRepeat = MaxRepeats();
      AARQ_Profile39();
      SetCurr(DEV_AARQ_I_39P);
      break;

    case DEV_AARQ_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+2);
          PROFILE_REPEAT_OR_ERROR(AARQ_Profile39(), DEV_AARQ_I_39P)
        } else {
          MakePause(DEV_RR_AARQ_O_39P);
        }  
      } else {
        Error39(220+3);
        PROFILE_REPEAT_OR_ERROR(AARQ_Profile39(), DEV_AARQ_I_39P)
      }
      break;


    case DEV_RR_AARQ_O_39P:
      Clear(); ShowPercent(63);

      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_RR_AARQ_I_39P);
      break;

    case DEV_RR_AARQ_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+4);
          PROFILE_REPEAT_OR_ERROR(RR_Profile39(), DEV_RR_AARQ_I_39P)
        } else {
          MakePause(DEV_TIME1_O_39P);
        }  
      } else {
        Error39(220+5);
        PROFILE_REPEAT_OR_ERROR(RR_Profile39(), DEV_RR_AARQ_I_39P)
      }
      break;
