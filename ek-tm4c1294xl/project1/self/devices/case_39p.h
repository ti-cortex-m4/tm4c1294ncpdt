
#ifndef SKIP_39

    case DEV_START_39P:
      MakePause(DEV_PREVTIME2_39P);
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
          MakePause(DEV_6_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_6_39P:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_7_39P);
      break;

    case DEV_7_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Profile())
          ErrorProfile();
        else
          MakePause(DEV_8_39P);
      } else {
        ErrorProfile();
      }
      break;


    case DEV_8_39P:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryEngAbs39_Profile();
      SetCurr(DEV_9_39P);
      break;

    case DEV_9_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateIframe_Profile())
          ErrorProfile();
        else {
          MakePause(DEV_10_39P);
        }
      } else {
        ErrorProfile();
      }
      break;


    case DEV_10_39P:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_11_39P);
      break;

    case DEV_11_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateSframe_Profile())
          ErrorProfile();
        else {
          ReadProfile39();
        }
      } else {
        ErrorProfile();
      }
      break;

    case DEV_PREVTIME2_39P:
      ShowPercent(50);

      cbRepeat = MaxRepeat39();
      QueryTime39();
      SetCurr(DEV_TIME2_39P);
      break;

    case DEV_TIME2_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue39 = ReadTime39();
        dwValue39 = DateToHouIndex(tiValue39);
        MakePause(DEV_INITHEADER_39P);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime39();
          SetCurr(DEV_TIME2_39P);
        }
      }
      break;

    case DEV_INITHEADER_39P:
      ShowPercent(75);
      InitHeader39();

      cbRepeat = MaxRepeat39();
      QueryHeader39();
      SetCurr(DEV_HEADER_39P);
      break;

    case DEV_HEADER_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadHeader39() == false)
          DoneProfile();
        else 
        {
          cbRepeat = MaxRepeat39();
          QueryHeader39();
          SetCurr(DEV_HEADER_39P);          
        }
      }  
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader39();
          SetCurr(DEV_HEADER_39P);
        }
      }
      break;

#endif
