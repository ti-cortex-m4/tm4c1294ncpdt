
#ifndef SKIP_39

    case DEV_START_39C:
      MakePause(DEV_DISC_O_39C);
      break;


    case DEV_DISC_O_39C:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      Query39_DISC_Current();
      SetCurr(DEV_DISC_I_39C);
      break;

    case DEV_DISC_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_SNRM_O_39C);
      } else {
        Error39(210);
        ErrorCurrent();
      }
      break;


    case DEV_SNRM_O_39C:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      Query39_SNRM();
      SetCurr(DEV_SNRM_I_39C);
      break;

    case DEV_SNRM_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_AARQ_O_39C);
      } else {
        Error39(211);
        ErrorCurrent();
      }
      break;


    case DEV_AARQ_O_39C:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      Query39_AARQ_Current();
      SetCurr(DEV_AARQ_I_39C);
      break;

    case DEV_AARQ_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current()) {
          Error39(210);
          ErrorCurrent();
        } else {
          MakePause(DEV_RR_AARQ_O_39C);
        }
      } else {
        Error39(210);
        ErrorCurrent();
      }
      break;


    case DEV_RR_AARQ_O_39C:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      Query39_RR_Current();
      SetCurr(DEV_RR_AARQ_I_39C);
      break;

    case DEV_RR_AARQ_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Current()) {
          Error39(210);
          ErrorCurrent();
        } else {
          MakePause(DEV_VALUE_O_39C);
        }
      } else {
        Error39(210);
        ErrorCurrent();
      }
      break;


    case DEV_VALUE_O_39C:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryValue_Current();
      SetCurr(DEV_VALUE_I_39C);
      break;

    case DEV_VALUE_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateFrame_Current()) {
          Error39(210);
          ErrorCurrent();
        } else {
          if (ReadValue_Current()) {
            MakePause(DEV_RR_VALUE_O_39C);
          } else {
            Error39(210);
            ErrorCurrent();
          }
        }
      } else {
        Error39(210);
        ErrorCurrent();
      }
      break;


    case DEV_RR_VALUE_O_39C:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Current();
      SetCurr(DEV_RR_VALUE_I_39C);
      break;

    case DEV_RR_VALUE_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateFrame_Current()) {
          Error39(210);
          ErrorCurrent();
        } else {
          MakePause(DEV_SCALER_O_39C);
        }
      } else {
        Error39(210);
        ErrorCurrent();
      }
      break;


    case DEV_SCALER_O_39C:
      Clear(); ShowPercent(56);

      cbRepeat = MaxRepeats();
      QueryScaler_Current();
      SetCurr(DEV_SCALER_I_39C);
      break;

    case DEV_SCALER_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateFrame_Current()) {
          Error39(210);
          ErrorCurrent();
        } else {
          if (ReadScaler_Current())
            MakePause(DEV_RR_SCALER_O_39C);
          else {
            Error39(210);
            ErrorCurrent();
          }
        }
      } else {
        Error39(210);
        ErrorCurrent();
      }
      break;


    case DEV_RR_SCALER_O_39C:
      Clear(); ShowPercent(57);

      cbRepeat = MaxRepeats();
      Query39_RR_Current();
      SetCurr(DEV_RR_SCALER_I_39C);
      break;

    case DEV_RR_SCALER_I_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateFrame_Current()) {
          Error39(210);
          ErrorCurrent();
        } else {
          ReadCurrent39();
        }
      }
      else {
        Error39(210);
        ErrorCurrent();
      }
      break;

#endif
