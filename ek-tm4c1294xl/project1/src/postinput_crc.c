/*------------------------------------------------------------------------------
POSTINPUT_CRC.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "display.h"
#include        "mem_settings.h"
#include        "mem_ports.h"
#include        "programs.h"
#include        "queries.h"
#include        "states.h"
#include        "access.h"
#include        "crc-16.h"
#include        "rtc.h"
#include        "keyboard.h"
#include        "ports.h"



static const uchar      mpbKeys[14] = {
  0x2B, 0x0E, 0x1E, 0x2E, 0x3E, 0x0D, 0x1D, 0x2D, 0x3D, 0x0B,
  0x1B, 0x3B, 0x07, 0x17
};



void    Common(void  *pbData, uint  wSize) {
  if (5+wSize < wOUTBUFF_SIZE-bMARGIN) {
    InitPushCRC();
    Push(pbData, wSize);
    Output(wSize);
  }
  else Result(bRES_OUTOVERFLOW);
}



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
        Common(PGetCurrTimeDate(), sizeof(time));
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

