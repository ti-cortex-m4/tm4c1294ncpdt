/*------------------------------------------------------------------------------
STORAGE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../hardware/watchdog.h"
#include "../flash/flash.h"
#include "../nvram/23x1024.h"
#include "../energy2.h"
#include "../kernel/array_mnt.h"
#include "../kernel/arrays_buff.h"
#include "../display/lcd.h"
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
  ShowPercent((ulong)100*(++wPage)/(IMPHOUCAN_PAGES + bMINUTES + bDAYS*2 + bMONTHS*3 + PARAMS_PAGES*wTIMES + bRECORD_PAGES*6 + wRECORD2_PAGES*1));
}


void    ShowFlashRead(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/((FLASH_END-FLASH_BEGIN+1)/2));
}



void    InitStorage(void) // TODO InitStorage
{
if (enGlobal == GLB_WORK)
{

  LoadRealtime();

//  wPageIn = IMPHOUCAN_BUFF;
//  if (SafePageRead())
//  {
//    time ti;
//    memcpy(&ti, &mpbPageIn[wLEAF_BYTES+4], sizeof(time));
//
//    ulong dw1 = DateToHouIndex(ti);
//    ulong dw2 = DateToHouIndex(tiCurr);
//
//    if (dw1 == dw2)
//    {
      LoadImpHouBuff();
//    }
//  }

  LoadImpDayBuff();
  LoadImpMonBuff();
  LoadImpAbsBuff();

  LoadPowDayBuff();
  LoadPowMonBuff();

  LoadCntMonBuff();
}
}



bool ResetFlash(void)
{
uint    i;

  ShowHi(szMemoryTest1);

  for (i=0; i<=dwNVRAM_BYTES/1000; i++)
  {
    ResetWDT();
    if (Test1WriteNvramBuff(i*1000, 1000) == false) TestError(szBadNVRAM);
    if (Test1ReadNvramBuff(i*1000, 1000) == false) TestError(szBadNVRAM);
    ShowPercent(0 + (uint)20*i/(dwNVRAM_BYTES/1000));
  }

  for (i=0; i<=dwNVRAM_BYTES/1000; i++)
  {
    ResetWDT();
    if (Test2WriteNvramBuff(i*1000, 1000, 0x55) == false) TestError(szBadNVRAM);
    if (Test2ReadNvramBuff(i*1000, 1000, 0x55) == false) TestError(szBadNVRAM);
    ShowPercent(20 + (uint)20*i/(dwNVRAM_BYTES/1000));
  }

  for (i=0; i<=dwNVRAM_BYTES/1000; i++)
  {
    ResetWDT();
    if (Test2WriteNvramBuff(i*1000, 1000, 0xAA) == false) TestError(szBadNVRAM);
    if (Test2ReadNvramBuff(i*1000, 1000, 0xAA) == false) TestError(szBadNVRAM);
    ShowPercent(40 + (uint)20*i/(dwNVRAM_BYTES/1000));
  }

  for (i=0; i<=dwNVRAM_BYTES/1000; i++)
  {
    ResetWDT();
    if (Test2WriteNvramBuff(i*1000, 1000, 0xFF) == false) TestError(szBadNVRAM);
    if (Test2ReadNvramBuff(i*1000, 1000, 0xFF) == false) TestError(szBadNVRAM);
    ShowPercent(60 + (uint)20*i/(dwNVRAM_BYTES/1000));
  }

  for (i=0; i<=dwNVRAM_BYTES/1000; i++)
  {
    ResetWDT();
    if (Test2WriteNvramBuff(i*1000, 1000, 0x00) == false) TestError(szBadNVRAM);
    if (Test2ReadNvramBuff(i*1000, 1000, 0x00) == false) TestError(szBadNVRAM);
    ShowPercent(80 + (uint)20*i/(dwNVRAM_BYTES/1000));
  }


  ShowHi(szFlashErase);
  wPage = 0;

  ibSoftDay = 0;
  ibSoftMon = 0; // TODO

  uint m;
  for (m=0; m<bMINUTES; m++)
  {
    if (FreeImpMnt(m) == false) return false;
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

  for (wPageOut=KEY_RECORD; wPageOut<(KEY_RECORD+bRECORD_PAGES*6+wRECORD2_PAGES*1); wPageOut++)
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

//  DelayMsg();

  return true;
}
