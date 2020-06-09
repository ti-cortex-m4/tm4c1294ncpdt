
#ifndef SKIP_38

    case DEV_START_P39:
      MakePause(DEV_PREVTIME2_P39);
      break;

    case DEV_PREVTIME2_P39:
      ShowPercent(50);

      cbRepeat = MaxRepeat39();
      QueryTime39();
      SetCurr(DEV_TIME2_P39);
      break;

    case DEV_TIME2_P39:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue39 = ReadTime39();
        dwValue39 = DateToHouIndex(tiValue39);
        MakePause(DEV_INITHEADER_P39);
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
          SetCurr(DEV_TIME2_P39);
        }
      }
      break;

    case DEV_INITHEADER_P39:
      ShowPercent(75);
      InitHeader39();

      cbRepeat = MaxRepeat39();
      QueryHeader39();
      SetCurr(DEV_HEADER_P39);
      break;

    case DEV_HEADER_P39:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadHeader39() == 0)
          DoneProfile();
        else 
          MakePause(DEV_DATA_P39);
      }  
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader39();
          SetCurr(DEV_HEADER_P39);
        }
      }
      break;

    case DEV_DATA_P39:
      cbRepeat = MaxRepeat39();
      QueryHeader39();
      SetCurr(DEV_HEADER_P39);
      break;

#endif
