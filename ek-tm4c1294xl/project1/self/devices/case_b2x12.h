
#ifndef SKIP_B

    // Меркурий-234 блоками по 12 получасов (версия 9.1.0+)
    case DEV_HEADER_B2x12:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2x12);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBx12();
          SetCurr(DEV_HEADER_B2x12);
        }
      }
      break;

    case DEV_POSTHEADER_B2x12:
      {
        NewBoundsAbs32(dwBaseCurr);

        uchar i;
        for (i=0; i<12; i++)
        {
          if (ReadHeaderBx12(i,0) == 0) break;
          (dwBaseCurr == 0) ? (dwBaseCurr = 0x1FFF0) : (dwBaseCurr -= 0x0010);
        }

        if (i != 12)
          DoneProfile();
        else
        {
          cbRepeat = MaxRepeats();
          QueryHeaderBx12();
          SetCurr(DEV_HEADER_B2x12);
        }
      }
      break;

#endif
