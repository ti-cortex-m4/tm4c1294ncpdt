/*------------------------------------------------------------------------------
PHONES2!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_tariffs.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_phones2.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../realtime/realtime.h"
#include "../../energy4.h"
#include "../../serial/ports.h"
#include "../../serial/ports_push.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_modems.h"
#include "../../serial/modems.h"
#include "../../digitals/digitals_status.h"
#include "../../flash/records.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "phones22.h"
#include "phones2.h"



typedef struct
{
  uint          cwSelf;
  time          tiSelf;
} stamp2;



// прогнозируемая мощность
float                  reCurrPhones2;

// таймаут
uchar                  bDelayPhone2;

// буфера
uchar                  mpbAnswer1Phones2[PHONE2_ANSWER], mpbAnswer2Phones2[PHONE2_ANSWER];

// буфер
stamp2                 mpstPhones2[PHONE2_CODES];

// буфер
uchar                  mpbBuffPhones2[PHONE2_RECORD];

// счётчики
ulong                  cdwPhones20, cdwPhones21, cdwPhones22, cdwPhones23, cdwPhones24, cdwPhones25;

// промежуточный буфер
char                   mpbInBuffSave2[100];



cache const             chPortPhones2 = {PORT_PHONES2, &bPortPhones2, sizeof(uchar)};
cache const             chPhones2 = {PHONES2, &mpphPhones2, sizeof(mpphPhones2)};
cache const             chMaxxPhones2 = {PORT_PHONES2, &reMaxxPhones2, sizeof(float)};


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

  uchar c;
  for (c=0; c<bPHONES2; c++)
  {
    mpphPhones2[c].szLine[0] = '0';
  }

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


uint    PushMessage(char*  msT)
{
uint  i = 0;

  while (1)
  {
    if (!*msT) break;
    PushChar(*msT++);
    i++;
  }

  return i;
}


void    QueryMessageMode(void) {
  InitPush(0);
  PushString("AT+CMGF=1\r\n");
  Query(SERIAL_MODEM, 11, 1);
}



void    QueryMessage0(void) {
  InitPush(0);
  PushChar(0x1B);
  Query(0, 1, 1);
  DelayOff();
}



void    QueryMessage1(uchar  ibPhn) {
  InitPush(0);
  PushString("AT+CMGS=");

  line phT = mpphPhones2[ibPhn];

  Clear();
  strcpy(szLo, phT.szLine);

  uchar i;
  for (i=0; i<bLINE_SIZE; i++)
  {
    if (phT.szLine[i] == 0) break;
    PushChar(phT.szLine[i]);
  }

  PushChar(0x0D);

  Query(4, 7+i+2, 1);
}



void    QueryMessage2(bool  fDebug) {
uint  i;

  InitPush(0);

  sprintf(mpbInBuffSave2, "SEM-2 %02u:%02u:%02u %02u.%02u.20%02u - ",
    tiCurr.bHour,
    tiCurr.bMinute,
    tiCurr.bSecond,
    tiCurr.bDay,
    tiCurr.bMonth,
    tiCurr.bYear
  );

  i = PushMessage(mpbInBuffSave2);

  if (fDebug == true)
    sprintf(mpbInBuffSave2+i, "test");
  else
    sprintf(mpbInBuffSave2+i, "prognoz %.3f bolsche limita %.3f !", reCurrPhones2, reMaxxPhones2);

  i += PushMessage(mpbInBuffSave2+i);

  PushChar(0x1A);   // 0x1A - send message, 0x1B - don't send message

  Query(100, i+1, 1);
}


phones2 WritePhones2(bool  fDebug) {
uchar i;

  ShowHi(szPhonesRun2);
  QueryMessage0();

  ShowLo(szPhonesMode21);
  for (i=0; i<MaxRepeatsFixed(); i++) {
    DelayOff();
    QueryModemBaud(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
  }

  if (i == MaxRepeatsFixed()) ;


  ShowLo(szPhonesMode22);
  for (i=0; i<MaxRepeatsFixed(); i++) {
    DelayOff();
    QueryModemCommon(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
    sprintf(szLo+15, "%1u", i+1);
  }

  if (i == MaxRepeatsFixed())
    return PH2_MODEMCOMMON;


  ShowLo(szPhonesMode23);
  for (i=0; i<MaxRepeatsFixed(); i++) {
    DelayOff();
    QueryMessageMode();

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return PH2_KEYBREAK;
    sprintf(szLo+15, "%1u", i+1);
  }

  if (i == MaxRepeatsFixed())
    return PH2_MESSAGEMODE;


  uchar ibCan;
  for (ibCan=0; ibCan<bPHONES2; ibCan++) {

    line phT = mpphPhones2[ibCan];
    if ((phT.szLine[0] == '0') && (phT.szLine[1] == 0)) continue;

    mpbBuffPhones2[ibCan] = ibCan+1;

    for (i=0; i<MaxRepeatsFixed(); i++) {
      DelayOff();
      QueryMessage1(ibCan);

      if (Phones2Input0() == SER_GOODCHECK) break;
      if (fKey == 1) return PH2_KEYBREAK;
      sprintf(szLo+15, "%1u", i+1);
    }

    if (i == MaxRepeatsFixed())
      return PH2_MESSAGE1;

    DelayOff();
    QueryMessage2(fDebug);

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


phones2 SafeWritePhones2(uchar  ibPrt, bool  fDebug) {
stream  s;
uint    w;
phones2 f;

  if (mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) {
    w = mpwMinorInDelay[ibPrt];
    mpwMinorInDelay[ibPrt] = 5*wFREQUENCY_T0;
    f = WritePhones2(fDebug);
    mpwMinorInDelay[ibPrt] = w;
  }
  else {
    s = mppoPorts[ibPrt].enStream;
    mppoPorts[ibPrt].enStream = STR_MASTERDIRECT;
    w = mpwMinorInDelay[ibPrt];
    mpwMinorInDelay[ibPrt] = 5*wFREQUENCY_T0;
    f = WritePhones2(fDebug);
    mppoPorts[ibPrt].enStream = s;
    mpwMinorInDelay[ibPrt] = w;
  }

  mpbBuffPhones2[PHONE2_RECORD-1] = f;

  if (f < PHONE2_CODES-1) {
    mpstPhones2[f].cwSelf++;
    mpstPhones2[f].tiSelf = *GetCurrTimeDate();
  }
  else {
    mpstPhones2[PHONE2_CODES-1].cwSelf++;
    mpstPhones2[PHONE2_CODES-1].tiSelf = *GetCurrTimeDate();
  }

  return f;
}


void    RunPhones2(bool  fDebug) {
  if (UsePhones2()) {
    Clear();

    ibPort = bPortPhones2-1;
    diCurr.ibPort = bPortPhones2-1;

    if (SafeWritePhones2(bPortPhones2-1, fDebug) == PH2_OK) {
      if (fDebug == false) cdwPhones25++;
    }
    else
      Error();

    mpSerial[ibPort] = SER_BEGIN;

    Work();
  }
}


void    TestPhones2(bool  fDebug) {
  AddPh2Record(EVE_PH2_DEBUG);
  memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));

  RunPhones2(fDebug);

  AddPh2Record(EVE_PH2_FINISH);

  SetCurr(DEV_BEGIN);
  ibPortPause = 0xFF;
}


void    MakePhones2(void) {
  if (UsePhones2() && (enGlobal != GLB_PROGRAM))  {

    cdwPhones20++;
    if ((mpibPowCurrTariff[ GetCurrHouIndex() ] == 2) ||
        (mpibPowCurrTariff[ GetCurrHouIndex() ] == 3))  {

      cdwPhones21++;
      reCurrPhones2 = GetPowGrpHouCurr(0,2);
      if (reCurrPhones2 > reMaxxPhones2) {

        cdwPhones23++;
        AddPh2Record(EVE_PH2_START);
        memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));

        RunPhones2(false);

        AddPh2Record(EVE_PH2_FINISH);

        Work(); OK();

        wProgram = 0;
        cbShowCurrTime = 2;

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



void    OutPhones2(void) {
  InitPushCRC();

  uint  i;
  for (i=0; i<400; i++) PushChar(0);

  InitPushCRC();

  PushChar(boShowMessages);
  PushChar(UsePhones2());
  PushChar(bPortPhones2);

  PushFloat(reCurrPhones2);
  PushFloat(reMaxxPhones2);

  Push(&mpphPhones2, sizeof(mpphPhones2));

  PushChar(false);
  PushChar(bDelayPhone2);

  Push(&mpbAnswer1Phones2, sizeof(mpbAnswer1Phones2));
  Push(&mpbAnswer2Phones2, sizeof(mpbAnswer2Phones2));

  Push(&mpstPhones2, sizeof(mpstPhones2));

  Push(&mpbBuffPhones2, sizeof(mpbBuffPhones2));

  PushLongBig(cdwPhones20);
  PushLongBig(cdwPhones21);
  PushLongBig(cdwPhones22);
  PushLongBig(cdwPhones23);
  PushLongBig(cdwPhones24);
  PushLongBig(cdwPhones25);

  Output(400);
}
