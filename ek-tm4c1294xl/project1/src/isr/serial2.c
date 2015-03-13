/*------------------------------------------------------------------------------
SERIAL2.C

// TODO volatile
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "inc/hw_memmap.h"
#include        "inc/hw_uart.h"
#include        "inc/hw_types.h"
#include        "inc/hw_ints.h"
#include        "driverlib/interrupt.h"
#include        "driverlib/uart.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_serial2.h"
#include        "../serial/flow.h"
#include        "../serial/ports.h"
#include        "../serial/bulk.h"
#include        "../crc-16.h"
#include        "../uarts.h"



static const uchar 		szPacketA[bPACKET_HEADER] = {0xCA, 0xE0, 0xEB, 0xFE, 0xEC, 0xED, 0xFB, 0x20};

//static const uchar 		szPacketB[1] = { 0x1A };



void    DTROff2(void) {
}


void    InputMode2(void) {
}


void    OutputMode2(void) {
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

/*
  // ведущий режим
  if (((mppoPorts[2].enStream == STR_MASTERDIRECT) ||
       (mppoPorts[2].enStream == STR_MASTERMODEM)) &&
      (mpboLocal[2] == false))
  {
    if (GetRI2())
    {
      bT = InByte2();

      if (mpSerial[2] == SER_BEGIN)
      {
        if (bT == szPacketB[ibPacket2])
        {
          if (++ibPacket2 >= sizeof(szPacketB))
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
        if (iwInBuff2 >= wINBUFF_SIZE)          // переполнение входного буфера ?
        {
          InputMode2();
          mpSerial[2] = SER_OVERFLOW;
        }
        else
        {
          if (mpSerial[2] == SER_ANSWER_MODEM)
          {
            mpbInBuff2[ iwInBuff2++ ] = bT;

            if ((bT == '\r') || (bT == '\n'))   // приём завершён
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

            if (++iwInBuff2 == cwInBuff2)       // приём завершён
            {
              InputMode2();
              mpSerial[2] = SER_POSTINPUT_MASTER;
            }
          }
        }
      }
    }

    if (GetTI2())
    {
      if (mpSerial[2] == SER_OUTPUT_MASTER)
      {
        bT = mpbOutBuff2[ iwOutBuff2 ];

        if (++iwOutBuff2 <= cwOutBuff2)         // продолжаем передачу ?
          OutByte2(bT);
        else                                    // передача завершена
        {
          if (cwInBuff2 == 0)
          {
            InputMode2();
            mpSerial[2] = SER_BEGIN;            // передача без ответа
          }
          else
          if (cwInBuff2 == SERIAL_LOCAL)
          {
            InputMode2();                       // передача с ответом
            mpSerial[2] = SER_BEGIN;            // начинаем приём

            mpboLocal[2] = true;
          }
          else
          if (cwInBuff2 == SERIAL_MODEM)
          {
            InputMode2();                       // передача с ответом
            mpSerial[2] = SER_ANSWER_MODEM;     // начинаем приём
          }
          else
          {
            InputMode2();                       // передача с ответом
            cwInDelay2 = mpwInDelay[2];

            mpSerial[2] = SER_INPUT_MASTER;     // начинаем приём
          }
        }
      }
    }
  }
*/

  // ведомый режим
  {
    if (GetRI2(ui32Status))
    {
      bT = InByte2();

      cwIn2++;
      bIn2 = bT;

      if ((mppoPorts[2].enStream == STR_SLAVECRC) || (IsFlow2() == 1))
      {
        if (mppoPorts[2].enStream != STR_SLAVEUNI)
          RepeatFlow();

        if (mpSerial[2] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay2 = mpwMinorInDelay[2];

          mpSerial[2] = SER_INPUT_SLAVE;
          iwInBuff2 = 0;
        }

        if (mpSerial[2] == SER_INPUT_SLAVE)
        {
          if (iwInBuff2 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode2();
            mpSerial[2] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay2 = mpwMinorInDelay[2];      // продолжаем приём
            mpbInBuff2[ iwInBuff2++ ] = bT;
          }

#ifndef MODBUS
          if (IsFlow2() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff2 >= 4) && (iwInBuff2 == mpbInBuff2[2] + mpbInBuff2[3]*0x100))
            {
              InputMode2();
              mpSerial[2] = SER_POSTINPUT_SLAVE;    // приём закончен: по количеству байт
            }
          }
#endif

        }
      }
      else if (mppoPorts[2].enStream == STR_SLAVEUNI)
      {
        if (mpSerial[2] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay2 = mpwMinorInDelay[2];

          mpSerial[2] = SER_INPUT_SLAVE2;
          iwInBuff2 = 0;
        }

        if (mpSerial[2] == SER_INPUT_SLAVE2)
        {
          if (iwInBuff2 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode2();
            mpSerial[2] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay2 = mpwMinorInDelay[2];      // продолжаем приём
            mpbInBuff2[ iwInBuff2++ ] = bT;
          }

          if (IsFlow2() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff2 >= 10) && (iwInBuff2 == mpbInBuff2[3] + mpbInBuff2[2]*0x100))
            {
              InputMode2();
              mpSerial[2] = SER_POSTINPUT_SLAVE2;   // приём закончен: по количеству байт
            }
          }
        }
      }
      else
      {
        if (bT == szPacketA[ibPacket2])
        {
          if (++ibPacket2 >= bPACKET_HEADER)
          {
            ibPacket2 = 0;
            mpSerial[2] = SER_PACKET_HEADER;
            iwInBuff2 = 0;
          }
        }
        else if (bT != szPacketA[0]) ibPacket2 = 0;

        if (mpSerial[2] == SER_PACKET_BODY)
        {
          if (iwInBuff2 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode2();
            mpSerial[2] = SER_BEGIN;            // начинаем приём сначала
          }
          else
            mpbInBuff2[ iwInBuff2++ ] = bT;     // продолжаем приём

          if ((iwInBuff2 >= 7) && (iwInBuff2 == mpbInBuff2[2] + mpbInBuff2[3]*0x100))
          {
            InputMode2();
            mpSerial[2] = SER_POSTINPUT_SLAVE;  // приём закончен: по количеству байт
          }
        }
        else if (mpSerial[2] == SER_PACKET_HEADER)
          mpSerial[2] = SER_PACKET_BODY;
        else
        {
          if (bT == 0x1A)
            mpSerial[2] = SER_CTRL_Z;

          else if ((bT == 0x1B) && ((mpSerial[2] == SER_BEGIN) || (mpSerial[2] == SER_PAUSE)))
            mpSerial[2] = SER_ESC;

          else if ((bT != 0x1B) && (mpSerial[2] == SER_ESC))
          {
            InputMode2();
            mpSerial[2] = SER_CHAR;

            mpbInBuff2[2] = bT;
          }
        }
      }
    }

    if (GetTI2(ui32Status))
    {
      if (mpSerial[2] == SER_OUTPUT_SLAVE)
      {
        bT = mpbOutBuff2[ iwOutBuff2++ ];

        if (iwOutBuff2 <= cwOutBuff2)           // продолжаем передачу ?
        {
          OutByte2(bT);
          OutByteBulk2();
        }
        else
        {
          InputMode2();
          mpSerial[2] = SER_BEGIN;              // передача завершена
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
        mpSerial[2] = SER_BEGIN;                // передача завершена
      }
    }
  }
}

