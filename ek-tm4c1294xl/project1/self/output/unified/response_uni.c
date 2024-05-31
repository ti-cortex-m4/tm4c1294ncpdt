/*------------------------------------------------------------------------------
RESPONSE_UNI!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_uni.h"
#include "../../keyboard/keyboard.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../display/display.h"
#include "../../serial/ports.h"
#include "../../serial/flow.h"
#include "../../include/queries_uni.h"
#include "../../time/rtc.h"
#include "../../kernel/crc-16.h"
#include "uni_time.h"
#include "u_config.h"
#include "u_param.h"
#include "u_transit.h"
#include "uni_mnt.h"
#include "uni_hhr.h"
#include "u_day.h"
#include "u_energy.h"
#include "uni_cnt.h"
#include "uni_events1.h"
#include "uni_events2.h"
#include "uni_events3.h"
#include "u_query_crc.h"
#include "u_transit2.h"
#include "uni.h"



void    ShowCommandUni(uchar  i)
{
  if (wProgram == bTEST_REQUEST)
  {
    ibPortActive = ibPort;
    HideCurrTime(0);
  }

  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"Порт %u: U-%02X%02X %u",ibPort+1,InBuff(4),InBuff(5),i);
    sprintf(szLo+14,"%02u",mpbDelayUni[ibPort]);

    ibPortActive = ibPort;
    HideCurrTime(0);
  }
}


void    ShowInfoUni(uchar  bInfo)
{
  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi+8,"%u",bInfo);
  }
}



#ifndef MODBUS

void    Output2_Code(uint  wSize, uchar  bCode, time  tiCode)
{
  InitPush(0);

  PushChar(0xC3);
  PushChar(bLogical);

  PushChar((wSize+16) / 0x100);
  PushChar((wSize+16) % 0x100);

  PushChar(bInBuff4);
  PushChar(bInBuff5);

  Skip(wSize);

  PushChar(bCode);

  PushChar(tiCode.bMinute);
  PushChar(tiCode.bHour);
  PushChar(tiCode.bDay);
  PushChar(tiCode.bMonth);
  PushChar(tiCode.bYear);

  PushChar(InBuff(IndexInBuff() - 4));
  PushChar(InBuff(IndexInBuff() - 3));

  MakeCRC16OutBuff(0,wSize+14);
  PushChar(bCRCHi);
  PushChar(bCRCLo);

  Answer(wSize+16,SER_OUTPUT_SLAVE);
}


void    Output2(uint  wSize)
{
  Output2_Code(wSize, 0, *GetCurrTimeDate());
}


void    Result2(uchar  bT)
{
  Output2_Code(0, bT, *GetCurrTimeDate());
}


void    Result2_Info(uchar  bT, uchar  bInfo)
{
  ShowInfoUni(bInfo);
  Output2_Code(0, bT, *GetCurrTimeDate());
}


void    Common2(void  *pbData, uint  wSize)
{
  if (16+wSize < wOUTBUFF_SIZE-bMARGIN)
  {
    InitPushUni();
    Push(pbData, wSize);
    Output2(wSize);
  }
  else Result2(bUNI_OUTOVERFLOW);
}


void    SetDelayUni(void)
{
  mpbDelayUni[ibPort] = bMaxDelayUni;
}



void    RunResponseUni(void)
{
  if (mpSerial[ibPort] == SER_POSTINPUT_SLAVE_UNI)
  {
    mpSerial[ibPort] = SER_BEGIN;

    ShowCommandUni(bSTA_BEGIN);

    MakeCRC16InBuff( 0, IndexInBuff() );
    if ((bCRCHi != 0) || (bCRCLo != 0))
    {
      ShowCommandUni(bSTA_BADCRC);
      return;
    }

    bInBuff0 = InBuff(0);
    bInBuff1 = InBuff(1);
    bInBuff2 = InBuff(2);
    bInBuff3 = InBuff(3);
    bInBuff4 = InBuff(4);
    bInBuff5 = InBuff(5);
    bInBuff6 = InBuff(6);
    bInBuff7 = InBuff(7);
    bInBuff8 = InBuff(8);
    bInBuff9 = InBuff(9);
    bInBuffA = InBuff(10);
    bInBuffB = InBuff(11);
    bInBuffC = InBuff(12);
    bInBuffD = InBuff(13);
    bInBuffE = InBuff(14);
    bInBuffF = InBuff(15);

    bQuery = bInBuff4;

    if (bInBuff1 != 0)
    {
      if (bInBuff1 != bLogical)
      {
        ShowCommandUni(bSTA_BADNUMBER);
        return;
      }
    }

    if (bInBuff3 + bInBuff2*0x100 != IndexInBuff())
    {
      ShowCommandUni(bSTA_BADSIZE);
      Result2(bUNI_BADDATA);
      return;
    }

    if ((mpbDelayUni[ibPort] == 0) &&
        (bInBuff5 + bInBuff4*0x100 != wUNI_GETOPEN) &&
        (bInBuff5 + bInBuff4*0x100 != wUNI_GETQUERY_CRC))
    {
      if (boEnblPassUni == true)
      {
        Result2(bUNI_BADACCESS);
        return;
      }
    }

    SetDelayUni();
    ShowCommandUni(bSTA_OK);

    switch (bInBuff5 + bInBuff4*0x100)
    {
      case wUNI_GETCURRTIME: GetTimeUni(); break;

      case wUNI_GETCORRECTTIME: GetCorrectUni(); break;
      case wUNI_GETCORRECTIONS: GetCorrectionsUni(); break;

      case wUNI_GETOPEN: GetOpenUni(); break;

      case wUNI_GETPARAMS1: GetParamUni1(); break;
      case wUNI_GETPARAMS2: GetParamUni2(); break;

      case wUNI_GETTRANSIT: GetTransitUni(); break;

      case wUNI_GETCONFIG: GetConfigUni(); break;
      case wUNI_GETSENSORS: GetSensorsUni(); break;
      case wUNI_GETDIGITALS: GetDigitalsUni(); break;
      case wUNI_GETSERIALS: GetSerialsUni(); break;
      case wUNI_GETCANALS: GetCanalsUni(); break;
      case wUNI_GETGROUPS: GetGroupsUni(); break;

      case wUNI_GETENGCANDAY: GetEngCanDayUni(false); break;
      case wUNI_GETENGGRPDAY: GetEngGrpDayUni(false); break;
      case wUNI_GETENGCANMON: GetEngCanMonUni(false); break;
      case wUNI_GETENGGRPMON: GetEngGrpMonUni(false); break;

      case wUNI_GETENGCANDAY_X2: GetEngCanDayUni(true); break;
      case wUNI_GETENGGRPDAY_X2: GetEngGrpDayUni(true); break;
      case wUNI_GETENGCANMON_X2: GetEngCanMonUni(true); break;
      case wUNI_GETENGGRPMON_X2: GetEngGrpMonUni(true); break;

      case wUNI_GETPOWCANMNT: GetPowCanMntUni(); break;
      case wUNI_GETPOWGRPMNT: GetPowGrpMntUni(); break;

      case wUNI_GETPOWCANHOU: GetPowCanHouUni(); break;
      case wUNI_GETPOWGRPHOU: GetPowGrpHouUni(); break;

      case wUNI_GETPOWCANHOU48: GetPowCanHou48Uni(); break;
      case wUNI_GETPOWGRPHOU48: GetPowGrpHou48Uni(); break;

      case wUNI_GETCNTCANMON: GetCntCanMonUni(false); break;
      case wUNI_GETCNTCAN: GetCntCanUni(false); break;

      case wUNI_GETCNTCANMON_X2: GetCntCanMonUni(true); break;
      case wUNI_GETCNTCAN_X2: GetCntCanUni(true); break;

      case wUNI_GETMAXGRPDAY: GetMaxGrpDayUni(); break;
      case wUNI_GETMAXGRPMON: GetMaxGrpMonUni(); break;

      case wUNI_GETDEFCANDAY: GetDefCanDayUni(); break;
      case wUNI_GETDEFGRPDAY: GetDefGrpDayUni(); break;

      case wUNI_GETEVENTS_COUNTS: GetEventsCountsUni(); break;
      case wUNI_GETEVENTS: GetEventsUni(); break;
      case wUNI_GETEVENTS_FIX: GetEventsUni_Fix(); break;
      case wUNI_GETEVENTS_MESSAGES: GetEventsMessagesUni(); break;

      case wUNI_GETQUERY_CRC:
        GetQueryCRCUni();
        break;

      case wUNI_GETTRANSIT2:
        GetTransitExecuteUni1();
        break;

      default:
        ShowCommandUni(bSTA_BADCOMMAND);
        Result2(bUNI_BADCOMMAND);
        break;
    }
  }
}


void    RunResponseUni_All(void)
{
  ibPort = 0;
  if (IsFlow0() == 0) RunResponseUni();

  ibPort = 1;
  if (IsFlow1() == 0) RunResponseUni();

  ibPort = 2;
  RunResponseUni();

  ibPort = 3;
  RunResponseUni();
}


#endif
