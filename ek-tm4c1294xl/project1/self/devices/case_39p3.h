
    case DEV_INIT_39P:
      InitProfile39_Profile();
      MakePause(DEV_QUERY_39P);
      break;


    case DEV_QUERY_39P:
      cbRepeat = MaxRepeats();
      QueryProfile39_Profile();
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
      Query39_RR_Profile();
      SetCurr(DEV_1_RR_I_39P);
      break;

    case DEV_1_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+0);
          ErrorProfile();
        } else {
          Read2_Profile();
          MakePause(DEV_15_39P);
        }
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_2_RR_O_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_2_RR_I_39P);
      break;

    case DEV_2_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+0);
          ErrorProfile();
        } else {
          Read3_Profile();
          if (UseBlocks_Profile()) {
            QueryNextBlock39_Profile();
            MakePause(DEV_READ_4_39P);
          } else {
            MakePause(DEV_27_39P);
          }
        }
      } else {
        Error39(220+0);
        ErrorProfile();
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
      Query39_RR_Profile();
      SetCurr(DEV_3_RR_I_39P);
      break;

    case DEV_3_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+0);
          ErrorProfile();
        } else {
          Read5_Profile();
          MakePause(DEV_20_39P);
        }
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_4_RR_O_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_4_RR_I_39P);
      break;

    case DEV_4_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {
          Error39(220+0);
          ErrorProfile();
        } else {
          MakePause(DEV_27_39P);
        }
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_27_39P:
      if (FinishProfile39_Profile())
        MakePause(DEV_QUERY_39P);
      else
        DoneProfile();
      break;

#endif
