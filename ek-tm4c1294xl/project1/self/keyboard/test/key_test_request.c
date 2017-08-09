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
    if (wOffset <= 999 - 8)
      wOffset += 8;
  }
  else if (bKey == bKEY_MINUS)
  {
    if (wOffset >= 0 + 8)
      wOffset -= 8;
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


static void TestRequest(uint  iwInBuff, uchar  *pbData) {
  szHi[0+0] = 'Ï';
  szHi[0+1] = '1'+ibPortActive;

  HiDec(5, iwInBuff);

  HiDec(9, wOffset);
  szHi[12] = '-';
  HiDec(13, wOffset+7);

  LoHex(0, iwInBuff, *(pbData++));
  LoHex(1, iwInBuff, *(pbData++));
  LoHex(2, iwInBuff, *(pbData++));
  LoHex(3, iwInBuff, *(pbData++));
  LoHex(4, iwInBuff, *(pbData++));
  LoHex(5, iwInBuff, *(pbData++));
  LoHex(6, iwInBuff, *(pbData++));
  LoHex(7, iwInBuff, *(pbData++));
}


void    auto_TestRequest(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    switch (ibPortActive)
    {
      case 0:
        TestRequest(iwInBuff0, mpbInBuff0 + wOffset);
        break;

      case 1:
        TestRequest(iwInBuff1, mpbInBuff1 + wOffset);
        break;

      case 2:
        TestRequest(iwInBuff2, mpbInBuff2 + wOffset);
        break;

      case 3:
        TestRequest(iwInBuff3, mpbInBuff3 + wOffset);
        break;
    }
  }
}
