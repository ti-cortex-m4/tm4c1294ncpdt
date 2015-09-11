/*------------------------------------------------------------------------------
SERIAL1.C

TODO: volatile
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_serial1.h"
#include "../memory/mem_uni.h"
#include "../serial/flow.h"
#include "../serial/ports.h"
#include "../serial/bulk.h"
#include "../serial/slave_modem.h"
#include "../kernel/crc-16.h"
#include "../uarts.h"
#include "serial.h"



void    DTROff1(void) {
}


void    InputMode1(void) {
}


void    OutputMode1(void) {
}



bool    GetRI1(uint32_t ui32Status) {
  return ((ui32Status & 0x00000010) != 0) || ((ui32Status & 0x00000040) != 0);
}


bool    GetTI1(uint32_t ui32Status) {
  return ((ui32Status & 0x00000020) != 0) || (ui32Status == 0);
}


uchar	InByte1(void) {
  return HWREG(UART2_BASE + UART_O_DR);
}


void    OutByte1(uchar  bT) {
	HWREG(UART2_BASE + UART_O_DR) = bT;
}



void    UART2IntHandler(void) {
uchar   bT;
uint32_t ui32Status;

  ui32Status = UARTIntStatus(UART2_BASE, true);
  UARTIntClear(UART2_BASE, ui32Status);


  // ведущий режим
  if (((mppoPorts[1].enStream == STR_MASTERDIRECT) ||
       (mppoPorts[1].enStream == STR_MASTERMODEM)) &&
      (mpboLocal[1] == false))
  {
    if (GetRI1(ui32Status))
    {
      bT = InByte1();

      if (mpSerial[1] == SER_BEGIN)
      {
        if (bT == szPacketCtrlZ[ibPacket1])
        {
          if (++ibPacket1 >= sizeof(szPacketCtrlZ))
          {
            ibPacket1 = 0;
            mpSerial[1] = SER_LOCAL;
          }
        }
        else ibPacket1 = 0;
      }
      else if ((mpSerial[1] == SER_OUTPUT_MASTER) ||
               (mpSerial[1] == SER_INPUT_MASTER)  ||
               (mpSerial[1] == SER_ANSWER_MODEM))
      {
        if (iwInBuff1 >= wINBUFF_SIZE)          // переполнение входного буфера ?
        {
          InputMode1();
          mpSerial[1] = SER_OVERFLOW;
        }
        else
        {
          if (mpSerial[1] == SER_ANSWER_MODEM)
          {
            mpbInBuff1[ iwInBuff1++ ] = bT;

            if ((bT == '\r') || (bT == '\n'))   // приём завершён
            {
              InputMode1();
              mpSerial[1] = SER_POSTANSWER_MODEM;
            }
          }
          else
          if (mpSerial[1] == SER_INPUT_MASTER)
          {
            mpbInBuff1[ iwInBuff1 ] = bT;
            cwInDelay1 = mpwInDelay[1];

            if (++iwInBuff1 == cwInBuff1)       // приём завершён
            {
              InputMode1();
              mpSerial[1] = SER_POSTINPUT_MASTER;
            }
          }
        }
      }
    }

    if (GetTI1(ui32Status))
    {
      if (mpSerial[1] == SER_OUTPUT_MASTER)
      {
        bT = mpbOutBuff1[ iwOutBuff1 ];

        if (++iwOutBuff1 <= cwOutBuff1)         // продолжаем передачу ?
          OutByte1(bT);
        else                                    // передача завершена
        {
          if (cwInBuff1 == 0)
          {
            InputMode1();
            mpSerial[1] = SER_BEGIN;            // передача без ответа
          }
          else
          if (cwInBuff1 == SERIAL_LOCAL)
          {
            InputMode1();                       // передача с ответом
            mpSerial[1] = SER_BEGIN;            // начинаем приём

            mpboLocal[1] = true;
          }
          else
          if (cwInBuff1 == SERIAL_MODEM)
          {
            InputMode1();                       // передача с ответом
            mpSerial[1] = SER_ANSWER_MODEM;     // начинаем приём
          }
          else
          {
            InputMode1();                       // передача с ответом
            cwInDelay1 = mpwInDelay[1];

            mpSerial[1] = SER_INPUT_MASTER;     // начинаем приём
          }
        }
      }
    }
  }


  // ведомый режим
  else
  {
    if (GetRI1(ui32Status))
    {
      bT = InByte1();

      cwIn1++;
      bIn1 = bT;

      if ((fSendAT == 1) && (IsFlow1() == 0))
      {
        ResetSendAT(1);
      }

      if ((mppoPorts[1].enStream == STR_SLAVECRC) || (IsFlow1() == 1))
      {
        if ((mppoPorts[1].enStream != STR_SLAVEUNI) || (boRepeatFlowUni == true))
          RepeatFlow();

        if (mpSerial[1] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay1 = mpwMinorInDelay[1];

          mpSerial[1] = SER_INPUT_SLAVE;
          iwInBuff1 = 0;
        }

        if (mpSerial[1] == SER_INPUT_SLAVE)
        {
          if (iwInBuff1 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode1();
            mpSerial[1] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay1 = mpwMinorInDelay[1];      // продолжаем приём
            mpbInBuff1[ iwInBuff1++ ] = bT;
          }

#ifndef MODBUS
          if (IsFlow1() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff1 >= 4) && (iwInBuff1 == mpbInBuff1[2] + mpbInBuff1[3]*0x100))
            {
              InputMode1();
              mpSerial[1] = SER_POSTINPUT_SLAVE;    // приём закончен: по количеству байт
            }
          }
#endif

        }
      }
      else if (mppoPorts[1].enStream == STR_SLAVEUNI)
      {
        if (mpSerial[1] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay1 = mpwMinorInDelay[1];

          mpSerial[1] = SER_INPUT_SLAVE_UNI;
          iwInBuff1 = 0;
        }

        if (mpSerial[1] == SER_INPUT_SLAVE_UNI)
        {
          if (iwInBuff1 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode1();
            mpSerial[1] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay1 = mpwMinorInDelay[1];      // продолжаем приём
            mpbInBuff1[ iwInBuff1++ ] = bT;
          }

          if (IsFlow1() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff1 >= 10) && (iwInBuff1 == mpbInBuff1[3] + mpbInBuff1[2]*0x100))
            {
              InputMode1();
              mpSerial[1] = SER_POSTINPUT_SLAVE_UNI;   // приём закончен: по количеству байт
            }
          }
        }
      }
      else
      {
        if (bT == szPacketCRC[ibPacket1])
        {
          if (++ibPacket1 >= bPACKET_HEADER)
          {
            ibPacket1 = 0;
            mpSerial[1] = SER_PACKET_HEADER;
            iwInBuff1 = 0;
          }
        }
        else if (bT != szPacketCRC[0]) ibPacket1 = 0;

        if (mpSerial[1] == SER_PACKET_BODY)
        {
          if (iwInBuff1 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode1();
            mpSerial[1] = SER_BEGIN;            // начинаем приём сначала
          }
          else
            mpbInBuff1[ iwInBuff1++ ] = bT;     // продолжаем приём

          if ((iwInBuff1 >= 7) && (iwInBuff1 == mpbInBuff1[2] + mpbInBuff1[3]*0x100))
          {
            InputMode1();
            mpSerial[1] = SER_POSTINPUT_SLAVE;  // приём закончен: по количеству байт
          }
        }
        else if (mpSerial[1] == SER_PACKET_HEADER)
          mpSerial[1] = SER_PACKET_BODY;
        else
        {
          if (bT == 0x1A)
            mpSerial[1] = SER_CTRL_Z;

          else if ((bT == 0x1B) && ((mpSerial[1] == SER_BEGIN) || (mpSerial[1] == SER_PAUSE)))
            mpSerial[1] = SER_ESC;

          else if ((bT != 0x1B) && (mpSerial[1] == SER_ESC))
          {
            InputMode1();
            mpSerial[1] = SER_CHAR;

            mpbInBuff1[1] = bT;
          }
        }
      }
    }

    if (GetTI1(ui32Status))
    {
      if (mpSerial[1] == SER_OUTPUT_SLAVE)
      {
        bT = mpbOutBuff1[ iwOutBuff1++ ];

        if (iwOutBuff1 <= cwOutBuff1)           // продолжаем передачу ?
        {
          OutByte1(bT);
          OutByteBulk1();
        }
        else
        {
          InputMode1();
          mpSerial[1] = SER_BEGIN;              // передача завершена
        }
      }

      else if (mpSerial[1] == SER_HEADER)
      {
        bT = mpbOutBuff1[ iwOutBuff1++ ];

        if (iwOutBuff1 < bHEADER)
        {
          OutByte1(bT);
          OutByteBulk1();
        }
        else
        {
          mpSerial[1] = SER_POINTER;
          OutByte1(bT);
          OutByteBulk1();
        }
      }
      else if (mpSerial[1] == SER_POINTER)
      {
        bT = bCRCHi1 ^ *pbData1;

        bCRCHi1 = bCRCLo1 ^ mpbCRCHi[bT];
        bCRCLo1 = mpbCRCLo[bT];

        bT = *(pbData1++);

        if (++iwOutBuff1 < cwOutBuff1)
        {
          OutByte1(bT);
          OutByteBulk1();
        }
        else
        {
          mpSerial[1] = SER_CRCHI;
          OutByte1(bT);
          OutByteBulk1();
        }
      }
      else if (mpSerial[1] == SER_CRCHI)
      {
        OutByte1(bCRCHi1);
        mpSerial[1] = SER_CRCLO;
        OutByteBulk1();
      }
      else if (mpSerial[1] == SER_CRCLO)
      {
        OutByte1(bCRCLo1);
        mpSerial[1] = SER_CLOSE;
        OutByteBulk1();
      }
      else if (mpSerial[1] == SER_CLOSE)
      {
        InputMode1();
        mpSerial[1] = SER_BEGIN;                // передача завершена
      }
    }
  }
}

void    InDelay1_Timer0(void) {
  if (mpSerial[1] == SER_INPUT_SLAVE)
  {
    if (cwInDelay1 == 0)
      mpSerial[1] = SER_POSTINPUT_SLAVE;        // приём закончен: по таймауту
    else
      cwInDelay1--;
  }
  else
  if (mpSerial[1] == SER_INPUT_SLAVE_UNI)
  {
    if (cwInDelay1 == 0)
      mpSerial[1] = SER_POSTINPUT_SLAVE_UNI;       // приём закончен: по таймауту
    else
      cwInDelay1--;
  }
  else
  if (mpSerial[1] == SER_INPUT_MASTER)
  {
    if (cwInDelay1 == 0)
      mpSerial[1] = SER_BADLINK;                // приём закончен: нет данных
    else
      cwInDelay1--;
  }
  else
  if (mpSerial[1] == SER_BULK)
  {
    RunBulk1();
  }
}



void    InitSerial1(void)
{
  ResetSendAT(1);

  mpboLocal[1] = false;

  InputMode1();
  DTROff1();

  mpSerial[1] = SER_BEGIN;
}



void    Query1(uint  cwIn, uchar  cbOut, bool  fMinInDelay)
{
  iwInBuff1  = 0;
  iwOutBuff1 = 0;

  cwInBuff1  = cwIn;
  cwOutBuff1 = cbOut;

  if (fMinInDelay == true)
    mpwInDelay[1] = mpwMinorInDelay[1];
  else
    mpwInDelay[1] = mpwMajorInDelay[1];

  OutputMode1();
  mpSerial[1] = SER_OUTPUT_MASTER;

  IntPendSet(INT_UART2);
}



void    Answer1(uint  wSize, serial  seT)
{
  iwOutBuff1 = 0;
  cwOutBuff1 = wSize;

  OutputMode1();
  mpSerial[1] = seT;
  AnswerBulk1();

  IntPendSet(INT_UART2);
}
