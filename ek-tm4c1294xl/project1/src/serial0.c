
#include 		"main.h"
#include 		"mem_ports.h"
#include 		"mem_serial0.h"
#include 		"flow.h"
#include 		"ports.h"
#include 		"bulk.h"
#include 		"crc-16.h"


static const uchar          szPacketA[bPACKET_HEADER] = "12345678";
static const uchar          szPacketB[1] = "\x1A";


uchar RI,TI,SBUF0,ES0,fSendAT;

void    DTROff0(void) {
}

void    InputMode0(void) {
}

void    OutputMode0(void) {
}



void    OutByte0(uchar  bT) {

}

void    Serial0(void) {
uchar   bT;


  // ведущий режим
  if (((mppoPorts[0].enStream == STR_MASTERDIRECT) ||
       (mppoPorts[0].enStream == STR_MASTERMODEM)) &&
      (mpboLocal[0] == boFalse))
  {
    if (RI == 1)
    {
      RI = 0;
      bT = SBUF0;

      if (mpSerial[0] == SER_BEGIN)
      {
        if (bT == szPacketB[ibPacket0])
        {
          if (++ibPacket0 >= sizeof(szPacketB))
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

    if (TI == 1)
    {
      TI = 0;

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

            mpboLocal[0] = boTrue;
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
    if (RI == 1)
    {
      RI = 0;
      bT = SBUF0;

      if ((fSendAT == 1) && (IsFlow0() == 0))
      {
        mpcbSendAT[0] = bANSWER_AT;
        mpanSendAT[0] = ANS_TIMEOUT;
      }

      cwIn0++;
      bIn0 = bT;

      if ((mppoPorts[0].enStream == STR_SLAVECRC) || (IsFlow0() == 1))
      {
        if (mppoPorts[0].enStream != STR_SLAVEUNI)
          RepeatFlow();

        if (mpSerial[0] == SER_BEGIN)           // приём первого байта в запросе
        {
          cwInDelay0 = mpwMinInDelay[0];

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
            cwInDelay0 = mpwMinInDelay[0];      // продолжаем приём
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
          cwInDelay0 = mpwMinInDelay[0];

          mpSerial[0] = SER_INPUT_SLAVE2;
          iwInBuff0 = 0;
        }

        if (mpSerial[0] == SER_INPUT_SLAVE2)
        {
          if (iwInBuff0 >= wINBUFF_SIZE)        // переполнение входного буфера ?
          {
            InputMode0();
            mpSerial[0] = SER_BEGIN;            // начинаем приём сначала
          }
          else
          {
            cwInDelay0 = mpwMinInDelay[0];      // продолжаем приём
            mpbInBuff0[ iwInBuff0++ ] = bT;
          }

          if (IsFlow0() == 0)                   // приём закончен: по количеству байт
          {
            if ((iwInBuff0 >= 10) && (iwInBuff0 == mpbInBuff0[3] + mpbInBuff0[2]*0x100))
            {
              InputMode0();
              mpSerial[0] = SER_POSTINPUT_SLAVE2;   // приём закончен: по количеству байт
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
            mpSerial[0] = SER_PACKET_HEADER;
            iwInBuff0 = 0;
          }
        }
        else if (bT != szPacketA[0]) ibPacket0 = 0;

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
            mpSerial[0] = SER_CTRL_Z;

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

    if (TI == 1)
    {
      TI = 0;

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

void    InDelay0(void) {
  if (mpSerial[0] == SER_INPUT_SLAVE)
  {
    if (cwInDelay0 == 0)
      mpSerial[0] = SER_POSTINPUT_SLAVE;        // приём закончен: по таймауту
    else
      cwInDelay0--;
  }
  else
  if (mpSerial[0] == SER_INPUT_SLAVE2)
  {
    if (cwInDelay0 == 0)
      mpSerial[0] = SER_POSTINPUT_SLAVE2;       // приём закончен: по таймауту
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

void    InitSerial0(void) {
  mpcbSendAT[0] = bANSWER_AT;
  mpanSendAT[0] = ANS_TIMEOUT;

  mpboLocal[0] = boFalse;

  InputMode0();
  DTROff0();

  mpSerial[0] = SER_BEGIN;
  ES0 = 1;
}
