
#ifndef SKIP_39

    case DEV_START_39C:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      Query39_DISC_Current();
      SetCurr(DEV_DISC_39C);
      break;

    case DEV_DISC_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_POSTDISC_39C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_DISC_Current();
          SetCurr(DEV_DISC_39C);
        }
      }
      break;


    case DEV_POSTDISC_39C:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      Query39_SNRM();
      SetCurr(DEV_SNRM_39C);
      break;

    case DEV_SNRM_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_POSTSNRM_39C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_SNRM();
          SetCurr(DEV_SNRM_39C);
        }
      }
      break;


    case DEV_POSTSNRM_39C:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      Query39_AARQ_Current();
      SetCurr(DEV_OPEN2_39C);
      break;

    case DEV_OPEN2_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateIframe_Current())
          ErrorCurrent();
        else
          MakePause(DEV_POSTOPEN2_39C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_AARQ_Current();
          SetCurr(DEV_OPEN2_39C);
        }
      }
      break;


    case DEV_POSTOPEN2_39C:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      Query39_RR_Current();
      SetCurr(DEV_RR1_39C);
      break;

    case DEV_RR1_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Current())
          ErrorCurrent();
        else
          MakePause(DEV_POSTRR1_39C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_RR_Current();
          SetCurr(DEV_RR1_39C);
        }
      }
      break;


    case DEV_POSTRR1_39C:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryEngAbs39_Current();
      SetCurr(DEV_ENGABS_39C);
      break;

    case DEV_ENGABS_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateIframe_Current())
          ErrorCurrent();
        else {
          SaveCurrent39();
          MakePause(DEV_POSTENGABS_39C);
        }
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs39_Current();
          SetCurr(DEV_ENGABS_39C);
        }
      }
      break;


    case DEV_POSTENGABS_39C:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Current();
      SetCurr(DEV_RR2_39C);
      break;

    case DEV_RR2_39C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateSframe_Current())
          ErrorCurrent();
        else {
          ReadCurrent39();
        }
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query39_RR_Current();
          SetCurr(DEV_RR2_39C);
        }
      }
      break;

#endif
