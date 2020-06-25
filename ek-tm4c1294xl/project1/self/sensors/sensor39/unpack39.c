/*------------------------------------------------------------------------------
unpack36*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "unpack39.h"


/*
void    Unpack39(void)
{
  uchar i = 1;
  uchar j = 1;

  while (i < IndexInBuff()) {
    if ((InBuff(i) == 0x7D) && (InBuff(i+1) == 0x5E)) {
      MonitorString("\n j1="); MonitorIntDec(i); MonitorIntDec(j);
      SetInBuff(j, 0x7E);
      i += 2;
      j++;
    } else if ((InBuff(i) == 0x7D) && (InBuff(i+1) == 0x5D)) {
      MonitorString("\n j2="); MonitorIntDec(i); MonitorIntDec(j);
      SetInBuff(j, 0x7D);
      i += 2;
      j++;
    } else {
      SetInBuff(j, InBuff(i));
      i++;
      j++;
    }
  }

  SetIndexInBuff(j);
}
*/


void    Decompress39(void)
{
  uchar i,c;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  c = 0;
  for (i=0; i<IndexInBuff(); i++) {
    if (InBuff(i) == 0x7E) c++;
  }
  if (c < 2) return;

  if ((InBuff(0) != 0x7E) || (InBuff(IndexInBuff()-1) != 0x7E))
    return;
/*
//#ifdef MONITOR_39
      MonitorString("\n unpack start "); MonitorIntDec(IndexInBuff());
      MonitorIn();
//#endif

      Unpack39();

//#ifdef MONITOR_39
      MonitorString("\n unpack finish "); MonitorIntDec(IndexInBuff());
      MonitorIn();
//#endif
*/
  uint wSize = (InBuff(1) & 0x07)*0x100 + InBuff(2) + 2;
  if (wSize != IndexInBuff()) {
//      Hi(0, wSize / 0x100);
//      Hi(2, wSize % 0x100);
//
//      Hi(5, IndexInBuff() / 0x100);
//      Hi(6, IndexInBuff() % 0x100);
    return;
  }

  MonitorIn();

  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}

/*
 *  Output: out=9 in=1000
 7e a0 07 03 03 91 9e 32 7e
 Input: in=7
 7e a0 41 03 03 58 7e
 Input HDLC:  Format=a041 wSize=0041 wCRCexpected=eac1 wCRCactual=3f00 CRC_error error1=2
 error 11

 if( (mbIn485[0] == 0x7E) && (mbIn485[wSizeIn485-1] == 0x7E) &&        //наличие старт и стоп байт
     ( ((mbIn485[1] & 0x07)*0x100 + mbIn485[2] + 2) == wSizeIn485 ) )  //верное кол-во байт
   return(1);
 else return(0);

 Input: in=65 12:54:58 13.06.20
 7e a0 41 03 03 56 00 dd 00 00 00 00 40 81 02 02 09 0c 07 e4 06 0c 05 11 00 00 ff 00 b4 00 15 00 00 00 00 00 00 40 8e 02 02 09 0c 07 e4 06 0c 05 11 1e 00 ff 00 b4 00 15 00 00 00 00 00 00 40 a5 7e ef


 */