void    InDelay2_Timer0(void) {
  if (mpSerial[2] == SER_INPUT_SLAVE)
  {
    if (cwInDelay2 == 0)
      mpSerial[2] = SER_POSTINPUT_SLAVE;        // приём закончен: по таймауту
    else
      cwInDelay2--;
  }
  else
  if (mpSerial[2] == SER_INPUT_SLAVE2)
  {
    if (cwInDelay2 == 0)
      mpSerial[2] = SER_POSTINPUT_SLAVE2;       // приём закончен: по таймауту
    else
      cwInDelay2--;
  }
  else
  if (mpSerial[2] == SER_INPUT_MASTER)
  {
    if (cwInDelay2 == 0)
      mpSerial[2] = SER_BADLINK;                // приём закончен: нет данных
    else
      cwInDelay2--;
  }
  else
  if (mpSerial[2] == SER_BULK)
  {
    RunBulk2();
  }
}



void    InitSerial2(void) {
  mpboLocal[2] = FALSE;

  InputMode2();
  DTROff2();

  mpwMajorInDelay[2] = 10;
  mppoPorts[2].enStream = STR_SLAVEESC;

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
  mpSerial[2] = SER_OUTPUT_MASTER;

  IntPendSet(INT_UART3);
}



void    Answer2(uint  wSize, serial  seT)
{
  iwOutBuff2 = 0;
  cwOutBuff2 = wSize;

  OutputMode2();
  mpSerial[2] = seT;
  AnswerBulk2();

  IntPendSet(INT_UART3);
}
