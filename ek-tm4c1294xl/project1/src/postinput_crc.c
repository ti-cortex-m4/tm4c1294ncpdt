/*------------------------------------------------------------------------------
POSTINPUT_CRC.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "display.h"
#include        "mem_settings.h"
#include        "mem_program.h"
#include        "mem_groups.h"
#include        "mem_ports.h"
#include        "programs.h"
#include        "queries.h"
#include        "states.h"
#include        "access.h"
#include        "crc-16.h"
#include        "rtc.h"
#include        "keyboard.h"
#include        "ports.h"



void    ShowCommandCRC(uchar  bState) {
  if (bProgram == bGET_ANALYSIS1)
  {
#ifdef  MODBUS
    sprintf(szHi,"Порт %u: Mod%03u %u",ibPort+1,InBuff(3),bState);
#else
    if (InBuff(4) == 0xFF)
      sprintf(szHi,"Порт %u: CFF%03u %u",ibPort+1,InBuff(5),bState);
    else
      sprintf(szHi,"Порт %u: CRC%03u %u",ibPort+1,InBuff(4),bState);
#endif

    ibPortActive = ibPort;
    NoShowTime(0);
  }
}



void    PostinputCRC(void) {
uchar  i;

  if (mpSerial[ibPort] == SER_POSTINPUT_SLAVE) {

    mpSerial[ibPort] = SER_BEGIN;
    ShowCommandCRC(bSTA_BEGIN);

    MakeCRC16InBuff( 0, IndexInBuff() );
    if ((bCRCHi != 0) || (bCRCLo != 0)) {
      ShowCommandCRC(bSTA_BADCRC);
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

    bQuery = bInBuff4;

    if ((bInBuff0 != 0) || (bInBuff1 != 0)) {
      if ((bInBuff0 != bLogical) || (bInBuff1 != 0)) {
        ShowCommandCRC(bSTA_BADNUMBER);
        return;
      }
    }

    if (bInBuff2 + bInBuff3*0x100 != IndexInBuff()) {
      ShowCommandCRC(bSTA_BADSIZE);
      Result(bRES_BADSIZE);
      return;
    }

    ShowCommandCRC(bSTA_OK);

    switch (bInBuff4)
    {
      case bINQ_GETCURRTIME:
        Common(PGetCurrTimeDate(), sizeof(time));
        break;

      case bINQ_GETGROUP:
        if (bInBuff5 < bGROUPS)
          Common(&mpgrGroups[ bInBuff5 ], sizeof(groups));
        else
          Result(bRES_BADADDRESS);
        break;

      case bINQ_SETGROUP:
        if (bInBuff5 < bGROUPS)
        {
          if ( (enGlobal == GLB_PROGRAM) ||
              ((enGlobal == GLB_REPROGRAM) && (mpboUsedGroups[bInBuff5] == boFalse)) )
          {
            for (i=0; i<bInBuff6; i++)
            {
              if ((InBuff(7+i) & 0x7F) >= bCANALS)
                break;
            }

            if (i == bInBuff6)
            {
              InitPop(6);
              Pop(&mpgrGroups[bInBuff5], sizeof(groups));

              boSetGroups = boTrue;
              LongResult(bRES_OK);
            }
            else Result(bRES_BADDATA);
          }
          else Result(bRES_NEEDPROGRAM);
        }
        else Result(bRES_BADADDRESS);
        break;

      case bINQ_SETKEY:
        if (TrueKey(bInBuff5) == 1) {
          bKey = mpbKeys[bInBuff5];
          fKey = 1;

          LongResult(bRES_OK);
        }
        else Result(bRES_BADDATA);
        break;

      case bINQ_GETDISPLAY:
        InitPushCRC();
        Push(&szHi,bDISPLAY);
        Push(&szLo,bDISPLAY);
        Output(2*bDISPLAY);
        break;

      default:
        ShowCommandCRC(bSTA_BADCOMMAND);
        Result(bRES_BADCOMMAND);
        break;
    } 
  }
}


void    PostinputCRC_Full(void) {
  ibPort = 0;
  PostinputCRC();
}

