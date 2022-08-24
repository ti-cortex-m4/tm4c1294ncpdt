
    case DEV_INIT_40P:
      InitProfile_Profile40(); // step 40.1
      MakePause(DEV_QUERY_40P);
      break;


    case DEV_QUERY_40P: // repeat: step 40.27
      cbRepeat = MaxRepeats();
      QueryProfile_Profile40(); // steps 40.2, 40.3, 40.4
      SetCurr(DEV_14_40P);
      break;

    case DEV_14_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+24, QueryProfile_Profile40(), DEV_14_40P)
        } else {
          Read1_Profile(); // steps 40.5, 40.6
          MakePause(DEV_15_40P);
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+25, QueryProfile_Profile40(), DEV_14_40P)
      }
      break;

    case DEV_15_40P:
      if (!LastSegmentDMLS()) { // true: step 40.7
        MakePause(DEV_1_RR_O_40P); // -> step 40.8
      } else {
        MakePause(DEV_2_RR_O_40P); // -> step 40.11
      }
      break;


    case DEV_1_RR_O_40P:
      cbRepeat = MaxRepeats();
      RR_Profile40(); // step 40.8
      SetCurr(DEV_1_RR_I_40P);
      break;

    case DEV_1_RR_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+26, RR_Profile40(), DEV_1_RR_I_40P)
        } else {
          Read2_Profile(); // step 40.9
          MakePause(DEV_15_40P); // repeat: step 40.10 -> step 40.7
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+27, RR_Profile40(), DEV_1_RR_I_40P)
      }
      break;


    case DEV_2_RR_O_40P:
      cbRepeat = MaxRepeats();
      RR_Profile40(); // step 40.11
      SetCurr(DEV_2_RR_I_40P);
      break;

    case DEV_2_RR_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+28, RR_Profile40(), DEV_2_RR_I_40P)
        } else {
          Read3_Profile(); // step 40.12
          MakePause(DEV_READ_3_40P);
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+29, RR_Profile40(), DEV_2_RR_I_40P)
      }
      break;

    case DEV_READ_3_40P:
      if (UseBlocks_Profile40()) { // step 40.13
        cbRepeat = MaxRepeats();
        QueryNextBlock_Profile40(); // steps 40.14, 40.15
        SetCurr(DEV_READ_4_40P);
      } else {
        MakePause(DEV_FINISH_40P); // step 40.16 -> step 40.24
      }
      break;

    case DEV_READ_4_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+30, QueryNextBlock_Profile40(), DEV_READ_4_40P)
        } else {
          Read4_Profile(); // steps 40.16, 40.17
          MakePause(DEV_20_40P);
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+31, QueryNextBlock_Profile40(), DEV_READ_4_40P)
      }
      break;

    case DEV_20_40P:
      if (!LastSegmentDMLS()) { // true: step 40.18
        MakePause(DEV_3_RR_O_40P); // -> step 40.19
      } else {
        MakePause(DEV_4_RR_O_40P); // -> step 40.22
      }
      break;


    case DEV_3_RR_O_40P:
      cbRepeat = MaxRepeats();
      RR_Profile40(); // step 40.19
      SetCurr(DEV_3_RR_I_40P);
      break;

    case DEV_3_RR_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+32, RR_Profile40(), DEV_3_RR_I_40P)
        } else {
          Read5_Profile(); // step 40.20
          MakePause(DEV_20_40P); // repeat: step 40.21 -> 40.18
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+33, RR_Profile40(), DEV_3_RR_I_40P)
      }
      break;


    case DEV_4_RR_O_40P:
      cbRepeat = MaxRepeats();
      RR_Profile40(); // step 40.22
      SetCurr(DEV_4_RR_I_40P);
      break;

    case DEV_4_RR_I_40P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile40()) {
          PROFILE40_REPEAT_OR_ERROR(210+34, RR_Profile40(), DEV_4_RR_I_40P)
        } else {
          MakePause(DEV_READ_3_40P); // repeat: step 40.23 -> step 40.13
        }
      } else {
        PROFILE40_REPEAT_OR_ERROR(210+35, RR_Profile40(), DEV_4_RR_I_40P)
      }
      break;


    case DEV_FINISH_40P: // step 40.24
      {
        bool2 b2 = FinishProfile_Profile40(); // steps 40.25, 40.26
        if (!b2.fValid)
          ErrorProfile();
        else if (b2.fValue)
          MakePause(DEV_QUERY_40P); // repeat: step 40.27
        else
          DoneProfile(); // finish: step 40.28
      }
      break;

#endif
