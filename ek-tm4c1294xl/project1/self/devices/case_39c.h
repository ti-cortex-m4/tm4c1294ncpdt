
#ifndef SKIP_39

    case DEV_START_39C:
      MakePause(DEV_DISC_O_39C);
      break;


    case DEV_DISC_O_39C:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      DISC_Current39();
      SetCurr(DEV_DISC_I_39C);
      break;

    case DEV_DISC_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_SNRM_O_39C);
      } else {
        CURRENT39_REPEAT_OR_ERROR(210+0, DISC_Current39(), DEV_DISC_I_39C)
      }
      break;


    case DEV_SNRM_O_39C:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      SNRM_Current39();
      SetCurr(DEV_SNRM_I_39C);
      break;

    case DEV_SNRM_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_AARQ_O_39C);
      } else {
        CURRENT39_REPEAT_OR_ERROR(210+1, SNRM_Current39(), DEV_SNRM_I_39C)
      }
      break;


    case DEV_AARQ_O_39C:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      AARQ_Current39();
      SetCurr(DEV_AARQ_I_39C);
      break;

    case DEV_AARQ_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(210+2, AARQ_Current39(), DEV_AARQ_I_39C)
        } else {
          MakePause(DEV_RR_AARQ_O_39C);
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(210+3, AARQ_Current39(), DEV_AARQ_I_39C)
      }
      break;


    case DEV_RR_AARQ_O_39C:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      RR_Current39();
      SetCurr(DEV_RR_AARQ_I_39C);
      break;

    case DEV_RR_AARQ_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(210+4, RR_Current39(), DEV_RR_AARQ_I_39C)
        } else {
          MakePause(DEV_VALUE_O_39C);
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(210+5, RR_Current39(), DEV_RR_AARQ_I_39C)
      }
      break;


    case DEV_VALUE_O_39C:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryValue_Current39();
      SetCurr(DEV_VALUE_I_39C);
      break;

    case DEV_VALUE_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(210+6, QueryValue_Current39(), DEV_VALUE_I_39C)
        } else {
          if (ReadValue_Current39()) {
            MakePause(DEV_RR_VALUE_O_39C);
          } else {
            Error39(210+7);
            ErrorCurrent();
          }
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(210+8, QueryValue_Current39(), DEV_VALUE_I_39C)
      }
      break;


    case DEV_RR_VALUE_O_39C:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      RR_Current39();
      SetCurr(DEV_RR_VALUE_I_39C);
      break;

    case DEV_RR_VALUE_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(210+9, RR_Current39(), DEV_RR_VALUE_I_39C)
        } else {
          MakePause(DEV_SCALER_O_39C);
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(210+10, RR_Current39(), DEV_RR_VALUE_I_39C)
      }
      break;


    case DEV_SCALER_O_39C:
      Clear(); ShowPercent(56);

      cbRepeat = MaxRepeats();
      QueryScaler_Current39();
      SetCurr(DEV_SCALER_I_39C);
      break;

    case DEV_SCALER_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(211+10, QueryScaler_Current39(), DEV_SCALER_I_39C)
        } else {
          if (ReadScaler_Current39()) {
            MakePause(DEV_RR_SCALER_O_39C);
          } else {
            Error39(210+12);
            ErrorCurrent();
          }
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(211+13, QueryScaler_Current39(), DEV_SCALER_I_39C)
      }
      break;


    case DEV_RR_SCALER_O_39C:
      Clear(); ShowPercent(57);

      cbRepeat = MaxRepeats();
      RR_Current39();
      SetCurr(DEV_RR_SCALER_I_39C);
      break;

    case DEV_RR_SCALER_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)  {
        if (!ValidateFrame_Current39()) {
          CURRENT39_REPEAT_OR_ERROR(211+14, RR_Current39(), DEV_RR_SCALER_I_39C)
        } else {
          ReadCurrent39();
        }
      } else {
        CURRENT39_REPEAT_OR_ERROR(211+15, RR_Current39(), DEV_RR_SCALER_I_39C)
      }
      break;

#endif
