
#ifndef SKIP_35

    case DEV_DATAGET_35:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MonitorString("\n repeat: completed");
        MakePause(GetCurr35Internal());
      }
      else
      {
        if (cbRepeat == 0)
        {
          if (exExtended == EXT_CURRENT_3MIN)
            ErrorCurrent();
          else
            ErrorProfile();
        }
        else
        {
          //ErrorLink();
          cbRepeat--;

          MonitorString("\n repeat: repeat");

          Query35Internal(250, 0, NNCL2_DATA_GET);
          SetCurr(DEV_DATAGET_35);
        }
      }
      break;



    case DEV_START_35C:
      Clear(); ShowPercent(25);

      cbRepeat = MaxRepeats();
      QueryConfig35();
      SetCurr(DEV_CONFIG_35C);
      SetCurr35Internal(DEV_CONFIG_35C);
      break;

    case DEV_CONFIG_35C:
      if (mpSerial[ibPort] == SER_PAUSE) // SER_GOODCHECK
      {
        ReadConfig35();
        MakePause(DEV_POSTCONFIG_35C);
      }
      else
      {
        MonitorString("\n read config: repeat "); MonitorIntDec(cbRepeat); MonitorString(" "); MonitorCharDec(mpSerial[ibPort]);
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryConfig35();
          SetCurr35(DEV_CONFIG_35C);
        }
      }
      break;

    case DEV_POSTCONFIG_35C:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryEngMon35(0);
      SetCurr35(DEV_ENERGY_35C);
      break;

    case DEV_ENERGY_35C:
      if (mpSerial[ibPort] == SER_PAUSE) // SER_GOODCHECK
        ReadCurrent35();
      else
      {
        MonitorString("\n read energy: repeat "); MonitorIntDec(cbRepeat);

        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngMon35(0);
          SetCurr35(DEV_ENERGY_35C);
        }
      }
      break;

#endif
