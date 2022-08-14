
    case DEV_INIT_39P:
      InitProfile_Profile39(); // step 39.1
      MakePause(DEV_QUERY_39P);
      break;


    case DEV_QUERY_39P: // repeat: step 39.27
      cbRepeat = MaxRepeats();
      QueryProfile_Profile39(); // steps 39.2, 39.3, 39.4
      SetCurr(DEV_14_39P);
      break;

    case DEV_14_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(210+24, QueryProfile_Profile39(), DEV_14_39P)
        } else {
          Read1_Profile(); // steps 39.5, 39.6
          MakePause(DEV_15_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+25, QueryProfile_Profile39(), DEV_14_39P)
      }
      break;

    case DEV_15_39P:
      if (!LastSegmentDMLS()) { // true: step 39.7
        MakePause(DEV_1_RR_O_39P); // -> step 39.8
      } else {
        MakePause(DEV_2_RR_O_39P); // -> step 39.11
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
          PROFILE39_REPEAT_OR_ERROR(210+26, RR_Profile39(), DEV_1_RR_I_39P)
        } else {
          Read2_Profile(); // step 39.9
          MakePause(DEV_15_39P); // repeat: step 39.10 -> step 39.7
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+27, RR_Profile39(), DEV_1_RR_I_39P)
      }
      break;


    case DEV_2_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39(); // step 39.11
      SetCurr(DEV_2_RR_I_39P);
      break;

    case DEV_2_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(210+28, RR_Profile39(), DEV_2_RR_I_39P)
        } else {
          Read3_Profile(); // step 39.12
          MakePause(DEV_READ_3_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+29, RR_Profile39(), DEV_2_RR_I_39P)
      }
      break;

    case DEV_READ_3_39P:
      if (UseBlocks_Profile39()) { // step 39.13
        cbRepeat = MaxRepeats();
        QueryNextBlock_Profile39(); // steps 39.14, 39.15
        SetCurr(DEV_READ_4_39P);
      } else {
        MakePause(DEV_FINISH_39P); // step 39.16 -> step 39.24
      }
      break;

    case DEV_READ_4_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(210+30, QueryNextBlock_Profile39(), DEV_READ_4_39P)
        } else {
          Read4_Profile(); // steps 39.16, 39.17
          MakePause(DEV_20_39P);
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+31, QueryNextBlock_Profile39(), DEV_READ_4_39P)
      }
      break;

    case DEV_20_39P:
      if (!LastSegmentDMLS()) { // true: step 38.18
        MakePause(DEV_3_RR_O_39P); // -> step 39.19
      } else {
        MakePause(DEV_4_RR_O_39P); // -> step 39.22
      }
      break;


    case DEV_3_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39(); // step 39.19
      SetCurr(DEV_3_RR_I_39P);
      break;

    case DEV_3_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(210+32, RR_Profile39(), DEV_3_RR_I_39P)
        } else {
          Read5_Profile(); // step 39.20
          MakePause(DEV_20_39P); // repeat: step 39.21 -> 39.18
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+33, RR_Profile39(), DEV_3_RR_I_39P)
      }
      break;


    case DEV_4_RR_O_39P:
      cbRepeat = MaxRepeats();
      RR_Profile39(); // step 39.22
      SetCurr(DEV_4_RR_I_39P);
      break;

    case DEV_4_RR_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile39()) {
          PROFILE39_REPEAT_OR_ERROR(210+34, RR_Profile39(), DEV_4_RR_I_39P)
        } else {
          MakePause(DEV_READ_3_39P); // repeat: step 39.23 -> step 39.13
        }
      } else {
        PROFILE39_REPEAT_OR_ERROR(210+35, RR_Profile39(), DEV_4_RR_I_39P)
      }
      break;


    case DEV_FINISH_39P: // step 39.24
      {
        bool2 b2 = FinishProfile_Profile39(); // steps 39.25, 39.26
        if (!b2.fValid)
          ErrorProfile();
        else if (b2.fValue)
          MakePause(DEV_QUERY_39P); // repeat: step 39.27
        else
          DoneProfile(); // finish: step 39.28
      }
      break;

#endif
