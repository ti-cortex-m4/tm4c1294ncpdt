/*------------------------------------------------------------------------------
RESPONSE2_CRC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_digitals.h"
#include        "../states.h"
#include        "../ports.h"
#include        "../output/response_crc.h"
#include        "../tariffs/gaps.h"
#include        "../output/out_groups.h"
#include        "../output/out_relaxs.h"
#include        "../output/out_gaps.h"
#include        "../output/out_digitals.h"
#include        "../output/out_version.h"



static void OutRealCan(real  *mpe)
{
uchar   i;
uchar   w;

  InitPushPtr();
  w = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      Push(&mpe[i], sizeof(real));
      w += sizeof(real);
    }
  }

  OutptrOutBuff(w);
}

/*
static void OutIntCan(uint  *mpw)
{
uchar   i;
uchar   w;

  InitPushPtr();
  w = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      Push(&mpw[i], sizeof(uint));
      w += sizeof(uint);
    }
  }

  OutptrOutBuff(w);
}


static void OutCharCan(uchar  *mpb)
{
uchar   i;
uchar   w;

  InitPushPtr();
  w = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      Push(&mpb[i], sizeof(uchar));
      w += sizeof(uchar);
    }
  }

  OutptrOutBuff(w);
}
*/

static void OutBoolCan(bool  *mpf)
{
uchar   i;
uchar   w;

  InitPushPtr();
  w = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      Push(&mpf[i], sizeof(bool));
      w += sizeof(bool);
    }
  }

  OutptrOutBuff(w);
}



void    Response2_CRC(void)
{
  switch (bInBuff5)
  {
    case bINQ_GETTRANS_ENG: OutRealCan(mpreTransEng); break;
    case bINQ_GETTRANS_CNT: OutRealCan(mpreTransCnt); break;
    case bINQ_GETPULSE_HOU: OutRealCan(mprePulseHou); break;
    case bINQ_GETPULSE_MNT: OutRealCan(mprePulseMnt); break;
    case bINQ_GETCOUNT:     OutRealCan(mpreCount);    break;
    case bINQ_GETLOSSE:     OutRealCan(mpreLosse);    break;

    case bEXT_GETGROUPS: OutGetGroupsExt(); break;

    case bEXT_GETDIGITALS: OutDigitalsExt(); break;
    case bEXT_GETENBLCAN: OutBoolCan(mpfEnblCan); break;

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
