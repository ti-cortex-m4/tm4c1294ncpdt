/*------------------------------------------------------------------------------
OUT_RECORDS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_records.h"
#include "../serial/ports.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "out_records.h"



static bool GetRecord(class  cl, uint  iwRecord)
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
  memcpy(&reCurr, &mpbPageIn + (i % bRECORD_BLOCK)*SIZEOF_RECORD, SIZEOF_RECORD);

  return(1);
}


static ulong GetRecordCount(class  cl)
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


static bool GetRecordsBlock(class  cl, uchar  ibBlock)
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



static ulong GetRecordCount2(class2  cl)
{
  switch (cl)
  {
    case CLA_AUXILIARY: return(cdwAuxRecord);
    default: ASSERT(false); return 0;
  }
}


static bool GetRecordsBlock2(class2  cl, uint  iwBlock)
{
  uint i = GetRecordCount2(cl) % wRECORDS2;
  iwBlock = (wRECORD2_PAGES + i/bRECORD_BLOCK - iwBlock) % wRECORD2_PAGES;

  switch (cl)
  {
    case CLA_AUXILIARY: return(OpenIn(AUX_RECORD + iwBlock));
    default: ASSERT(false); return 0;
  }
}



void    OutRecordExt(void)
{
  if (InBuff(7)*0x100 + InBuff(8) >= wRECORDS)
    Result(bRES_BADADDRESS);
  else if (GetRecord((class) InBuff(6), InBuff(7)*0x100 + InBuff(8)) == 0)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLong( GetRecordCount((class) InBuff(6)) );
    PushInt(wRECORDS);

    Push(&reCurr, SIZEOF_RECORD);
    Output(6+SIZEOF_RECORD);
  }
}


void    OutRecordsBlockExt(void)
{
  if ((InBuff(6) >= bEVENTS) || (InBuff(7) >= bRECORD_PAGES))
    Result(bRES_BADADDRESS);
  else if (GetRecordsBlock((class) InBuff(6), InBuff(7)) == 0)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLong( GetRecordCount((class) InBuff(6)) );
    PushInt(wRECORDS);

    Push(&mpbPageIn, wLEAF_BYTES);
    Output(6+wLEAF_BYTES);
  }
}


void    OutRecordsBlockExt2(void)
{
  if ((InBuff(6) >= bEVENTS2) || (InBuff(7)*0x100+InBuff(8) >= wRECORD2_PAGES))
    Result(bRES_BADADDRESS);
  else if (GetRecordsBlock2((class) InBuff(6), InBuff(7)*0x100+InBuff(8)) == 0)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLong( GetRecordCount2((class) InBuff(6)) );
    PushInt(wRECORDS2);

    Push(&mpbPageIn, wLEAF_BYTES);
    Output(6+wLEAF_BYTES);
  }
}

