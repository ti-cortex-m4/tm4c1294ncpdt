/*------------------------------------------------------------------------------
U_EVENTS.C


------------------------------------------------------------------------------*/
/*
#include        <string.h>
#include "main.h"
#include "xdata.h"
#include "rtc.h"
#include "timedate.h"
#include "engine.h"
#include "flash.h"
#include "record.h"
#include "record2.h"
#include "ports.h"
#include "ports2.h"
#include "queries2.h"
#include "postinput2.h"
#include "watchdog.h"



#ifndef MODBUS

uint    GetPagesCount(uchar  ibClass)
{
  if (ibClass == 1)
    return bRECORD_SIZE;
  else if (ibClass == 2) 
    return wRECORD2_SIZE;
  else
    return bRECORD_SIZE;
}


uint    GetMaxRecordsCount(uchar  ibClass)
{
  if (ibClass == 1)
    return wRECORDS;
  else if (ibClass == 2) 
    return wRECORDS2;
  else
    return wRECORDS;
}


uint    GetRecordsCount(uchar  ibClass)
{
  if (ibClass == 1)
    return (cdwSysRecord < wRECORDS) ? cdwSysRecord : wRECORDS;
  else if (ibClass == 2) 
    return (cdwAuxRecord < wRECORDS2) ? cdwAuxRecord : wRECORDS2;
  else
    return (cdwImpRecord < wRECORDS) ? cdwImpRecord : wRECORDS;
}


void    LoadEventsPage(uchar  ibClass, uint  iwPage)
{
//uint    i;

  //x_str("\n\n page"); x_intdec(iwPage); 
  ResetWDT();

  if (ibClass == 1)
    GetRecordsBlock(CLA_SYSTEM, iwPage);
  else if (ibClass == 2) 
    GetRecordsBlock2(CLA_AUXILIARY, iwPage);
  else
    GetRecordsBlock(CLA_IMPULSE, iwPage);
/ *
  x_str("\n");
  for (i=0; i<wFREE_BYTES; i++)
  {
    if (i % sizeof(record) == 0) { x_str("\n"); x_bytedec(i / sizeof(record)); }
    x_bytehex(mpbPageIn[i]);
  }
  x_str("\n");
* /
}


void    ReadEventBlock(uchar  ibBlock) // 1 .. bRECORD_BLOCK
{
  memcpy(&reCurr, &mpbPageIn + ((ibBlock-1) % bRECORD_BLOCK)*sizeof(record), sizeof(record));
  tiAlt = reCurr.tiNow;

  //x_str("\n block"); x_bytedec(ibBlock-1); 
  //x_intdec(reCurr.cdwRecord);
  //x_bytedec(reCurr.evCode); 
  //if (reCurr.evCode != 0xFF) x_time(&reCurr.tiNow); 
}



void    IncEventsCount(uint  i)
{
uint    j;

  i = 6+1+2+2+i*4;
  j = 0x100*GetOutBuff(i+0)+GetOutBuff(i+1);
  j++;
  SetOutBuff(i+0, j / 0x100);
  SetOutBuff(i+1, j % 0x100);
}


void    PushEventsCounts(void)
{
uint    iwPage;
uchar   ibBlock;

  //x_str("\n\n get events table ");
  //x_str("\n day index "); x_intdec(0x100*bInBuff8+bInBuff9);
  //x_str("\n days count "); x_intdec(0x100*bInBuffA+bInBuffB);

  tiAlt = *GetCurrTimeDate();
  dwBuffY = DateToDayIndex();

  fAlt = 0;

  for (iwPage=0; iwPage<GetPagesCount(bInBuff7); iwPage++)
  { 
    LoadEventsPage(bInBuff7, iwPage);

    for (ibBlock=bRECORD_BLOCK; ibBlock>0; ibBlock--) 
    { 
      ReadEventBlock(ibBlock);

      //x_str(" countdown "); x_intdec(bRECORD_BLOCK*iwPage + (bRECORD_BLOCK-ibBlock)); x_intdec(GetRecordsCount(bInBuff7) + bRECORD_BLOCK);
      if (bRECORD_BLOCK*iwPage + (bRECORD_BLOCK-ibBlock) > GetRecordsCount(bInBuff7) + bRECORD_BLOCK)
      {
        //x_str(" exit ");
        return;
      }
      else
      {
        dwBuffC = DateToDayIndex();
        //x_str(" delta "); x_longdec(dwBuffY); x_str("-"); x_longdec(dwBuffC); x_str("="); x_longdec(dwBuffY - dwBuffC);

        if ((fAlt == 0) && (dwBuffY >= dwBuffC))
        {
          if (dwBuffY - dwBuffC >= 0x100*bInBuff8+bInBuff9) 
          {
            //x_str(" start ");
            fAlt = 1;
          }
        }

        if (fAlt == 1)
        {
          //x_str(" add ");
          IncEventsCount(dwBuffY - dwBuffC);

          if (dwBuffY - dwBuffC >= (0x100*bInBuff8+bInBuff9) + (0x100*bInBuffA+bInBuffB))
          {
            //x_str(" stop ");
            return;
          }
        }
      }
    }
  }
}


void    GetEventsCountsUni(void)
{
uint    i;

  if (bInBuff6 != 0)
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 3))
    Result2_Info(bUNI_BADDATA,2);
  else if (0x100*bInBuffA+bInBuffB == 0)
    Result2_Info(bUNI_BADDATA,3);
  else
  {
    InitPushUni();

    PushChar(bInBuff7);
    PushInt(GetMaxRecordsCount(bInBuff7));
    PushInt(GetRecordsCount(bInBuff7));
    
    tiAlt = *GetCurrTimeDate();
    dwBuffC = DateToDayIndex();

    for (i=0; i<0x100*bInBuffA+bInBuffB; i++)
    {
      PushInt(0);
      PushChar(tiAlt.bDay);
      PushChar(tiAlt.bMonth);

      dwBuffC--;
      DayIndexToDate(dwBuffC);
    }

    //x_init();
    PushEventsCounts();
    //x_done();

    Output2(1+2+2+(0x100*bInBuffA+bInBuffB)*4);
  }
}



void    PushEventText(uchar  code  *szT)
{
uchar   i;

  fAlt = 1;
  for (i=0; i<63-1; i++)
  {
    if (!*szT) fAlt = 0;
    if (fAlt == 1) PushChar(*szT++); else PushChar(0);
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


void    PushEventParams(void)
{
  switch (reCurr.evCode)
  {
    case EVE_PREVNEXTTIME2: 

    case EVE_PROGRAM_2: 
    case EVE_EXT_CORRECT2: 
    case EVE_ESC_K: 
    case EVE_ESC_k: 
    case EVE_INQ_CORRECT1: 
    case EVE_INQ_CORRECT2: 
    case EVE_INQ_CORRECT4: 
      tiAlt.bSecond = reCurr.mpbBuff[0];
      tiAlt.bMinute = reCurr.mpbBuff[1];
      tiAlt.bHour   = reCurr.mpbBuff[2];
      tiAlt.bDay    = reCurr.mpbBuff[3];
      tiAlt.bMonth  = reCurr.mpbBuff[4];
      tiAlt.bYear   = reCurr.mpbBuff[5];

      coFloat.dwBuff = DateToSecIndex();

      PushChar(coFloat.mpbBuff[0]);
      PushChar(coFloat.mpbBuff[1]);
      PushChar(coFloat.mpbBuff[2]);
      PushChar(coFloat.mpbBuff[3]);
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

  tiAlt = reCurr.tiNow;
}



void    PushEvents2(uint  iwPage, uchar  ibBlock, uchar  bTotal)
{
uchar   i,j;

  //x_str("\n\n push events \n");
  //x_str("\n page "); x_intdec(iwPage); x_str(" block "); x_bytedec(ibBlock-1); x_str(" total "); x_bytedec(bTotal);
  //x_str(" index "); x_bytedec(bInBuffA); x_str(" count "); x_bytedec(bInBuffB);

  InitPushUni();

  j = 0;
  LoadEventsPage(bInBuff6, iwPage);

  for (i=0; i<bTotal; i++) 
  {
    ReadEventBlock(ibBlock);

    //x_str(" index "); x_bytedec(i); 
    if (i+1 >= bInBuffA)
    { 
      if ((tiAlt.bDay == bInBuff7) && (tiAlt.bMonth == bInBuff8) && (tiAlt.bYear == bInBuff9))
      {
        //x_str(" push ");
        PushChar(reCurr.evCode); 
        PushEventParams();

        PushChar(tiAlt.bMinute); 
        PushChar(tiAlt.bHour); 
        PushChar(tiAlt.bDay); 
        PushChar(tiAlt.bMonth); 
        PushChar(tiAlt.bYear); 

        if (++j >= bInBuffB)
        {
          //x_str("\n success"); 
          Output2(bInBuffB*10);
          return;
        }
      }
    }

    if (++ibBlock > bRECORD_BLOCK)
    {
      ibBlock = 1;
      if (iwPage > 0) 
      {
        iwPage--;
        LoadEventsPage(bInBuff6, iwPage);
      }
      else
      {
        //x_str("\n underflow"); 
        Result2_Info(bUNI_BADDATA,7);
        return;
      }
    }
  }

   //x_str("\n failure"); 
   Result2_Info(bUNI_BADDATA,8);
}


void    PushEvents1(void)
{
uint    iwPage,i;
uchar   ibBlock,j,bTotal;

  //x_str("\n\n get events \n"); 
  //x_bytedec(bInBuff7); x_str("."); x_bytedec(bInBuff8); x_str("."); x_bytedec(bInBuff9);
  //x_str(" index "); x_bytedec(bInBuffA); x_str(" count "); x_bytedec(bInBuffB);

  fAlt = 0;
  bTotal = 0;
  i = 0;
  j = 0;

  for (iwPage=0; iwPage<GetPagesCount(bInBuff6); iwPage++)
  {
    LoadEventsPage(bInBuff6, iwPage);

    for (ibBlock=bRECORD_BLOCK; ibBlock>0; ibBlock--) 
    { 
      ReadEventBlock(ibBlock);

      if ((tiAlt.bDay == bInBuff7) && (tiAlt.bMonth == bInBuff8) && (tiAlt.bYear == bInBuff9))
      { 
        //x_str(" calc ");

        fAlt = 1;
        bTotal++;
        i = iwPage;
        j = ibBlock;
      }
      else
      {
        if (fAlt == 1)
        { 
          //x_str("\n success"); 
          PushEvents2(i, j, bTotal);
          return;
        }
      }
    }
  }

  //x_str("\n failure"); 
  Result2_Info(bUNI_BADDATA,6);
}


void    GetEventsUni(void)
{
  if ((bInBuff6 < 1) || (bInBuff6 > 3))
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 31))
    Result2_Info(bUNI_BADDATA,2);
  else if ((bInBuff8 < 1) || (bInBuff8 > 12))
    Result2_Info(bUNI_BADDATA,3);
  else if (bInBuff9 > 99)
    Result2_Info(bUNI_BADDATA,4);
  else if (bInBuffB == 0)
    Result2_Info(bUNI_BADDATA,5);
  else
  {
    //x_init();
    SetDelayUni();
    PushEvents1();
    //x_done();
  }
}



void    GetEventsMessagesUni(void) 
{
uchar   i;

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

    for (i=0; i<bInBuff9; i++)
      PushEventsMessage(bInBuff8 + i);

    Output2(2+bInBuff9*64);
  }
}

#endif
*/
