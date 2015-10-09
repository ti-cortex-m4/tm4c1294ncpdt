
#ifndef SKIP_V

    case DEV_START_V3:
      ShowPercent(25);

      cbRepeat = GetMaxRepeats();
      QueryConfigS();
      SetCurr(DEV_CONFIG_V3);
      break;

    case DEV_CONFIG_V3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfigS();
        MakePause(DEV_POSTCONFIG_V3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryConfigS();
          SetCurr(DEV_CONFIG_V3);
        }
      }
      break;

    case DEV_POSTCONFIG_V3:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryEngMonS(0);
      SetCurr(DEV_ENERGY_V3);
      break;

    case DEV_ENERGY_V3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentS();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngMonS(0);
          SetCurr(DEV_ENERGY_V3);
        }
      }
      break;

#endif
