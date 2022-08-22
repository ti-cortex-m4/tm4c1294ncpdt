
#ifndef SKIP_40

    case DEV_START_40P:
      MakePause(DEV_DISC_O_40P);
      break;


    case DEV_DISC_O_40P:
      Clear(); ShowPercent(60);

      cbRepeat = MaxRepeats();
      DISC_Profile40();
      SetCurr(DEV_DISC_I_40P);
      break;

    case DEV_DISC_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_SNRM_O_40P);
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+0, DISC_Profile40(), DEV_DISC_I_40P)
      }
      break;


    case DEV_SNRM_O_40P:
      Clear(); ShowPercent(61);

      cbRepeat = MaxRepeats();
      SNRM_Profile40();
      SetCurr(DEV_SNRM_I_40P);
      break;

    case DEV_SNRM_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_AARQ_O_40P);
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+1, SNRM_Profile40(), DEV_SNRM_I_40P)
      }
      break;


    case DEV_AARQ_O_40P:
      Clear(); ShowPercent(62);

      cbRepeat = MaxRepeats();
      AARQ_Profile40();
      SetCurr(DEV_AARQ_I_40P);
      break;

    case DEV_AARQ_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+2, AARQ_Profile40(), DEV_AARQ_I_40P)
        } else {
          if (AARE_CheckPass()) {
            MakePause(DEV_RR_AARQ_O_40P);
          } else {
            Error40(210+3);
            ErrorProfile();
          }
        }  
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+4, AARQ_Profile40(), DEV_AARQ_I_40P)
      }
      break;


    case DEV_RR_AARQ_O_40P:
      Clear(); ShowPercent(63);

      cbRepeat = MaxRepeats();
      RR_Profile40();
      SetCurr(DEV_RR_AARQ_I_40P);
      break;

    case DEV_RR_AARQ_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+5, RR_Profile40(), DEV_RR_AARQ_I_40P)
        } else {
          Init_Correct40();

          MakePause(DEV_TIME1_O_40P);
        }  
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+6, RR_Profile40(), DEV_RR_AARQ_I_40P)
      }
      break;
