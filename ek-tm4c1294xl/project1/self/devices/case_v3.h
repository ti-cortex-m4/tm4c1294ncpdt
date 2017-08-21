
#ifndef SKIP_V

    case DEV_START_V3:
      cbRepeat = MaxRepeats();
      QueryEngAbsV();
      SetCurr(DEV_ENERGY_V3);
      break;

    case DEV_ENERGY_V3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentV();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsV();
          SetCurr(DEV_ENERGY_V3);
        }
      }
      break;

#endif
