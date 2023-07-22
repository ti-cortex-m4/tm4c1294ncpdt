
#ifndef SKIP_B

    // Меркурий-233 блоками по 17 получасов
    case DEV_HEADER_B2x17:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2x17);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBx17();
          SetCurr(DEV_HEADER_B2x17);
        }
      }
      break;

    case DEV_POSTHEADER_B2x17:
      {
        NewBoundsAbs32(dwBaseCurr);

        uchar i;
        for (i=0; i<17; i++)
        {
          if (ReadHeaderBx17(i,1) == 0) break;
          (dwBaseCurr == 0) ? (dwBaseCurr = 0x1FFF0) : (dwBaseCurr -= 0x0010);
        }

        if (i != 17)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderBx17();
          SetCurr(DEV_HEADER_B2x17);
        }
      }
      break;

#endif
