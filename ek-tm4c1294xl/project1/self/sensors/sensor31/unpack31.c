/*------------------------------------------------------------------------------
UNPACK31!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "automatic31.h"
#include "unpack31.h"



void    Unpack31(void)
{
uchar   i,j,k,a,b,c;
uint    x;

  MonitorString("\n raw");
  MonitorIn();

  if ((InBuff(2) & 0x80) == 0)          // ��� ������
  {
    InitPopCod();

    for (i=0; i<InBuff(1); i++) SetInBuff(i+3, PopCharCod());

    MonitorString("\n without unpack");
    MonitorIn();
  }
  else                                  // ���� ������
  {
    SetInBuff(2, InBuff(2) & 0x7F);

    InitPopCod();

    j = PopCharCod();                   // ������� �������
    x = 0x200;                          // ����� �������������� ������

    i = 0;
    while (i < InBuff(1)-1)
    {
      a = PopCharCod(); i++;

      if (a != j) SetInBuff(x++, a);
      else
      {
        b = PopCharCod(); i++;          // ����������� ��������
        c = PopCharCod(); i++;          // ����������� ����

        for (k=0; k<b; k++) SetInBuff(x++, c);
      }
    }

    SetInBuff(1, x-0x200);
    for (i=0; i<InBuff(1); i++) SetInBuff(i+3, InBuff(i+0x200));

    SetIndexInBuff(3+InBuff(1));        // ������ ��������� ������

    MonitorString("\n with unpack");
    MonitorIn();
  }
}
