
#ifndef SKIP_39

    case DEV_START_39P:
      MakePause(DEV_PREVTIME2_39P);
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
