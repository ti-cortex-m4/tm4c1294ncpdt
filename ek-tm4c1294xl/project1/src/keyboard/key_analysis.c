/*------------------------------------------------------------------------------
_ANALYSIS.H

 
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_serial0.h"
#include        "../memory/mem_ports.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../ports.h"



//                                         0123456789ABCDEF
static char const       szAnalysis1[]   = "Запросы         ";



void    key_Analysis1(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szAnalysis1);
      Clear();
    }
  }
}



void    auto_Analysis1(void)
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
    }
  }
}
