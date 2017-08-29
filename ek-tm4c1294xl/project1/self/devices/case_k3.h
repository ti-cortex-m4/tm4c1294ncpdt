
#ifndef SKIP_K

    case DEV_START_K3:
      ShowPercent(50);
      ibMinor = 0;

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_K3);
      break;

    case DEV_OPENCANAL_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_K3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_K3:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionK();
      SetCurr(DEV_OPTION_K3);
      break;

    case DEV_OPTION_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_K3);
        }
      }
      break;

    case DEV_POSTOPTION_K3:
      ShowPercent(52+ibMinor);

      cbRepeat = MaxRepeats();
      QueryEnergySpecK(ibMinor);
      SetCurr(DEV_ENERGY_K3);
      break;

    case DEV_ENERGY_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecK(ibMinor);
          SetCurr(DEV_ENERGY_K3);
        }
      }
      break;

    case DEV_POSTENERGY_K3:
      ReadEnergyK(ibMinor);

      if ((diCurr.bDevice == 14) ||
          (diCurr.bDevice == 17))
        ReadCurrentK(1);
      else
      {
        if (++ibMinor < 4)
          MakePause(DEV_POSTOPTION_K3);
        else
          ReadCurrentK(4);
      }
      break;

#endif
