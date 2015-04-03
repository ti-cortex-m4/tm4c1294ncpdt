/*------------------------------------------------------------------------------
SERIAL3.C

// TODO volatile
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "inc/hw_memmap.h"
#include        "inc/hw_uart.h"
#include        "inc/hw_types.h"
#include        "inc/hw_ints.h"
#include        "inc/hw_sysctl.h"
#include        "inc/hw_gpio.h"
#include        "driverlib/interrupt.h"
#include        "driverlib/uart.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_serial3.h"
#include        "../serial/flow.h"
#include        "../serial/ports.h"
#include        "../serial/bulk.h"
#include        "../time/delay.h"
#include        "../kernel/crc-16.h"
#include        "../uarts.h"



static const uchar 		szPacketA[bPACKET_HEADER] = {0xCA, 0xE0, 0xEB, 0xFE, 0xEC, 0xED, 0xFB, 0x20};

static const uchar 		szPacketB[1] = { 0x1A };



void    DTROff3(void) {
}


void    InputMode3(void) {
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0100) = ~0x0040;
  bPortsStatus &= 0xFD;
}


void    OutputMode3(void) {
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0100) = 0x0040;
  bPortsStatus |= 0x02;
}



bool    GetRI3(uint32_t ui32Status) {
  return ((ui32Status & 0x00000010) != 0) || ((ui32Status & 0x00000040) != 0);
}


bool    GetTI3(uint32_t ui32Status) {
  return ((ui32Status & 0x00000020) != 0) || (ui32Status == 0);
}


uchar	InByte3(void) {
  return HWREG(UART4_BASE + UART_O_DR);
}


void    OutByte3(uchar  bT) {
	HWREG(UART4_BASE + UART_O_DR) = bT;
}



void    UART4IntHandler(void) {
uchar   bT;
uint32_t ui32Status;

  ui32Status = UARTIntStatus(UART4_BASE, true);
  UARTIntClear(UART4_BASE, ui32Status);


  // ведущий режим
  if (((mppoPorts[3].enStream == STR_MASTERDIRECT) ||
       (mppoPorts[3].enStream == STR_MASTERMODEM)) &&
      (mpboLocal[3] == false))
  {
    if (GetRI3(ui32Status))
    {
      bT = InByte3();

      if (mpSerial[3] == SER_BEGIN)
      {
        if (bT == szPacketB[ibPacket3])
        {
          if (++ibPacket3 >= sizeof(szPacketB))
          {
            ibPacket3 = 0;
            mpSerial[3] = SER_LOCAL;
          }
        }
        else ibPacket3 = 0;
      }
      else if ((mpSerial[3] == SER_OUTPUT_MASTER) ||
               (mpSerial[3] == SER_INPUT_MASTER)  ||
               (mpSerial[3] == SER_ANSWER_MODEM))
      {
        if (iwInBuff3 >= wINBUFF_SIZE)          // переполнение входного буфера ?
        {
          InputMode3();
          mpSerial[3] = SER_OVERFLOW;
        }
        else
        {
          if (mpSerial[3] == SER_ANSWER_MODEM)
          {
            mpbInBuff3[ iwInBuff3++ ] = bT;

            if ((bT == '\r') || (bT == '\n'))   // приём завершён
            {
              InputMode3();
              mpSerial[3] = SER_POSTANSWER_MODEM;
            }
          }
          else
          if (mpSerial[3] == SER_INPUT_MASTER)
          {
            mpbInBuff3[ iwInBuff3 ] = bT;
            cwInDelay3 = mpwInDelay[3];

            if (++iwInBuff3 == cwInBuff3)       // приём завершён
            {
              InputMode3();
              mpSerial[3] = SER_POSTINPUT_MASTER;
            }
          }
        }
      }
    }

    if (GetTI3(ui32Status))
    {
      if (mpSerial[3] == SER_OUTPUT_MASTER)
      {
        bT = mpbOutBuff3[ iwOutBuff3 ];

        if (++iwOutBuff3 <= cwOutBuff3)         // продолжаем передачу ?
          OutByte3(bT);
        else                                    // передача завершена
        {
          if (cwInBuff3 == 0)
          {
            InputMode3();
            mpSerial[3] = SER_BEGIN;            // передача без ответа
          }
          else
          if (cwInBuff3 == SERIAL_LOCAL)
          {
            InputMode3();                       // передача с ответом
            mpSerial[3] = SER_BEGIN;            // начинаем приём

            mpboLocal[3] = TRUE;
          }
          else
          if (cwInBuff3 == SERIAL_MODEM)
          {
            InputMode3();                       // передача с ответом
            mpSerial[3] = SER_ANSWER_MODEM;     // начинаем приём
          }
          else
          {
            InputMode3();                       // передача с ответом
            cwInDelay3 = mpwInDelay[3];

            mpSerial[3] = SER_INPUT_MASTER;     // начинаем приём
          }
        }
      }
    }
  }


  // ведомый режим
  else
  {
    if (GetRI3(ui32Status))
    {
      bT = InByte3();

      cwIn3++;
      bIn3 = bT;

      if ((mppoPorts[3].enStream == STR_SLAVECRC) || (IsFlow3() == 1))
      {
//        if (mppoPorts[3].enStream != STR_SLAVEUNI)
//          RepeatFlow();

        if (mpSerial[3] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay3 = mpwMinorInDelay[3];

          mpSerial[3] = SER_INPUT_SLAVE;
          iwInBuff3 = 0;
        }

        if (mpSerial[3] == SER_INPUT_SLAVE)
        {
          if (iwInBuff3 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode3();
            mpSerial[3] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay3 = mpwMinorInDelay[3];      // продолжаем приём
            mpbInBuff3[ iwInBuff3++ ] = bT;
          }

#ifndef MODBUS
          if (IsFlow3() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff3 >= 4) && (iwInBuff3 == mpbInBuff3[2] + mpbInBuff3[3]*0x100))
            {
              InputMode3();
              mpSerial[3] = SER_POSTINPUT_SLAVE;    // приём закончен: по количеству байт
            }
          }
#endif

        }
      }
      else if (mppoPorts[3].enStream == STR_SLAVEUNI)
      {
        if (mpSerial[3] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay3 = mpwMinorInDelay[3];

          mpSerial[3] = SER_INPUT_SLAVE_UNI;
          iwInBuff3 = 0;
        }

        if (mpSerial[3] == SER_INPUT_SLAVE_UNI)
        {
          if (iwInBuff3 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode3();
            mpSerial[3] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay3 = mpwMinorInDelay[3];      // продолжаем приём
            mpbInBuff3[ iwInBuff3++ ] = bT;
          }

          if (IsFlow3() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff3 >= 10) && (iwInBuff3 == mpbInBuff3[3] + mpbInBuff3[2]*0x100))
            {
              InputMode3();
              mpSerial[3] = SER_POSTINPUT_SLAVE_UNI;   // приём закончен: по количеству байт
            }
          }
        }
      }
      else
      {
        if (bT == szPacketA[ibPacket3])
        {
          if (++ibPacket3 >= bPACKET_HEADER)
          {
            ibPacket3 = 0;
            mpSerial[3] = SER_PACKET_HEADER;
            iwInBuff3 = 0;
          }
        }
        else if (bT != szPacketA[0]) ibPacket3 = 0;

        if (mpSerial[3] == SER_PACKET_BODY)
        {
          if (iwInBuff3 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode3();
            mpSerial[3] = SER_BEGIN;            // начинаем приём сначала
          }
          else
            mpbInBuff3[ iwInBuff3++ ] = bT;     // продолжаем приём

          if ((iwInBuff3 >= 7) && (iwInBuff3 == mpbInBuff3[2] + mpbInBuff3[3]*0x100))
          {
            InputMode3();
            mpSerial[3] = SER_POSTINPUT_SLAVE;  // приём закончен: по количеству байт
          }
        }
        else if (mpSerial[3] == SER_PACKET_HEADER)
          mpSerial[3] = SER_PACKET_BODY;
        else
        {
          if (bT == 0x1A)
            mpSerial[3] = SER_CTRL_Z;

          else if ((bT == 0x1B) && ((mpSerial[3] == SER_BEGIN) || (mpSerial[3] == SER_PAUSE)))
            mpSerial[3] = SER_ESC;

          else if ((bT != 0x1B) && (mpSerial[3] == SER_ESC))
          {
            InputMode3();
            mpSerial[3] = SER_CHAR;

            mpbInBuff3[3] = bT;
          }
        }
      }
    }

    if (GetTI3(ui32Status))
    {
      if (mpSerial[3] == SER_OUTPUT_SLAVE)
      {
        bT = mpbOutBuff3[ iwOutBuff3++ ];

        if (iwOutBuff3 <= cwOutBuff3)           // продолжаем передачу ?
        {
          OutByte3(bT);
          OutByteBulk3();
        }
        else
        {
          InputMode3();
          mpSerial[3] = SER_BEGIN;              // передача завершена
        }
      }

      else if (mpSerial[3] == SER_HEADER)
      {
        bT = mpbOutBuff3[ iwOutBuff3++ ];

        if (iwOutBuff3 < bHEADER)
        {
          OutByte3(bT);
          OutByteBulk3();
        }
        else
        {
          mpSerial[3] = SER_POINTER;
          OutByte3(bT);
          OutByteBulk3();
        }
      }
      else if (mpSerial[3] == SER_POINTER)
      {
        bT = bCRCHi3 ^ *pbData3;

        bCRCHi3 = bCRCLo3 ^ mpbCRCHi[bT];
        bCRCLo3 = mpbCRCLo[bT];

        bT = *(pbData3++);

        if (++iwOutBuff3 < cwOutBuff3)
        {
          OutByte3(bT);
          OutByteBulk3();
        }
        else
        {
          mpSerial[3] = SER_CRCHI;
          OutByte3(bT);
          OutByteBulk3();
        }
      }
      else if (mpSerial[3] == SER_CRCHI)
      {
        OutByte3(bCRCHi3);
        mpSerial[3] = SER_CRCLO;
        OutByteBulk3();
      }
      else if (mpSerial[3] == SER_CRCLO)
      {
        OutByte3(bCRCLo3);
        mpSerial[3] = SER_CLOSE;
        OutByteBulk3();
      }
      else if (mpSerial[3] == SER_CLOSE)
      {
        InputMode3();
        mpSerial[3] = SER_BEGIN;                // передача завершена
      }
    }
  }
}

void    InDelay3_Timer0(void) {
  if (mpSerial[3] == SER_INPUT_SLAVE)
  {
    if (cwInDelay3 == 0)
      mpSerial[3] = SER_POSTINPUT_SLAVE;        // приём закончен: по таймауту
    else
      cwInDelay3--;
  }
  else
  if (mpSerial[3] == SER_INPUT_SLAVE_UNI)
  {
    if (cwInDelay3 == 0)
      mpSerial[3] = SER_POSTINPUT_SLAVE_UNI;       // приём закончен: по таймауту
    else
      cwInDelay3--;
  }
  else
  if (mpSerial[3] == SER_INPUT_MASTER)
  {
    if (cwInDelay3 == 0)
      mpSerial[3] = SER_BADLINK;                // приём закончен: нет данных
    else
      cwInDelay3--;
  }
  else
  if (mpSerial[3] == SER_BULK)
  {
    RunBulk3();
  }
}



void    InitSerial3(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R3; // GPIO Port D Run Mode Clock Gating Control
  RunClocking();
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x0040; // GPIO Direction
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x0040; // GPIO Digital Enable

  mpboLocal[3] = FALSE;

  InputMode3();
  DTROff3();

  mpSerial[3] = SER_BEGIN;
}



void    Query3(uint  cwIn, uchar  cbOut, bool  fMinInDelay)
{
  iwInBuff3  = 0;
  iwOutBuff3 = 0;

  cwInBuff3  = cwIn;
  cwOutBuff3 = cbOut;

  if (fMinInDelay == true)
    mpwInDelay[3] = mpwMinorInDelay[3];
  else
    mpwInDelay[3] = mpwMajorInDelay[3];

  OutputMode3();
  mpSerial[3] = SER_OUTPUT_MASTER;

  IntPendSet(INT_UART4);
}



void    Answer3(uint  wSize, serial  seT)
{
  iwOutBuff3 = 0;
  cwOutBuff3 = wSize;

  OutputMode3();
  mpSerial[3] = seT;
  AnswerBulk3();

  IntPendSet(INT_UART4);
}
