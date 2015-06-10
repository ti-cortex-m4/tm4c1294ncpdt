/*------------------------------------------------------------------------------
STORAGE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../hardware/watchdog.h"
#include "../flash/at45.h"
#include "../energy2.h"
#include "../energy3.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "../time/calendar.h"
#include "../realtime/realtime_init.h"



//                                         0123456789ABCDEF
static char const       szMemoryTest1[] = "Тест памяти: 1  ",
                        szFlashErase[]  = "Тест памяти: 2  ",
                        szFlashRead[]   = "Тест памяти: 3  ";


static uint             wPage;



void    ShowFlashErase(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/(IMPHOUCAN_PAGES + bMINUTES + bDAYS*2 + bMONTHS*3 + PARAMS_PAGES*wTIMES + 7));
}


void    ShowFlashRead(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/((FLASH_END-FLASH_BEGIN+1)/2));
}



void    InitStorage(void) // TODO InitStorage
{
  LoadRealtime();

  wPageIn = IMPHOUCAN_BUFF;
  if (SafePageRead())
  {
    time ti;
    memcpy(&ti, &mpbPageIn[wFREEPAGE_SIZE+4], sizeof(time));

    ulong dw1 = DateToHouIndex(ti);
    ulong dw2 = DateToHouIndex(tiCurr);

    if (dw1 == dw2)
    {
      LoadImpHouBuff();
    }
  }

  LoadImpDayBuff();
  LoadImpMonBuff();
  LoadImpAbsBuff();

  LoadPowDayBuff();
  LoadPowMonBuff();

  LoadCntMonBuff();
}



bool ResetFlash(void)
{
uint    i;

  ShowHi(szMemoryTest1);
  for (i=0; i<=100; i++)
  {
    ResetWDT();
    ShowPercent(i);
    Delay(20);
  }


  ShowHi(szFlashErase);
  wPage = 0;

  ibSoftDay = 0;
  ibSoftMon = 0; // TODO

  for (wPageOut=IMPMNTCAN; wPageOut<(IMPMNTCAN+bMINUTES); wPageOut++)
  {
    if (SafePageErase() == false) return false;
    if (GetFlashStatus() != 0) return false;
    ShowFlashErase();
  }

  for (wPageOut=IMPHOUCAN; wPageOut<(IMPHOUCAN+IMPHOUCAN_PAGES); wPageOut++)
  {
    if (SafePageErase() == false) return false;
    if (GetFlashStatus() != 0) return false;
    ShowFlashErase();
  }

  memset(&mpimDayCan, 0, sizeof(mpimDayCan));
  for (i=0; i<bDAYS; i++) 
  {
    if (SaveImpDay(0,i,ibSoftDay) == false) return false;
    if (GetFlashStatus() != 0) return false;
    ShowFlashErase();
  }

  memset(&mpimMonCan, 0, sizeof(mpimMonCan));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SaveImpMon(0,i,ibSoftMon) == false) return false;
    if (GetFlashStatus() != 0) return false;
    ShowFlashErase();
  }

  memset(&mppoDayGrp, 0, sizeof(mppoDayGrp));
  for (i=0; i<bDAYS; i++) 
  {
    if (SavePowDay(0,i,ibSoftDay) == false) return false;
    if (GetFlashStatus() != 0) return false;
    ShowFlashErase();
  }

  memset(&mppoMonGrp, 0, sizeof(mppoMonGrp));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SavePowMon(0,i,ibSoftMon) == false) return false;
    if (GetFlashStatus() != 0) return false;
    ShowFlashErase();
  }

  memset(&mpdbCntMonCan, 0, sizeof(mpdbCntMonCan));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SaveCntMon(0,i,ibSoftMon) == false) return false;
    if (GetFlashStatus() != 0) return false;
    ShowFlashErase();
  }

  for (wPageOut=PARAMS_VALUES; wPageOut<(PARAMS_VALUES+PARAMS_PAGES*wTIMES); wPageOut++)
  {
    if (SafePageErase() == false) return false;
    if (GetFlashStatus() != 0) return false;
    ShowFlashErase();
  }

  if (CleanImpHouBuff() == false) return false;

  if (CleanImpDayBuff() == false) return false;
  if (CleanImpMonBuff() == false) return false;
  if (CleanImpAbsBuff() == false) return false;

  if (CleanPowDayBuff() == false) return false;
  if (CleanPowMonBuff() == false) return false;

  if (CleanCntMonBuff() == false) return false;


  ShowHi(szFlashRead);
  wPage = 0;

  for (wPageIn=FLASH_BEGIN; wPageIn<FLASH_END; wPageIn += 2)
  {
    if (SafePageRead() == false) return false;
    if (GetFlashChecksum() == 0) return false;
    ShowFlashRead();
  }

  DelayMsg(); 

  return true;
}
