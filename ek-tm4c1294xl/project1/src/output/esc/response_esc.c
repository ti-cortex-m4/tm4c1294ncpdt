/*------------------------------------------------------------------------------
RESPONSE_ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_esc.h"
#include "../../console.h"
#include "../../serial/ports.h"
#include "../../serial/flow.h"
#include "../../keyboard/key_timedate.h"
#include "../../access.h"
#include "esc.h"


void    EscPtrReset(void)
{
}


void    Esc(uint  wSize)
{
  InitPush(0);

  uchar bT = 0;

  uint i;
  for (i=0; i<wSize; i++)
  {
    bT += SkipChar();
  }

  PushChar(bT);

  Answer(wSize+1, SER_OUTPUT_SLAVE);
}


void    EscDisplay(void)
{
  InitPush(0);

  PushChar(0x0D); PushChar(0x0A); Push(&szHi,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A); Push(&szLo,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A);

  Esc(2*bDISPLAY+3*2);
}



void    EscError(uchar  bCode)
{
  InitPush(0);

  PushChar(0x1B);
  PushChar(bQuery);
  PushChar(bCode);

  Esc(3);
}



static void ShowCtrlZ()
{
  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"Порт %u: Ctrl Z",ibPort+1);
    Clear();
    HideCurrentTime(0);
  }
}


static void ShowCommand(void)
{
  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"Порт %u: Esc %c",ibPort+1,bQuery);
    HideCurrentTime(0);
  }
}

/*
static void ShowNumber(uchar  i)
{
  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi+14,"%2u",i);
    HideCurrentTime(0);
  }
}
*/

