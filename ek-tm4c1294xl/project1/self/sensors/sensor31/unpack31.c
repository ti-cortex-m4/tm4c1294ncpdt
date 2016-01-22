/*------------------------------------------------------------------------------
UNPACK_N31!C


------------------------------------------------------------------------------*/

#include "unpack31.h"

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../serial/ports2.h"
//#include "../serial/monitor.h"
//#include "../display/display.h"
#include "automatic31.h"



void    UnpackN31(void)
{
uchar   i,j,k,a,b,c;
uint    x;

  if ((InBuff(2) & 0x80) == 0)          // нет сжати€
  {
    InitPopCod();

    for (i=0; i<InBuff(1); i++) SetInBuff(i+3, PopCharCod());
  }
  else                                  // есть сжатие
  {
    SetInBuff(2, InBuff(2) & 0x7F);

    InitPopCod();

    j = PopCharCod();                   // признак повтора
    x = 0x200;                          // адрес промежуточного буфера

    i = 0;
    while (i < InBuff(1)-1)
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
    for (i=0; i<InBuff(1); i++) SetInBuff(i+3, InBuff(i+0x200));

    SetIndexInBuff(3+InBuff(1));        // размер прин€того пакета
  }
}
