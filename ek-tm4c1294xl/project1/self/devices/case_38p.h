
#ifndef SKIP_38

    case DEV_START_38P:
      MakePause(DEV_PREVTIME_38P);
      break;


    case DEV_PREVTIME_38P:
      cbRepeat = MaxRepeats();
      QueryTime38();
      SetCurr(DEV_TIME_38P);
      break;

    case DEV_TIME_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValue38 = ReadTime38();
        dwValue38 = DateToHouIndex(tiValue38);
        MakePause(DEV_POSTTIME_38P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeProfile38();
          SetCurr(DEV_TIME_38P);
        }
      }
      break;


    case DEV_POSTTIME_38P:
      InitHeader38();

      cbRepeat = MaxRepeats();
      QueryHeader38();
      SetCurr(DEV_HEADER_38P);
      break;

    case DEV_HEADER_38P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadData38() == false)
          DoneProfile();
        else
          MakePause(DEV_DATA_38P);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader38();
          SetCurr(DEV_HEADER_38P);
        }
      }
      break;

    case DEV_DATA_38P:
      cbRepeat = MaxRepeats();
      QueryHeader38();
      SetCurr(DEV_HEADER_38P);
      break;

#endif
