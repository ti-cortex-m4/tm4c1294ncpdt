/*------------------------------------------------------------------------------
OUT_RECORDS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"



void    OutRecordExt(void)
{
  if (InBuff(7)*0x100 + InBuff(8) >= wRECORDS)
    Result(bRES_BADADDRESS);
  else if (GetRecord(InBuff(6), InBuff(7)*0x100 + InBuff(8)) == 0)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLong( PGetRecordCount(InBuff(6)) );
    PushInt(wRECORDS);

    Push(&reCurr, sizeof(record));
    Output(6+sizeof(record));
  }
}


void    OutRecordsBlockExt(void)
{
  if ((InBuff(6) >= bEVENTS) || (InBuff(7) >= bRECORD_SIZE))
    Result(bRES_BADADDRESS);
  else if (GetRecordsBlock(InBuff(6),InBuff(7)) == 0)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLong( PGetRecordCount(InBuff(6)) );
    PushInt(wRECORDS);

    Push(&mpbPageIn, wFREEPAGE_SIZE);
    Output(6+wFREEPAGE_SIZE);
  }
}


void    OutRecordsBlockExt2(void)
{
  if ((InBuff(6) >= bEVENTS2) || (InBuff(7)*0x100+InBuff(8) >= wRECORD2_SIZE))
    Result(bRES_BADADDRESS);
  else if (GetRecordsBlock2(InBuff(6),InBuff(7)*0x100+InBuff(8)) == 0)
    Result(bRES_BADFLASH);
  else
  {
    InitPushCRC();
    PushLong( PGetRecordCount2(InBuff(6)) );
    PushInt(wRECORDS2);

    Push(&mpbPageIn, wFREEPAGE_SIZE);
    Output(6+wFREEPAGE_SIZE);
  }
}
