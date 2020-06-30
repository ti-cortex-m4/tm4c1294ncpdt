
    case DEV_INIT_39P:
      InitProfile_Profile39();
      MakePause(DEV_QUERY_39P);
      break;


    case DEV_QUERY_39P:
      cbRepeat = MaxRepeats();
      QueryProfile_Profile39();
      SetCurr(DEV_14_39P);
      break;

    case DEV_14_39P:
      Read1_Profile();
      MakePause(DEV_15_39P);
      break;

    case DEV_15_39P:
      if (!LastSegmentDMLS()) {
        MakePause(DEV_1_RR_O_39P);
      } else {
        MakePause(DEV_2_RR_O_39P);
      }
      break;


    case DEV_1_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_1_RR_I_39P);
      break;

    case DEV_1_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            RR_Profile39();
            SetCurr(DEV_1_RR_I_39P);
          }
        } else {
          Read2_Profile();
          MakePause(DEV_15_39P);
        }
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          RR_Profile39();
          SetCurr(DEV_1_RR_I_39P);
        }
      }
      break;


    case DEV_2_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_2_RR_I_39P);
      break;

    case DEV_2_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            RR_Profile39();
            SetCurr(DEV_2_RR_I_39P);
          }
        } else {
          Read3_Profile();
          if (UseBlocks_Profile()) {
            QueryNextBlock_Profile39();
            MakePause(DEV_READ_4_39P);
          } else {
            MakePause(DEV_FINISH_39P);
          }
        }
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          RR_Profile39();
          SetCurr(DEV_2_RR_I_39P);
        }
      }
      break;


    case DEV_READ_4_39P:
      Read4_Profile();
      MakePause(DEV_20_39P);
      break;

    case DEV_20_39P:
      if (!LastSegmentDMLS()) {
        MakePause(DEV_3_RR_O_39P);
      } else {
        MakePause(DEV_4_RR_O_39P);
      }
      break;


    case DEV_3_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_3_RR_I_39P);
      break;

    case DEV_3_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            RR_Profile39();
            SetCurr(DEV_3_RR_I_39P);
          }
        } else {
          Read5_Profile();
          MakePause(DEV_20_39P);
        }
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          RR_Profile39();
          SetCurr(DEV_3_RR_I_39P);
        }
      }
      break;


    case DEV_4_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39();
      SetCurr(DEV_4_RR_I_39P);
      break;

    case DEV_4_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          Error39(220+0);

          if (cbRepeat == 0) ErrorProfile();
          else {
            ErrorLink_RepeatDecrement();
            RR_Profile39();
            SetCurr(DEV_4_RR_I_39P);
          }
        } else {
          MakePause(DEV_FINISH_39P);
        }
      } else {
        Error39(220+0);

        if (cbRepeat == 0) ErrorProfile();
        else {
          ErrorLink_RepeatDecrement();
          RR_Profile39();
          SetCurr(DEV_4_RR_I_39P);
        }
      }
      break;


    case DEV_FINISH_39P:
      bool2 b2 = FinishProfile_Profile39();
      if (b2.fError)
        ErrorProfile();
      else if (b2.fValue)
        MakePause(DEV_QUERY_39P);
      else
        DoneProfile();
      break;

#endif
