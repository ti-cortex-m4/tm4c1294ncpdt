/*------------------------------------------------------------------------------
DIAGRAM!C

 График значений счетчиков по получасам за сутки ('Отчет №65 от 03.08.2010')
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_diagram.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy.h"
#include "../../hardware/watchdog.h"
#include "../../digitals/digitals.h"
//#include "../../realtime/realtime.h"
#include "../../realtime/realtime_storage.h"
#include "../../energy.h"
#include "../../flash/flash.h"
#include "../../flash/files.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "../../time/rtc.h"
#include "diagram.h"



cache const             chEnblDiagram = {ENBL_DIAGRAM, &fEnblDiagram, sizeof(bool)};



void    InitDiagram(void)
{
  LoadCache(&chEnblDiagram);
}


void    ResetDiagram(void)
{
  SaveCacheBool(&chEnblDiagram, false);
}



static bool SaveDgrHou(uint  iwHouTo)
{
  ASSERT(iwHouTo < wHOURS_DIAGRAM);
  return SaveBuff(DIAGRAM_HHR_VALUES + iwHouTo*DIAGRAM_CAN_PAGES, mpDiagram, sizeof(mpDiagram));
}


bool LoadDgrHou(uint  iwHouFrom)
{
  ASSERT(iwHouFrom < wHOURS_DIAGRAM);
  return LoadBuff(DIAGRAM_HHR_VALUES + iwHouFrom*DIAGRAM_CAN_PAGES, mpDiagram, sizeof(mpDiagram));
}



bool    ClearDiagram(void)
{
  uint wPageOut;
  for (wPageOut=DIAGRAM_HHR_VALUES; wPageOut<DIAGRAM_HHR_VALUES+DIAGRAM_PAGES; wPageOut++)
  {
    if (SafePageErase(wPageOut) == 0) return(0);
    if (GetFlashStatus() != 0) return(0);
    ResetWatchdog();
  }

  return 1;
}



void    NextHouDiagram(void)
{
  if (++iwHardDgr >= wHOURS_DIAGRAM)
    iwHardDgr = 0;

  if (++ibSoftDgr >= 2)
    ibSoftDgr = 0;

  SavePointersDgr();


  if (fEnblDiagram)
  {
    LoadDgrHou(iwHardDgr);

    memset(&mpDiagram, 0xFF, sizeof(mpDiagram));

    uchar c;
    for (c=0; c<16; c++)
    {
      if (GetDigitalDevice(c) == 0)
      {
        double db = *PGetCanImpAll(mpimAbsCan,c);
        db *= mpdbValueCntHou[c];
        db += mpdbCount[c];

        diagram vl;
        vl.dbValue = db;

        time ti = *GetCurrTimeDate();
        vl.stValue.bSecond = ti.bSecond;
        vl.stValue.bMinute = ti.bMinute;
        vl.stValue.bHour   = ti.bHour;

        mpDiagram[c] = vl;
      }
    }

    SaveDgrHou(iwHardDgr);
  }
}


void    MakeDiagram(uchar  ibCan, double  db)
{
  LoadDgrHou(iwHardDgr);

  diagram vl;
  vl.dbValue = db;

  time ti = *GetCurrTimeDate();
  vl.stValue.bSecond = ti.bSecond;
  vl.stValue.bMinute = ti.bMinute;
  vl.stValue.bHour   = ti.bHour;

  mpDiagram[ibCan] = vl;

  SaveDgrHou(iwHardDgr);
}
