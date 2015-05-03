/*------------------------------------------------------------------------------



------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../serial/ports2.h"



#ifndef SKIP_K

void    DecompressK(bit  fShow)
{
uint    i;
uchar   j;

  if (cbHeaderBcc == 0) return;

  if (cwInBuffBcc == IndexInBuff()) return;
  cwInBuffBcc = IndexInBuff();

  if ((fShow == 1) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

  if (IndexInBuff() > 2) 
  {
    InitPop(1);

    j = 0;
    for (i=0; i<IndexInBuff()-2; i++) 
    {
      if (PopChar0Bcc() == ')') j++;

      if ((j == cbHeaderBcc) && (i+6 == IndexInBuff()))
      {
        SetCountInBuff(i+6);

        if ((fShow == 1) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

        InputMode();
        mpSerial[ibPort] = SER_POSTINPUT_MASTER;
        break;
      }
    }
  }
}


void    DecompressK2(bit  fShow, uchar  bOffset)
{
uint    i;
uchar   j;

  if (cbHeaderBcc == 0) return;

  if (cwInBuffBcc == IndexInBuff()) return;
  cwInBuffBcc = IndexInBuff();

  if ((fShow == 1) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

  if (IndexInBuff() > 2) 
  {
    InitPop(1);

    j = 0;
    for (i=0; i<IndexInBuff()-2; i++) 
    {
      if (PopChar0Bcc() == ')') j++;
         
      if ((j == cbHeaderBcc) && (i+bOffset == IndexInBuff()))
      {
        SetCountInBuff(i+bOffset);

        if ((fShow == 1) && (IndexInBuff() > 40)) sprintf(szLo," прием: %-4u    ",IndexInBuff());

        InputMode();
        mpSerial[ibPort] = SER_POSTINPUT_MASTER;
        break;
      }
    }
  }
}

#endif

