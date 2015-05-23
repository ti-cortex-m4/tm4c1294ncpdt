
#ifndef SKIP_D

    case DEV_START_D3:
      cbRepeat = bMAJORREPEATS;

      QueryOpenD();
      SetCurr(DEV_OPENCANAL_D3);             
      break;

    case DEV_OPENCANAL_D3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_D3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ShowPercent(bMAJORREPEATS - cbRepeat);   
          cbRepeat--;

          QueryOpenD();
          SetCurr(DEV_OPENCANAL_D3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_D3:
      ShowPercent(98);

      cbRepeat = GetMaxRepeats();
      QueryPasswordD();
      SetCurr(DEV_PASSWORD_D3);
      break;

    case DEV_PASSWORD_D3:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultD() == 1))
        MakePause(DEV_POSTPASSWORD_D3);
      else 
      {
        if (cbRepeat == 0) ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryPasswordD();
          SetCurr(DEV_PASSWORD_D3);
        }
      } 
      break;

    case DEV_POSTPASSWORD_D3:
      ShowPercent(99);

      cbRepeat = GetMaxRepeats();
      QueryEnergyD();
      SetCurr(DEV_ENERGY_D3);
      break;

    case DEV_ENERGY_D3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ibMinor = 0;
        ReadEnergyD();

        MakePause(DEV_POSTENERGY_D3);
      }
      else 
      {
        if (cbRepeat == 0) ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyD();
          SetCurr(DEV_ENERGY_D3);
        }
      } 
      break;

    case DEV_POSTENERGY_D3:
      cbRepeat = GetMaxRepeats();
      QueryContinueD();
      SetCurr(DEV_CONTINUE_D3);
      break;

    case DEV_CONTINUE_D3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ShowProgress(12,(ulong)100*ibMinor/(16-1));
        ReadEnergyD();

        if (ibMinor < GetEnergyBlocksD())
          MakePause(DEV_POSTCONTINUE_D3);  
        else
        {
          cbRepeat = GetMaxRepeats();
          QueryStopD();
          SetCurr(DEV_QUADRANTS_D3);
        }
      }
      else 
      {
        if (cbRepeat == 0) ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryContinueD();
          SetCurr(DEV_CONTINUE_D3);
        }
      } 
      break;

    case DEV_POSTCONTINUE_D3:
      cbRepeat = GetMaxRepeats();
      QueryContinueD();
      SetCurr(DEV_CONTINUE_D3);
      break;

    case DEV_QUADRANTS_D3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ShowProgress(12,(ulong)100);
        ReadQuadrantsD();

        ReadCurrentD();
      }
      else 
      {
        if (cbRepeat == 0) ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryStopD();
          SetCurr(DEV_QUADRANTS_D3);
        }
      } 
      break;

#endif
