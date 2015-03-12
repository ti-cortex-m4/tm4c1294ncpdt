/*------------------------------------------------------------------------------
SERIAL1.C


------------------------------------------------------------------------------*/

#include 		"main.h"
#include        "inc/hw_memmap.h"
#include        "inc/hw_uart.h"
#include        "inc/hw_types.h"
#include        "inc/hw_ints.h"
#include        "driverlib/interrupt.h"
#include        "driverlib/uart.h"
#include 		"memory/mem_ports.h"
#include 		"memory/mem_serial1.h"
#include 		"serial/flow.h"
#include 		"serial/ports.h"
#include 		"serial/bulk.h"
#include 		"crc-16.h"
#include 		"uarts.h"



static const uchar 		szPacketA[bPACKET_HEADER] = {0xCA, 0xE0, 0xEB, 0xFE, 0xEC, 0xED, 0xFB, 0x20};

//static const uchar 		szPacketB[1] = { 0x1A };



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

/*
  // ведущий режим
  if (((mppoPorts[1].enStream == STR_MASTERDIRECT) ||
       (mppoPorts[1].enStream == STR_MASTERMODEM)) &&
      (mpboLocal[1] == false))
  {
    if (GetRI1())
    {
      bT = InByte1();

      if (mpSerial[1] == SER_BEGIN)
      {
        if (bT == szPacketB[ibPacket0])
        {
          if (++ibPacket0 >= sizeof(szPacketB))
          {
            ibPacket0 = 0;
            mpSerial[1] = SER_LOCAL;
          }
        }
        else ibPacket0 = 0;
      }
      else if ((mpSerial[1] == SER_OUTPUT_MASTER) ||
               (mpSerial[1] == SER_INPUT_MASTER)  ||
               (mpSerial[1] == SER_ANSWER_MODEM))
      {
        if (iwInBuff0 >= wINBUFF_SIZE)          // переполнение входного буфера ?
        {
          InputMode1();
          mpSerial[1] = SER_OVERFLOW;
        }
        else
        {
          if (mpSerial[1] == SER_ANSWER_MODEM)
          {
            mpbInBuff0[ iwInBuff0++ ] = bT;

            if ((bT == '\r') || (bT == '\n'))   // приём завершён
            {
              InputMode1();
              mpSerial[1] = SER_POSTANSWER_MODEM;
            }
          }
          else
          if (mpSerial[1] == SER_INPUT_MASTER)
          {
            mpbInBuff0[ iwInBuff0 ] = bT;
            cwInDelay0 = mpwInDelay[1];

            if (++iwInBuff0 == cwInBuff0)       // приём завершён
            {
              InputMode1();
              mpSerial[1] = SER_POSTINPUT_MASTER;
            }
          }
        }
      }
    }

    if (GetTI1())
    {
      if (mpSerial[1] == SER_OUTPUT_MASTER)
      {
        bT = mpbOutBuff0[ iwOutBuff0 ];

        if (++iwOutBuff0 <= cwOutBuff0)         // продолжаем передачу ?
          OutByte1(bT);
        else                                    // передача завершена
        {
          if (cwInBuff0 == 0)
          {
            InputMode1();
            mpSerial[1] = SER_BEGIN;            // передача без ответа
          }
          else
          if (cwInBuff0 == SERIAL_LOCAL)
          {
            InputMode1();                       // передача с ответом
            mpSerial[1] = SER_BEGIN;            // начинаем приём

            mpboLocal[1] = true;
          }
          else
          if (cwInBuff0 == SERIAL_MODEM)
          {
            InputMode1();                       // передача с ответом
            mpSerial[1] = SER_ANSWER_MODEM;     // начинаем приём
          }
          else
          {
            InputMode1();                       // передача с ответом
            cwInDelay0 = mpwInDelay[1];

            mpSerial[1] = SER_INPUT_MASTER;     // начинаем приём
          }
        }
      }
    }
  }
*/

  // ведомый режим
  {
    if (GetRI1(ui32Status))
    {
      bT = InByte1();

      cwIn0++;
      bIn0 = bT;

      if ((mppoPorts[1].enStream == STR_SLAVECRC) || (IsFlow1() == 1))
      {
        if (mppoPorts[1].enStream != STR_SLAVEUNI)
          RepeatFlow();

        if (mpSerial[1] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay0 = mpwMinorInDelay[1];

          mpSerial[1] = SER_INPUT_SLAVE;
          iwInBuff0 = 0;
        }

        if (mpSerial[1] == SER_INPUT_SLAVE)
        {
          if (iwInBuff0 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode1();
            mpSerial[1] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay0 = mpwMinorInDelay[1];      // продолжаем приём
            mpbInBuff0[ iwInBuff0++ ] = bT;
          }

#ifndef MODBUS
          if (IsFlow1() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff0 >= 4) && (iwInBuff0 == mpbInBuff0[2] + mpbInBuff0[3]*0x100))
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
          cwInDelay0 = mpwMinorInDelay[1];

          mpSerial[1] = SER_INPUT_SLAVE2;
          iwInBuff0 = 0;
        }

        if (mpSerial[1] == SER_INPUT_SLAVE2)
        {
          if (iwInBuff0 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode1();
            mpSerial[1] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay0 = mpwMinorInDelay[1];      // продолжаем приём
            mpbInBuff0[ iwInBuff0++ ] = bT;
          }

          if (IsFlow1() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff0 >= 10) && (iwInBuff0 == mpbInBuff0[3] + mpbInBuff0[2]*0x100))
            {
              InputMode1();
              mpSerial[1] = SER_POSTINPUT_SLAVE2;   // приём закончен: по количеству байт
            }
          }
        }
      }
      else
      {
        if (bT == szPacketA[ibPacket0])
        {
          if (++ibPacket0 >= bPACKET_HEADER)
          {
            ibPacket0 = 0;
            mpSerial[1] = SER_PACKET_HEADER;
            iwInBuff0 = 0;
          }
        }
        else if (bT != szPacketA[1]) ibPacket0 = 0;

        if (mpSerial[1] == SER_PACKET_BODY)
        {
          if (iwInBuff0 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode1();
            mpSerial[1] = SER_BEGIN;            // начинаем приём сначала
          }
          else
            mpbInBuff0[ iwInBuff0++ ] = bT;     // продолжаем приём

          if ((iwInBuff0 >= 7) && (iwInBuff0 == mpbInBuff0[2] + mpbInBuff0[3]*0x100))
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

            mpbInBuff0[1] = bT;
          }
        }
      }
    }

    if (GetTI1(ui32Status))
    {
      if (mpSerial[1] == SER_OUTPUT_SLAVE)
      {
        bT = mpbOutBuff0[ iwOutBuff0++ ];

        if (iwOutBuff0 <= cwOutBuff0)           // продолжаем передачу ?
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
        bT = mpbOutBuff0[ iwOutBuff0++ ];

        if (iwOutBuff0 < bHEADER)
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
        bT = bCRCHi0 ^ *pbData0;

        bCRCHi0 = bCRCLo0 ^ mpbCRCHi[bT];
        bCRCLo0 = mpbCRCLo[bT];

        bT = *(pbData0++);

        if (++iwOutBuff0 < cwOutBuff0)
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
        OutByte1(bCRCHi0);
        mpSerial[1] = SER_CRCLO;
        OutByteBulk1();
      }
      else if (mpSerial[1] == SER_CRCLO)
      {
        OutByte1(bCRCLo0);
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

void    InDelay0_Timer0(void) {
  if (mpSerial[1] == SER_INPUT_SLAVE)
  {
    if (cwInDelay0 == 0)
      mpSerial[1] = SER_POSTINPUT_SLAVE;        // приём закончен: по таймауту
    else
      cwInDelay0--;
  }
  else
  if (mpSerial[1] == SER_INPUT_SLAVE2)
  {
    if (cwInDelay0 == 0)
      mpSerial[1] = SER_POSTINPUT_SLAVE2;       // приём закончен: по таймауту
    else
      cwInDelay0--;
  }
  else
  if (mpSerial[1] == SER_INPUT_MASTER)
  {
    if (cwInDelay0 == 0)
      mpSerial[1] = SER_BADLINK;                // приём закончен: нет данных
    else
      cwInDelay0--;
  }
  else
  if (mpSerial[1] == SER_BULK)
  {
    RunBulk1();
  }
}



void    InitSerial1(void) {
  mpboLocal[1] = FALSE;

  InputMode1();
  DTROff1();

  mpwMajorInDelay[1] = 10;
  mppoPorts[1].enStream = STR_SLAVEESC;

  mpSerial[1] = SER_BEGIN;
}



void    Query1(uint  cwIn, uchar  cbOut, bool  fMinInDelay)
{
  iwInBuff0  = 0;
  iwOutBuff0 = 0;

  cwInBuff0  = cwIn;
  cwOutBuff0 = cbOut;

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
  iwOutBuff0 = 0;
  cwOutBuff0 = wSize;

  OutputMode1();
  mpSerial[1] = seT;
  AnswerBulk1();

  IntPendSet(INT_UART2);
}
