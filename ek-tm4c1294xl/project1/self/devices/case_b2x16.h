
#ifndef SKIP_B

    // Меркурий-230 блоками по 16 получасов
    case DEV_HEADER_B2x16:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2x16);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBx16();
          SetCurr(DEV_HEADER_B2x16);
        }
      }
      break;

    case DEV_POSTHEADER_B2x16:
      {
        NewBoundsAbs16(dwBaseCurr);

        uchar i;
        for (i=0; i<PROFILE2X16_SIZE; i++)
        {
          if (ReadHeaderBx16(i,1) == 0) break;
          (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
        }

        if (i != PROFILE2X16_SIZE)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderBx16();
          SetCurr(DEV_HEADER_B2x16);
        }
      }
      break;

#endif
