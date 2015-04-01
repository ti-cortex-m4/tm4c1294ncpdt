
#ifndef SKIP_C

    case DEV_START_C3:
      cbRepeat = bMINORREPEATS;

      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C3);             
      break;

    case DEV_OPENCANAL_C3:
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
        MakePause(DEV_POSTOPENCANAL_C3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenC();
          SetCurr(DEV_OPENCANAL_C3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_C3:
      cbRepeat = bMINORREPEATS;
      QueryTimeC();                          
      SetCurr(DEV_TIME_C3);          
      break;

    case DEV_TIME_C3:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTIME_C3);
      else                                    
      {
        if (cbRepeat == 0) 
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeC();
          SetCurr(DEV_TIME_C3);
        }
      } 
      break;

    case DEV_POSTTIME_C3:
      ReadTimeAltC(); 
      tiOffs = tiAlt;          

      cbRepeat = bMINORREPEATS;
      QueryEnergyAbsC();
      SetCurr(DEV_ENERGY_C3);
      break;

    case DEV_ENERGY_C3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentC();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyAbsC();
          SetCurr(DEV_ENERGY_C3);
        }
      } 
      break;

#endif
