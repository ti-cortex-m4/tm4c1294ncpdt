#ifndef SKIP_38

    case DEV_START_38C:
      cbRepeat = MaxRepeats();
      Query38_DISC();
      SetCurr(DEV_DISC_38C);
      break;

    case DEV_DISC_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
//        if (ReadOpen38() == false)
//          ErrorCurrent();
//        else
//          MakePause(DEV_POSTOPENCANAL_38C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          Query38_DISC();
          SetCurr(DEV_DISC_38C);
        }
      }
      break;


    case DEV_POSTDISC_38C:
      cbRepeat = MaxRepeats();
      Query38_SNRM();
      SetCurr(DEV_SNRM_38C);
      break;

    case DEV_SNRM_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
//        if (ReadOpen38() == false)
//          ErrorCurrent();
//        else
//          MakePause(DEV_POSTOPENCANAL_38C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          Query38_SNRM();
          SetCurr(DEV_SNRM_38C);
        }
      }
      break;


    case DEV_POSTSNRM_38C:
      cbRepeat = MaxRepeats();
      Query38_Open2();
      SetCurr(DEV_OPEN2_38C);
      break;

    case DEV_OPEN2_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
//        if (ReadOpen38() == false)
//          ErrorCurrent();
//        else
//          MakePause(DEV_POSTOPENCANAL_38C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          Query38_Open2();
          SetCurr(DEV_OPEN2_38C);
        }
      }
      break;


    case DEV_POSTOPEN2_38C:
      cbRepeat = MaxRepeats();
      Query38_RR();
      SetCurr(DEV_RR1_38C);
      break;

    case DEV_RR1_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
//        if (ReadOpen38() == false)
//          ErrorCurrent();
//        else
//          MakePause(DEV_POSTOPENCANAL_38C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          Query38_RR();
          SetCurr(DEV_RR1_38C);
        }
      }
      break;


    case DEV_POSTRR_38C:
      cbRepeat = MaxRepeats();
      QueryEngAbs38();
      SetCurr(DEV_ENGABS_38C);
      break;

    case DEV_ENGABS_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadCurrent38();
//        if (ReadOpen38() == false)
//          ErrorCurrent();
//        else
//          MakePause(DEV_POSTOPENCANAL_38C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs38();
          SetCurr(DEV_ENGABS_38C);
        }
      }
      break;


    case DEV_POSTENGABS_38C:
      cbRepeat = MaxRepeats();
      Query38_RR();
      SetCurr(DEV_RR2_38C);
      break;

    case DEV_RR2_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadCurrent38();
//        if (ReadOpen38() == false)
//          ErrorCurrent();
//        else
//          MakePause(DEV_POSTOPENCANAL_38C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          Query38_RR();
          SetCurr(DEV_RR2_38C);
        }
      }
      break;

#endif
