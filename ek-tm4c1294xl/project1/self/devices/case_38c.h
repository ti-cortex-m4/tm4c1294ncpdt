
#if false

    case DEV_START_38C:
      Clear(); ShowPercent(50);

      ibLine38 = 0;

      cbRepeat = MaxRepeats();
      QueryEngAbs38(ibLine38);
      SetCurr(DEV_ENERGY_38C);
      break;

    case DEV_ENERGY_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEng38(11);
        if (++ibLine38 < 4)
        {
          Clear(); ShowPercent(50+ibLine38);
          QueryEngAbs38(ibLine38);
          SetCurr(DEV_ENERGY_38C);
        }
        else
          ReadCurrent38();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs38(ibLine38);
          SetCurr(DEV_ENERGY_38C);
        }
      }
      break;

#endif
