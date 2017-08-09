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


static void LoHex(uchar  i, uchar  bT) {
  uchar j = i*2;

  if (i <= wOffset+7)
    Lo(j, bT);
  else
  {
    szLo[j+0] = '-';
    szLo[j+1] = '-';
  }
}

static void HiDec(uchar  i, uchar  bT) {
  szHi[i+0] = szDigits[bT / 100];
  szHi[i+1] = szDigits[(bT % 100) / 10];
  szHi[i+2] = szDigits[bT % 10];
}


static void TestRequest(uint iwInBuff, uchar  *pbData) {
  HiDec(0, iwInBuff);

  HiDec(4, wOffset);
  szHi[7] = '-';
  HiDec(8, wOffset+7);

  LoHex(0, *(pbData++));
  LoHex(1, *(pbData++));
  LoHex(2, *(pbData++));
  LoHex(3, *(pbData++));
  LoHex(4, *(pbData++));
  LoHex(5, *(pbData++));
  LoHex(6, *(pbData++));
  LoHex(7, *(pbData++));
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
        TestRequest(iwInBuff3, mpbInBuff3 + wOffset);
        break;
    }
  }
}
