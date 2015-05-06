/*------------------------------------------------------------------------------
KEY_RESPONSE,H

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_serial0.h"
#include "../../memory/mem_serial1.h"
#include "../../memory/mem_serial2.h"
#include "../../memory/mem_serial3.h"
#include "../../memory/mem_ports.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../serial/ports.h"



//                                          0123456789ABCDEF
static char const       szTestResponse[] = "Запросы         ";



void    key_TestResponse(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestResponse);
      Clear();
    }
  }
}



void    auto_TestResponse(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
    switch (ibPortActive)
    {
      case 0: 
        Lo(0,  mpSerial[0]);
        Lo(3,  cwIn0 % 0x100);
        Lo(5,  bIn0); 
        Lo(8,  iwInBuff0 % 0x100);
        Lo(11, ibPacket0);
        break;

      case 1:
        Lo(0,  mpSerial[1]);
        Lo(3,  cwIn1 % 0x100);
        Lo(5,  bIn1);
        Lo(8,  iwInBuff1 % 0x100);
        Lo(11, ibPacket1);
        break;

      case 2:
        Lo(0,  mpSerial[2]);
        Lo(3,  cwIn2 % 0x100);
        Lo(5,  bIn2);
        Lo(8,  iwInBuff2 % 0x100);
        Lo(11, ibPacket2);
        break;

      case 3:
        Lo(0,  mpSerial[3]);
        Lo(3,  cwIn3 % 0x100);
        Lo(5,  bIn3);
        Lo(8,  iwInBuff3 % 0x100);
        Lo(11, ibPacket3);
        break;
    }
  }
}
