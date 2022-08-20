
#ifndef SKIP_40

    case DEV_START_40C:
      MakePause(DEV_DISC_O_40C);
      break;


    case DEV_DISC_O_40C:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      DISC_Current39();
      SetCurr(DEV_DISC_I_40C);
      break;

    case DEV_DISC_I_40C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_SNRM_O_40C);
      } else {
        CURRENT39_REPEAT_OR_ERROR(190+0, DISC_Current39(), DEV_DISC_I_40C)
      }
      break;


    case DEV_SNRM_O_40C:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      SNRM_Current39();
      SetCurr(DEV_SNRM_I_40C);
      break;

    case DEV_SNRM_I_40C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_AARQ_O_40C);
      } else {
        CURRENT39_REPEAT_OR_ERROR(190+1, SNRM_Current39(), DEV_SNRM_I_40C)
      }
      break;


    case DEV_AARQ_O_40C:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      AARQ_Current39();
      SetCurr(DEV_AARQ_I_40C);
      break;

    case DEV_AARQ_I_40C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(190+2, AARQ_Current39(), DEV_AARQ_I_40C)
        } else {
          if (AARE_CheckPass()) {
            MakePause(DEV_RR_AARQ_O_40C);
          } else {
            Error40(190+3);
            ErrorCurrent();
          }
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(190+4, AARQ_Current39(), DEV_AARQ_I_40C)
      }
      break;


    case DEV_RR_AARQ_O_40C:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      RR_Current39();
      SetCurr(DEV_RR_AARQ_I_40C);
      break;

    case DEV_RR_AARQ_I_40C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(190+5, RR_Current39(), DEV_RR_AARQ_I_40C)
        } else {
          ClearLine39();
          MakePause(DEV_VALUE_O_40C);
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(190+6, RR_Current39(), DEV_RR_AARQ_I_40C)
      }
      break;


    case DEV_VALUE_O_40C:
      Clear(); ShowPercent(54+GetLine39()*2);

      cbRepeat = MaxRepeats();
      QueryValue_Current39();
      SetCurr(DEV_VALUE_I_40C);
      break;

    case DEV_VALUE_I_40C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(190+7, QueryValue_Current39(), DEV_VALUE_I_40C)
        } else {
          if (ReadValue_Current39()) {
            MakePause(DEV_RR_VALUE_O_40C);
          } else {
            Error40(190+8);
            ErrorCurrent();
          }
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(190+9, QueryValue_Current39(), DEV_VALUE_I_40C)
      }
      break;


    case DEV_RR_VALUE_O_40C:
      Clear(); ShowPercent(55+GetLine39()*2);

      cbRepeat = MaxRepeats();
      RR_Current39();
      SetCurr(DEV_RR_VALUE_I_40C);
      break;

    case DEV_RR_VALUE_I_40C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(190+10, RR_Current39(), DEV_RR_VALUE_I_40C)
        } else {
          if (IncLine39() < 4)
            MakePause(DEV_VALUE_O_40C);
          else
            MakePause(DEV_SCALER_O_40C);
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(190+11, RR_Current39(), DEV_RR_VALUE_I_40C)
      }
      break;


    case DEV_SCALER_O_40C:
      Clear(); ShowPercent(62);

      cbRepeat = MaxRepeats();
      QueryScaler_Current39();
      SetCurr(DEV_SCALER_I_40C);
      break;

    case DEV_SCALER_I_40C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(190+12, QueryScaler_Current39(), DEV_SCALER_I_40C)
        } else {
          if (ReadScaler_Current39()) {
            MakePause(DEV_RR_SCALER_O_40C);
          } else {
            Error40(190+13);
            ErrorCurrent();
          }
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(190+14, QueryScaler_Current39(), DEV_SCALER_I_40C)
      }
      break;


    case DEV_RR_SCALER_O_40C:
      Clear(); ShowPercent(63);

      cbRepeat = MaxRepeats();
      RR_Current39();
      SetCurr(DEV_RR_SCALER_I_40C);
      break;

    case DEV_RR_SCALER_I_40C:
      if (mpSerial[ibPort] == SER_GOODCHECK)  {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(190+15, RR_Current39(), DEV_RR_SCALER_I_40C)
        } else {
          ReadCurrent39();
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(190+16, RR_Current39(), DEV_RR_SCALER_I_40C)
      }
      break;

#endif
