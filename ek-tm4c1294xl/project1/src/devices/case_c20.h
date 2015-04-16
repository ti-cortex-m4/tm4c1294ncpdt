/*
#ifndef SKIP_C

    case DEV_INIT_61_C2: // опрос начат  
      if (boShortProfileC == boFalse)
      { 
        InitHeaderC_6();

        //x_str("\n INIT MAIN QUERY");
        ResetDataC1();
        MakePause(DEV_DATA_61_C2);
      }
      else
      {
        ShowLo(" ошибка режима  ");
        ErrorProfile();
      }
      break;

    case DEV_DATA_61_C2: // основной опрос                  
      //x_str("\n\n START MAIN QUERY");

      cbRepeat = bMINORREPEATS;
      QueryHeaderC1_6();
      SetCurr(DEV_HEADER_61_C2);
      break;

    case DEV_HEADER_61_C2:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_61_C2);         
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink(); cbRepeat--;

          QueryHeaderC1_6();
          SetCurr(DEV_HEADER_61_C2);
        }
      } 
      break;

    case DEV_POSTHEADER_61_C2:                   
      if (PushDataC1_6() == 0)
      {
        //x_str("\n DONE PROFILE 1");
        DoneProfile(); // опрос завершен
      }
      else if (ibValue7 < bVALUE7_USED_SIZE)
      { 
        //x_str("\n NEXT MAIN QUERY");
        MakePause(DEV_DATA_61_C2); // продолжаем основной опрос
      }
      else 
      {
        ibHouCheck = 0;
        ResetDataC2();
        MakePause(DEV_DATA_62_C2); // начинаем проверочный опрос
      }
      break;

    case DEV_DATA_62_C2: // проверочный опрос
      //x_str("\n START TEST QUERY: "); x_bytehex(ibHouCheck); x_bytehex(mpbHouCheck[ibDig]);

      cbRepeat = bMINORREPEATS;   
      QueryHeaderC2_6();
      SetCurr(DEV_HEADER_62_C2);
      break;

    case DEV_HEADER_62_C2:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_62_C2);         
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink(); cbRepeat--;

          QueryHeaderC2_6();
          SetCurr(DEV_HEADER_62_C2);
        }
      } 
      break;

    case DEV_POSTHEADER_62_C2:                   
      if (PushDataC2_6() == 0)
      {
        //x_str("\n DONE PROFILE 2");
        DoneProfile(); // опрос завершен
      }
      else if (ibValue7 < bVALUE7_USED_SIZE)
      { 
        //x_str("\n NEXT TEST QUERY");
        MakePause(DEV_DATA_62_C2);  // продолжаем проверочный опрос
      }
      else 
      {
        //x_str("\n CHECK");
        if (TestDataC0_6() == 0)
        { 
          //x_str("\n GOOD CHECK");
          if (++ibHouCheck < mpbHouCheck[ibDig])
          {
            ResetDataC2();
            MakePause(DEV_DATA_62_C2); // начинаем следующий проверочный опрос
          }
          else if (SaveDataC0_6() == 1)
          { 
            //x_str("\n NEXT NORMAL READ"); 
            ResetDataC1();
            MakePause(DEV_DATA_61_C2); // следующий основной опрос
          }
          else
          { 
            //x_str("\n DONE PROFILE 3");
            DoneProfile(); // опрос завершен
          }
        }
        else
        {          
          //x_str("\n WRONG CHECK");

          sprintf(szLo, "проверка: ошибка");
          ibHouCheck = 0;
          ResetDataC2();
          MakePause(DEV_DATA_62_C2); // начинаем проверочный опрос заново
        }  
      }
      break;

#endif
*/