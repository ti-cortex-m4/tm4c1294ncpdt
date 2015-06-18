/*------------------------------------------------------------------------------
KEY_DIGITALS,C

 Задание и просмотр цифровых счетчиков
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
#include "../../flash/records.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/devices.h"
#include "../../digitals/correct_limit.h"
#include "../../serial/speeds.h"
#include "../../serial/speeds_display.h"
#include "../../serial/speeds_storage.h"



//                                          0123456789ABCDEF
static char const       szDigitals[]     = "Счетчики        ",
                        szPort[]         = "Порт...         ",
                        szPhone[]        = "Телефон...      ",
                        szDevice[]       = "Тип счетчика... ",
                        szAddress[]      = "Адрес...        ",
                        szLine[]         = "Вид ~нергии...  ",
                        szCanal[]        = "Номер канала... ",
                        szMask[]         = "_ __ __ ___ __";



static void MakeKeys(uchar  ibDig, uchar  bDevice)
{
  memset(&mpphKeys[ibDig].szNumber, 0, sizeof(mpphKeys[ibDig].szNumber));

  switch (bDevice)
  {
    case 1:   strcpy((char *)&mpphKeys[ibDig].szNumber, "000000");    break;
    case 2:   strcpy((char *)&mpphKeys[ibDig].szNumber, "222222");    break;
    case 4:   strcpy((char *)&mpphKeys[ibDig].szNumber, "00000000");  break;
    case 21:  strcpy((char *)&mpphKeys[ibDig].szNumber, "00000000");  break;
    default:  strcpy((char *)&mpphKeys[ibDig].szNumber, "0");         break;
  }

  SaveFile(&flKeys);
}


static void MakeInDelays(uchar  ibPort, uchar  ibPhone, uchar  bDevice)
{
  if (ibPhone == 0)
  {
    switch (bDevice)
    {
      case 1:
      case 2:
      case 12:
      case 3:
      case 4:
      case 11:
      case 20:
      case 18:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*0.4);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*0.4); break;

      case 6:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*1);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*1); break;

      case 7:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*60);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*5); break;

      case 15:
      case 8:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*5);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*5); break;

      case 21:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*3);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*3); break;

      case 17:
      case 16:
      case 14:
      case 13:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*2);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*2); break;

      default:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*4);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*4); break;
    }
  }
  else
  {
    switch (bDevice)
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
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*2);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*2); break;

      case 7:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*60);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*10); break;

      case 15:
      case 8:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*10);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*10); break;

      default:
        mpwMajorInDelay[ibPort] = (uint)(wFREQUENCY_T0*8);
        mpwMinorInDelay[ibPort] = (uint)(wFREQUENCY_T0*8); break;
    }
  }

  SaveMajorInDelay();
  SaveMinorInDelay();
}



static void AddDigital(uchar  ibDig, digital  *pdi)
{
  enKeyboard = KBD_POSTENTER;
  ShowHi(szDigitals);

  AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
  SetDigital(ibDig, pdi);
  AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

  MakeKeys(ibDig, pdi->bDevice);

  MakeDigitalsMask();
  MakeCorrectLimit();
  if (pdi->bDevice != 0) MakeInDelays(pdi->ibPort, pdi->ibPhone, pdi->bDevice);

  if (++ibDig >= bCANALS) ibDig = 0;

  ShowDigital(ibDig);
}


static void AddAllDigitals(uchar  ibDig, digital  *pdi)
{
  enKeyboard = KBD_POSTENTER;
  ShowHi(szDigitals);

  uchar i;
  for (i=0; i<mpbMaxLines[ pdi->bDevice ]; i++)
  {
    pdi->ibLine = i;

    AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
    SetDigital(ibDig, pdi);
    AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

    MakeKeys(ibDig, pdi->bDevice);

    ShowDigital(ibDig);
    DelayMsg();

    if (++ibDig >= bCANALS) break;
  }

  MakeDigitalsMask();
  MakeCorrectLimit();
  if (pdi->bDevice != 0) MakeInDelays(pdi->ibPort, pdi->ibPhone, pdi->bDevice);

  ShowDigital(ibDig);
}



void    key_SetDigitals(void)
{
static digital diT;
static uchar ibDig;

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

      ibDig = 0;
      ShowDigital(ibDig);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibDig = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDigital(ibDig);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibDig >= bCANALS) ibDig = 0;

      ShowDigital(ibDig);
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      if ((diT.bAddress = GetCharLo(8,10)) < 255)
        AddAllDigitals(ibDig, &diT);
      else
        Beep();
    }
    else if (enKeyboard == KBD_INPUT6)
    {
      AddAllDigitals(ibDig, &diT);
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      diT.ibLine = GetCharLo(12,13) - 1;
      if (diT.ibLine < mpbMaxLines[ diT.bDevice ])
      {
        AddDigital(ibDig, &diT);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibDig > 0) ibDig--; else ibDig = bCANALS-1;

      ShowDigital(ibDig);
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((diT.ibPort = GetCharLo(0,0) - 1) < bPORTS)
      {
        if (StreamPortCan(diT.ibPort,ibDig) == 1)
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
        if (StreamPortPhoneCan(diT.ibPort,diT.ibPhone,ibDig) == 1)
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
          SetDigital(ibDig, &diT);
          AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

          MakeDigitalsMask();  
          MakeKeys(ibDig, diT.bDevice);

          ShowDigital(ibDig);
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
      if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
      {
        enKeyboard = KBD_POSTENTER;
        ShowHi(szDigitals);

        diT.ibPort = 0;
        diT.ibPhone = 0;
        diT.bDevice = 0;
        diT.bAddress = 0;
        diT.ibLine = 0;

        AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
        SetDigital(ibDig, &diT);
        AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

        MakeDigitalsMask();  
        MakeKeys(ibDig, diT.bDevice);

        ShowDigital(ibDig);
        LongBeep();
      }
      else Beep();
    }
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
      {
        enKeyboard = KBD_INPUT2;
        ShowHi(szPort);
        ShowLo(szMask);
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
