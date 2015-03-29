/*------------------------------------------------------------------------------
RESPONSE255_CRC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_digitals.h"
#include        "../include/states.h"
#include        "../serial/ports.h"
#include        "../output/response_crc.h"
#include        "../flash/flash_control.h"
#include        "../tariffs/gaps.h"
#include        "../output/out_groups.h"
#include        "../output/out_relaxs.h"
#include        "../output/out_gaps.h"
#include        "../output/out_decret.h"
#include        "../output/out_digitals.h"
#include        "../output/out_max_power.h"
#include        "../output/out_energy.h"
#include        "../output/out_impulse.h"
#include        "../output/out_minute3.h"
#include        "../output/out_minute30.h"
#include        "../output/out_minute30_48.h"
#include        "../output/out_current.h"
#include        "../output/out_version.h"
#include        "../output/out_ports.h"
#include        "../output/out_names.h"
#include        "../output/profile/out_limits.h"



void    OutRealCanExt(real  *mpe)
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
void    OutIntCanExt(uint  *mpw)
{
uchar   i;
uchar   w;

  InitPushPtr();
  w = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      PushInt(mpw[i]);
      w += sizeof(uint);
    }
  }

  OutptrOutBuff(w);
}


void    OutCharCanExt(uchar  *mpb)
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

void    OutBoolCanExt(boolean  *mpf)
{
uchar   i;
uchar   w;

  InitPushPtr();
  w = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      Push(&mpf[i], sizeof(boolean));
      w += sizeof(boolean);
    }
  }

  OutptrOutBuff(w);
}



void    Response255_CRC(void)
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

    case bINQ_GETMAXPOWGRPDAY_ALL:  OutMaxPowDayGrpExt();  break;
    case bINQ_GETMAXPOWGRPMON_ALL:  OutMaxPowMonGrpExt();  break;

    case bINQ_GETENGGRPDAY_ALL:     OutEngDayGrpExt0();    break;
    case bINQ_GETENGGRPMON_ALL:     OutEngMonGrpExt0();    break;

    case bINQ_GETENGGRPDAY_ALLSUM:  OutEngDayGrpExt1();    break;
    case bINQ_GETENGGRPMON_ALLSUM:  OutEngMonGrpExt1();    break;

    case bINQ_GETIMPCANDAY_ALL:     OutImpDayCanExt();     break;
    case bINQ_GETIMPCANMON_ALL:     OutImpMonCanExt();     break;

    case bINQ_GETPOWGRPHOU_DAY:     OutPowGrpHou48Ext();   break;
    case bINQ_GETIMPCANHOU_DAY:     OutImpCanHou48Ext();   break;
    case bINQ_GETPOWCANHOU_DAY:     OutPowCanHou48Ext();   break;

    case bINQ_GETIMPCANMNT_ALL:     OutImpMntCanExt();     break;
    case bINQ_GETPOWCANMNT_ALL:     OutPowMntCanExt();     break;

    case bEXT_GETIMPCANHOU:         OutImpCanHouExt();     break;
    case bEXT_GETIMPCANMNT:         OutImpCanMntExt();     break;
    case bEXT_GETPOWCANMNT:         OutPowCanMntExt();     break;

    case bEXT_GETCURRENT:           OutCurrentExt();       break;

    case bEXT_GETDIGITALS: OutDigitalsExt(); break;

    case bEXT_GETENBLCAN: OutBoolCanExt(mpboEnblCan); break;

    case bEXT_SETCTRLHOU:
      InitPop(6);
      for (i=0; i<48; i++)
        mpboCtrlHou[i] = PopChar();
      Result(bRES_OK);
      break;

    case bEXT_GETENBLPORTHOU:
      if (bInBuff6 < bPORTS)
        Common(&mpboEnblPorHou[ bInBuff6 ], 48);
      else
        Result(bRES_BADADDRESS);
      break;

    case bEXT_SETENBLPORTHOU:
      if (bInBuff6 < bPORTS)
      {
        InitPop(7);
        for (i=0; i<48; i++)
          mpboEnblPorHou[bInBuff6][i] = PopChar();
        LongResult(bRES_OK);
      }
      else
        Result(bRES_BADADDRESS);
      break;

    case bEXT_GETRELAXS: OutGetRelaxs(); break;
    case bEXT_SETRELAXS: OutSetRelaxs(); break;

    case bEXT_GETSTARTCAN: OutStartCan(); break;

    case bEXT_GETVERSION: OutVersion(); break;
    case bEXT_GETPORTS: OutPorts(); break;
/*
    case bEXT_GETHOUCANDEF:         OutImpCanHou48Def();  break;
    case bEXT_GETHOUGRPDEF:         OutPowGrpHou48Def();  break;
    case bEXT_GETDAYCANDEF_ALL:     OutDayCanDefAll();    break;
    case bEXT_GETMONCANDEF_ALL:     OutMonCanDefAll();    break;
    case bEXT_GETDAYGRPDEF_ALL:     OutDayGrpDefAll();    break;
    case bEXT_GETMONGRPDEF_ALL:     OutMonGrpDefAll();    break;
    case bEXT_GETDAYCANDEF:         OutDayCanDef();       break;
    case bEXT_GETMONCANDEF:         OutMonCanDef();       break;
    case bEXT_GETDAYGRPDEF:         OutDayGrpDef();       break;
    case bEXT_GETMONGRPDEF:         OutMonGrpDef();       break;

    case bINQ_GETENGGRPDAY_DEF:     OutEngDayGrpDef();    break;
    case bINQ_GETENGGRPMON_DEF:     OutEngMonGrpDef();    break;
    case bINQ_GETMAXPOWGRPDAY_DEF:  OutMaxPowDayGrpDef(); break;
    case bINQ_GETMAXPOWGRPMON_DEF:  OutMaxPowMonGrpDef(); break;
    case bINQ_GETENGGRPHOUPREV_DEF: OutPowHouGrpDef(1);   break;
    case bINQ_GETPOWGRPHOUPREV_DEF: OutPowHouGrpDef(2);   break;
*/
    case bEXT_GETGAPS1: OutGaps1(); break;
    case bEXT_GETGAPS2: OutGaps2(); break;

    case bEXT_GETSTOPAUXCAN: OutStopAuxCan(); break;

    case bEXT_GETDECRET: OutDecret(); break;
/*
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
*/
    case bEXT_GETOBJECTNAME: 
      GetObjectNameExt();
      break;

    case bEXT_SETOBJECTNAME: 
      SetObjectNameExt();
      break;

    case bEXT_GETCANALSNAME:
      GetCanalsNameExt();
      break;

    case bEXT_SETCANALSNAME:
      SetCanalsNameExt();
      break;

    case bEXT_GETGROUPSNAME:
      GetGroupsNameExt();
      break;

    case bEXT_SETGROUPSNAME:
      SetGroupsNameExt();
      break;

    case bEXT_FLASH_CONTROL:
      OutFlashControl();
      break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
