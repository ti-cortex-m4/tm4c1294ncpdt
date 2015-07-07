/*------------------------------------------------------------------------------
UNI_EVENTS3.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_records.h"
#include "../../memory/mem_flash.h"
#include "../../include/flash.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/print2.h"
#include "../../flash/records.h"
#include "../../flash/records2.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/rtc.h"
#include "../../hardware/watchdog.h"
#include "response_uni.h"
#include "uni_events0.h"
#include "uni_events3.h"



void    PushEventText(uchar  *szT)
{
uchar   i;

  bool f = 1;
  for (i=0; i<63-1; i++)
  {
    if (!*szT) f = 0;
    if (f == 1) PushChar(*szT++); else PushChar(0);
  }

  PushChar(0);
}


void    PushEventsMessage(uchar  bCode)
{
  PushChar(bCode);

  switch (bCode)
  {
    case EVE_PREVNEXTTIME2:   PushEventText("Начало догонки после выключения #t4"); break;
    case EVE_POSTNEXTTIME:    PushEventText("Конец  догонки"); break;
    case EVE_WATCHDOG:        PushEventText("Watchdog reset"); break;
    case EVE_START:           PushEventText("Запуск"); break;
    case EVE_RESTART:         PushEventText("Перезапуск"); break;
    case EVE_PASSWORD:        PushEventText("Распароливание"); break;
    case EVE_DOOROPEN:        PushEventText("Дверца открыта"); break;
    case EVE_DOORCLOSE:       PushEventText("Дверца закрыта"); break;

    case EVE_PROGRAM_2:       PushEventText("Коррекция c клавиатуры: #t4"); break;
    case EVE_EXT_CORRECT2:    PushEventText("Коррекция - запрос 0xFF 0x0B: #t4"); break;
    case EVE_ESC_K:           PushEventText("Коррекция - запрос Esc K: #t4"); break;
    case EVE_ESC_k:           PushEventText("Коррекция - запрос Esc k: #t4"); break;
    case EVE_INQ_CORRECT1:    PushEventText("Коррекция 1: #t4"); break;
    case EVE_INQ_CORRECT2:    PushEventText("Коррекция 2: #t4"); break;
    case EVE_INQ_CORRECT4:    PushEventText("Коррекция 3: #t4"); break;
    case EVE_TIME_OK:         PushEventText("Коррекция: ОК"); break;

    case 62: PushEventText("Канал запрещен !"); break;
    case 63: PushEventText("Получас запрещен !"); break;
    case 64: PushEventText(" Канал #bd[0], регулярный опрос *"); break;
    case 65: PushEventText(" Канал #bd[0], ручной опрос *"); break;
    case 99: PushEventText("Готовность: #id[0]-#id[1] ========"); break;
    case 78: PushEventText("Завершение: опрос счётчиков"); break;
    case 97: PushEventText("Завершение: #id[0]-#id[1] *"); break;
    case 81: PushEventText("Начало дозвона"); break;
    case 82: PushEventText("Конец  дозвона"); break;
    case 83: PushEventText("Начало отбоя"); break;
    case 84: PushEventText("Конец  отбоя"); break;
    case 86: PushEventText("Опрос завершен ! ========"); break;
    case 87: PushEventText("Опрос прерван ==========="); break;
    case 88: PushEventText("Начало расчёта 1"); break;
    case 89: PushEventText("Конец  расчёта 1"); break;
    case 90: PushEventText("Без расчёта"); break;
    case 91: PushEventText("Начало расчёта 2"); break;
    case 92: PushEventText("Конец  расчёта 2"); break;
    case 93: PushEventText("Ошибка #bh[0].#bh[1].#bh[2]"); break;
    case 94: PushEventText("Опрос завершен за #id[0] сек."); break;
    case 95: PushEventText("Начало очистки пустых профилей *"); break;
    case 96: PushEventText("Конец  очистки пустых профилей "); break;
    case 98: PushEventText("Специальный старт: 0x#ih[0]"); break;

    default: PushEventText(" нет описания для события"); break;
  }
}


time    PushEventParams(void)
{
  switch (reCurr.ev)
  {
    case EVE_PREVNEXTTIME2: 

    case EVE_PROGRAM_2: 
    case EVE_EXT_CORRECT2: 
    case EVE_ESC_K: 
    case EVE_ESC_k: 
    case EVE_INQ_CORRECT1: 
    case EVE_INQ_CORRECT2: 
    case EVE_INQ_CORRECT4: 
      {
        time  ti;
        ti.bSecond = reCurr.mpbBuff[0];
        ti.bMinute = reCurr.mpbBuff[1];
        ti.bHour   = reCurr.mpbBuff[2];
        ti.bDay    = reCurr.mpbBuff[3];
        ti.bMonth  = reCurr.mpbBuff[4];
        ti.bYear   = reCurr.mpbBuff[5];

        combo32 co;
        co.dwBuff = DateToSecIndex(ti);

        PushChar(co.mpbBuff[0]);
        PushChar(co.mpbBuff[1]);
        PushChar(co.mpbBuff[2]);
        PushChar(co.mpbBuff[3]);
      }
      break;

    case 64: 
    case 65: 
      PushChar(reCurr.mpbBuff[0]+1);
      PushChar(0);
      PushChar(0);
      PushChar(0);
      break;

    case 93: 
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      PushChar(0);
      break;

    case 94: 
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(0);
      PushChar(0);
      break;

    case 98: 
      PushChar(reCurr.mpbBuff[0]);
      PushChar(reCurr.mpbBuff[1]);
      PushChar(0);
      PushChar(0);

    case 97: 
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      PushChar(reCurr.mpbBuff[4]);
      PushChar(reCurr.mpbBuff[5]);
      break;

    case 99: 
      PushChar(reCurr.mpbBuff[0]);
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      break;

    default: PushChar(0); PushChar(0); PushChar(0); PushChar(0); break;  
  }

  return reCurr.ti;
}



void    GetEventsMessagesUni(void) 
{
  if (bInBuff6 != 0)
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 3))
    Result2_Info(bUNI_BADDATA,2);
  else if (bInBuff9 == 0)
    Result2_Info(bUNI_BADDATA,3);
  else if ((uint)(bInBuff8 + bInBuff9 - 1) > 255)
    Result2_Info(bUNI_BADDATA,4);
  else
  {
    SetDelayUni();

    InitPushUni();

    PushChar(bInBuff7);
    PushChar(0xFF);

    uchar i;
    for (i=0; i<bInBuff9; i++)
    {
      PushEventsMessage(bInBuff8 + i);
    }

    Output2(2+bInBuff9*64);
  }
}
