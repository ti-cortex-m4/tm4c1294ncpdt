
#ifndef SKIP_35

    case DEV_DATAGET_35:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MonitorString("\n REPEAT: COMPLETED"); // TODO 35
        Serial35 = SER_GOODCHECK;
        MakePause(GetCurr35Internal());
      }
      else
      {
        if (cbRepeat == 0)
        {
          MonitorString("\n REPEAT: ERROR");  // TODO 35
          if (exExtended == EXT_CURRENT_3MIN)
            ErrorCurrent();
          else
            ErrorProfile();
        }
        else
        {
          //ErrorLink();
          cbRepeat--;

          MonitorString("\n REPEAT: REPEAT "); MonitorCharDec(mpSerial[ibPort]);  // TODO 35

          Query35Internal(250, 0, NNCL2_DATA_GET);
          SetCurr(DEV_DATAGET_35);
        }
      }
      break;



    case DEV_START_35C:
      Clear(); ShowPercent(25);

      cbRepeat = MaxRepeats();
      QueryConfig35();
      SetCurr35(DEV_CONFIG_35C);
      break;

    case DEV_CONFIG_35C:
      if (IsSerial35())
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
      if (IsSerial35())
        ReadCurrent35();
      else
      {
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
