/*------------------------------------------------------------------------------
UNI_EVENTS3,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_records.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../time/calendar.h"
#include "response_uni.h"
#include "uni_events0.h"
#include "uni_events3.h"



static void PushEventText(uchar const  *sz)
{
  bool f = 1;

  uchar i;
  for (i=0; i<63-1; i++)
  {
    if (!*sz) f = 0;
    if (f == 1) PushChar(*sz++); else PushChar(0);
  }

  PushChar(0);
}


static void PushEventMessage(uchar  bCode)
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
      PushEventMessage(bInBuff8 + i);
    }

    Output2(2+bInBuff9*64);
  }
}
