
    case DEV_INIT_39P:
      InitProfile_Profile39(); // step 39.1
      MakePause(DEV_QUERY_39P);
      break;


    case DEV_QUERY_39P: // from step 25
      cbRepeat = MaxRepeats();
      QueryProfile_Profile39(); // steps 39.2, 39.3, 39.4
      SetCurr(DEV_14_39P);
      break;

    case DEV_14_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+19, QueryProfile_Profile39(), DEV_14_39P)
        } else {
          Read1_Profile(); // steps 39.5, 39.6
          MakePause(DEV_15_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+21, QueryProfile_Profile39(), DEV_14_39P)
      }
      break;

    case DEV_15_39P:
      if (!LastSegmentDMLS()) { // true: step 39.7
        MakePause(DEV_1_RR_O_39P); // -> step 39.8
      } else {
        MakePause(DEV_2_RR_O_39P); // -> step 39.10
      }
      break;


    case DEV_1_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39(); // step 39.8
      SetCurr(DEV_1_RR_I_39P);
      break;

    case DEV_1_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+23, RR_Profile39(), DEV_1_RR_I_39P)
        } else {
          Read2_Profile(); // step 39.9
          MakePause(DEV_15_39P); // repeat: step 39.10
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+24, RR_Profile39(), DEV_1_RR_I_39P)
      }
      break;


    case DEV_2_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39(); // step 10
      SetCurr(DEV_2_RR_I_39P);
      break;

    case DEV_2_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+25, RR_Profile39(), DEV_2_RR_I_39P)
        } else {
          Read3_Profile(); // step 11
          MakePause(DEV_READ_3_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+26, RR_Profile39(), DEV_2_RR_I_39P)
      }
      break;

    case DEV_READ_3_39P:
      if (UseBlocks_Profile39()) { // step 12
        cbRepeat = MaxRepeats();
        QueryNextBlock_Profile39();  // step 13, 14
        SetCurr(DEV_READ_4_39P);
      } else {
        MakePause(DEV_FINISH_39P); // step 12a -> step 22
      }
      break;

    case DEV_READ_4_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+29, QueryNextBlock_Profile39(), DEV_READ_4_39P)
        } else {
          Read4_Profile(); // steps 15, 16
          MakePause(DEV_20_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+30, QueryNextBlock_Profile39(), DEV_READ_4_39P)
      }
      break;

    case DEV_20_39P:
      if (!LastSegmentDMLS()) { // step 17
        MakePause(DEV_3_RR_O_39P);
      } else {
        MakePause(DEV_4_RR_O_39P);
      }
      break;


    case DEV_3_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39(); // step 18
      SetCurr(DEV_3_RR_I_39P);
      break;

    case DEV_3_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+27, RR_Profile39(), DEV_3_RR_I_39P)
        } else {
          Read5_Profile(); // step 19
          MakePause(DEV_20_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+28, RR_Profile39(), DEV_3_RR_I_39P)
      }
      break;


    case DEV_4_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39(); // step 20
      SetCurr(DEV_4_RR_I_39P);
      break;

    case DEV_4_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(220+29, RR_Profile39(), DEV_4_RR_I_39P)
        } else {
          MakePause(DEV_READ_3_39P); // step 21 -> step 12
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(220+30, RR_Profile39(), DEV_4_RR_I_39P)
      }
      break;


    case DEV_FINISH_39P: // step 22
      {
        bool2 b2 = FinishProfile_Profile39(); // step 23
        if (!b2.fValid)
          ErrorProfile();
        else if (b2.fValue)
          MakePause(DEV_QUERY_39P); // step 25
        else
          DoneProfile(); // step 26
      }
      break;

#endif
