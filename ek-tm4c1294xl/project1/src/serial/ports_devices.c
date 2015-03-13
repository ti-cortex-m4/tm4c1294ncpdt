/*------------------------------------------------------------------------------
PORTS_DEVICES.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../crc-16.h"
#include        "../keyboard/keyboard.h"
#include        "../hardware/watchdog.h"
#include        "../digitals/wait_answer.h"
#include        "../isr/serial0.h"
#include        "../isr/serial1.h"
#include        "../isr/serial2.h"
#include        "../isr/serial3.h"
#include        "ports.h"



void    Query(uint  cwIn, uchar  cbOut, bool  fMinor)
{
//  DebugOut(cwIn, cbOut);

  // ��� �������� ���� ������������� � ������� ����� �� ���������� ��������
  mpboLocal[ibPort] = boFalse;

  // �������� �������� �������� ��������� � ��������� (����� ������������ � ��������� ������� ����� �� ��������)
  if (cwIn != SERIAL_LOCAL) cbWaitQuery = bWAITQUERY;

  switch (ibPort)
  {
    case 0:  Query0(cwIn, cbOut, fMinor);  break;
    case 1:  Query1(cwIn, cbOut, fMinor);  break;
    case 2:  Query2(cwIn, cbOut, fMinor);  break;
    case 3:  Query3(cwIn, cbOut, fMinor);  break;
  }
}



// �������� ������� �� ���������� (�� ��������� ������)
void    QueryIO(uint  cwIn, uchar  cbOut)
{
  MakeCRC16OutBuff(0,cbOut-2);

  InitPush(0);
  Skip(cbOut-2);

  PushChar(bCRCHi);
  PushChar(bCRCLo);

  Query(cwIn,cbOut,1);
}



serial  Input(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == 1) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWDT();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      MakeCRC16InBuff( 0, CountInBuff() );

      if ((bCRCHi == 0) && (bCRCLo == 0))
        mpSerial[ibPort] = SER_GOODCHECK;
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return( mpSerial[ibPort] );
}
