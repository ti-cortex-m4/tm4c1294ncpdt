/*------------------------------------------------------------------------------
POSTINPUT_CRC.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "mem_settings.h"
#include        "mem_ports.h"
#include        "states.h"
#include        "access.h"
#include        "crc-16.h"
#include        "output/out_rtc.h"
#include        "output/out_groups.h"
#include        "output/out_flash.h"
#include        "output/out_delay.h"
#include        "output/out_console.h"
#include        "display.h"
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
        OutGetCurrTimeDate();
        break;

      case bINQ_GETGROUP:
        OutGetGroup();
        break;

      case bINQ_SETGROUP:
        OutSetGroup();
        break;

      case bINQ_GETFLASHPAGE:
        OutFlashPage();
        break;

      case bINQ_SETDELAY:
        OutSetDelay();
        break;

      case bINQ_SETKEY:
        OutSetKey();
        break;

      case bINQ_GETDISPLAY:
        OutGetDisplay();
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

