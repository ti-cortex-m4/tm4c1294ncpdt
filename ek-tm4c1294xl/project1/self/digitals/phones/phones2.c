/*------------------------------------------------------------------------------
PHONES2!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../serial/ports_push.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_modems.h"
#include "../../serial/modems.h"
#include "phones2.h"
#include "phones2.h"



// размер буфера результата СМС-контроля
#define PHONE2_ANSWER     50

// количество кодов результата СМС-контроля
#define PHONE2_CODES      10

// размер буфера журнала СМС-контроля
#define PHONE2_RECORD     8



// номер порта
uchar                  bPortPhones2;

// прогнозируемая мощность
real                   reCurrPhones2;

// лимит мощности
real                   reMaxxPhones2;

// список телефонов
phone                  mpphPhones2[bPHONES2];

// режим работы
bool                   boDebugPhones2;

// таймаут
uchar                  bDelayPhone2;

// буфера
uchar                  mpbAnswer1Phones2[PHONE2_ANSWER], mpbAnswer2Phones2[PHONE2_ANSWER];

// буфер
stamp                  mpstPhones2[PHONE2_CODES];

// буфер
uchar                  mpbBuffPhones2[PHONE2_RECORD];

// счётчик записей
ulong                  cdwPh2Record;

// счётчики
ulong                  cdwPhones20, cdwPhones21, cdwPhones22, cdwPhones23, cdwPhones24, cdwPhones25;



//                                         0123456789ABCDEF
char const              szPhonesRun2[]    = "СМС-контроль    ",
                        szPhonesMode21[]  = " настройки 1... ",
                        szPhonesMode22[]  = " настройки 2... ",
                        szPhonesMode23[]  = " настройки 3... ",
                        szNoExcess[]      = "нет превышения !",
                        szNoPeak[]        = "непиковые зоны !";


void    ResetPhones2(void) {
uchar   i;

  bPortPhones2 = 0;
  reCurrPhones2 = 0;
  reMaxxPhones2 = 1000;

  for (i=0; i<bPHONES2; i++)
    strcpy(&mpphPhones2[i].szNumber, "0");

  boDebugPhones2 = false;
  bDelayPhone2 = 0;

  memset(&mpbAnswer1Phones2, 0, sizeof(mpbAnswer1Phones2));
  memset(&mpbAnswer2Phones2, 0, sizeof(mpbAnswer2Phones2));

  for (i=0; i<PHONE2_CODES; i++) {
    mpstPhones2[i].cwSelf = 0;
    mpstPhones2[i].tiSelf = tiZero;
  }

  memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));

  cdwPhones20 = 0;
  cdwPhones21 = 0;
  cdwPhones22 = 0;
  cdwPhones23 = 0;
  cdwPhones24 = 0;
  cdwPhones25 = 0;
}



bool    UsePhones2(void) {
  return ((bPortPhones2 > 0) && (bPortPhones2 <= bPORTS));
}



void    QueryMessageMode(void) {
  InitPush();
  PushString("AT+CMGF=1\r\n");
  Query(SERIAL_MODEM, 11, 1);
}



void    QueryMessage0(void) {
  InitPush();
  PushChar(0x1B);
  Query(0, 1, 1);
  DelayOff();
}



void    QueryMessage1(uchar  ibPhn) {
uchar i;

  InitPush();
  PushString("AT+CMGS=");

  phT = mpphPhones2[ibPhn];

  Clear();
  strcpy(szLo, phT.szNumber);

  for (i=0; i<bPHONENUMBER; i++)
  {
    if (phT.szNumber[i] == 0) break;
    PushChar(phT.szNumber[i]);
  }

  PushChar(0x0D);

  Query(4, 7+i+2, 1);
}



void    QueryMessage2() {
uint  i;

  InitPush();

  sprintf(mpbInBuffSave, "SEM-2 %02bu:%02bu:%02bu %02bu.%02bu.20%02bu - ",
    tiCurr.bHour,
    tiCurr.bMinute,
    tiCurr.bSecond,
    tiCurr.bDay,
    tiCurr.bMonth,
    tiCurr.bYear
  );

  i = PushString(mpbInBuffSave);

  if (boDebugPhones2 == true)
    sprintf(mpbInBuffSave+i, "test");
  else
    sprintf(mpbInBuffSave+i, "prognoz %.3f bolsche limita %.3f !", reCurrPhones2, reMaxxPhones2);

  i += PushMessage(mpbInBuffSave+i);

  PushChar(0x1A);   // 0x1A - send message, 0x1B - don't send message

  Query(100, i+1, 1);
}


phones2 WritePhones2() {
uchar i;

  ShowHi(szPhonesRun2);
  QueryMessage0();

  ShowLo(szPhonesMode21);
  for (i=0; i<bMINORREPEATS; i++) {
    DelayOff();
    QueryModemBaud(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
  }

  if (i == bMINORREPEATS) ;


  ShowLo(szPhonesMode22);
  for (i=0; i<bMINORREPEATS; i++) {
    DelayOff();
    QueryModemCommon(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
    sprintf(szLo+15, "%1bu", i+1);
  }

  if (i == bMINORREPEATS)
    return PH2_MODEMCOMMON;


  ShowLo(szPhonesMode23);
  for (i=0; i<bMINORREPEATS; i++) {
    DelayOff();
    QueryMessageMode();

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
    sprintf(szLo+15, "%1bu", i+1);
  }

  if (i == bMINORREPEATS)
    return PH2_MESSAGEMODE;


  for (ibCan=0; ibCan<bPHONES2; ibCan++) {

    phT = mpphPhones2[ibCan];
    if ((phT.szNumber[0] == '0') && (phT.szNumber[1] == 0)) continue;

    mpbBuffPhones2[ibCan] = ibCan+1;

    for (i=0; i<bMINORREPEATS; i++) {
      DelayOff();
      QueryMessage1(ibCan);

      if (Phones2Input0() == SER_GOODCHECK) break;
      if (fKey == 1) return PH2_KEYBREAK;
      sprintf(szLo+15, "%1bu", i+1);
    }

    if (i == bMINORREPEATS)
      return PH2_MESSAGE1;

    DelayOff();
    QueryMessage2();

    if (Phones2Input1() == SER_GOODCHECK) ;

    Clear();
    if (Phones2Answer()) {
      (Phones2Result() == 0x30) ? OK() : sprintf(szLo+3, "ошибка: %c", Phones2Result()); // нужно обрабатывать ошибку
    }
    else Error(); // нужно обрабатывать ошибку
    DelayMsg();
  }


  return PH2_OK;
}


phones2 SafeWritePhones2(uchar  ibPrt) {
stream  s;
uint    w;
phones2 f;

  if (mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) {
    w = mpwMinInDelay[ibPrt];
    mpwMinInDelay[ibPrt] = 5*wFREQUENCY_T0;
    f = WritePhones2();
    mpwMinInDelay[ibPrt] = w;
  }
  else {
    s = mppoPorts[ibPrt].enStream;
    mppoPorts[ibPrt].enStream = STR_MASTERDIRECT;
    w = mpwMinInDelay[ibPrt];
    mpwMinInDelay[ibPrt] = 5*wFREQUENCY_T0;
    f = WritePhones2();
    mppoPorts[ibPrt].enStream = s;
    mpwMinInDelay[ibPrt] = w;
  }

  mpbBuffPhones2[PHONE2_RECORD-1] = f;

  if (f < PHONE2_CODES-1) {
    mpstPhones2[f].cwSelf++;
    mpstPhones2[f].tiSelf = *PGetCurrTimeDate();
  }
  else {
    mpstPhones2[PHONE2_CODES-1].cwSelf++;
    mpstPhones2[PHONE2_CODES-1].tiSelf = *PGetCurrTimeDate();
  }

  return f;
}


void    RunPhones2() {
  if (UsePhones2()) {
    Clear();

    ibPort = bPortPhones2-1;
    diCurr.ibPort = bPortPhones2-1;

    if (SafeWritePhones2(bPortPhones2-1) == PH2_OK) {
      if (boDebugPhones2 == false) cdwPhones25++;
    }
    else
      Error();

    mpSerial[ibPort] = SER_BEGIN;

    Work();
  }
}


void    TestPhones2() {
  AddPh2Record(EVE_PH2_DEBUG);
  memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));

  RunPhones2();

  AddPh2Record(EVE_PH2_FINISH);

  SetCurr(DEV_BEGIN);
  ibPortPause = 0xFF;
}


void    MakePhones2(void) {
  if (UsePhones2() && (enGlobal != GLB_PROGRAM))  {

    cdwPhones20++;
    if ((mpibPowCurrTariff[ GetHouIndex() ] == 2) ||
        (mpibPowCurrTariff[ GetHouIndex() ] == 3))  {

      cdwPhones21++;
      reCurrPhones2 = *PGetPowGrpHouCurr(0,2);
      if (reCurrPhones2 > reMaxxPhones2) {

        cdwPhones23++;
        AddPh2Record(EVE_PH2_START);
        memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));

        boDebugPhones2 = false;
        RunPhones2();

        AddPh2Record(EVE_PH2_FINISH);

        Work(); OK();

        bProgram = 0; wProgram = 0;
        cbShowTime = 2;

        SetCurr(DEV_BEGIN);
        ibPortPause = 0xFF;
      }
      else {
        cdwPhones24++;
        if (boShowMessages == true) {
          ShowHi(szPhonesRun2); ShowLo(szNoExcess);
          DelayMsg();
          Work(); OK();
        }
      }
    }
    else {
      cdwPhones22++;
      if (boShowMessages == true) {
        ShowHi(szPhonesRun2); ShowLo(szNoPeak);
        DelayMsg();
        Work(); OK();
      }
    }
  }
}

/*

#ifndef MODBUS

void    OutPhones2(void) {
uint  i;

  InitPushCRC();
  for (i=0; i<400; i++) PushChar(0);

  InitPushCRC();

  PushChar(boShowMessages);
  PushChar(UsePhones2());
  PushChar(bPortPhones2);

  reBuffA = reCurrPhones2; PushReal();
  reBuffA = reMaxxPhones2; PushReal();

  Push(&mpphPhones2, bPHONES2*sizeof(phone));

  PushChar(boDebugPhones2);
  PushChar(bDelayPhone2);

  Push(&mpbAnswer1Phones2, sizeof(mpbAnswer1Phones2));
  Push(&mpbAnswer2Phones2, sizeof(mpbAnswer2Phones2));

  Push(&mpstPhones2, sizeof(mpstPhones2));

  Push(&mpbBuffPhones2, sizeof(mpbBuffPhones2));

  PushLong(&cdwPhones20);
  PushLong(&cdwPhones21);
  PushLong(&cdwPhones22);
  PushLong(&cdwPhones23);
  PushLong(&cdwPhones24);
  PushLong(&cdwPhones25);

  Output(400);
}

#endif
*/
