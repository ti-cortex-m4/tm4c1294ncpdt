#ifndef SKIP_N31
/*
    case DEV_START_G3:
      cbRepeat = bMINORREPEATS;
      QueryOpenG();
      SetCurr(DEV_OPENCANAL_G3);
      break;

    case DEV_OPENCANAL_G3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpenG() == 0)
          ErrorCurrent();
        else
          MakePause(DEV_POSTOPENCANAL_G3);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenG();
          SetCurr(DEV_OPENCANAL_G3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_G3:
      cbRepeat = bMINORREPEATS;
      QueryEnergyAbsG();
      SetCurr(DEV_ENERGY_G3);
      break;

    case DEV_ENERGY_G3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentG();
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergyAbsG();
          SetCurr(DEV_ENERGY_G3);
        }
      }
      break;
*/
#endif
