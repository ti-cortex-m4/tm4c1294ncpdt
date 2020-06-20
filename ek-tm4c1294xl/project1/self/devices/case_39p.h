
#ifndef SKIP_39

    case DEV_START_39P:
      MakePause(DEV_1_39P);
      break;


    case DEV_1_39P:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      Query39_DISC_Profile();
      SetCurr(DEV_2_39P);
      break;

    case DEV_2_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_3_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_3_39P:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      Query39_SNRM();
      SetCurr(DEV_4_39P);
      break;

    case DEV_4_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_5_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_5_39P:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      Query39_AARQ_Profile();
      SetCurr(DEV_6_39P);
      break;

    case DEV_6_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateIframe_Profile())
          ErrorProfile();
        else
          MakePause(DEV_7_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_7_39P:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_8_39P);
      break;

    case DEV_8_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Profile())
          ErrorProfile();
        else
          MakePause(DEV_9_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_9_39P:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryTime39_Profile();
      SetCurr(DEV_10_39P);
      break;

    case DEV_10_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateIframe_Profile())
          ErrorProfile();
        else {
          ReadTime39_Profile();
          MakePause(DEV_11_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_11_39P:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_12_39P);
      break;

    case DEV_12_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Profile())
          ErrorProfile();
        else
          MakePause(DEV_13_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_13_39P:
      InitProfile39_Profile();
      MakePause(DEV_13a_39P);
      break;


    case DEV_13a_39P:
      cbRepeat = MaxRepeats();
      QueryProfile39_Profile();
      SetCurr(DEV_14_39P);
      break;

    case DEV_14_39P:
      Read1_Profile();
      MakePause(DEV_15_39P);
      break;

    case DEV_15_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK)  {
        if (!LastSegmentDMLS()) {
          MakePause(DEV_16_39P);
        } else {          
          MakePause(DEV_18_39P);
        }
      } else {
        ErrorProfile();
      } 
      break;


    case DEV_16_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_17_39P);
      break;

    case DEV_17_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          ErrorProfile();
        } else {
          Read2_Profile();
          MakePause(DEV_15_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_18_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_19_39P);
      break;

    case DEV_19_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          ErrorProfile();
        } else {
          Read3_Profile();
          if (UseBlocks_Profile()) {
            QueryNextBlock39_Profile();
            MakePause(DEV_19a_39P);
          } else {
            MakePause(DEV_25_39P);
          }
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_19a_39P:
      Read4_Profile();
      MakePause(DEV_20_39P);
      break;

    case DEV_20_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK)  {
        if (!LastSegmentDMLS()) {
          MakePause(DEV_21_39P);
        } else {          
          MakePause(DEV_23_39P);
        }
      } else {
        ErrorProfile();
      } 
      break;


    case DEV_21_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_22_39P);
      break;

    case DEV_22_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          ErrorProfile();
        } else {
          Read5_Profile();
          MakePause(DEV_20_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_23_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_24_39P);
      break;

    case DEV_24_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          ErrorProfile();
        } else {
          MakePause(DEV_25_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_25_39P:
      if (FinishProfile39_Profile())
        MakePause(DEV_13a_39P);
      else
        DoneProfile();
      break;

#endif
