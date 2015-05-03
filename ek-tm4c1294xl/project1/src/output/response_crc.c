/*------------------------------------------------------------------------------
RESPONSE_CRC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../include/states.h"
#include "../access.h"
#include "../kernel/crc-16.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../keyboard/key_timedate.h"
#include "../serial/ports.h"
#include "../serial/flow.h"
#include "response1_crc.h"



void    ShowTestResponse(uchar  bState) {
  if (wProgram == bTEST_RESPONSE)
  {
#ifdef  MODBUS
    sprintf(szHi,"项痱 %u: Mod%03u %u",ibPort+1,InBuff(3),bState);
#else
    if (InBuff(4) == 0xFF)
      sprintf(szHi,"项痱 %u: CFF%03u %u",ibPort+1,InBuff(5),bState);
    else if (InBuff(4) == 0xFE)
      sprintf(szHi,"项痱 %u: CFE%03u %u",ibPort+1,InBuff(5),bState);
    else
      sprintf(szHi,"项痱 %u: CRC%03u %u",ibPort+1,InBuff(4),bState);
#endif

    ibPortActive = ibPort;
    HideCurrentTime(0);
  }
}



void    RunResponseCRC(void) {
  if (mpSerial[ibPort] == SER_POSTINPUT_SLAVE) {

    mpSerial[ibPort] = SER_BEGIN;
    ShowTestResponse(bSTA_BEGIN);

    MakeCRC16InBuff( 0, IndexInBuff() );
    if ((bCRCHi != 0) || (bCRCLo != 0)) {
      ShowTestResponse(bSTA_BADCRC);
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
        ShowTestResponse(bSTA_BADNUMBER);
        return;
      }
    }

    if (bInBuff2 + bInBuff3*0x100 != IndexInBuff()) {
      ShowTestResponse(bSTA_BADSIZE);
      Result(bRES_BADSIZE);
      return;
    }

    ShowTestResponse(bSTA_OK);
    Response1_CRC();
  }
}


void    RunResponseCRC_All(void) {
  ibPort = 0;
  if (IsFlow0() == 0) RunResponseCRC();

  ibPort = 1;
  if (IsFlow1() == 0) RunResponseCRC();

  ibPort = 2;
  RunResponseCRC();

  ibPort = 3;
  RunResponseCRC();
}

