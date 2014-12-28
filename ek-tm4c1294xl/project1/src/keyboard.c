/*------------------------------------------------------------------------------
KEYBOARD.C

 Главная функция обработки нажатий клавиатуры
------------------------------------------------------------------------------*/
/*
#include        <absacc.h>
*/
#include        "main.h"
/*
#include        "xdata.h"
#include        "display.h"
#include        "lines.h"
#include        "beep.h"
#include        "label.h"
#include        "delay.h"
#include        "timer0.h"
#include        "programs.h"
#include        "programs2.h"
#include        "nexttime.h"
#include        "sensors.h"
#include        "digitals.h"
#include        "status.h"
#include        "essential.h"
#include        "info.h"
#include        "record.h"
#include        "keyboard2.h"
#include        "answer_flag.h"
#include        "_timedate.h"
#include        "_groups.h"
#include        "_password.h"
#include        "_start.h"
#include        "_yesno.h"
#include        "_nodes.h"
#include        "_defects.h"
#include        "_canals.h"
#include        "_dayzone.h"
#include        "_yearzone.h"
#include        "_number.h"
#include        "_relaxs.h"
#include        "_relaxs2.h"
#include        "_speed.h"
#include        "_decret.h"
#include        "_season.h"
#include        "_double.h"
#include        "_single.h"
#include        "_single2.h"
#include        "_fullyear.h"
#include        "_fullyear2.h"
#include        "_oldyearzone.h"
#include        "_oldmode.h"
#include        "_oldprogram5.h"
#include        "_oldprogram73.h"
#include        "_oldprogram74.h"
#include        "_search.h"
#include        "_digitals.h"
#include        "_automatic1.h"
#include        "_automatic3.h"
#include        "_version.h"
#include        "_devices.h"
#include        "_flow.h"
#include        "_phones.h"
#include        "_addresses.h"
#include        "_keys.h"
#include        "_hours.h"          
#include        "_sensors.h"          
#include        "_control.h"          
#include        "_analysis.h"
#include        "_delays.h"
#include        "_modems.h"
#include        "_clear.h"
#include        "_limits.h"
#include        "_limits2.h"
#include        "_limits30.h"
#include        "_limits31.h"
#include        "_limits32.h"
#include        "_limits33.h"
#include        "_oldprogram85.h"
#include        "_params.h"
#include        "_divider.h"
#include        "_another.h"
#include        "_newprogram79.h"
#include        "_maxpowcan.h"
#include        "_door.h"
#include        "_contacts.h"
#include        "_contacts2.h"
#include        "_contacts3.h"
#include        "_contacts4.h"
#include        "_contacts5.h"
#include        "_contacts6.h"
#include        "_contacts7.h"
#include        "_contacts8.h"
#include        "_relays.h"
#include        "_static.h"
#include        "_stream.h"
#include        "_quadrants.h"
#include        "_inslines.h"
#include        "_gps_config.h"
#include        "_gps_data.h"
#include        "_gps_gmt.h"
#include        "_gps_correct.h"
#include        "_gps_run.h"
#include        "_smk_config.h"
#include        "_smk_data.h"
#include        "_smk_correct.h"
#include        "_smk_run.h"
#include        "_smk_delay.h"
#include        "_recalc.h"
#include        "_dtr_test.h"
#include        "_dtr_reset.h"
#include        "_device19.h"
#include        "_recalc2.h"
#include        "_extended_3a.h"
#include        "_extended_3b.h"
#include        "_extended_4.h"
#include        "_extended_41.h"
#include        "_reset_4.h"
#include        "_reset_6.h"
#include        "_modems2.h"
#include        "_phones20.h"
#include        "_phones21.h"
#include        "_phones22.h"
#include        "_phones23.h"
#include        "_correct2.h"
#include        "_correct30.h"
#include        "_correct31.h"
#include        "_correct32.h"
#include        "_blocking_esc.h"



//                                         0123456789ABCDEF
uchar           code    szProgram[]     = "Программа ?     ",
                        szMaskKey[]     = " ___            ",
                        szNeed[]        = "Необходимо:     ",
                        szBlock[]       = "Запрещено:      ",
                        szNot[]         = "Нет:            ",
                        szButtonP[]     = "   кнопка 'P'   ",
                        szNoNumber[]    = "номер программы ";


// коды отклика клавиш: '0'..'9', '-', '.', 'Программа', 'Ввод'
uchar           code    mpbKeys[14] = 
{ 0x2B, 0x0E, 0x1E, 0x2E, 0x3E, 0x0D, 0x1D, 0x2D, 0x3D, 0x0B,
  0x1B, 0x3B, 0x07, 0x17 };
*/
uchar                   bKey;
bool                    fKey;
/*
// состояние клавиатурного блока
key             data    enKeyboard;

// состояние прибора
global          data    enGlobal;

// номер вызываемой программы
uchar           data    bProgram;

// флаги обновления показаний
bit                     fUpdateA,
                        fUpdateB;

// глобальные переменные
uchar           data    ibX,ibY,ibZ;

uchar           idata   ibXmin,ibXmax,
                        ibYmin,ibYmax;

uint            idata   iwA,iwAmin,iwAmax;



// инициализация блока клавиатуры
void    InitKeyboard(void)
{
  enKeyboard = KBD_BEGIN;

  bKey = 0;
  fKey = 0;

  cbShowTime = 0;

  boSetTime     = boFalse;
  boSetDate     = boFalse;
  boSetPassword = boTrue;

  if (GetLabelXDATA() == 1)
    enGlobal = GLB_WORK;
  else
    enGlobal = GLB_PROGRAM;

  boDoorPrev = boFalse;
}


// сброс блока клавиатуры
void    ResetKeyboard(void)
{
  boLoadMnt      = boFalse;
  boLoadHou      = boTrue;
//  boLoadCnt      = boTrue;

  boControlTime  = boTrue;
  boManageTime   = boTrue;
  boSlaveModem   = boFalse;
  boShowMessages = boFalse;
  boExtendedEscS = boTrue;
  boExtendedEscV = boTrue;
  boExtendedEscU = boTrue;
  boEnableParam  = boFalse;
  boQuickParam   = boFalse;
  boCustomModem  = boFalse;
  boPoweredEsc   = boTrue;
  boBlockingCRC  = boFalse;
  boBlockingEsc  = boFalse;
  boEnableKeys   = boFalse;
  boEnableLines  = boFalse;

  boSeparateCan  = boFalse;
  boEnableWDT    = boTrue;

  boControlQ     = boFalse;
  boControlK     = boTrue;

  boRecalcMaxPowCurrDay = boFalse;
}



// выводит сообщение об отсутствии программы
void    NoProgram(void)
{
  ShowHi(szNot);
  sprintf(szLo,"  программы %bu  ",bProgram);
  LongBeep();
}


// выводит сообщение о невозможности выполнения программы
void    BlockProgram(uchar  bA)
{
  ShowHi(szBlock);
  sprintf(szLo," программой %bu  ",bA);
  LongBeep();
}


// выводит сообщение о невозможности выполнения программы
void    BlockProgramExt(uchar  bA)
{
  ShowHi(szBlock);
  sprintf(szLo," программой %bu  ",bA);
  NoShowTime(1);
}


// выводит сообщение о невозможности выполнения программы
void    BlockPrograms(uchar  bA, uchar  bB)
{
  ShowHi(szBlock);
  sprintf(szLo," программы %bu,%bu ",bA,bB);
  LongBeep();
}


// выводит сообщение о невыполненной программе
void    NeedProgram(uchar  bA)
{
  ShowHi(szNeed);
  sprintf(szLo,"  программа %bu  ",bA);
  LongBeep();
}


// выводит сообщение о невыполненных программах
void    NeedPrograms(uchar  bA, uchar  bB)
{
  ShowHi(szNeed);
  sprintf(szLo," программы %bu,%bu ",bA,bB);
  LongBeep(); 
}



// выводит сообщение о необходимости ввода номера программы
void    NeedNumber(void)
{
  ShowHi(szNeed);
  ShowLo(szNoNumber);

  LongBeep();
  DelayInf();

  bKey = bKEY_PROGRAM;
  fKey = 1; 
}



// выводит сообщение в зависимсти от текущего варианта просмотра
void    ShowLogin(void)
{
  if ((reReview == REV_GROUPSZONE) || (reReview == REV_GROUPS))
    Group();
  else
    Canal();
}


// возвращает маскимальный индекс в зависимсти от текущего варианта просмотра
uchar   GetMaximum(void)
{
  if ((reReview == REV_GROUPSZONE) || (reReview == REV_GROUPS))
    return(bGROUPS);
  else
    return(bCANALS);
}



// главная функция обработки нажатий на клавиатуру
void    Keyboard(void)
{
uchar   i;

  // проверка состояния датчика
  if ((FVAR(uchar,0x500000) & 0x20) == 0) 
    boDoorCurr = boFalse;
  else         
    boDoorCurr = boTrue;

  if (boDoorCurr != boDoorPrev)
  {
    if (boDoorCurr == boTrue)
      AddSysRecord(EVE_DOOROPEN);
    else
      AddSysRecord(EVE_DOORCLOSE);

    boDoorPrev = boDoorCurr;
  }


  // постоянно выполняемые программы
  if (enGlobal == GLB_PROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bGET_GPS_DATA:       auto_GetGPSData();      break;
      case bGET_GPS_CORRECT:    auto_GetGPSCorrect();   break;
      case bGET_SMK_DATA:       auto_GetSMKData();      break;
      case bGET_SMK_CORRECT:    auto_GetSMKCorrect();   break;
      case bGET_DOOR:           auto_Door();            break;
      case bSET_CONTACTS3:      auto_SetContacts3();    break;
      case bGET_ANALYSIS1:      auto_Analysis1();       break;
#ifdef  FLOW
      case bGET_ANALYSIS2:      auto_Analysis2();       break;
#endif
      case bGET_ANALYSIS3:      auto_Analysis3();       break;
      case bGET_ANALYSIS4:      auto_Analysis4();       break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (bProgram)
    {
      case bGET_CORRECTNOW:
      case bGET_CURRTIME:       auto_GetCurrTime();     break;
      case bGET_CURRDATE:       auto_GetCurrDate();     break;

      case bGET_GPS_DATA:       auto_GetGPSData();      break;
      case bGET_GPS_CORRECT:    auto_GetGPSCorrect();   break;
      case bGET_SMK_DATA:       auto_GetSMKData();      break;
      case bGET_SMK_CORRECT:    auto_GetSMKCorrect();   break;
      case bGET_DOOR:           auto_Door();            break;
      case bSET_CONTACTS3:      auto_SetContacts3();    break;
      case bGET_ANALYSIS1:      auto_Analysis1();       break;
#ifdef  FLOW
      case bGET_ANALYSIS2:      auto_Analysis2();       break;
#endif
      case bGET_ANALYSIS3:      auto_Analysis3();       break;
      case bGET_ANALYSIS4:      auto_Analysis4();       break;
    }                        

    // обновление показаний с каждым импульсом
    if (fUpdateA == 1)          
    {
      fUpdateA = 0;
      switch (bProgram)
      {
//        case bGET_READSENSORS:
        case bGET_COUNTNEW:
        case bGET_COUNTOLD:         if (GetDigitalDevice(ibX) == 0)
                                    auto_GetSingle();   break;

        case bGET_IMPCANCURRMNT:    auto_GetSingle();   break;
      }
    }

    // обновление показаний с частотой 1 Гц
    if (fUpdateB == 1)
    {
      fUpdateB = 0;
      switch (bProgram)
      {
#ifdef  POWER
        case bGET_TRUE:   
        case bGET_FALSE:  
        case bGET_REPEAT: 
        case bGET_MORE:   
        case bGET_LESS:   
        case bGET_BASE:   
#endif
        case bGET_POWGRPPREVHOU:
        case bGET_POWGRPCURRHOU:      

        case bGET_POWGRPCURRMNT:    auto_GetSingle();   break;

        case bGET_POWCANPREVHOU:
        case bGET_POWCANCURRHOU:      

        case bGET_POWCANCURRMNT:    auto_GetSingle2();  break;
/ *
        case bGET_IMPCANMNT:
        case bGET_IMPCANHOU:
        case bGET_POWGRPMNT:
        case bGET_POWGRPHOU:

        case bGET_IMPCANDAY:
        case bGET_IMPCANMON:
        case bGET_IMPCANABS:
        case bGET_ENGGRPDAY:
        case bGET_ENGGRPMON:    auto_GetDouble();       break;
* /
        case bGET_PROGRAM73:    auto_GetOldProgram73(); break;
        case bGET_PROGRAM74:    auto_GetOldProgram74(); break;
      }
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bGET_GPS_DATA:       auto_GetGPSData();      break;
      case bGET_GPS_CORRECT:    auto_GetGPSCorrect();   break;
      case bGET_SMK_DATA:       auto_GetSMKData();      break;
      case bGET_SMK_CORRECT:    auto_GetSMKCorrect();   break;
      case bGET_DOOR:           auto_Door();            break;
      case bSET_CONTACTS3:      auto_SetContacts3();    break;
      case bGET_ANALYSIS1:      auto_Analysis1();       break;
#ifdef  FLOW
      case bGET_ANALYSIS2:      auto_Analysis2();       break;
#endif
      case bGET_ANALYSIS3:      auto_Analysis3();       break;
      case bGET_ANALYSIS4:      auto_Analysis4();       break;
    }
  }

  // факт нажатия на клавиатуру
  if (fKey == 0) return;
  fKey = 0;

  for (i=0; i<sizeof(mpbKeys); i++)
    if (bKey == mpbKeys[i]) break;
      
  if (i < sizeof(mpbKeys)) bKey = i; else return;


  // обновляем показания на дисплее
  fUpdateA = 1;
  fUpdateB = 1;

  // обнуляем счётчик вызова программы по умолчанию
  cbShowTime = 0;

  // разрешаем оставаться в режиме connect на следующие паузу bMAXWAITONLINE 
  cbWaitOnline = 0;

  // останавливаем опрос цифровых счётчиков
  if ((fConnect == 1) || (GetCurr() != DEV_BEGIN)) 
  {
//    if (bKey != bKEY_PROGRAM) return;

    if (((bProgram != bGET_READTIMEDATE1) && 
         (bProgram != bGET_READTIMEDATE2) &&
         (wProgram != wGET_READTRANS)     &&
         (wProgram != wGET_READPULSE)     &&
         (bProgram != bGET_STREAM)        &&
         (bProgram != bGET_CNTCANYEAR1)   &&  
         (bProgram != bGET_CNTCANYEAR10)  &&  
//         (bProgram != bGET_CNTCANYEAR2)   &&  
//         (bProgram != bGET_CNTCANYEAR20)  &&  
         (bProgram != bGET_COUNTNEW)      && 
         (bProgram != bGET_COUNTOLD))     || (bKey == bKEY_PROGRAM))
    {
      SetCurr(DEV_BEGIN); 
      SetPause(DEV_BEGIN);

      if (IsOpenSpecial()) { InfoBreak(); CloseSpecial(); Stop(); } 
      boOpenCalc = boFalse;
      AddDigRecord(EVE_SPECIALCLOSE);

      KeyBreakConnect();
      EnableAnswer();
      return;
    }
  }

  // останавливаем опрос цифровых счётчиков
  if (fCurrent == 1)
  {
    SetCurr(DEV_BEGIN);
    if (cbWaitQuery == 0) cbWaitQuery = bWAITQUERY;
  }

  // перед вызовом программы необходимо нажать кнопку 'Программа'
  if ((enKeyboard == KBD_BEGIN) && (bKey != bKEY_PROGRAM))
  {
    ShowHi(szNeed);
    ShowLo(szButtonP);
    LongBeep();

    return;     
  }

  // нажаты кнопки '-' или '.'
  if ((bKey == bKEY_MINUS) || (bKey == bKEY_POINT))
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS)) 
    {      
      NeedNumber(); DelayInf();
      bKey = bKEY_PROGRAM;
    }
  }

  // нажата кнопка 'Программа'
  if (bKey == bKEY_PROGRAM)
  {
    enKeyboard = KBD_PROGRAM;
    bProgram = 0; wProgram = 0;

    fSlide = 0;           

    ShowHi(szProgram);
    ShowLo(szMaskKey);

    if (enGlobal == GLB_WORK)
      szLo[0] = '>';
    else
    if (enGlobal == GLB_PROGRAM)
      szLo[0] = '-';
    else
    if (enGlobal == GLB_REPROGRAM)
      szLo[0] = '=';

    return;
  }

  // нажата цифровая кнопка: ввод номера программы
  if (bKey < 10)
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS))
    {
      enKeyboard = KBD_DIGITS;
      ShiftLo(1,3);

      return;
    }
  }

  // нажата кнопка 'Ввод'
  if (bKey == bKEY_ENTER)
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS))
    {      
      enKeyboard = KBD_ENTER;

      wProgram = GetInt(1,3);
      if (wProgram > 0xFF) bProgram = 0xFF; else bProgram = wProgram;

      if (bProgram == 0)
      { 
        NeedNumber();
        return;
      }
      else boReset = boTrue;
    }
  }

  // базовая обработка нажатий кнопок
  if (enGlobal == GLB_PROGRAM)
  {
    switch (bProgram)
    {
      case 0xFF:                Keyboard2Program();     break;

      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;
      case bSET_SPEED:          key_SetSpeeds();        break;

      case bSET_GROUPS:         key_SetGroups();        break;
//      case bSET_NODES:          key_SetNodes();         break;

      case bSET_PASSWORD:       key_SetPassword();      break;
      case bSET_STARTHOU:
      case bSET_START:          key_Start();            break;
      case bSET_DEBUG:          key_Debug();            break;
      case bSET_VERSION:        key_GetVersion();       break;

      case bSET_ENABLELOADMNT: 
      case bSET_ENABLELOADHOU: 
//      case bSET_ENABLELOADCNT: 
      case bSET_CONTROLTIME: 
      case bSET_MANAGETIME: 
      case bSET_SLAVEMODEM: 
      case bSET_CUSTOMMODEM: 
      case bSET_POWERED_ESC: 
      case bSET_BLOCKING_CRC: 
      case bSET_ENABLEWATCHDOG: 
      case bSET_EXTENDED_ESC_S: 
      case bSET_EXTENDED_ESC_V: 
      case bSET_EXTENDED_ESC_U: 
      case bSET_ENABLE_PARAM: 
      case bSET_QUICK_PARAM: 
      case bSET_ENABLE_KEYS: 
      case bSET_ENABLE_LINES: 
      case bSET_GPS_SEASON: 
      case bSET_DTR_ENABLE: 
      case bSET_RECALC_ENABLE: 
      case bSET_RECALC_ALWAYS: 
      case bSET_EXT3_FLAG: 
      case bSET_EXT4_FLAG: 
      case bSET_EXT5_FLAG: 
      case bSET_RELAXS_FLAG: 
      case bSET_OLD_VERSION_D:
      case bSET_SHOWMESSAGES:
      case bSET_SEPARATECAN:  / *
      case bSET_RESETZONES: 
      case bSET_RESETGROUPS: 
      case bSET_RESETRELAXS: 
      case bSET_RESETENGINE:  * /
      case bSET_PUBLIC:       
      case bSET_RESETWATCHDOG:     
      case bSET_EXT3_RESET:
      case bSET_RESETCUSTOM:     
      case bSET_RESETFULL:      key_SetYesNo();         break;

      case bSET_MAJORDELAYS:
      case bSET_MINORDELAYS:    key_SetDelays();        break;

#ifdef  FLOW
      case bSET_MAXFLOWDELAY:
#endif
      case bSET_CONNECTTIME:
      case bSET_TIMEOUT_HOU:
      case bSET_TIMEOUT_MNT:
      case bSET_MACHINES:
      case bSET_LOGICAL:        key_SetChar();          break;

      case bSET_PRIVATE:        key_SetInt();           break;

      case bSET_DAYZONE:        key_SetDayZone();       break;
      case bSET_RELAXS:         key_SetRelaxs();        break;

      case bSET_TRANS_ENG:        
      case bSET_TRANS_CNT:        
      case bSET_PULSE_HOU:       
      case bSET_PULSE_MNT:       
      case bSET_LOSSE:         
      case bSET_LEVEL:         
      case bSET_COUNT:          key_SetCanals();        break;

      case bSET_PHONES20:       key_SetPhones20();      break;
      case bSET_PHONES21:       key_SetPhones21();      break;
      case bSET_PHONES22:       key_SetPhones22();      break;
      case bSET_PHONES23:       key_SetPhones23();      break;

      case bSET_CORRECT2:       key_SetCorrect2();      break;
      case bSET_CORRECT30:      key_SetCorrect30();     break;
      case bSET_CORRECT31:      key_SetCorrect31();     break;
      case bSET_CORRECT32:      key_SetCorrect32();     break;

      case bGET_MODEMS_QUALITY: key_GetModemsQuality(); break;
      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_KEYS:           key_SetKeys();          break;
      case bSET_LINES:          key_SetInsLines();      break;

      case bSET_GPS_CONFIG:     key_SetGPSConfig();     break;
      case bSET_GPS_GMT:        key_SetGPS_GMT();       break;
      case bGET_GPS_DATA:       key_GetGPSData();       break;
      case bGET_GPS_CORRECT:    key_GetGPSCorrect();    break;
      case bSET_GPS_RUN:        key_SetGPSRun();        break;

      case bSET_SMK_CONFIG:     key_SetSMKConfig();     break;
      case bGET_SMK_DATA:       key_GetSMKData();       break;
      case bGET_SMK_CORRECT:    key_GetSMKCorrect();    break;
      case bSET_SMK_RUN:        key_SetSMKRun();        break;
      case bSET_SMK_DELAY:      key_SetSMKDelay();      break;

      case bSET_DTR_TEST:       key_SetDTRTest();       break;
      case bSET_DTR_RESET:      key_SetDTRReset();      break;

      case bGET_DEVICESINT:     key_GetDevicesInt();    break;
      case bGET_DEVICESREAL:    key_GetDevicesReal();   break;

      case bSET_SETRECALC:      key_SetRecalc();        break;

#ifdef  DS80C400
      case bSET_ENBLHOURS:      key_SetEnblHours();     break;
      case bSET_ENBLSENSORS:    key_SetEnblSensors();   break;
#endif
      case bSET_CONTROL:        key_SetControl();       break;

      case bGET_COUNTOLD:
//      case bGET_READSENSORS:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:  reReview = REV_CANALS;    
                                key_GetSingle();        break;

//      case bGET_READTRANS:
//      case bGET_READPULSE:      key_GetSingle3();       break;

      case bSET_PROGRAM10:    
      case bSET_PROGRAM17:    
      case bSET_PROGRAM20:    
      case bSET_PROGRAM27:      key_SetOldYearZone();   break;

      case bSET_PROGRAM18:      key_SetOldMode();       break;
/ *
      case bSET_ENGMODE1:    
      case bSET_ENGMODE2:  
      case bSET_ENGMODE3:   
      case bSET_POWMODE1:    
      case bSET_POWMODE2:  
      case bSET_POWMODE3:   
      case bSET_PUBMODE1:    
      case bSET_PUBMODE2:  
      case bSET_PUBMODE3:       key_SetYearZone();      break;
* /
#ifdef  DS80C400
      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:   
      case bSET_SUMMER:         key_SetSeason();        break;
#endif

      case bSET_PROGRAM79:      key_SetNewProgram79();  break;
      case bSET_PROGRAM85:      key_GetOldProgram85();  break;

      case bSET_FINDDEVICESPEED:   key_FindDeviceSpeed();   break;
      case bSET_FINDDEVICENUMBER:  key_FindDeviceNumber();  break;

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_LIMITS:         key_SetLimits();        break;
      case bSET_LIMITS30:       key_SetLimits30();      break;
      case bSET_LIMITS31:       key_SetLimits31();      break;
      case bSET_LIMITS32:       key_SetLimits32();      break;
      case bSET_LIMITS33:       key_SetLimits33();      break;
      case bSET_LIMITS2:        key_SetLimits2();       break;
      case bSET_AUTOMATIC:      key_Automatic();        break;
      case bSET_AUTOMATIC2:     key_Automatic2();       break;

      case bSET_PARAMS:         key_SetParams();        break;
      case bSET_DIVIDER:        key_SetDivider();       break;
      case bGET_PARAMCURR:
      case bGET_PARAMBUFF:
      case bGET_PARAMFULL:      key_GetAnother();       break;

      case bSET_CONTACTS:       key_SetContacts();      break;
      case bSET_CONTACTS2:      key_SetContacts2();     break;
      case bSET_CONTACTS3:      key_SetContacts3();     break;
      case bSET_CONTACTS4:      key_SetContacts4();     break;
      case bSET_CONTACTS5:      key_SetContacts5();     break;
      case bSET_CONTACTS7:      key_SetContacts7();     break;
      case bSET_CONTACTS8:      key_SetContacts8();     break;
      case bSET_RELAYS:         key_SetRelays();        break;

      case bSET_EXT3_EVENTS_A:  key_SetExtended3A();    break;
      case bSET_EXT3_EVENTS_B:  key_SetExtended3B();    break;

      case bSET_EXT4_MONTHS:    key_SetExtended4();     break;
      case bSET_EXT4_CANALS:    key_SetExtended41();    break;
      case bSET_EXT4_RESET:     key_SetReset4();        break;
      case bSET_EXT6_RESET:     key_SetReset6();        break;

      case bSET_RELAXS_TARIFF:  key_SetRelaxs2();       break;

#ifdef  DS80C400
      case bGET_MODEMS:         key_GetModems();        break;
#endif

#ifdef  FLOW
      case bSET_PORTTO:         key_PortTo();           break;
      case bSET_PORTFROM:       key_PortFrom();         break;
      case bGET_ANALYSIS2:      key_Analysis2();        break;
#endif
      case bGET_ANALYSIS1:      key_Analysis1();        break;
      case bGET_ANALYSIS3:      key_Analysis3();        break;
      case bGET_ANALYSIS4:      key_Analysis4();        break;
      case bGET_DOOR:           key_Door();             break;
      case bGET_STREAM:         key_GetStream();        break;
      case bGET_READQUADRANTS:  key_GetQuadrants();     break;

      case bSET_BLOCKING_ESC:   key_SetBlockingEsc();   break;

      default:                  NoProgram();            break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (bProgram)
    {
      case 0xFF:                Keyboard2Work();        break;

      case bGET_CURRTIME:       key_SetCurrTime();      break;
      case bGET_CURRDATE:       key_SetCurrDate();      break;
      case bGET_SPEED:          key_SetSpeeds();        break;

      case bGET_GROUPS:         key_GetGroups();        break;
//      case bSET_NODES:          key_SetNodes();         break;
/ *
      case bGET_DEFECTHOU: 
      case bGET_DEFECTDAY: 
      case bGET_DEFECTMON:      key_GetDefects();       break;
* /
      case bGET_CORRECTNOW:     key_CorrectNow();       break;
      case bGET_CORRECTCURR:    key_GetCorrectCurr();   break;
      case bGET_CORRECTPREV:    key_GetCorrectPrev();   break;

      case bSET_PASSWORD:       key_GetPassword();      break;

      case bSET_VERSION:
      case bGET_VERSION:        key_GetVersion();       break;

      case bSET_MAJORDELAYS:
      case bSET_MINORDELAYS:    key_SetDelays();        break;

#ifdef  FLOW
      case bSET_MAXFLOWDELAY:
#endif
      case bSET_CONNECTTIME:
      case bSET_TIMEOUT_HOU:
      case bSET_TIMEOUT_MNT:
      case bSET_MACHINES:
      case bSET_LOGICAL:        key_SetChar();          break;

      case bSET_PRIVATE:        key_SetInt();           break;

      case bSET_RELAXS:         key_GetRelaxs();        break;
//      case bGET_WEEKDAY:        key_GetWeekday();       break;

      case bGET_PROGRAM5:       key_GetOldProgram5();   break;
      case bGET_PROGRAM84:
      case bGET_PROGRAM85:      key_GetOldProgram84();  break;

      case bGET_PROGRAM18:      key_GetProgram18();     break;
      case bGET_PROGRAM19:      key_GetProgram19();     break;

      case bGET_TRANS_ENG:        
      case bGET_TRANS_CNT:        
      case bGET_PULSE_HOU:       
      case bGET_PULSE_MNT:
/ *      case bGET_VALUE_ENGHOU:
      case bGET_VALUE_CNTHOU:       
      case bGET_VALUE_ENGMNT:       
      case bGET_VALUE_CNTMNT:* /
      case bGET_LOSSE:        
      case bSET_LEVEL:          key_GetCanals();        break;

      case bSET_PHONES20:       key_SetPhones20();      break;
      case bSET_PHONES21:       key_SetPhones21();      break;
      case bSET_PHONES22:       key_SetPhones22();      break;
      case bSET_PHONES23:       key_SetPhones23();      break;

      case bSET_CORRECT2:       key_SetCorrect2();      break;
      case bSET_CORRECT30:      key_SetCorrect30();     break;
      case bSET_CORRECT31:      key_SetCorrect31();     break;
      case bSET_CORRECT32:      key_SetCorrect32();     break;

      case bGET_MODEMS_QUALITY: key_GetModemsQuality(); break;
      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_KEYS:           key_SetKeys();          break;
      case bSET_LINES:          key_SetInsLines();      break;

      case bSET_GPS_CONFIG:     key_SetGPSConfig();     break;
      case bSET_GPS_GMT:        key_SetGPS_GMT();       break;
      case bGET_GPS_DATA:       key_GetGPSData();       break;
      case bGET_GPS_CORRECT:    key_GetGPSCorrect();    break;
      case bSET_GPS_RUN:        key_SetGPSRun();        break;

      case bSET_SMK_CONFIG:     key_SetSMKConfig();     break;
      case bGET_SMK_DATA:       key_GetSMKData();       break;
      case bGET_SMK_CORRECT:    key_GetSMKCorrect();    break;
      case bSET_SMK_RUN:        key_SetSMKRun();        break;
      case bSET_SMK_DELAY:      key_SetSMKDelay();      break;

      case bSET_DTR_RESET:      key_SetDTRReset();      break;

      case bGET_DEVICESINT:     key_GetDevicesInt();    break;
      case bGET_DEVICESREAL:    key_GetDevicesReal();   break;

      case bSET_SETRECALC:      key_SetRecalc();        break;

#ifdef  DS80C400
      case bSET_ENBLHOURS:      key_SetEnblHours();     break;
      case bSET_ENBLSENSORS:    key_SetEnblSensors();   break;
#endif
      case bSET_CONTROL:        key_SetControl();       break;

/ *
      case bSET_ENGMODE1:    
      case bSET_ENGMODE2:  
      case bSET_ENGMODE3:   
      case bSET_POWMODE1:    
      case bSET_POWMODE2:  
      case bSET_POWMODE3:   
      case bSET_PUBMODE1:    
      case bSET_PUBMODE2:  
      case bSET_PUBMODE3:       key_SetYearZone();      break;
* /
#ifdef  DS80C400
      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:   
      case bSET_SUMMER:         key_SetSeason();        break;
#endif
      case bSET_ENABLELOADMNT: 
      case bSET_ENABLELOADHOU: 
//      case bSET_ENABLELOADCNT: 
      case bSET_CONTROLTIME: 
      case bSET_MANAGETIME: 
      case bSET_SLAVEMODEM: 
      case bSET_CUSTOMMODEM: 
      case bSET_POWERED_ESC: 
      case bSET_BLOCKING_CRC: 
      case bSET_ENABLEWATCHDOG: 
      case bSET_EXTENDED_ESC_S: 
      case bSET_EXTENDED_ESC_V: 
      case bSET_EXTENDED_ESC_U: 
      case bSET_ENABLE_PARAM: 
      case bSET_QUICK_PARAM: 
      case bSET_ENABLE_KEYS: 
      case bSET_ENABLE_LINES: 
      case bSET_GPS_SEASON: 
      case bSET_DTR_ENABLE: 
      case bSET_RECALC_ENABLE: 
      case bSET_RECALC_ALWAYS: 
      case bSET_EXT3_FLAG: 
      case bSET_EXT4_FLAG: 
      case bSET_EXT5_FLAG: 
      case bSET_RELAXS_FLAG: 
      case bSET_OLD_VERSION_D:
      case bSET_SHOWMESSAGES: 
      case bSET_SEPARATECAN: 
      case bGET_PUBLIC:         key_SetYesNo();         break;

      case bGET_PROGRAM38:      key_SetOldMode();       break;
#ifdef  POWER
      case bGET_TRUE:   
      case bGET_FALSE:  
      case bGET_REPEAT: 
      case bGET_MORE:   
      case bGET_LESS:   
      case bGET_BASE:   
#endif
      case bGET_COUNTNEW:
      case bGET_COUNTOLD:
//      case bGET_READSENSORS:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:
      case bGET_IMPCANCURRMNT:  reReview = REV_CANALS;    
                                key_GetSingle();        break;

//      case bGET_READTRANS:
//      case bGET_READPULSE:      key_GetSingle3();       break;

      case bGET_ENGGRPYEAR_ABCD:
      case bGET_ENGGRPYEAR_CD:  
      case bGET_ENGGRPYEAR_B:   
      case bGET_ENGGRPYEAR_A:   reReview = REV_GROUPS;
                                key_GetFullyear();      break;  

      case bGET_CNTCANYEAR1:
      case bGET_CNTCANYEAR10:
      case bGET_CNTCANYEAR2:
      case bGET_CNTCANYEAR20:   reReview = REV_CANALS;
                                key_GetFullyear();      break;  

      case bGET_POWGRPPREVHOU:
      case bGET_POWGRPCURRHOU:      

      case bGET_POWGRPDAYPREV_ABCD:
      case bGET_POWGRPDAYPREV_C:    
      case bGET_POWGRPDAYPREV_D:

      case bGET_POWGRPDAYCURR_ABCD:
      case bGET_POWGRPDAYCURR_C:    
      case bGET_POWGRPDAYCURR_D:    

      case bGET_POWGRPMONPREV_ABCD: 
      case bGET_POWGRPMONPREV_C:    
      case bGET_POWGRPMONPREV_D:    

      case bGET_POWGRPMONCURR_ABCD: 
      case bGET_POWGRPMONCURR_C:    
      case bGET_POWGRPMONCURR_D:    

      case bGET_ENGGRPDAYPREV_ABCD:
      case bGET_ENGGRPDAYPREV_CD:  
      case bGET_ENGGRPDAYPREV_B:   
      case bGET_ENGGRPDAYPREV_A:   

      case bGET_ENGGRPDAYCURR_ABCD:
      case bGET_ENGGRPDAYCURR_CD:  
      case bGET_ENGGRPDAYCURR_B:   
      case bGET_ENGGRPDAYCURR_A:   

//      case bGET_ENGGRPMONPREV_SPEC:

      case bGET_ENGGRPMONPREV_ABCD:
      case bGET_ENGGRPMONPREV_CD:  
      case bGET_ENGGRPMONPREV_B:   
      case bGET_ENGGRPMONPREV_A:   

      case bGET_ENGGRPMONCURR_ABCD:
      case bGET_ENGGRPMONCURR_CD:  
      case bGET_ENGGRPMONCURR_B:   
      case bGET_ENGGRPMONCURR_A:   

      case bGET_POWGRPCURRMNT:  reReview = REV_GROUPS;
                                key_GetSingle();        break;

      case bGET_POWCANPREVHOU:
      case bGET_POWCANCURRHOU:      

      case bGET_ENGCANDAYPREV_ABCD:
      case bGET_ENGCANDAYPREV_CD:  
      case bGET_ENGCANDAYPREV_B:   
      case bGET_ENGCANDAYPREV_A:   

      case bGET_ENGCANDAYCURR_ABCD:
      case bGET_ENGCANDAYCURR_CD:  
      case bGET_ENGCANDAYCURR_B:   
      case bGET_ENGCANDAYCURR_A:   

      case bGET_ENGCANMONPREV_ABCD:
      case bGET_ENGCANMONPREV_CD:  
      case bGET_ENGCANMONPREV_B:   
      case bGET_ENGCANMONPREV_A:   

      case bGET_ENGCANMONCURR_ABCD:
      case bGET_ENGCANMONCURR_CD:  
      case bGET_ENGCANMONCURR_B:   
      case bGET_ENGCANMONCURR_A:   

      case bGET_POWCANCURRMNT:  key_GetSingle2();       break;

      case bGET_POWGRPMONPREV_C2:    
      case bGET_POWGRPMONPREV_D2:    
      case bGET_POWGRPMONCURR_C2:    
      case bGET_POWGRPMONCURR_D2: key_GetRecalc2();     break;    

      case bGET_ENGCANYEAR_ABCD:
      case bGET_ENGCANYEAR_CD:  
      case bGET_ENGCANYEAR_B:   
      case bGET_ENGCANYEAR_A:   key_GetFullyear2();     break;  

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_LIMITS:         key_SetLimits();        break;
      case bSET_LIMITS30:       key_SetLimits30();      break;
      case bSET_LIMITS31:       key_SetLimits31();      break;
      case bSET_LIMITS33:       key_SetLimits33();      break;

      case bSET_PARAMS:         key_SetParams();        break;
      case bSET_DIVIDER:        key_SetDivider();       break;
      case bGET_PARAMCURR:
      case bGET_PARAMBUFF:
      case bGET_PARAMFULL:      key_GetAnother();       break;

      case bSET_CONTACTS:       key_SetContacts();      break;
      case bSET_CONTACTS2:      key_SetContacts2();     break;
      case bSET_CONTACTS3:      key_SetContacts3();     break;
      case bSET_CONTACTS4:      key_SetContacts4();     break;
      case bSET_CONTACTS5:      key_SetContacts5();     break;
      case bSET_CONTACTS6:      key_SetContacts6();     break;
      case bSET_CONTACTS8:      key_SetContacts8();     break;

      case bSET_EXT3_EVENTS_A:  key_SetExtended3A();    break;
      case bSET_EXT3_EVENTS_B:  key_SetExtended3B();    break;

      case bSET_EXT4_MONTHS:    key_SetExtended4();     break;
      case bSET_EXT4_CANALS:    key_SetExtended41();    break;
      case bSET_EXT4_RESET:     key_SetReset4();        break;
      case bSET_EXT6_RESET:     key_SetReset6();        break;

      case bSET_RELAXS_TARIFF:  key_SetRelaxs2();       break;

#ifdef  DS80C400
      case bGET_MODEMS:         key_GetModems();        break;
#endif

      case bGET_RUNDIGITALS:    key_RunDigitals();      break;
/ *
      case bGET_IMPCANMNT:
      case bGET_IMPCANHOU:      reReview = REV_CANALS;
                                key_GetDouble();        break;

      case bGET_POWGRPMNT:
      case bGET_POWGRPHOU:      reReview = REV_GROUPS;
                                key_GetDouble();        break;

      case bGET_IMPCANDAY:
      case bGET_IMPCANMON:
      case bGET_IMPCANABS:      reReview = REV_CANALSZONE;
                                key_GetDouble();        break;

      case bGET_ENGGRPDAY:
      case bGET_ENGGRPMON:      reReview = REV_GROUPSZONE;
                                key_GetDouble();        break;
* /
      case bGET_MAXPOWMONCAN:   key_GetMaxPowMonCan();  break;
      case bGET_MAXPOWDAYCAN:   key_GetMaxPowDayCan();  break;

      case bGET_PROGRAM73:      key_GetOldProgram73();  break;
      case bGET_PROGRAM74:      key_GetOldProgram74();  break;

#ifdef  FLOW
      case bSET_PORTTO:         key_PortTo();           break;
      case bSET_PORTFROM:       key_PortFrom();         break;
      case bGET_ANALYSIS2:      key_Analysis2();        break;
#endif
      case bGET_ANALYSIS1:      key_Analysis1();        break;
      case bGET_ANALYSIS3:      key_Analysis3();        break;
      case bGET_ANALYSIS4:      key_Analysis4();        break;
      case bGET_DOOR:           key_Door();             break;
      case bGET_STATIC:         key_GetStatic();        break;
      case bGET_STREAM:         key_GetStream();        break;
      case bGET_READQUADRANTS:  key_GetQuadrants();     break;

      case bSET_BLOCKING_ESC:   key_SetBlockingEsc();   break;

      default:                  NoProgram();            break;
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (bProgram)
    {
      case 0xFF:                Keyboard2Reprogram();   break;

      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;
      case bSET_SPEED:          key_SetSpeeds();        break;

      case bSET_GROUPS:         key_SetGroups();        break;

      case bSET_PASSWORD:       key_SetPassword();      break;
      case bSET_START:          key_Restart();          break;
      case bSET_VERSION:        key_GetVersion();       break;

      case bSET_ENABLELOADMNT: 
      case bSET_ENABLELOADHOU: 
//      case bSET_ENABLELOADCNT: 
      case bSET_CONTROLTIME: 
      case bSET_MANAGETIME: 
      case bSET_SLAVEMODEM: 
      case bSET_CUSTOMMODEM: 
      case bSET_POWERED_ESC: 
      case bSET_BLOCKING_CRC: 
      case bSET_ENABLEWATCHDOG: 
      case bSET_EXTENDED_ESC_S: 
      case bSET_EXTENDED_ESC_V: 
      case bSET_EXTENDED_ESC_U: 
      case bSET_ENABLE_PARAM: 
      case bSET_QUICK_PARAM: 
      case bSET_ENABLE_KEYS: 
      case bSET_ENABLE_LINES: 
      case bSET_GPS_SEASON: 
      case bSET_DTR_ENABLE: 
      case bSET_RECALC_ENABLE: 
      case bSET_RECALC_ALWAYS: 
      case bSET_EXT3_FLAG: 
      case bSET_EXT4_FLAG: 
      case bSET_EXT5_FLAG: 
      case bSET_RELAXS_FLAG: 
      case bSET_OLD_VERSION_D:
      case bSET_SHOWMESSAGES:
      case bSET_SEPARATECAN:  / *
      case bSET_RESETZONES: 
      case bSET_RESETGROUPS: 
      case bSET_RESETRELAXS: 
      case bSET_RESETENGINE:  * /
      case bSET_PUBLIC:       
      case bSET_RECALC2:   
      case bSET_RECALCFULL:   
      case bSET_RECALCMAXPOW:
      case bSET_RECALCENG:    
      case bSET_RESETWATCHDOG:     
      case bSET_EXT3_RESET:
      case bSET_RESETCUSTOM:     
      case bSET_RESETFULL:      key_SetYesNo();         break;

      case bSET_MAJORDELAYS:
      case bSET_MINORDELAYS:    key_SetDelays();        break;

#ifdef  FLOW
      case bSET_MAXFLOWDELAY:
#endif
      case bSET_CONNECTTIME:
      case bSET_TIMEOUT_HOU:
      case bSET_TIMEOUT_MNT:
      case bSET_MACHINES:
      case bSET_LOGICAL:        key_SetChar();          break;

      case bSET_PRIVATE:        key_SetInt();           break;

      case bSET_PROGRAM10:    
      case bSET_PROGRAM17:    
      case bSET_PROGRAM20:    
      case bSET_PROGRAM27:      key_SetOldYearZone();   break;

      case bSET_PROGRAM18:      key_SetOldMode();       break;

      case bSET_DAYZONE:        key_SetDayZone();       break;
      case bSET_RELAXS:         key_SetRelaxs();        break;

      case bSET_LEVEL:         
      case bSET_COUNT:          key_SetCanals();        break;

      case bSET_PHONES20:       key_SetPhones20();      break;
      case bSET_PHONES21:       key_SetPhones21();      break;
      case bSET_PHONES22:       key_SetPhones22();      break;
      case bSET_PHONES23:       key_SetPhones23();      break;

      case bSET_CORRECT2:       key_SetCorrect2();      break;
      case bSET_CORRECT30:      key_SetCorrect30();     break;
      case bSET_CORRECT31:      key_SetCorrect31();     break;
      case bSET_CORRECT32:      key_SetCorrect32();     break;

      case bGET_MODEMS_QUALITY: key_GetModemsQuality(); break;
      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_KEYS:           key_SetKeys();          break;
      case bSET_LINES:          key_SetInsLines();      break;

      case bSET_GPS_CONFIG:     key_SetGPSConfig();     break;
      case bSET_GPS_GMT:        key_SetGPS_GMT();       break;
      case bGET_GPS_DATA:       key_GetGPSData();       break;
      case bGET_GPS_CORRECT:    key_GetGPSCorrect();    break;
      case bSET_GPS_RUN:        key_SetGPSRun();        break;

      case bSET_SMK_CONFIG:     key_SetSMKConfig();     break;
      case bGET_SMK_DATA:       key_GetSMKData();       break;
      case bGET_SMK_CORRECT:    key_GetSMKCorrect();    break;
      case bSET_SMK_RUN:        key_SetSMKRun();        break;
      case bSET_SMK_DELAY:      key_SetSMKDelay();      break;

      case bSET_DTR_TEST:       key_SetDTRTest();       break;
      case bSET_DTR_RESET:      key_SetDTRReset();      break;

      case bGET_DEVICESINT:     key_GetDevicesInt();    break;
      case bGET_DEVICESREAL:    key_GetDevicesReal();   break;

      case bSET_SETRECALC:      key_SetRecalc();        break;

#ifdef  DS80C400
      case bSET_ENBLHOURS:      key_SetEnblHours();     break;
      case bSET_ENBLSENSORS:    key_SetEnblSensors();   break;
#endif
      case bSET_CONTROL:        key_SetControl();       break;

      case bGET_COUNTOLD:
//      case bGET_READSENSORS:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:  reReview = REV_CANALS;    
                                key_GetSingle();        break;

//      case bGET_READTRANS:
//      case bGET_READPULSE:      key_GetSingle3();       break;
/ *
      case bSET_ENGMODE1:    
      case bSET_ENGMODE2:  
      case bSET_ENGMODE3:   
      case bSET_POWMODE1:    
      case bSET_POWMODE2:  
      case bSET_POWMODE3:   
      case bSET_PUBMODE1:    
      case bSET_PUBMODE2:  
      case bSET_PUBMODE3:       key_SetYearZone();      break;
* /
#ifdef  DS80C400
      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:   
      case bSET_SUMMER:         key_SetSeason();        break;
#endif  

      case bSET_PROGRAM79:      key_GetNewProgram79();  break;
      case bSET_PROGRAM85:      key_GetOldProgram85();  break;

      case bSET_FINDDEVICESPEED:   key_FindDeviceSpeed();   break;
      case bSET_FINDDEVICENUMBER:  key_FindDeviceNumber();  break;

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_LIMITS:         key_SetLimits();        break;
      case bSET_LIMITS30:       key_SetLimits30();      break;
      case bSET_LIMITS31:       key_SetLimits31();      break;
      case bSET_LIMITS32:       key_SetLimits32();      break;
      case bSET_LIMITS33:       key_SetLimits33();      break;
      case bSET_LIMITS2:        key_SetLimits2();       break;

      case bSET_PARAMS:         key_SetParams();        break;
      case bSET_DIVIDER:        key_SetDivider();       break;
      case bGET_PARAMCURR:
      case bGET_PARAMBUFF:
      case bGET_PARAMFULL:      key_GetAnother();       break;

      case bSET_CONTACTS:       key_SetContacts();      break;
      case bSET_CONTACTS2:      key_SetContacts2();     break;
      case bSET_CONTACTS3:      key_SetContacts3();     break;
      case bSET_CONTACTS4:      key_SetContacts4();     break;
      case bSET_CONTACTS5:      key_SetContacts5();     break;
      case bSET_CONTACTS6:      key_SetContacts6();     break;
      case bSET_CONTACTS7:      key_SetContacts7();     break;
      case bSET_CONTACTS8:      key_SetContacts8();     break;

      case bSET_EXT3_EVENTS_A:  key_SetExtended3A();    break;
      case bSET_EXT3_EVENTS_B:  key_SetExtended3B();    break;

      case bSET_EXT4_MONTHS:    key_SetExtended4();     break;
      case bSET_EXT4_CANALS:    key_SetExtended41();    break;
      case bSET_EXT4_RESET:     key_SetReset4();        break;
      case bSET_EXT6_RESET:     key_SetReset6();        break;

      case bSET_RELAXS_TARIFF:  key_SetRelaxs2();       break;

#ifdef  DS80C400
      case bGET_MODEMS:         key_GetModems();        break;
#endif

//      case bSET_CLEARCANALS_1:  
      case bSET_CLEARCANALS_2:  key_ClearCanals();      break;

#ifdef  FLOW
      case bSET_PORTTO:         key_PortTo();           break;
      case bSET_PORTFROM:       key_PortFrom();         break;
      case bGET_ANALYSIS2:      key_Analysis2();        break;
#endif
      case bGET_ANALYSIS1:      key_Analysis1();        break;
      case bGET_ANALYSIS3:      key_Analysis3();        break;
      case bGET_ANALYSIS4:      key_Analysis4();        break;
      case bGET_DOOR:           key_Door();             break;
      case bGET_STATIC:         key_GetStatic();        break;
      case bGET_STREAM:         key_GetStream();        break;
      case bGET_READQUADRANTS:  key_GetQuadrants();     break;

      case bSET_BLOCKING_ESC:   key_SetBlockingEsc();   break;

      default:                  NoProgram();            break;
    }
  }
}
*/
