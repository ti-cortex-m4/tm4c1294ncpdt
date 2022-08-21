/*------------------------------------------------------------------------------
KEY_DIGITALS,C

 Цифровые счетчики
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_records.h"
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



static void MakeKeys(uchar  ibCan, uchar  bDevice)
{
  memset(&mpphKeys[ibCan].szLine, 0, sizeof(line));

  switch (bDevice)
  {
    case 1:   strcpy((char *)&mpphKeys[ibCan].szLine, "000000");    break;
    case 2:   strcpy((char *)&mpphKeys[ibCan].szLine, "222222");    break;
    case 4:   strcpy((char *)&mpphKeys[ibCan].szLine, "00000000");  break;
    case 21:  strcpy((char *)&mpphKeys[ibCan].szLine, "00000000");  break;
    case 34:  strcpy((char *)&mpphKeys[ibCan].szLine, "222222");    break;
    default:  strcpy((char *)&mpphKeys[ibCan].szLine, "0");         break;
  }

  SaveCache(&chKeys);
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
      case 34:
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
      case 40:
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
      case 34:
      case 38:
      case 39:
      case 40:
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



static uchar AddDigital(uchar  ibCan, digital  *pdi)
{
  enKeyboard = KBD_POSTENTER;
  ShowHi(szDigitals);

  ClearSerial(ibCan);

  ibRecordCan = ibCan;
  AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
  SetDigital(ibCan, pdi);
  AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

  MakeKeys(ibCan, pdi->bDevice);

  MakeDigitalsMask();
  MakeCorrectLimit(pdi->ibPort, pdi->bDevice);
  if (pdi->bDevice != 0) MakeInDelays(pdi->ibPort, pdi->ibPhone, pdi->bDevice);

  if (++ibCan >= bCANALS) ibCan = 0;

  ShowDigital(ibCan);

  return ibCan;
}


static uchar AddAllDigitals(uchar  ibCan, digital  *pdi)
{
  enKeyboard = KBD_POSTENTER;
  ShowHi(szDigitals);

  ClearSerials(ibCan, mpbMaxLines[ pdi->bDevice ]);

  uchar i;
  for (i=0; i<mpbMaxLines[ pdi->bDevice ]; i++)
  {
    pdi->ibLine = i;

    ibRecordCan = ibCan;
    AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
    SetDigital(ibCan, pdi);
    AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

    MakeKeys(ibCan, pdi->bDevice);

    ShowDigital(ibCan);
    DelayInf();

    if (++ibCan >= bCANALS) break;
  }

  MakeDigitalsMask();
  MakeCorrectLimit(pdi->ibPort, pdi->bDevice);
  if (pdi->bDevice != 0) MakeInDelays(pdi->ibPort, pdi->ibPhone, pdi->bDevice);

  ShowDigital(ibCan);
  Beep();

  return ibCan;
}



void    key_SetDigitals(void)
{
static digital diT;
static uchar ibCan;

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

      ibCan = 0;
      ShowDigital(ibCan);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibCan = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDigital(ibCan);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibCan >= bCANALS) ibCan = 0;

      ShowDigital(ibCan);
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      if ((diT.bAddress = GetCharLo(8,10)) < 255)
        ibCan = AddAllDigitals(ibCan, &diT);
      else
        Beep();
    }
    else if (enKeyboard == KBD_INPUT6)
    {
      ibCan = AddAllDigitals(ibCan, &diT);
    }
    else if (enKeyboard == KBD_POSTINPUT6)
    {
      diT.ibLine = GetCharLo(12,13) - 1;
      if (diT.ibLine < mpbMaxLines[ diT.bDevice ])
      {
        ibCan = AddDigital(ibCan, &diT);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibCan > 0) ibCan--; else ibCan = bCANALS-1;

      ShowDigital(ibCan);
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((diT.ibPort = GetCharLo(0,0) - 1) < bPORTS)
      {
        if (StreamPortCan(diT.ibPort,ibCan) == 1)
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
        if (StreamPortPhoneCan(diT.ibPort,diT.ibPhone,ibCan) == 1)
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
      if ((diT.bDevice <= bMAXDEVICES) && ValidDevice(diT.bDevice))
      {
        if (diT.bDevice == 0)
        {
          enKeyboard = KBD_POSTENTER;
          ShowHi(szDigitals);

          diT.bAddress = 0;
          diT.ibLine = 0;

          ibRecordCan = ibCan;
          AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
          SetDigital(ibCan, &diT);
          AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

          MakeDigitalsMask();
          MakeKeys(ibCan, diT.bDevice);

          ShowDigital(ibCan);
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

        ClearSerial(ibCan);

        ibRecordCan = ibCan;
        AddSysRecordReprogram(EVE_EDIT_DIGITAL1);
        SetDigital(ibCan, &diT);
        AddSysRecordReprogram(EVE_EDIT_DIGITAL2);

        MakeDigitalsMask();
        MakeKeys(ibCan, diT.bDevice);

        ShowDigital(ibCan);
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
