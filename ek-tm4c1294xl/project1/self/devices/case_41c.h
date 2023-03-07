
#ifndef SKIP_38

    case DEV_START_38C:
      Clear();

      cbRepeat = MaxRepeats();
      QueryEngAbs38();
      SetCurr(DEV_ENERGY_38C);
      break;

    case DEV_ENERGY_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrent38();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs38();
          SetCurr(DEV_ENERGY_38C);
        }
      }
      break;

#endif
