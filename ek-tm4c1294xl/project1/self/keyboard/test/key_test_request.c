/*------------------------------------------------------------------------------
KEY_REQUEST,H


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_serial0.h"
#include "../../memory/mem_serial1.h"
#include "../../memory/mem_serial2.h"
#include "../../memory/mem_serial3.h"
#include "../../memory/mem_ports.h"
#include "../../console.h"
#include "../../serial/ports.h"



//                                         0123456789ABCDEF
static char const       szTestRequest[] = "                ";


static uint wOffset = 0;



void    key_TestRequest(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestRequest);
      Clear();

      wOffset = 0;
    }
  }
  else if (bKey == bKEY_POINT)
  {
    wOffset += 8;
  }
  else if (bKey == bKEY_MINUS)
  {
    if (wOffset >= 8)
      wOffset -= 8;
  }
}


static void Dump(uchar  i, uint iMax, uchar  bT) {
  if (i < iMax)
    Lo(i, bT);
  else
  {
    szLo[i+0] = '-';
    szLo[i+1] = '-';
  }
}

static void HiDec(uchar  i, uchar  bT) {
  szHi[i+0] = szDigits[bT / 100];
  szHi[i+1] = szDigits[(bT % 100) / 10];
  szHi[i+2] = szDigits[bT % 10];
}


static void TestRequest3(void) {
  HiDec(0, iwInBuff3);

  HiDec(4, wOffset);
  szHi[7] = '-';
  HiDec(8, wOffset+7);

  Dump(0, mpbInBuff3[0]);
  Dump(1, mpbInBuff3[1]);
  Dump(2, mpbInBuff3[2]);
  Dump(3, mpbInBuff3[3]);
  Dump(4, mpbInBuff3[4]);
  Dump(5, mpbInBuff3[5]);
  Dump(6, mpbInBuff3[6]);
  Dump(7, mpbInBuff3[7]);
}


void    auto_TestRequest(void)
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
        TestRequest3();
        break;
    }
  }
}
