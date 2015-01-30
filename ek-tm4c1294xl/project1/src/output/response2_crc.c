/*------------------------------------------------------------------------------



------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_canals.h"
#include        "../memory/mem_groups.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_tariffs.h"
#include        "../hardware/memory.h"
#include        "../states.h"
#include        "../access.h"
#include        "../keyboard.h"
#include        "../groups.h"
#include        "../crc-16.h"
#include        "../ports.h"
#include        "../postinput_crc.h"
#include        "../timedate.h"
#include        "../tariffs/relaxs.h"
#include        "../tariffs/gaps.h"



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


void    OutGroupsExt(void)
{
uchar   i;
uchar   wT;

  InitPushPtr();
  wT = 0;

  for (i=0; i<bGROUPS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      Push(&mpgrGroups[i], sizeof(groups));
      wT += sizeof(groups);
    }
  }

  OutptrOutBuff(wT);
}



void    OutVersion(void)
{
uchar i;

  InitPushCRC();
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();
  PushChar(0);
  PushChar(bMAXVERSION);
  PushChar(bMINVERSION);
  PushInt(GetCODEChecksum());
  PushInt(GetBuildNumber());
  PushChar(GetBuildDate_Second());
  PushChar(GetBuildDate_Minute());
  PushChar(GetBuildDate_Hour());
  PushChar(GetBuildDate_Day());
  PushChar(GetBuildDate_Month());
  PushChar(GetBuildDate_Year());
  PushInt(wPrivate);
  PushChar(bLogical);

  PushChar(bCANALS);
  PushChar(bGROUPS);
  PushInt(bMINUTES);
  PushInt(wHOURS);
  PushInt(bDAYS);
  PushInt(bMONTHS);

  Output(100);
}



void    Response2_CRC(void)
{
uchar   i;

  switch (bInBuff5)
  {
    case bINQ_GETTRANS_ENG:         OutRealCanExt(mpreTransEng);    break;
    case bINQ_GETTRANS_CNT:         OutRealCanExt(mpreTransCnt);    break;
    case bINQ_GETPULSE_HOU:         OutRealCanExt(mprePulseHou);    break;
    case bINQ_GETPULSE_MNT:         OutRealCanExt(mprePulseMnt);    break;
    case bINQ_GETCOUNT:             OutRealCanExt(mpreCount);       break;
    case bINQ_GETLOSSE:             OutRealCanExt(mpreLosse);       break;

    case bEXT_GETGROUPS:            OutGroupsExt();                 break;

    case bEXT_GETRELAXS:
      InitPushCRC();
      PushChar(boRelaxsFlag);
      PushChar(ibRelaxsTariff);
      Push(&mpreRelaxs, sizeof(mpreRelaxs));
      Output(2+sizeof(mpreRelaxs));
      break;

    case bEXT_SETRELAXS:
      if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
      {
        InitPop(6);     
        i = PopChar();
        if (i <= bRELAXS)
        {
          memset(&mpreRelaxs, 0, sizeof(mpreRelaxs));
          mpreRelaxs.bSize = i;
          if (mpreRelaxs.bSize > 0)
          {            
            for (i=0; i<mpreRelaxs.bSize; i++)
            {
              Pop(&tiAlt, sizeof(time));
              mpreRelaxs.mptiDate[i] = tiAlt;
            }
          }
          LongResult(bRES_OK);
        }
        else Result(bRES_BADDATA);
      }
      else Result(bRES_NEEDREPROGRAM);
      break;

    case bEXT_GETVERSION:    OutVersion();    break;

    case bEXT_GETGAPS1:             OutGaps1();           break;
    case bEXT_GETGAPS2:             OutGaps2();           break;
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

#ifdef  BULK
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
#endif

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
*/

//    case bEXT_FLASH_CONTROL:
//      OutFlashControl();
//      break;

    default:
      ShowCommandCRC(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
