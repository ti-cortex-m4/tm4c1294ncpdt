
#ifndef SKIP_41

    case DEV_START_41C:
      Clear();

      cbRepeat = MaxRepeats();
      QueryEngAbs38();
      SetCurr(DEV_ENERGY_41C);
      break;

    case DEV_ENERGY_41C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrent41();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs38();
          SetCurr(DEV_ENERGY_41C);
        }
      }
      break;

#endif
