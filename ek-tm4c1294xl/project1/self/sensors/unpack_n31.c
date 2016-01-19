/*------------------------------------------------------------------------------



------------------------------------------------------------------------------*/

#include        "main.h"
#include        "xdata.h"
#include        "ports.h"
#include        "ports2.h"



#ifndef SKIP_G

void    DecompressG(void)
{
uchar   i,j,k,a,b,c;
uint    x;

  if ((GetInBuff(2) & 0x80) == 0)       // нет сжати€
  {
    InitPopCod();
                                        
    for (i=0; i<GetInBuff(1); i++) SetInBuff(i+3, PopCharCod());
  }
  else                                  // есть сжатие
  {
    SetInBuff(2, GetInBuff(2) & 0x7F);

    InitPopCod();

    j = PopCharCod();                   // признак повтора
    x = 0x200;                          // адрес промежуточного буфера

    i = 0;
    while (i < GetInBuff(1)-1)
    {
      a = PopCharCod(); i++;

      if (a != j) SetInBuff(x++, a);
      else 
      {
        b = PopCharCod(); i++;          // количесство повторов
        c = PopCharCod(); i++;          // повтор€емый байт

        for (k=0; k<b; k++) SetInBuff(x++, c);
      }
    }

    SetInBuff(1, x-0x200);
    for (i=0; i<GetInBuff(1); i++) SetInBuff(i+3, GetInBuff(i+0x200));

    SetIndexInBuff(3+GetInBuff(1));     // размер прин€того пакета
  }
}

#endif

