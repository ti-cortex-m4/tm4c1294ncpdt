
#ifndef SKIP_U

    case DEV_START_U3:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U3);
      break;

    case DEV_OPENCANAL_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_U3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_U3:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionU();
      SetCurr(DEV_OPTION_U3);
      break;

    case DEV_OPTION_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_U3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_U3);
        }
      }
      break;

    case DEV_POSTOPTION_U3:
      Clear(); ShowPercent(52);

      ibMinor = 0;
      if (SkipLine(ibDig, ibMinor) == true)
      {
        ReadEnergyU_SkipLine(ibMinor);
        ibMinor++;
      }

      cbRepeat = GetMaxRepeats();
      QueryEnergySpecU(ibMinor);
      SetCurr(DEV_ENERGY_U3);
      break;

    case DEV_ENERGY_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyU(ibMinor);

        if (SkipLine(ibDig, ibMinor+1) == true)
        {
          ReadEnergyU_SkipLine(ibMinor+1);
          ibMinor++;
        }

        uchar bMaxLine = GetMaxLine(ibDig);
        if (++ibMinor < bMaxLine)
        {
          Clear(); ShowPercent(52+ibMinor);
          QueryEnergySpecU(ibMinor);
          SetCurr(DEV_ENERGY_U3);
        }
        else
          ReadCurrentU(bMaxLine);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecU(ibMinor);
          SetCurr(DEV_ENERGY_U3);
        }
      }
      break;

#endif
