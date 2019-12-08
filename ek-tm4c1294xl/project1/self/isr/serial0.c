/*------------------------------------------------------------------------------
SERIAL0!C

// TODO volatile
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_serial0.h"
#include "../memory/mem_uni.h"
#include "../serial/flow.h"
#include "../serial/ports.h"
#include "../serial/bulk.h"
#include "../serial/slave_modem.h"
#include "../kernel/crc-16.h"
#include "../hardware/uarts.h"
#include "serial_flow.h"
#include "serial.h"



void    DTROff0(void) {
}


void    InputMode0(void) {
}


void    OutputMode0(void) {
}



bool    GetRI0(uint32_t ui32Status) {
  return ((ui32Status & 0x00000010) != 0) || ((ui32Status & 0x00000040) != 0);
}


bool    GetTI0(uint32_t ui32Status) {
  return ((ui32Status & 0x00000020) != 0) || (ui32Status == 0);
}


uchar	InByte0(void) {
  return HWREG(UART0_BASE + UART_O_DR);
}


void    OutByte0(uchar  bT) {
	HWREG(UART0_BASE + UART_O_DR) = bT;
}



void    UART0IntHandler(void) {
uchar   bT;
uint32_t ui32Status;

  ui32Status = UARTIntStatus(UART0_BASE, true);
  UARTIntClear(UART0_BASE, ui32Status);


  // ведущий режим
  if (((mppoPorts[0].enStream == STR_MASTERDIRECT) ||
       (mppoPorts[0].enStream == STR_MASTERMODEM)) &&
      (mpboLocal[0] == false))
  {
    if (GetRI0(ui32Status))
    {
      bT = InByte0();

      if (mpSerial[0] == SER_BEGIN)
      {
        if (bT == szPacketCtrlZ[ibPacket0])
        {
          if (++ibPacket0 >= sizeof(szPacketCtrlZ))
          {
            ibPacket0 = 0;
            mpSerial[0] = SER_LOCAL;
          }
        }
        else ibPacket0 = 0;
      }
      else if ((mpSerial[0] == SER_OUTPUT_MASTER) ||
               (mpSerial[0] == SER_INPUT_MASTER)  ||
               (mpSerial[0] == SER_ANSWER_MODEM))
      {
        if (iwInBuff0 >= wINBUFF_SIZE)          // переполнение входного буфера ?
        {
          InputMode0();
          mpSerial[0] = SER_OVERFLOW;
        }
        else
        {
          if (mpSerial[0] == SER_ANSWER_MODEM)
          {
            mpbInBuff0[ iwInBuff0++ ] = bT;

            if ((bT == '\r') || (bT == '\n'))   // приём завершён
            {
              InputMode0();
              mpSerial[0] = SER_POSTANSWER_MODEM;
            }
          }
          else
          if (mpSerial[0] == SER_INPUT_MASTER)
          {
            mpbInBuff0[ iwInBuff0 ] = bT;
            cwInDelay0 = mpwInDelay[0];

            if (++iwInBuff0 == cwInBuff0)       // приём завершён
            {
              InputMode0();
              mpSerial[0] = SER_POSTINPUT_MASTER;
            }
          }
        }
      }
    }

    if (GetTI0(ui32Status))
    {
      if (mpSerial[0] == SER_OUTPUT_MASTER)
      {
        bT = mpbOutBuff0[ iwOutBuff0 ];

        if (++iwOutBuff0 <= cwOutBuff0)         // продолжаем передачу ?
          OutByte0(bT);
        else                                    // передача завершена
        {
          if (cwInBuff0 == 0)
          {
            InputMode0();
            mpSerial[0] = SER_BEGIN;            // передача без ответа
          }
          else
          if (cwInBuff0 == SERIAL_LOCAL)
          {
            InputMode0();                       // передача с ответом
            mpSerial[0] = SER_BEGIN;            // начинаем приём

            mpboLocal[0] = true;
          }
          else
          if (cwInBuff0 == SERIAL_MODEM)
          {
            InputMode0();                       // передача с ответом
            mpSerial[0] = SER_ANSWER_MODEM;     // начинаем приём
          }
          else
          {
            InputMode0();                       // передача с ответом
            cwInDelay0 = mpwInDelay[0];

            mpSerial[0] = SER_INPUT_MASTER;     // начинаем приём
          }
        }
      }
    }
  }


  // ведомый режим
  else
  {
    if (GetRI0(ui32Status))
    {
      bT = InByte0();

      cwIn0++;
      bIn0 = bT;
      InSerialFlow(0, bT);

      if ((fSendAT == 1) && (IsFlow0() == 0))
      {
        ResetSendAT(0);
      }

      if ((mppoPorts[0].enStream == STR_SLAVECRC) || (IsFlow0() == 1))
      {
        if ((mppoPorts[0].enStream != STR_SLAVEUNI) || (boRepeatFlowUni == true))
          RepeatFlow();

        if (mpSerial[0] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay0 = mpwMinorInDelay[0];

          mpSerial[0] = SER_INPUT_SLAVE;
          iwInBuff0 = 0;
        }

        if (mpSerial[0] == SER_INPUT_SLAVE)
        {
          if (iwInBuff0 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode0();
            mpSerial[0] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay0 = mpwMinorInDelay[0];      // продолжаем приём
            mpbInBuff0[ iwInBuff0++ ] = bT;
          }

#ifndef MODBUS
          if (IsFlow0() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff0 >= 4) && (iwInBuff0 == mpbInBuff0[2] + mpbInBuff0[3]*0x100))
            {
              InputMode0();
              mpSerial[0] = SER_POSTINPUT_SLAVE;    // приём закончен: по количеству байт
            }
          }
#endif

        }
      }
      else if (mppoPorts[0].enStream == STR_SLAVEUNI)
      {
        if (mpSerial[0] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay0 = mpwMinorInDelay[0];

          mpSerial[0] = SER_INPUT_SLAVE_UNI;
          iwInBuff0 = 0;
        }

        if (mpSerial[0] == SER_INPUT_SLAVE_UNI)
        {
          if (iwInBuff0 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode0();
            mpSerial[0] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay0 = mpwMinorInDelay[0];      // продолжаем приём
            mpbInBuff0[ iwInBuff0++ ] = bT;
          }

          if (IsFlow0() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff0 >= 10) && (iwInBuff0 == mpbInBuff0[3] + mpbInBuff0[2]*0x100))
            {
              InputMode0();
              mpSerial[0] = SER_POSTINPUT_SLAVE_UNI;   // приём закончен: по количеству байт
            }
          }
        }
      }
      else
      {
        if (bT == szPacketCRC[ibPacket0])
        {
          if (++ibPacket0 >= bPACKET_HEADER)
          {
            ibPacket0 = 0;
            mpSerial[0] = SER_PACKET_HEADER;
            iwInBuff0 = 0;
          }
        }
        else if (bT != szPacketCRC[0]) ibPacket0 = 0;

        if (mpSerial[0] == SER_PACKET_BODY)
        {
          if (iwInBuff0 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode0();
            mpSerial[0] = SER_BEGIN;            // начинаем приём сначала
          }
          else
            mpbInBuff0[ iwInBuff0++ ] = bT;     // продолжаем приём

          if ((iwInBuff0 >= 7) && (iwInBuff0 == mpbInBuff0[2] + mpbInBuff0[3]*0x100))
          {
            InputMode0();
            mpSerial[0] = SER_POSTINPUT_SLAVE;  // приём закончен: по количеству байт
          }
        }
        else if (mpSerial[0] == SER_PACKET_HEADER)
          mpSerial[0] = SER_PACKET_BODY;
        else
        {
          if (bT == 0x1A)
          {
            InputMode0();
            mpSerial[0] = SER_CTRL_Z;
          }

          else if ((bT == 0x1B) && ((mpSerial[0] == SER_BEGIN) || (mpSerial[0] == SER_PAUSE)))
            mpSerial[0] = SER_ESC;

          else if ((bT != 0x1B) && (mpSerial[0] == SER_ESC))
          {
            InputMode0();
            mpSerial[0] = SER_CHAR;

            mpbInBuff0[0] = bT;
          }
        }
      }
    }

    if (GetTI0(ui32Status))
    {
      if (mpSerial[0] == SER_OUTPUT_SLAVE)
      {
        bT = mpbOutBuff0[ iwOutBuff0++ ];

        if (iwOutBuff0 <= cwOutBuff0)           // продолжаем передачу ?
        {
          OutByte0(bT);
          OutByteBulk0();
        }
        else
        {
          InputMode0();
          mpSerial[0] = SER_BEGIN;              // передача завершена
        }
      }

      else if (mpSerial[0] == SER_HEADER)
      {
        bT = mpbOutBuff0[ iwOutBuff0++ ];

        if (iwOutBuff0 < bHEADER)
        {
          OutByte0(bT);
          OutByteBulk0();
        }
        else
        {
          mpSerial[0] = SER_POINTER;
          OutByte0(bT);
          OutByteBulk0();
        }
      }
      else if (mpSerial[0] == SER_POINTER)
      {
        bT = bCRCHi0 ^ *pbData0;

        bCRCHi0 = bCRCLo0 ^ mpbCRCHi[bT];
        bCRCLo0 = mpbCRCLo[bT];

        bT = *(pbData0++);

        if (++iwOutBuff0 < cwOutBuff0)
        {
          OutByte0(bT);
          OutByteBulk0();
        }
        else
        {
          mpSerial[0] = SER_CRCHI;
          OutByte0(bT);
          OutByteBulk0();
        }
      }
      else if (mpSerial[0] == SER_CRCHI)
      {
        OutByte0(bCRCHi0);
        mpSerial[0] = SER_CRCLO;
        OutByteBulk0();
      }
      else if (mpSerial[0] == SER_CRCLO)
      {
        OutByte0(bCRCLo0);
        mpSerial[0] = SER_CLOSE;
        OutByteBulk0();
      }
      else if (mpSerial[0] == SER_CLOSE)
      {
        InputMode0();
        mpSerial[0] = SER_BEGIN;                // передача завершена
      }
    }
  }
}

void    InDelay0_Timer0(void) {
  if (mpSerial[0] == SER_INPUT_SLAVE)
  {
    if (cwInDelay0 == 0)
      mpSerial[0] = SER_POSTINPUT_SLAVE;        // приём закончен: по таймауту
    else
      cwInDelay0--;
  }
  else
  if (mpSerial[0] == SER_INPUT_SLAVE_UNI)
  {
    if (cwInDelay0 == 0)
      mpSerial[0] = SER_POSTINPUT_SLAVE_UNI;       // приём закончен: по таймауту
    else
      cwInDelay0--;
  }
  else
  if (mpSerial[0] == SER_INPUT_MASTER)
  {
    if (cwInDelay0 == 0)
      mpSerial[0] = SER_BADLINK;                // приём закончен: нет данных
    else
      cwInDelay0--;
  }
  else
  if (mpSerial[0] == SER_BULK)
  {
    RunBulk0();
  }
}



void    InitSerial0(void)
{
  ResetSendAT(0);

  mpboLocal[0] = false;

  InputMode0();
  DTROff0();

  mpSerial[0] = SER_BEGIN;
}



void    Query0(uint  cwIn, uchar  cbOut, bool  fMinInDelay)
{
  iwInBuff0  = 0;
  iwOutBuff0 = 0;

  cwInBuff0  = cwIn;
  cwOutBuff0 = cbOut;

  if (fMinInDelay == true)
    mpwInDelay[0] = mpwMinorInDelay[0];
  else
    mpwInDelay[0] = mpwMajorInDelay[0];

  OutputMode0();
  mpSerial[0] = SER_OUTPUT_MASTER;

  IntPendSet(INT_UART0);
}



void    Answer0(uint  wSize, serial  seT)
{
  iwOutBuff0 = 0;
  cwOutBuff0 = wSize;

  OutputMode0();
  mpSerial[0] = seT;
  AnswerBulk0();

  IntPendSet(INT_UART0);
}
