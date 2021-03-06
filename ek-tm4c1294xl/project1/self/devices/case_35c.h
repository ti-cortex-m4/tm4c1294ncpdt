
#ifndef SKIP_35

    case DEV_RUN_WAIT_35:
      MonitorString("\t run: wait");

      Query35Internal(250, 0, NNCL2_DATA_GET);
      SetCurr(DEV_RUN_DATA_GET_35);
      break;

    case DEV_RUN_BREAK_35:
      MonitorString("\t run: break");

      if (exExtended == EXT_CURRENT_3MIN)
        ErrorCurrent();
      else
        ErrorProfile();
      break;

    case DEV_RUN_DATA_GET_35:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MonitorString("\t run: good data");

        SetSerial35(SER_GOODCHECK);
        MakePause(GetCurr35Internal());
      }
      else
      {
        MonitorString("\t run: bad data");

        SetSerial35(SER_BADCHECK);
        MakePause(GetCurr35Internal());
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
