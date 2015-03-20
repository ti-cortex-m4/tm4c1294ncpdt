/*------------------------------------------------------------------------------
POSTINPUT2.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_uni.h"
#include        "../crc-16.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../serial/ports.h"
#include        "../flash/files.h"

//#include        "main.h"
//#include        "xdata.h"
//#include        "ports.h"
//#include        "flow.h"
//#include        "crc-16.h"
//#include        "states.h"
//#include        "queries2.h"
//#include        "keyboard.h"
//#include        "programs.h"
//#include        "display.h"
//#include        "groups.h"
//#include        "nexttime.h"
//#include        "rtc.h"
//#include        "u_config.h"
//#include        "u_mnt.h"
//#include        "u_hou.h"
//#include        "u_day.h"
//#include        "u_energy.h"
//#include        "u_cnt.h"
//#include        "u_param.h"
//#include        "u_transit.h"
//#include        "u_events.h"
//#include        "u_query_crc.h"
//#include        "_timedate.h"



file const              flObjectName = {FLS_OBJECT_NAME, &szObjectName, sizeof(szObjectName)};
file const              flCanalsName = {FLS_CANALS_NAME, &mpszCanalsName, sizeof(mpszCanalsName)};
file const              flGroupsName = {FLS_GROUPS_NAME, &mpszGroupsName, sizeof(mpszGroupsName)};

file const              flStrictUni = {FLS_STRICT_UNI, &boStrictUni, sizeof(boolean)};
file const              flMaxDelayUni = {FLS_MAX_DELAY_UNI, &bMaxDelayUni, sizeof(uchar)};
file const              flRepeatFlowUni = {FLS_REPEAT_FLOW_INI, &boRepeatFlowUni, sizeof(boolean)};


/*
void    InitUni(void)
{
uchar   i;

  for (i=0; i<bPORTS; i++)
    mpbDelayUni[i] = 0;  

  if ((bMaxDelayUni < 10) || (bMaxDelayUni > 250)) bMaxDelayUni = 60;
}



void    ResetUni(void)
{
uchar   i;

  memset(&szObjectName,  0, sizeof(szObjectName));
  memset(&mpszCanalsName, 0, sizeof(mpszCanalsName));
  memset(&mpszGroupsName, 0, sizeof(mpszGroupsName));

  sprintf(&szObjectName, "object %u", wPrivate);

  for (i=0; i<bCANALS; i++)
    sprintf(mpszCanalsName[i], "canal %bu", i+1);

  for (i=0; i<bGROUPS; i++)
    sprintf(mpszGroupsName[i], "group %bu", i+1);

  boStrictUni = boTrue;

  bMaxDelayUni = 60;

  boRepeatFlowUni = boFalse;
}



void    DelayUni(void)
{
  if (mpbDelayUni[0] > 0) mpbDelayUni[0]--;
  if (mpbDelayUni[1] > 0) mpbDelayUni[1]--;
  if (mpbDelayUni[2] > 0) mpbDelayUni[2]--;

#ifdef  UPGRADE
  if (mpbDelayUni[3] > 0) mpbDelayUni[3]--;
#endif
}



void    ShowCommandUni(uchar  i)
{
  if (bProgram == bGET_ANALYSIS1)
  {
    sprintf(szHi,"Порт %bu: U-%02bX%02bX %bu",ibPort+1,InBuff(4),InBuff(5),i);
    sprintf(szLo+14,"%02bu",mpbDelayUni[ibPort]);

    ibPortActive = ibPort;
    NoShowTime(0);
  }
}


void    ShowInfoUni(uchar  bInfo)
{
  if (bProgram == bGET_ANALYSIS1)
  {
    sprintf(szHi+8,"%bu",bInfo);
  }
}



#ifndef MODBUS

void    Output2_Code(uint  wSize, uchar  bCode, time  *mptiCode)
{
  InitPush();

  PushChar(0xC3);
  PushChar(bLogical);

  PushChar((wSize+16) / 0x100);
  PushChar((wSize+16) % 0x100);

  PushChar(bInBuff4);
  PushChar(bInBuff5);
  
  Skip(wSize);

  PushChar(bCode);

  PushChar((*mptiCode).bMinute);
  PushChar((*mptiCode).bHour);
  PushChar((*mptiCode).bDay);
  PushChar((*mptiCode).bMonth);
  PushChar((*mptiCode).bYear);

  PushChar(InBuff(IndexInBuff() - 4));
  PushChar(InBuff(IndexInBuff() - 3));

  MakeCRC16OutBuff(0,wSize+14);
  PushChar(bCRCHi);
  PushChar(bCRCLo);

  Answer(wSize+16,SER_OUTPUT_SLAVE);
}


void    Output2(uint  wSize)
{
  Output2_Code(wSize, 0, PGetCurrTimeDate());
}


void    Result2(uchar  bT)
{
  Output2_Code(0, bT, PGetCurrTimeDate());
}


void    Result2_Info(uchar  bT, uchar  bInfo)
{
  ShowInfoUni(bInfo);
  Output2_Code(0, bT, PGetCurrTimeDate());
}


void    Common2(void  xdata  *pbData, uint  wSize)
{
  if (16+wSize < wOUTBUFF_SIZE-bSHADOW)
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



void    Postinput2(void)
{
  if (mpSerial[ibPort] == SER_POSTINPUT_SLAVE2)
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
      if (boDisablePasswordUni == boFalse)
      {
        Result2(bUNI_BADACCESS);
        return;
      }
    }

    SetDelayUni();
    ShowCommandUni(bSTA_OK);

    switch (bInBuff5 + bInBuff4*0x100)
    {
      case wUNI_GETCURRTIME:
        Common2(PGetCurrTimeDate(), sizeof(time));
        break;

      case wUNI_GETCORRECTTIME: 
        GetCorrectUni(); 
        break;

      case wUNI_GETCORRECTIONS: 
        GetCorrectionsUni(); 
        break;

      case wUNI_GETOPEN: 
        GetOpenUni(); 
        break;

      case wUNI_GETPARAMS1:
        GetParamUni1(); 
        break;

      case wUNI_GETPARAMS2:
        GetParamUni2(); 
        break;

      case wUNI_GETTRANSIT:
        GetTransitUni(); 
        break;

      case wUNI_GETCONFIG: 
        GetConfigUni(); 
        break;

      case wUNI_GETSENSORS: 
        GetSensorsUni(); 
        break;

      case wUNI_GETDIGITALS: 
        GetDigitalsUni(); 
        break;

      case wUNI_GETCANALS: 
        GetCanalsUni(); 
        break;

      case wUNI_GETGROUPS: 
        GetGroupsUni(); 
        break;

      case wUNI_GETENGCANDAY: 
        GetEngCanDayUni(); 
        break;

      case wUNI_GETENGGRPDAY: 
        GetEngGrpDayUni(); 
        break;

      case wUNI_GETENGCANMON: 
        GetEngCanMonUni(); 
        break;

      case wUNI_GETENGGRPMON: 
        GetEngGrpMonUni(); 
        break;

      case wUNI_GETPOWCANMNT: 
        GetPowCanMntUni(); 
        break;

      case wUNI_GETPOWGRPMNT: 
        GetPowGrpMntUni(); 
        break;

      case wUNI_GETPOWCANHOU:
        GetPowCanHouUni(); 
        break;

      case wUNI_GETPOWGRPHOU:
        GetPowGrpHouUni(); 
        break;

      case wUNI_GETPOWCANHOU48:
        GetPowCanHou48Uni(); 
        break;

      case wUNI_GETPOWGRPHOU48:
        GetPowGrpHou48Uni(); 
        break;

      case wUNI_GETCNTCANMON:
        GetCntCanMonUni(); 
        break;

      case wUNI_GETCNTCAN:
        GetCntCanUni(); 
        break;

      case wUNI_GETMAXGRPDAY:
        GetMaxGrpDayUni(); 
        break;

      case wUNI_GETMAXGRPMON:
        GetMaxGrpMonUni(); 
        break;

      case wUNI_GETDEFCANDAY:
        GetDefCanDayUni(); 
        break;

      case wUNI_GETDEFGRPDAY:
        GetDefGrpDayUni(); 
        break;

      case wUNI_GETEVENTS_COUNTS:
        GetEventsCountsUni(); 
        break;

      case wUNI_GETEVENTS:
        GetEventsUni(); 
        break;

      case wUNI_GETEVENTS_MESSAGES:
        GetEventsMessagesUni(); 
        break;

      case wUNI_GETQUERY_CRC:
        GetQueryCRCUni(); 
        break;

      default:
        ShowCommandUni(bSTA_BADCOMMAND);
        Result2(bUNI_BADCOMMAND);
        break;
    } 
  }
}


void    UniMaster(void)
{
  ibPort = 0;
  if (IsFlow0() == 0) Postinput2();

  ibPort = 1;
  if (IsFlow1() == 0) Postinput2();

  ibPort = 2;
  Postinput2();

#ifdef  UPGRADE
  ibPort = 3;
  Postinput2();
#endif
}



bit     GetDefCan(uchar  ibCanal)
{
  return (mpwImpHouCan[ PrevSoftHou() ][ibCanal] == 0xFFFF);
}


bit     GetDefGrp(uchar  ibGroup)
{
uchar   i;

  if (GetGroupsSize(ibGroup) == 0)
    return 0;

  for (i=0; i<GetGroupsSize(ibGroup); i++)
    if (mpwImpHouCan[ PrevSoftHou() ][ GetGroupsNodeCanal(ibGroup, i) ] == 0xFFFF)
      return 1;

  return 0;
}



void    PushFFFFFF(void)
{
  PushChar(0xFF); PushChar(0xFF); PushChar(0xFF);
}


void    PushRealUni(status4  status, real  *preT)
{
  if (boStrictUni == boTrue)
  {
    switch (status)
    {
      case ST4_NONE:          PushFFFFFF(); PushChar(0xFF); break;
      case ST4_NOTSUPPORTED:  PushFFFFFF(); PushChar(0xFF); break;
      case ST4_NOTPRESENTED:  PushFFFFFF(); PushChar(0xFF); break;
      case ST4_BADDIGITAL:    PushFFFFFF(); PushChar(0xFE); break;
      case ST4_BADFLASH:      PushFFFFFF(); PushChar(0xFF); break;
      case ST4_BADPORT:       PushFFFFFF(); PushChar(0xFE); break;
      case ST4_BADENABLING:   PushFFFFFF(); PushChar(0xFF); break;
      default:                Push(preT, sizeof(real)); break;
    }
  }
  else
  {
    switch (status)
    {
      case ST4_NONE:          PushFFFFFF(); PushChar(0xE0); break;
      case ST4_NOTSUPPORTED:  PushFFFFFF(); PushChar(0xE1); break;
      case ST4_NOTPRESENTED:  PushFFFFFF(); PushChar(0xE2); break;
      case ST4_BADDIGITAL:    PushFFFFFF(); PushChar(0xE3); break;
      case ST4_BADFLASH:      PushFFFFFF(); PushChar(0xE4); break;
      case ST4_BADPORT:       PushFFFFFF(); PushChar(0xE5); break;
      case ST4_BADENABLING:   PushFFFFFF(); PushChar(0xE6); break;
      default:                Push(preT, sizeof(real)); break;
    }
  }
}

#endif
*/
