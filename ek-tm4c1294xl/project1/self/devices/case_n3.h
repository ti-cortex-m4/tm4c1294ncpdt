
#ifndef SKIP_N

    case DEV_START_N3:
      cbRepeat = MaxRepeats();
      QueryEnergyAbsN();
      SetCurr(DEV_ENERGY_N3);
      break;

    case DEV_ENERGY_N3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentN();
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--; mpwRepeat[ibDig]++;

          QueryEnergyAbsN();
          SetCurr(DEV_ENERGY_N3);
        }
      }
      break;

#endif
