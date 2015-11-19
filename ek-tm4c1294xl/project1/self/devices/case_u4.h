
#ifndef SKIP_U

    case DEV_PREVHEADER_U4:
      iwMajor = 0;
      InitHeaderU_Plc();

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == 1)
      {
        ReadHeaderU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = GetMaxRepeats();
      QueryHeaderU_Plc();
      SetCurr(DEV_HEADER_U4);
      break;

    case DEV_HEADER_U4:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 3)                        // если нет требуемой записи
        {
          if (iwMajor >= wPlcUShutdown)                // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            iwMajor += bPlcUSize;
            sprintf(szLo," выключено: %-4u   ",iwMajor);

            wBaseCurr += bPlcUSize;
            iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
            ShowProgressDigHou();

            if (wBaseCurr >= wHOURS)
              DoneProfile();
            else if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_U4);
          }
        }
        else
        {
          ReadHeaderU_Plc();

          if (SkipLine(ibDig, ibLineU+1) == 1)
          {
            ReadHeaderU_SkipLine(ibLineU+1);
            ibLineU++;
          }

          iwMajor = 0;                                  // если есть требуемая запись
          MakePause(DEV_POSTHEADER_U4);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderU_Plc();
          SetCurr(DEV_HEADER_U4);
        }
      }
      break;

    case DEV_POSTHEADER_U4:
      if (++ibLineU < bMaxLineU)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderU_Plc();
        SetCurr(DEV_HEADER_U4);
      }
      else
      {
        if (ReadDataU_Plc() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_U4);
      }
      break;

    case DEV_DATA_U4:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        ibLineU = 0;

        if (SkipLine(ibDig, ibLineU) == 1)
        {
          ReadHeaderU_SkipLine(ibLineU);
          ibLineU++;
        }

        cbRepeat = GetMaxRepeats();
        QueryHeaderU_Plc();
        SetCurr(DEV_HEADER_U4);
      }
      break;

#endif
