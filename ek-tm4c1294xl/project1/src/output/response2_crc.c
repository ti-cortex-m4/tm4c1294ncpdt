/*------------------------------------------------------------------------------



------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_canals.h"
#include        "../memory/mem_ports.h"
#include        "../states.h"
#include        "../ports.h"
#include        "../postinput_crc.h"
#include        "../tariffs/gaps.h"
#include        "../output/out_groups.h"
#include        "../output/out_relaxs.h"
#include        "../output/out_version.h"



void    OutRealCanExt(real  *mpreT)
{
uchar   i;
uchar   wT;

  InitPushPtr();
  wT = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      Push(&mpreT[i], sizeof(real));
      wT += sizeof(real);
    }
  }

  OutptrOutBuff(wT);
}

/*
void    OutIntCanExt(uint  *mpwT)
{
uchar   i;
uchar   wT;

  InitPushPtr();
  wT = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      Push(&mpwT[i], sizeof(uint));
      wT += sizeof(uint);
    }
  }

  OutptrOutBuff(wT);
}


void    OutCharCanExt(uchar  *mpbT)
{
uchar   i;
uchar   wT;

  InitPushPtr();
  wT = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      Push(&mpbT[i], sizeof(uchar));
      wT += sizeof(uchar);
    }
  }

  OutptrOutBuff(wT);
}
*/


void    Response2_CRC(void)
{
  switch (bInBuff5)
  {
    case bINQ_GETTRANS_ENG: OutRealCanExt(mpreTransEng); break;
    case bINQ_GETTRANS_CNT: OutRealCanExt(mpreTransCnt); break;
    case bINQ_GETPULSE_HOU: OutRealCanExt(mprePulseHou); break;
    case bINQ_GETPULSE_MNT: OutRealCanExt(mprePulseMnt); break;
    case bINQ_GETCOUNT:     OutRealCanExt(mpreCount);    break;
    case bINQ_GETLOSSE:     OutRealCanExt(mpreLosse);    break;

    case bEXT_GETGROUPS: OutGetGroupsExt(); break;

    case bEXT_GETRELAXS: OutGetRelaxs(); break;
    case bEXT_SETRELAXS: OutSetRelaxs(); break;

    case bEXT_GETVERSION: OutVersion(); break;

    case bEXT_GETGAPS1: OutGaps1(); break;
    case bEXT_GETGAPS2: OutGaps2(); break;
/*
    case bEXT_GETDECRET:
      InitPushCRC();
      PushChar(deDecret);
      Push(&tiSummer, sizeof(time));
      PushChar(cbSummer);
      Push(&tiWinter, sizeof(time));
      PushChar(cbWinter);
      Output(1+6+1+6+1);
      break;

    case bEXT_GETSTART:
      InitPushCRC();
      Push(&tiStart, sizeof(time));
      Push(&tiPowerOff, sizeof(time));
      Push(&tiPowerOn,  sizeof(time));
      PushChar(cbPowerOn);
      Output(6+6+6+1);
      break;

    case bEXT_GETBULK:
      InitPushCRC();
      PushChar(boEnableBulk);
      PushChar(bMaxBulk);
      Push(&cbBulk, sizeof(cbBulk));
      PushInt(wMaxBulkDelay);
      Push(&cwBulkDelay, sizeof(cwBulkDelay));
      Push(&mpSerial, sizeof(mpSerial));
      Push(&mpSerial_Bulk, sizeof(mpSerial_Bulk));
      Output(1+1+4*1+2+4*2+4*1+4*1);
      break;

    case bEXT_GETOBJECTNAME: 
      GetObjectNameExt();
      break;

    case bEXT_SETOBJECTNAME: 
      SetObjectNameExt();
      break;

    case bEXT_GETCANALNAME: 
      GetCanalNameExt();
      break;

    case bEXT_SETCANALNAME: 
      SetCanalNameExt();
      break;

    case bEXT_GETGROUPNAME: 
      GetGroupNameExt();
      break;

    case bEXT_SETGROUPNAME: 
      SetGroupNameExt();
      break;

    case bEXT_FLASH_CONTROL:
      OutFlashControl();
      break;
*/
    default:
      ShowCommandCRC(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
