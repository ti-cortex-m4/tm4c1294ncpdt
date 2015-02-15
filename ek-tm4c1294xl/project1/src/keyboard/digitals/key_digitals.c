/*------------------------------------------------------------------------------
KEY_DIGITALS.C

 Цифровые счётчики
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../memory/mem_ports.h"
#include        "../../display/display.h"
#include        "../../keyboard.h"
#include        "../../flash/files.h"
#include        "../../flash/records.h"
#include        "../../digitals/digitals.h"
#include        "../../digitals/devices.h"
#include        "../../serial/speed.h"



//                                          0123456789ABCDEF
static char const       szDigitals[]     = "Счетчики        ",
                        szPort[]         = "Порт...         ",
                        szPhone[]        = "Телефон...      ",
                        szDevice[]       = "Тип счетчика... ",
                        szAddress[]      = "Адрес...        ",
                        szLine[]         = "Вид ~нергии...  ",
                        szCanal[]        = "Номер канала... ",
                        szMaskDigital[]  = "_ __ __ ___ __";


static digital          diT;


                        
void    MakeKeys(void)
{
  switch (diT.bDevice)
  {
    case 1:   strcpy((char *) &mpphKeys[ibX].szNumber, "000000");  break;
    case 2:   strcpy((char *)&mpphKeys[ibX].szNumber, "222222");  break;
    case 4:   strcpy((char *)&mpphKeys[ibX].szNumber, "00000000");  break;
    case 21:  strcpy((char *)&mpphKeys[ibX].szNumber, "00000000");  break;
    default:  strcpy((char *)&mpphKeys[ibX].szNumber, "0");       break;
  }
}



void    key_SetDigitals(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szDigitals);

      Canal();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowDigital(ibX);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDigital(ibX);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) 
        ibX = 0;

      ShowDigital(ibX);
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      diT.ibLine = GetCharLo(12,13) - 1;
      if (diT.ibLine < mpbMaxLines[ diT.bDevice ])
      {
        enKeyboard = KBD_POSTENTER;
        ShowHi(szDigitals);

        AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
        SetDigital(ibX, &diT);
        AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

        MakeDigitalsMask();  
        MakeKeys();
        MakeCorrectLimit();

        if (diT.bDevice != 0)
        {
          ibY = diT.ibPort;
          if (diT.ibPhone == 0)
          {
            switch (diT.bDevice)
            {
              case 1:
              case 2:
              case 12:
              case 3:
              case 4:
              case 11:
              case 20:
              case 18:
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*0.4);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*0.4); break;

              case 6: 
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*1);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*1); break;

              case 7: 
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*60);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*5); break;

              case 15: 
              case 8: 
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*5);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*5); break;

              case 21: 
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*3);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*3); break;

              case 17: 
              case 16: 
              case 14: 
              case 13: 
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*2);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*2); break;

              default:
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*4);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*4); break;
            }
          }
          else
          {
            switch (diT.bDevice)
            {
              case 1:
              case 2:
              case 12:
              case 3:
              case 4:
              case 6:
              case 11:
              case 20:
              case 18:
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*2);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*2); break;

              case 7: 
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*60);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*10); break;

              case 15: 
              case 8: 
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*10);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*10); break;

              default:
                mpwMajInDelay[ibY] = (uint)(wFREQUENCY_T0*8);
                mpwMinInDelay[ibY] = (uint)(wFREQUENCY_T0*8); break;
            }
          }
        }

        if (++ibX >= bCANALS) 
          ibX = 0;

        ShowDigital(ibX);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) ibX--; else ibX = bCANALS-1;

      ShowDigital(ibX);
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((diT.ibPort = GetCharLo(0,0) - 1) < bPORTS)
      {
        if (StreamPortCan(diT.ibPort,ibX) == 1) 
        {
          enKeyboard = KBD_INPUT3;
          ShowHi(szPhone);
          szLo[1] = '.';
        }
        else Beep();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if ((diT.ibPhone = GetCharLo(2,3)) < bCANALS)
      { 
        if (StreamPortPhoneCan(diT.ibPort,diT.ibPhone,ibX) == 1) 
        {
          enKeyboard = KBD_INPUT4;
          ShowHi(szDevice);
          szLo[4] = '.';
        }
        else Beep();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      diT.bDevice = GetCharLo(5,6);
      if (diT.bDevice <= bDEVICES)
      {
        if (diT.bDevice == 0)
        {
          enKeyboard = KBD_POSTENTER;
          ShowHi(szDigitals);

          diT.bAddress = 0;
          diT.ibLine = 0;

          AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
          SetDigital(ibX, &diT);
          AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

          MakeDigitalsMask();  
          MakeKeys();
          // mpbAddLines[ibX] = diT.ibLine;

          ShowDigital(ibX);
        }
        else
        {
          enKeyboard = KBD_INPUT5;
          ShowHi(szAddress);
          szLo[7] = '.';
        }
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      if ((diT.bAddress = GetCharLo(8,10)) < 255)
      {
        if (((diT.bDevice == 9) || (diT.bDevice == 10)) && (diT.bAddress == 0))
          Beep();
        else
        {
          enKeyboard = KBD_INPUT6;

          if ((diT.bDevice == 5) || (diT.bDevice == 6) || (diT.bDevice == 7))
            ShowHi(szCanal);
          else
            ShowHi(szLine);

          szLo[11] = '.';
        }
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if ((enGlobal == GLB_PROGRAM) || ((enGlobal == GLB_REPROGRAM) /*&& SuperUser()*/))
      {
        enKeyboard = KBD_POSTENTER;
        ShowHi(szDigitals);

        diT.ibPort = 0;
        diT.ibPhone = 0;
        diT.bDevice = 0;
        diT.bAddress = 0;
        diT.ibLine = 0;

        AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
        SetDigital(ibX, &diT);
        AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

        MakeDigitalsMask();  
        MakeKeys();

        ShowDigital(ibX);
        LongBeep();
      }
      else Beep();
    }
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if ((enGlobal == GLB_PROGRAM) || ((enGlobal == GLB_REPROGRAM) /*&& SuperUser()*/))
      {
        enKeyboard = KBD_INPUT2;
        ShowHi(szPort);
        ShowLo(szMaskDigital);
      }
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(0,0);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(2,3);
    }
    else 
    if ((enKeyboard == KBD_INPUT4) || (enKeyboard == KBD_POSTINPUT4))
    {
      enKeyboard = KBD_POSTINPUT4;
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
    {
      enKeyboard = KBD_POSTINPUT5;
      ShiftLo(8,10);
    }
    else 
    if ((enKeyboard == KBD_INPUT6) || (enKeyboard == KBD_POSTINPUT6))
    {
      enKeyboard = KBD_POSTINPUT6;
      ShiftLo(12,13);
    }
    else Beep(); 
  }
  else Beep();
}
