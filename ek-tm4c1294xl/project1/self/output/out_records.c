/*------------------------------------------------------------------------------
OUT_RECORDS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_records.h"
#include "../serial/ports.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "../flash/records2.h"
#include "out_records.h"



void    OutRecordExt(void)
{
  if (InBuff(7)*0x100 + InBuff(8) >= wRECORDS)
    Result(bRES_BADADDRESS);
  else if (GetRecord((class) InBuff(6), InBuff(7)*0x100 + InBuff(8)) == false)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLongBig(GetRecordCount((class) InBuff(6)));
    PushIntBig(wRECORDS);

    Push(&reCurr, SIZEOF_RECORD);
    Output(6+SIZEOF_RECORD);
  }
}


void    OutRecordsBlockExt(void)
{
  if ((InBuff(6) >= bEVENTS) || (InBuff(7) >= bRECORD_PAGES))
    Result(bRES_BADADDRESS);
  else if (GetRecordsBlock((class) InBuff(6), InBuff(7)) == false)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLongBig(GetRecordCount((class) InBuff(6)));
    PushIntBig(wRECORDS);

    Push(&mpbPageIn, wLEAF_BYTES);
    Output(6+wLEAF_BYTES);
  }
}


void    OutRecordsBlockExt2(void)
{
  if ((InBuff(6) >= bEVENTS2) || (InBuff(7)*0x100+InBuff(8) >= wRECORD2_PAGES))
    Result(bRES_BADADDRESS);
  else if (GetRecordsBlock2((class2) InBuff(6), InBuff(7)*0x100+InBuff(8)) == false)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLongBig(GetRecordCount2((class2) InBuff(6)));
    PushIntBig(wRECORDS2);

    Push(&mpbPageIn, wLEAF_BYTES);
    Output(6+wLEAF_BYTES);
  }
}