void    RunResponseEsc(void)
{
uchar   i;

  if (mpSerial[ibPort] == SER_CTRL_Z)
  {
    mpSerial[ibPort] = SER_BEGIN;
    EscPtrReset();

    ShowCtrlZ();
  }
  else
  if (mpSerial[ibPort] == SER_CHAR)
  {
    mpSerial[ibPort] = SER_BEGIN;

    if (enGlobal == GLB_PROGRAM)
      return;

    if (boBlockingEsc == TRUE)
      return;

    bQuery = InBuff(0);

    ibMachineEsc = mpibMachineEsc[ibPort];

    switch (bQuery)
    {
      case 0x30:
        ibMachineEsc = 0xFF;
        mpibMachineEsc[ibPort] = ibMachineEsc;
        return;

      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
      case 0x3A:
      case 0x3B:
      case 0x3C:
      case 0x3D:
      case 0x3E:
      case 0x3F:
      case 0x40:
        for (i=0; i<bMaxMachineEsc; i++)
        {
          if ((bQuery - 0x31) == (bLogical + i - 1))
            break;
        }

        if (i != bMaxMachineEsc)
        {
          ibMachineEsc = (bQuery - 0x31) - (bLogical - 1);
          mpibMachineEsc[ibPort] = ibMachineEsc;

          InitPush(0);
          PushChar(bQuery);
          Esc(1);

          ShowCommand();
        }
        else
        {
          ibMachineEsc = 0xFF;
          mpibMachineEsc[ibPort] = ibMachineEsc;
        }

        return;
    }

    if (bQuery == 'A')
    {
      Beep();
      ShowCommand();
      return;
    }

    if (ibMachineEsc >= bMaxMachineEsc) return;

    ShowCommand();

    if (boBlockingEsc == TRUE)
    {
      if (bQuery != 'R') 
      {
        InitPush(0);
        Push("Disabled !",10);
        Esc(10);
        return;
      } 
    }

    switch (bQuery)
    {/*
      case 'K':
        if (Correct2Disable()) 
        { 
          Correct2(EVE_ESC_K);

          InitPush(0);
          Push("Correction disabled !",21);
          Esc(21);
          break;
        }

        if (Correct3Disable()) 
        { 
          Correct3(EVE_ESC_K);

          InitPush(0);
          Push("Correction blocked ! ",21);
          Esc(21);
          break;
        }

        CorrectTime(EVE_ESC_K);
        break;

      case 'k':
        if (Correct2Disable()) 
        { 
          Correct2(EVE_ESC_k);

          InitPush(0);
          Push("Correction disabled !",21);
          Esc(21);
          break;
        }

        if (Correct3Disable()) 
        { 
          Correct3(EVE_ESC_k);

          InitPush(0);
          Push("Correction blocked ! ",21);
          Esc(21);
          break;
        }

        InitPush(0);
        PushChar('k');

        if (CorrectTime(EVE_ESC_k) == 1)
          PushChar(0x55);
        else
          PushChar(0x80);

        Esc(2);
        break;

      case 'l':
        i = mpbEsc_l[ ibMachineEsc ];

        if (++i >= wHOURS/48) i = 0;

        mpbEsc_l[ ibMachineEsc ] = i;

        InitPush(0);
        PushChar('l');
        PushChar(i);
        Esc(2);

        ShowNumberEsc( mpbEsc_l[ ibMachineEsc ] );
        break;

      case 'v':
        i = mpbEsc_v[ ibMachineEsc ];

        if (++i >= 6) i = 0;

        mpbEsc_v[ ibMachineEsc ] = i;

        InitPush(0);
        PushChar('v');
        PushChar(i);
        Esc(2);

        ShowNumberEsc( mpbEsc_v[ ibMachineEsc ] );
        break;

      case '{':
        InitPush(0);
        for (i=0; i<16; i++)
        {
          tiAlt = *PGetCanTime(mptiEsc_S, i+16*ibMachineEsc);
          Push(&tiAlt, sizeof(time));
        }
        Esc(16*sizeof(time));
        break;

      case '}':
        InitPush(0);
        for (i=0; i<16; i++)
        {
          tiAlt = *PGetCanTime(mptiEsc_V, i+16*ibMachineEsc);
          Push(&tiAlt, sizeof(time));
        }
        Esc(16*sizeof(time));
        break;

      case 'T':
        InitPush(0);
        PushChar( ToBCD(tiCurr.bSecond) );
        PushChar( ToBCD(tiCurr.bMinute) );
        PushChar( ToBCD(tiCurr.bHour  ) );
        PushChar( ToBCD(tiCurr.bDay   ) );
        PushChar( ToBCD(tiCurr.bMonth ) );
        PushChar( ToBCD(tiCurr.bYear  ) );
        Esc(6);
        break;

      case 'W':
        InitPush(0);

        if (GetFlashStatus() == 0)
          i = 0x07;                            // норма
        else
          i = 0x01;                            // ошибка флэш-памяти

        if (cbPowerOn == 0)
          PushChar(i | 0x08);
        else
        if (cbPowerOn == 1)
          PushChar(i | 0x10);
        else
          PushChar(i);

        Push(&tiPowerOff, sizeof(time));       // время последнего выключения питания
        Push(&tiPowerOn,  sizeof(time));       // время последнего включения питания
        PushChar(cbPowerOn);                   // количество выключений питания

        PushChar(0);                           // время выключения за предыдущий месяц (дней, часов, минут)
        PushChar(0);
        PushChar(0);

        PushChar(0);                           // время выключения за текущий месяц (дней, часов, минут)
        PushChar(0);
        PushChar(0);

        Esc(20);
        break;

      case 'w':
        InitPush(0);

        // первый байт состояния
        i = bOldMode;

        tiAlt = *PGetCurrTimeDate();
        if (GetModeAlt != 0)
          i |= 0x04;

        if (enGlobal == GLB_REPROGRAM)
          i |= 0x20;

        PushChar(i);

        // второй байт состояния
        if (bOldMode == 4)
          PushChar(4);
        else
          PushChar(0);

        // дата/время первого запуска
        PushChar( ToBCD(tiStart.bSecond) );
        PushChar( ToBCD(tiStart.bMinute) );
        PushChar( ToBCD(tiStart.bHour  ) );
        PushChar( ToBCD(tiStart.bDay   ) );
        PushChar( ToBCD(tiStart.bMonth ) );
        PushChar( ToBCD(tiStart.bYear  ) );

        // тарифные зоны по кварталам
        ibMode = 0;
        for (ibMonth=12; ibMonth<16; ibMonth++)
        {
          zoAlt = *PGetZonePowMonthMode();
          PushZone();
        }

        // тарифные зоны текущего месяца
        ibMode  = 0;
        ibMonth = tiCurr.bMonth - 1;

        zoAlt = *PGetZonePowMonthMode();
        PushZone();

        // список праздников
        for (i=0; i<GetRelaxSize(); i++)
        {
          if (i >= 20) break;

          GetRelaxDate(i);
          PushChar( ToBCD(tiRelax.bDay)   );
          PushChar( ToBCD(tiRelax.bMonth) );
        }

        while (i++ < 20)
        {
          PushChar(0x55);
          PushChar(0x55);
        }

        // соcтав групп: все каналы
        for (i=bFRAMES*ibMachineEsc; i<bFRAMES*(1+ibMachineEsc); i++)
        {
          wBuffD = 0;

          for (j=0; j<GetGroupsSize(i); j++)
          {
            if (j > 16) break;
            wBuffD |= (uint)(0x01 << GetGroupsNodeCanal(i,j));
          }

          PushChar(wBuffD % 0x100);
          PushChar(wBuffD / 0x100);
        }

        // соcтав групп: каналы с отрицательным знаком
        for (i=bFRAMES*ibMachineEsc; i<bFRAMES*(1+ibMachineEsc); i++)
        {
          wBuffD = 0;

          for (j=0; j<GetGroupsSize(i); j++)
          {
            if (j > 16) break;
            if (GetGroupsNodeSign(i,j) == 1)
              wBuffD |= (uint)(0x01 << GetGroupsNodeCanal(i,j));
          }

          PushChar(wBuffD % 0x100);
          PushChar(wBuffD / 0x100);
        }

        // коэффициенты трансформации
        for (i=0; i<16; i++)
        {
          reBuffA = *PGetCanReal(mpreTransEng, i+16*ibMachineEsc);
          PushRealBCD();
        }

        // коэффициенты преобразования
        for (i=0; i<16; i++)
        {
          reBuffA = *PGetCanReal(mprePulseHou, i+16*ibMachineEsc);
          PushRealBCD();
        }

        // лимиты
        for (i=0; i<18; i++)  PushChar(0);

        // заводской номер
        PushChar( ToBCD(wPrivate % 100)         );
        PushChar( ToBCD((wPrivate % 10000)/100) );
        PushChar( ToBCD(wPrivate / 10000)       );

        // заводской номер
        PushChar( ToBCD(wPrivate % 100)         );
        PushChar( ToBCD((wPrivate % 10000)/100) );
        PushChar( ToBCD(wPrivate / 10000)       );

        // коэффициенты потерь
        for (i=0; i<16; i++)
        {
          reBuffA = *PGetCanReal(mpreLosse, i+16*ibMachineEsc) * 1000000;
          PushRealBCD();
        }

        Esc(300);
        break;

      case '*':
        InitPush(0);

        ibMode = 0;
        for (ibMonth=0; ibMonth<12; ibMonth++)
        {
          zoAlt = *PGetZonePowMonthMode();
          PushZone();
        }

        ibMode = 0;
        for (ibMonth=0; ibMonth<12; ibMonth++)
        {
          zoAlt = *PGetZoneEngMonthMode();
          PushZone();
        }

        PushChar(0);
        PushChar(0);
        PushChar(0);
        PushChar(0);

        if (boPublicCurr == FALSE)
          PushChar(1);
        else
          PushChar(0);

        if (boPublicPrev == FALSE)
          PushChar(1);
        else
          PushChar(0);

        Esc(300);
        break;
*/
      case 'R':
        InitPush(0);
        Push("CќЊ+2 V.06 10.10.08!",20);
        PushChar(0x31+ibMachineEsc);
        Esc(21);
        break;

      case 'а':
      case 'б':
      case 'в':
      case 'г':
      case 'д':
      case 'е':
      case 'ж':
      case 'з':
      case 'и':
      case 'й':
      case 'к':
      case 'л':
      case 'м':
      case 'н':
        i = bQuery-'а';
        if (TrueKey(i) == 1)
        {
          bKey = mpbKeys[i];
          fKey = 1;

          EscDisplay();
        }
        else EscError(bESC_BADDATA);
        break;

      case 'о':
        EscDisplay();
        break;
/*
#ifdef  FLOW
      case 0x1C:
        InitPush(0);

        for (i=0; i<16; i++)
          PushChar(GetDigitalDevice(i+16*ibMachineEsc));

        for (i=0; i<16; i++)
        {
          PushChar(GetDigitalAddress(i+16*ibMachineEsc));
          PushChar(GetDigitalLine(i+16*ibMachineEsc)+1);
        }

        Esc(16+32);
        break;

      case 0x1F:
        if (cbWaitQuery != 0)
        {
          InitPush(0);
          Push("Transit error: busy !",21);
          Esc(21);
        }
        else if (ibPort == 0) 
        {
          RunFlow0();

          InitPush(0);
          Push("Transit OK: 1 !",15);
          Esc(15);
        }
        else if (ibPort == 1)
        {
          RunFlow1();

          InitPush(0);
          Push("Transit OK: 1 !",15);
          Esc(15);
        }
        break;
#endif

      case 'Щ':
        InitPush(0);
        PushChar(bPortGPS);
        PushChar(bStatusGPS);
        PushChar(bVersionMaxGPS);
        PushChar(bVersionMinGPS);
        PushChar(bGMT);
        Push(mpboGPSRun, sizeof(mpboGPSRun));
        Push(mpcwGPSRun, sizeof(mpcwGPSRun));
        Push(&tiPrevCorrect, sizeof(time));
        Push(&tiPostCorrect, sizeof(time));
        Push(&mpcwPosValueCurr, sizeof(mpcwPosValueCurr));
        Push(&mpcwNegValueCurr, sizeof(mpcwNegValueCurr));
        Push(&mpcwPosCountCurr, sizeof(mpcwPosCountCurr));
        Push(&mpcwNegCountCurr, sizeof(mpcwNegCountCurr));
        Push(&mpcwPosValuePrev, sizeof(mpcwPosValuePrev));
        Push(&mpcwNegValuePrev, sizeof(mpcwNegValuePrev));
        Push(&mpcwPosCountPrev, sizeof(mpcwPosCountPrev));
        Push(&mpcwNegCountPrev, sizeof(mpcwNegCountPrev));
        PushChar(SeasonCurr());
        PushChar(boSeasonGPS);
        Esc(345+2);
        break;

      case 'Ъ':
        InitPush(0);
        for (i=0; i<bCANALS; i++)
        {
          PushChar(mpboDefEscV[i]); PushInt(mpcwEscV_OK[i]); PushInt(mpcwEscV_Error[i]);
          PushChar(mpboDefEscS[i]); PushInt(mpcwEscS_OK[i]); PushInt(mpcwEscS_Error[i]);
          PushChar(mpboDefEscU[i]); PushInt(mpcwEscU_OK[i]); PushInt(mpcwEscU_Error[i]);          
        }
        Esc(bCANALS*15);
        break;

      case 'Ь':
        InitPush(0);
        for (i=0; i<bCANALS; i++)
        {
          PushInt(mpcwDigital_OK[i]);
          PushInt(mpcwProfile_OK[i]); PushInt(mpcwProfile_Error[i]);
          PushInt(mpcwCalcDig[i]);
        }
        Esc(bCANALS*8);
        break;

      case 'Ю':
        InitPush(0);
        PushInt(GetCODEChecksum());
        PushInt(wPrivate);
        PushChar(bLogical);
        Esc(5);
        break;
*/
      case 'Я':
        InitPush(0);
        PushInt(wPrivate);
        Esc(2);
        break;

      default:
//        EscPtrReset();
        break;
    }
  }
}


