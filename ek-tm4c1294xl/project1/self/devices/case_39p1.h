
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
        PROFILE39_REPEAT_OR_ERROR(210+0, DISC_Profile39(), DEV_DISC_I_39P)
      }
      break;


    case DEV_SNRM_O_39P:
      Clear(); ShowPercent(61);

      cbRepeat = MaxRepeats();
      SNRM_Profile39();
      SetCurr(DEV_SNRM_I_39P);
      break;

    case DEV_SNRM_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_AARQ_O_39P);
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+1, SNRM_Profile39(), DEV_SNRM_I_39P)
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
          PROFILE39_REPEAT_OR_ERROR(210+2, AARQ_Profile39(), DEV_AARQ_I_39P)
        } else {
          if (AARE_CheckPass()) {
            MakePause(DEV_RR_AARQ_O_39P);
          } else {
            Error39(210+3);
            ErrorProfile();
          }
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+4, AARQ_Profile39(), DEV_AARQ_I_39P)
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
          PROFILE39_REPEAT_OR_ERROR(210+5, RR_Profile39(), DEV_RR_AARQ_I_39P)
        } else {
          Init_Correct39();

          MakePause(DEV_TIME1_O_39P);
        }  
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+6, RR_Profile39(), DEV_RR_AARQ_I_39P)
      }
      break;
