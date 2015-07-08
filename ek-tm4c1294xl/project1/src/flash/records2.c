/*------------------------------------------------------------------------------
RECORDS2,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_records.h"
#include "../serial/ports.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "records2.h"



bool    GetRecord(class  cl, uint  iwRecord)
{
  uint wPage;
  switch (cl)
  {
    case CLA_KEYBOARD: wPage = KEY_RECORD; break;
    case CLA_SYSTEM:   wPage = SYS_RECORD; break;
    case CLA_DIGITAL:  wPage = DIG_RECORD; break;
    case CLA_IMPULSE:  wPage = IMP_RECORD; break;
    case CLA_MODEM:    wPage = MOD_RECORD; break;
    case CLA_PHONES2:  wPage = PH2_RECORD; break;
    default: ASSERT(false);
  }

  uint i = (iwRecord % wRECORDS);

  OpenIn(wPage + i / bRECORD_BLOCK);
  BuffToRecord((uchar *) &mpbPageIn + (i % bRECORD_BLOCK)*SIZEOF_RECORD);

  return(1);
}


ulong   GetRecordCount(class  cl)
{
  switch (cl)
  {
    case CLA_KEYBOARD: return(cdwKeyRecord);
    case CLA_SYSTEM:   return(cdwSysRecord);
    case CLA_DIGITAL:  return(cdwDigRecord);
    case CLA_IMPULSE:  return(cdwImpRecord);
    case CLA_MODEM:    return(cdwModRecord);
    case CLA_PHONES2:  return(cdwPh2Record);
    default: ASSERT(false); return 0;
  }
}


bool    GetRecordsBlock(class  cl, uchar  ibBlock)
{
  uint i = GetRecordCount(cl) % wRECORDS;
  ibBlock = (bRECORD_PAGES + i/bRECORD_BLOCK - ibBlock) % bRECORD_PAGES;

  switch (cl)
  {
    case CLA_KEYBOARD: return(OpenIn(KEY_RECORD + ibBlock));
    case CLA_SYSTEM:   return(OpenIn(SYS_RECORD + ibBlock));
    case CLA_DIGITAL:  return(OpenIn(DIG_RECORD + ibBlock));
    case CLA_IMPULSE:  return(OpenIn(IMP_RECORD + ibBlock));
    case CLA_MODEM:    return(OpenIn(MOD_RECORD + ibBlock));
    case CLA_PHONES2:  return(OpenIn(PH2_RECORD + ibBlock));
    default: ASSERT(false); return 0;
  }
}



ulong   GetRecordCount2(class2  cl)
{
  switch (cl)
  {
    case CLA_AUXILIARY: return(cdwAuxRecord);
    default: ASSERT(false); return 0;
  }
}


bool    GetRecordsBlock2(class2  cl, uint  iwBlock)
{
  uint i = GetRecordCount2(cl) % wRECORDS2;
  iwBlock = (wRECORD2_PAGES + i/bRECORD_BLOCK - iwBlock) % wRECORD2_PAGES;

  switch (cl)
  {
    case CLA_AUXILIARY: return(OpenIn(AUX_RECORD + iwBlock));
    default: ASSERT(false); return 0;
  }
}
