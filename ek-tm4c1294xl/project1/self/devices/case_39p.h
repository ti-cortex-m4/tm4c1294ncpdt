
#ifndef SKIP_38

    case DEV_START_P39:
      MakePause(DEV_POSTVALUE_P39);
      break;

    case DEV_POSTCONFIG_P39:
      ShowPercent(50);

      cbRepeat = MaxRepeat39();
      QueryTime39();
      SetCurr(DEV_VALUE_P39);
      break;

    case DEV_VALUE_P39:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueS = ReadTime39();
        dwValueS = DateToHouIndex(tiValueS);
        MakePause(DEV_POSTVALUE_P39);
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
          SetCurr(DEV_VALUE_P39);
        }
      }
      break;

    case DEV_POSTVALUE_P39:
      ShowPercent(75);
      InitHeader39();

      cbRepeat = MaxRepeat39();
      QueryHeader39();
      SetCurr(DEV_HEADER_P39);
      break;

    case DEV_HEADER_P39:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_P39);
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

    case DEV_POSTHEADER_P39:
      if (ReadHeader39() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_P39);
      break;

    case DEV_DATA_P39:
      cbRepeat = MaxRepeat39();
      QueryHeader39();
      SetCurr(DEV_HEADER_P39);
      break;

#endif
