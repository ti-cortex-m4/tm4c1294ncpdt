/*------------------------------------------------------------------------------
STORAGE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_flash.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../hardware/watchdog.h"
#include        "../flash/at45.h"
#include        "../energy2.h"
#include        "../energy3.h"
#include        "../display/display.h"
#include        "../delay.h"



//                                         0123456789ABCDEF
static char const       szFlashErase[]  = "Тест памяти: 2  ",
                        szFlashRead[]   = "Тест памяти: 3  ";


static uint             wPage;



void    ShowFlashErase(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/(IMPHOUCAN_PAGES + bDAYS*2 + bMONTHS*3 + 6));
}


void    ShowFlashRead(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/((FLS_END-FLS_BEGIN)/8));
}



void    InitStorage(void)
{
  LoadImpHouBuff();

  LoadImpDayBuff();
  LoadImpMonBuff();
  LoadImpAbsBuff();

  LoadPowDayBuff();
  LoadPowMonBuff();

  LoadCntMonBuff();
}



boolean ResetFlash(void)
{
uint    i;

  ShowHi(szFlashErase);
  wPage = 0;

  for (wPageOut=FLS_IMPHOUCAN; wPageOut<FLS_IMPDAYCAN; wPageOut++) 
  {
    if (SafePageErase() == FALSE) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }

  memset(&mpwImpHouCan, 0, sizeof(mpwImpHouCan));
  if (SaveImpHouBuff() == 0) return FALSE;

  memset(&mpimDayCan, 0, sizeof(mpimDayCan));
  for (i=0; i<bDAYS; i++) 
  {
    if (SaveImpDay(0,i,ibSoftDay) == 0) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }
  if (SaveImpDayBuff() == 0) return FALSE;

  memset(&mpimMonCan, 0, sizeof(mpimMonCan));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SaveImpMon(0,i,ibSoftMon) == 0) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }
  if (SaveImpMonBuff() == 0) return FALSE;

  memset(&mpimAbsCan, 0, sizeof(mpimAbsCan));
  if (SaveImpAbsBuff() == 0) return FALSE;

  memset(&mppoDayGrp, 0, sizeof(mppoDayGrp));
  for (i=0; i<bDAYS; i++) 
  {
    if (SavePowDay(0,i,ibSoftDay) == 0) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }
  if (SavePowDayBuff() == 0) return FALSE;

  memset(&mppoMonGrp, 0, sizeof(mppoMonGrp));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SavePowMon(0,i,ibSoftMon) == 0) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }
  if (SavePowMonBuff() == 0) return FALSE;

  memset(&mpreCntMonCan, 0, sizeof(mpreCntMonCan));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SaveCntMon(0,i,ibSoftMon) == 0) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }
  if (SaveCntMonBuff() == 0) return FALSE;

  ShowHi(szFlashRead);
  wPage = 0;

  for (wPageIn=FLS_BEGIN; wPageIn<FLS_END; wPageIn += 8)
  {
    if (SafePageRead() == FALSE) return FALSE;
    if (GetFlashChecksum() == 0) return FALSE;
    ShowFlashRead();
  }

  DelayMsg(); 

  return TRUE;
}
