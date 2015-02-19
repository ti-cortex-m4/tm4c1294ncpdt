/*------------------------------------------------------------------------------
STORAGE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_flash.h"
#include        "../memory/mem_realtime.h"
#include        "../hardware/watchdog.h"
#include        "../flash/at45.h"
#include        "../energy2.h"
#include        "../display/display.h"
#include        "../delay.h"



//                                             0123456789ABCDEF
static char const       szDataFlashErase[]  = "Тест памяти: 2  ",
                        szDataFlashRead[]   = "Тест памяти: 3  ";


static uint             wPage;



void    ShowDataFlashErase(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/(wIMPHOUCAN_SIZE+bDAYS*2+bMONTHS*3));
}


void    ShowDataFlashRead(void)
{
  ResetWDT();
  ShowPercent((ulong)100*(++wPage)/((wFLA_END-wFLA_BEGIN)/8));
}



void    ResetMemory(void)
{
  memset(&mpimDayCan,    0, sizeof(mpimDayCan));
  memset(&mpimMonCan,    0, sizeof(mpimMonCan));

  memset(&mppoDayGrp,    0, sizeof(mppoDayGrp));
  memset(&mppoMonGrp,    0, sizeof(mppoMonGrp));

  memset(&mpreCntMonCan, 0, sizeof(mpreCntMonCan));
}


bool    ResetDataFlash(void)
{
uint    i;

  ResetMemory();

  ShowHi(szDataFlashErase);
  wPage = 0;

  for (wPageOut=wFLA_IMPHOUCAN; wPageOut<wFLA_IMPDAYCAN; wPageOut++) 
  {
    if (SafePageErase() == 0) return(0);
    if (GetFlashStatus() != 0) return(0);
    ShowDataFlashErase();
  }

  for (i=0; i<bDAYS; i++) 
  {
    if (SaveImpDay(0,i,ibSoftDay) == 0) return(0);
    if (GetFlashStatus() != 0) return(0);
    ShowDataFlashErase();
  }

  for (i=0; i<bMONTHS; i++) 
  {
    if (SaveImpMon(0,i,ibSoftMon) == 0) return(0);
    if (GetFlashStatus() != 0) return(0);
    ShowDataFlashErase();
  }

  for (i=0; i<bDAYS; i++) 
  {
    if (SavePowDay(0,i,ibSoftDay) == 0) return(0);
    if (GetFlashStatus() != 0) return(0);
    ShowDataFlashErase();
  }

  for (i=0; i<bMONTHS; i++) 
  {
    if (SavePowMon(0,i,ibSoftMon) == 0) return(0);
    if (GetFlashStatus() != 0) return(0);
    ShowDataFlashErase();
  }

  for (i=0; i<bMONTHS; i++) 
  {
    if (SaveCntMon(0,i,ibSoftMon) == 0) return(0);
    if (GetFlashStatus() != 0) return(0);
    ShowDataFlashErase();
  }

  ShowHi(szDataFlashRead);
  wPage = 0;

  for (wPageIn=wFLA_BEGIN; wPageIn<wFLA_END; wPageIn += 8)
  {
    if (SafePageRead() == 0) return(0);
    if (GetFlashChecksum() == 0) return(0);
    ShowDataFlashRead();
  }

  DelayMsg(); 

  return(1);
}
