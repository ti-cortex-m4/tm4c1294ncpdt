/*------------------------------------------------------------------------------
SERIAL2!C

// TODO volatile
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_serial2.h"
#include "../serial/flow.h"
#include "../serial/ports.h"
#include "../serial/bulk.h"
#include "../serial/slave_modem.h"
#include "../time/delay.h"
#include "../kernel/crc-16.h"
#include "../hardware/uarts.h"
#include "serial.h"



void    DTROff2(void) {
}


void    InputMode2(void) {
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0080) = ~0x0020;
  bPortsStatus &= 0xFE;
}


void    OutputMode2(void) {
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0080) = 0x0020;
  bPortsStatus |= 0x01;
}



bool    GetRI2(uint32_t ui32Status) {
  return ((ui32Status & 0x00000010) != 0) || ((ui32Status & 0x00000040) != 0);
}


bool    GetTI2(uint32_t ui32Status) {
  return ((ui32Status & 0x00000020) != 0) || (ui32Status == 0);
}


uchar	InByte2(void) {
  return HWREG(UART3_BASE + UART_O_DR);
}


void    OutByte2(uchar  bT) {
	HWREG(UART3_BASE + UART_O_DR) = bT;
}



void    UART3IntHandler(void) {
uchar   bT;
uint32_t ui32Status;

  ui32Status = UARTIntStatus(UART3_BASE, true);
  UARTIntClear(UART3_BASE, ui32Status);


  // ������� �����
  if (((mppoPorts[2].enStream == STR_MASTERDIRECT) ||
       (mppoPorts[2].enStream == STR_MASTERMODEM)) &&
      (mpboLocal[2] == false))
  {
    if (GetRI2(ui32Status))
    {
      bT = InByte2();

      if (mpSerial[2] == SER_BEGIN)
      {
        if (bT == szPacketCtrlZ[ibPacket2])
        {
          if (++ibPacket2 >= sizeof(szPacketCtrlZ))
          {
            ibPacket2 = 0;
            mpSerial[2] = SER_LOCAL;
          }
        }
        else ibPacket2 = 0;
      }
      else if ((mpSerial[2] == SER_OUTPUT_MASTER) ||
               (mpSerial[2] == SER_INPUT_MASTER)  ||
               (mpSerial[2] == SER_ANSWER_MODEM))
      {
        if (iwInBuff2 >= wINBUFF_SIZE)          // ������������ �������� ������ ?
        {
          InputMode2();
          mpSerial[2] = SER_OVERFLOW;
        }
        else
        {
          if (mpSerial[2] == SER_ANSWER_MODEM)
          {
            mpbInBuff2[ iwInBuff2++ ] = bT;

            if ((bT == '\r') || (bT == '\n'))   // ���� ��������
            {
              InputMode2();
              mpSerial[2] = SER_POSTANSWER_MODEM;
            }
          }
          else
          if (mpSerial[2] == SER_INPUT_MASTER)
          {
            mpbInBuff2[ iwInBuff2 ] = bT;
            cwInDelay2 = mpwInDelay[2];

            if (++iwInBuff2 == cwInBuff2)       // ���� ��������
            {
              InputMode2();
              mpSerial[2] = SER_POSTINPUT_MASTER;
            }
          }
        }
      }
    }

    if (GetTI2(ui32Status))
    {
      if (mpSerial[2] == SER_OUTPUT_MASTER)
      {
        bT = mpbOutBuff2[ iwOutBuff2 ];

        if (++iwOutBuff2 <= cwOutBuff2)         // ���������� �������� ?
          OutByte2(bT);
        else                                    // �������� ���������
        {
          if (cwInBuff2 == 0)
          {
            InputMode2();
            mpSerial[2] = SER_BEGIN;            // �������� ��� ������
          }
          else
          if (cwInBuff2 == SERIAL_LOCAL)
          {
            InputMode2();                       // �������� � �������
            mpSerial[2] = SER_BEGIN;            // �������� ����

            mpboLocal[2] = true;
          }
          else
          if (cwInBuff2 == SERIAL_MODEM)
          {
            InputMode2();                       // �������� � �������
            mpSerial[2] = SER_ANSWER_MODEM;     // �������� ����
          }
          else
          {
            InputMode2();                       // �������� � �������
            cwInDelay2 = mpwInDelay[2];

            mpSerial[2] = SER_INPUT_MASTER;     // �������� ����
          }
        }
      }
    }
  }


  // ������� �����
  else
  {
    if (GetRI2(ui32Status))
    {
      bT = InByte2();

      cwIn2++;
      bIn2 = bT;

      if (fSendAT == 1)
      {
        ResetSendAT(2);
      }

      if ((mppoPorts[2].enStream == STR_SLAVECRC) || (IsFlow2() == 1))
      {
//        if (mppoPorts[2].enStream != STR_SLAVEUNI)
//          RepeatFlow();

        if (mpSerial[2] == SER_BEGIN)           // ���� ������� ����� � �������
        {
          cwInDelay2 = mpwMinorInDelay[2];

          mpSerial[2] = SER_INPUT_SLAVE;
          iwInBuff2 = 0;
        }

        if (mpSerial[2] == SER_INPUT_SLAVE)
        {
          if (iwInBuff2 >= wINBUFF_SIZE)        // ������������ �������� ������ ?
          {
            InputMode2();
            mpSerial[2] = SER_BEGIN;            // �������� ���� �������
          }
          else
          {
            cwInDelay2 = mpwMinorInDelay[2];      // ���������� ����
            mpbInBuff2[ iwInBuff2++ ] = bT;
          }

#ifndef MODBUS
          if (IsFlow2() == 0)                   // ���� ��������: �� ���������� ����
          {
            if ((iwInBuff2 >= 4) && (iwInBuff2 == mpbInBuff2[2] + mpbInBuff2[3]*0x100))
            {
              InputMode2();
              mpSerial[2] = SER_POSTINPUT_SLAVE;    // ���� ��������: �� ���������� ����
            }
          }
#endif

        }
      }
      else if (mppoPorts[2].enStream == STR_SLAVEUNI)
      {
        if (mpSerial[2] == SER_BEGIN)           // ���� ������� ����� � �������
        {
          cwInDelay2 = mpwMinorInDelay[2];

          mpSerial[2] = SER_INPUT_SLAVE_UNI;
          iwInBuff2 = 0;
        }

        if (mpSerial[2] == SER_INPUT_SLAVE_UNI)
        {
          if (iwInBuff2 >= wINBUFF_SIZE)        // ������������ �������� ������ ?
          {
            InputMode2();
            mpSerial[2] = SER_BEGIN;            // �������� ���� �������
          }
          else
          {
            cwInDelay2 = mpwMinorInDelay[2];      // ���������� ����
            mpbInBuff2[ iwInBuff2++ ] = bT;
          }

          if (IsFlow2() == 0)                   // ���� ��������: �� ���������� ����
          {
            if ((iwInBuff2 >= 10) && (iwInBuff2 == mpbInBuff2[3] + mpbInBuff2[2]*0x100))
            {
              InputMode2();
              mpSerial[2] = SER_POSTINPUT_SLAVE_UNI;   // ���� ��������: �� ���������� ����
            }
          }
        }
      }
      else
      {
        if (bT == szPacketCRC[ibPacket2])
        {
          if (++ibPacket2 >= bPACKET_HEADER)
          {
            ibPacket2 = 0;
            mpSerial[2] = SER_PACKET_HEADER;
            iwInBuff2 = 0;
          }
        }
        else if (bT != szPacketCRC[0]) ibPacket2 = 0;

        if (mpSerial[2] == SER_PACKET_BODY)
        {
          if (iwInBuff2 >= wINBUFF_SIZE)        // ������������ �������� ������ ?
          {
            InputMode2();
            mpSerial[2] = SER_BEGIN;            // �������� ���� �������
          }
          else
            mpbInBuff2[ iwInBuff2++ ] = bT;     // ���������� ����

          if ((iwInBuff2 >= 7) && (iwInBuff2 == mpbInBuff2[2] + mpbInBuff2[3]*0x100))
          {
            InputMode2();
            mpSerial[2] = SER_POSTINPUT_SLAVE;  // ���� ��������: �� ���������� ����
          }
        }
        else if (mpSerial[2] == SER_PACKET_HEADER)
          mpSerial[2] = SER_PACKET_BODY;
        else
        {
          if (bT == 0x1A)
          {
            InputMode2();
            mpSerial[2] = SER_CTRL_Z;
          }

          else if ((bT == 0x1B) && ((mpSerial[2] == SER_BEGIN) || (mpSerial[2] == SER_PAUSE)))
            mpSerial[2] = SER_ESC;

          else if ((bT != 0x1B) && (mpSerial[2] == SER_ESC))
          {
            InputMode2();
            mpSerial[2] = SER_CHAR;

            mpbInBuff2[0] = bT;
          }
        }
      }
    }

    if (GetTI2(ui32Status))
    {
      if (mpSerial[2] == SER_OUTPUT_SLAVE)
      {
        bT = mpbOutBuff2[ iwOutBuff2++ ];

        if (iwOutBuff2 <= cwOutBuff2)           // ���������� �������� ?
        {
          OutByte2(bT);
          OutByteBulk2();
        }
        else
        {
          InputMode2();
          mpSerial[2] = SER_BEGIN;              // �������� ���������
        }
      }

      else if (mpSerial[2] == SER_HEADER)
      {
        bT = mpbOutBuff2[ iwOutBuff2++ ];

        if (iwOutBuff2 < bHEADER)
        {
          OutByte2(bT);
          OutByteBulk2();
        }
        else
        {
          mpSerial[2] = SER_POINTER;
          OutByte2(bT);
          OutByteBulk2();
        }
      }
      else if (mpSerial[2] == SER_POINTER)
      {
        bT = bCRCHi2 ^ *pbData2;

        bCRCHi2 = bCRCLo2 ^ mpbCRCHi[bT];
        bCRCLo2 = mpbCRCLo[bT];

        bT = *(pbData2++);

        if (++iwOutBuff2 < cwOutBuff2)
        {
          OutByte2(bT);
          OutByteBulk2();
        }
        else
        {
          mpSerial[2] = SER_CRCHI;
          OutByte2(bT);
          OutByteBulk2();
        }
      }
      else if (mpSerial[2] == SER_CRCHI)
      {
        OutByte2(bCRCHi2);
        mpSerial[2] = SER_CRCLO;
        OutByteBulk2();
      }
      else if (mpSerial[2] == SER_CRCLO)
      {
        OutByte2(bCRCLo2);
        mpSerial[2] = SER_CLOSE;
        OutByteBulk2();
      }
      else if (mpSerial[2] == SER_CLOSE)
      {
        InputMode2();
        mpSerial[2] = SER_BEGIN;                // �������� ���������
      }
    }
  }
}

void    InDelay2_Timer0(void) {
  if (mpSerial[2] == SER_INPUT_SLAVE)
  {
    if (cwInDelay2 == 0)
      mpSerial[2] = SER_POSTINPUT_SLAVE;        // ���� ��������: �� ��������
    else
      cwInDelay2--;
  }
  else
  if (mpSerial[2] == SER_INPUT_SLAVE_UNI)
  {
    if (cwInDelay2 == 0)
      mpSerial[2] = SER_POSTINPUT_SLAVE_UNI;       // ���� ��������: �� ��������
    else
      cwInDelay2--;
  }
  else
  if (mpSerial[2] == SER_INPUT_MASTER)
  {
    if (cwInDelay2 == 0)
      mpSerial[2] = SER_BADLINK;                // ���� ��������: ��� ������
    else
      cwInDelay2--;
  }
  else
  if (mpSerial[2] == SER_BULK)
  {
    RunBulk2();
  }
}



void    InitSerial2(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R3; // GPIO Port D Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x0020; // GPIO Direction
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x0020; // GPIO Digital Enable

  ResetSendAT(2);

  mpboLocal[2] = false;

  InputMode2();
  DTROff2();

  mpSerial[2] = SER_BEGIN;
}



void    Query2(uint  cwIn, uchar  cbOut, bool  fMinInDelay)
{
  iwInBuff2  = 0;
  iwOutBuff2 = 0;

  cwInBuff2  = cwIn;
  cwOutBuff2 = cbOut;

  if (fMinInDelay == true)
    mpwInDelay[2] = mpwMinorInDelay[2];
  else
    mpwInDelay[2] = mpwMajorInDelay[2];

  OutputMode2();
  Delay(mpwOutputDelay[2]);

  mpSerial[2] = SER_OUTPUT_MASTER;

  IntPendSet(INT_UART3);
  Delay(mpwTxDelay[2]);
}



void    Answer2(uint  wSize, serial  seT)
{
  iwOutBuff2 = 0;
  cwOutBuff2 = wSize;

  OutputMode2();
  Delay(mpwOutputDelay[2]);

  mpSerial[2] = seT;
  AnswerBulk2();

  IntPendSet(INT_UART3);
}
