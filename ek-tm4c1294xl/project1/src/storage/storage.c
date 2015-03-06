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
#include        "../time/delay.h"



//                                         0123456789ABCDEF
static char const       szFlashErase[]  = "Тест памяти: 2  ",
                        szFlashRead[]   = "Тест памяти: 3  ";


static uint             wPage;



void    ShowFlashErase(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/(IMPHOUCAN_PAGES + bMINUTES + bDAYS*2 + bMONTHS*3 + 7));
}


void    ShowFlashRead(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/((FLS_END-FLS_BEGIN+1)/2));
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

  ibSoftDay = 0;
  ibSoftMon = 0; // TODO

  for (wPageOut=FLS_IMPMNTCAN; wPageOut<(FLS_IMPMNTCAN+bMINUTES); wPageOut++)
  {
    if (SafePageErase() == FALSE) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }

  for (wPageOut=FLS_IMPHOUCAN; wPageOut<(FLS_IMPHOUCAN+IMPHOUCAN_PAGES); wPageOut++)
  {
    if (SafePageErase() == FALSE) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }

  memset(&mpimDayCan, 0, sizeof(mpimDayCan));
  for (i=0; i<bDAYS; i++) 
  {
    if (SaveImpDay(0,i,ibSoftDay) == FALSE) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }

  memset(&mpimMonCan, 0, sizeof(mpimMonCan));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SaveImpMon(0,i,ibSoftMon) == FALSE) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }

  memset(&mppoDayGrp, 0, sizeof(mppoDayGrp));
  for (i=0; i<bDAYS; i++) 
  {
    if (SavePowDay(0,i,ibSoftDay) == FALSE) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }

  memset(&mppoMonGrp, 0, sizeof(mppoMonGrp));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SavePowMon(0,i,ibSoftMon) == FALSE) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }

  memset(&mpreCntMonCan, 0, sizeof(mpreCntMonCan));
  for (i=0; i<bMONTHS; i++) 
  {
    if (SaveCntMon(0,i,ibSoftMon) == FALSE) return FALSE;
    if (GetFlashStatus() != 0) return FALSE;
    ShowFlashErase();
  }

  if (CleanImpHouBuff() == FALSE) return FALSE;

  if (CleanImpDayBuff() == FALSE) return FALSE;
  if (CleanImpMonBuff() == FALSE) return FALSE;
  if (CleanImpAbsBuff() == FALSE) return FALSE;

  if (CleanPowDayBuff() == FALSE) return FALSE;
  if (CleanPowMonBuff() == FALSE) return FALSE;

  if (CleanCntMonBuff() == FALSE) return FALSE;

  ShowHi(szFlashRead);
  wPage = 0;

  for (wPageIn=FLS_BEGIN; wPageIn<FLS_END; wPageIn += 2)
  {
    if (SafePageRead() == FALSE) return FALSE;
    if (GetFlashChecksum() == 0) return FALSE;
    ShowFlashRead();
  }

  DelayMsg(); 

  return TRUE;
}
