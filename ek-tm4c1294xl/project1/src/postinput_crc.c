/*------------------------------------------------------------------------------
POSTINPUT_CRC.C


------------------------------------------------------------------------------*/

//#include        <absacc.h>
#include        "main.h"
#include        "mem_display.h"
#include        "mem_settings.h"
/*
#include        "xdata.h"
#include        "x_digitals.h"
#include        "x_params.h"
*/
#include        "programs.h"
#include        "states.h"
/*
#include        "display.h"
#include        "access.h"
#include        "tariffs.h"
*/
#include        "crc-16.h"
#include        "keyboard.h"
#include        "queries.h"
/*
#include        "states.h"
#include        "modbus.h"
#include        "rtc.h"
#include        "energy.h"
#include        "engine.h"
#include        "zones.h"
#include        "nexttime.h"
#include        "timedate.h"
#include        "power.h"
#include        "general.h"
#include        "general_far.h"
#include        "flash.h"
#include        "at45d081.h"
#include        "oldtariffs.h"
#include        "groups.h"
#include        "defects.h"
*/
#include        "stack.h"
#include        "ports.h"
#include        "mem_ports.h"
/*
#include        "sensors.h"
#include        "params.h"
#include        "devices_far.h"
#include        "c_power.h"
#include        "c_energy.h"
#include        "c_defects.h"
#include        "c_counters.h"
#include        "c_digitals.h"
#include        "extended.h"
#include        "flow.h"
#include        "memory.h"
#include        "digitals.h"
#include        "pause.h"
#include        "blocking.h"
#include        "correct2.h"
#include        "correct3.h"
#include        "record.h"
#include        "gps2.h"
#include        "contacts.h"
#include        "contacts_pass.h"
#include        "answer_flag.h"
#include        "_automatic1.h"
#include        "_timedate.h"
*/

static const uchar              mpbKeys[14] =
{ 0x2B, 0x0E, 0x1E, 0x2E, 0x3E, 0x0D, 0x1D, 0x2D, 0x3D, 0x0B,
  0x1B, 0x3B, 0x07, 0x17 };

// передача произвольного массива
void    Common(void  *pbData, uint  wSize) {
  if (5+wSize < 0x20) // ???
  {
    InitPushCRC();
    Push(pbData, wSize);
    Output(wSize);
  }
  else Result(bRES_OUTOVERFLOW);
}



void    ShowCommandCRC(uchar  i)
{
}




// базовая программа обработки запросов
void    PostinputCRC(void)
{
  if (mpSerial[ibPort] == SER_POSTINPUT_SLAVE)
  {
    mpSerial[ibPort] = SER_BEGIN;

    ShowCommandCRC(bSTA_BEGIN);

    // проверяем контрольную сумму
    MakeCRC16InBuff( 0, IndexInBuff() );
    if ((bCRCHi != 0) || (bCRCLo != 0))
    {
      ShowCommandCRC(bSTA_BADCRC);
      return;
    }

    // загружаем данные из входных буферов
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

    // номер функции
    bQuery = bInBuff4;

    // если в запросе задан не нулевой логический номер
    if ((bInBuff0 != 0) || (bInBuff1 != 0))
    {
      //  проверяем логический номер
      if ((bInBuff0 != bLogical) || (bInBuff1 != 0))
      {
        ShowCommandCRC(bSTA_BADNUMBER);
        return;
      }
    }

    // проверяем длину запроса
    if (bInBuff2 + bInBuff3*0x100 != IndexInBuff())
    {
      ShowCommandCRC(bSTA_BADSIZE);
      Result(bRES_BADSIZE);
      return;
    }

    ShowCommandCRC(bSTA_OK);

    switch (bInBuff4)
    {
//      case bINQ_GETCURRTIME:
//        Common(PGetCurrTimeDate(), sizeof(time));
//        break;

      case bINQ_SETKEY:
//        if (TrueKey(bInBuff5) == 1)
        {
          bKey = mpbKeys[bInBuff5];
          fKey = 1;

          LongResult(bRES_OK);
        }
        //else Result(bRES_BADDATA);
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


void    PostinputCRCAll(void) {
  ibPort = 0;
  PostinputCRC();
}

