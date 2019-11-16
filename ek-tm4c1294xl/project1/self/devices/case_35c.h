
#ifndef SKIP_35

    case DEV_START_35C:
      ShowPercent(25);

      cbRepeat = MaxRepeats();
      QueryConfig35();
      SetCurr(DEV_CONFIG_35C);
      break;

    case DEV_CONFIG_35C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfig35();
        MakePause(DEV_POSTCONFIG_35C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryConfig35();
          SetCurr(DEV_CONFIG_35C);
        }
      }
      break;

    case DEV_POSTCONFIG_35C:
      ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryEngMon35(0);
      SetCurr(DEV_ENERGY_35C);
      break;

    case DEV_ENERGY_35C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrent35();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngMon35(0);
          SetCurr(DEV_ENERGY_35C);
        }
      }
      break;

#endif
