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


static uint             wOffset;
static uchar            bDirection;



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
      bDirection = 1;
    }
  }

  else if (bKey == bKEY_POINT)
  {
    if (wOffset <= 999 - 8)
      wOffset += 8;
  }
  else if (bKey == bKEY_MINUS)
  {
    if (wOffset >= 0 + 8)
      wOffset -= 8;
  }

  else if (bKey == 0)
  {
    wOffset = 0;
    bDirection = 0;
  }
  else if (bKey == 1)
  {
    wOffset = 0;
    bDirection = 1;
  }
}


static void LoHex(uchar  i, uint iwInBuff, uchar  bT) {
  uchar j = i*2;

  if (i + wOffset < iwInBuff)
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


static void TestRequest(uint  iwBuff, uchar  *pbData) {
  szHi[0+0] = (bDirection == 0 ? 'O' : 'I');
  szHi[0+1] = '1'+ibPortActive;

  HiDec(5, iwBuff);

  HiDec(9, wOffset);
  szHi[12] = '-';
  HiDec(13, wOffset+7);

  LoHex(0, iwBuff, *(pbData++));
  LoHex(1, iwBuff, *(pbData++));
  LoHex(2, iwBuff, *(pbData++));
  LoHex(3, iwBuff, *(pbData++));
  LoHex(4, iwBuff, *(pbData++));
  LoHex(5, iwBuff, *(pbData++));
  LoHex(6, iwBuff, *(pbData++));
  LoHex(7, iwBuff, *(pbData++));
}


void    auto_TestRequest(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    switch (ibPortActive)
    {
      case 0:
        bDirection == 0
        ? TestRequest(iwOutBuff0 - 1, mpbOutBuff0 + wOffset)
        : TestRequest(iwInBuff0, mpbInBuff0 + wOffset);
        break;

      case 1:
        bDirection == 0
        ? TestRequest(iwOutBuff1 - 1, mpbOutBuff1 + wOffset)
        : TestRequest(iwInBuff1, mpbInBuff1 + wOffset);
        break;

      case 2:
        bDirection == 0
        ? TestRequest(iwOutBuff2 - 1, mpbOutBuff2 + wOffset)
        : TestRequest(iwInBuff2, mpbInBuff2 + wOffset);
        break;

      case 3:
        bDirection == 0
        ? TestRequest(iwOutBuff3 - 1, mpbOutBuff3 + wOffset)
        : TestRequest(iwInBuff3, mpbInBuff3 + wOffset);
        break;
    }
  }
}
