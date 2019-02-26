#ifndef SKIP_34

    case DEV_START_34C:
      cbRepeat = MaxRepeats();
      QueryEngAbs34();
      SetCurr(DEV_ENERGY_34C);
      break;

    case DEV_ENERGY_34C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrent34();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs34();
          SetCurr(DEV_ENERGY_34C);
        }
      }
      break;

#endif