/*
void    EscAT(void)
{
  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('\r');
  PushChar('\n');

  Answer(4,SER_OUTPUT_SLAVE);

  DelayMsg();

  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('&');                        // &D0 - игнорировать сигнал DTR
  PushChar('D');
  PushChar('0');

  PushChar('&');                        // &K0 - управление потоком запрещено
  PushChar('K');
  PushChar('0');

  PushChar('S');                        // S0=2 - подъём телефонной трубки на втором гудке
  PushChar('0');
  PushChar('=');
  PushChar('2');

  PushChar('\r');
  PushChar('\n');

  Answer(8,SER_OUTPUT_SLAVE);
}


void    SlaveModem(void)
{
  if ((boSlaveModem == boTrue) && (mpanSendAT[ibPort] == ANS_ANSWER))
  {
    mpanSendAT[ibPort] = ANS_BEGIN;

    SaveDisplay();

    sprintf(szHi,"Порт %bu: AT      ",ibPort+1);
    Clear();
    DelayMsg();

    LoadDisplay();

    EscAT();
    fSendAT = 0;
  }
}
*/


void    RunResponseEsc_All(void)
{
  ibPort = 0;
  if (IsFlow0() == 0) RunResponseEsc();

  ibPort = 1;
  if (IsFlow1() == 0) RunResponseEsc();

  ibPort = 2;
  RunResponseEsc();

  ibPort = 3;
  RunResponseEsc();
}
