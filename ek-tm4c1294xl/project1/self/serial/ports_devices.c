/*------------------------------------------------------------------------------
PORTS_DEVICES.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_profile.h"
#include "../keyboard/keyboard.h"
#include "../hardware/watchdog.h"
#include "../digitals/wait_answer.h"
#include "../digitals/wait_query.h"
#include "../devices/devices.h"
#include "../devices/decompress_k.h"
#include "../isr/serial.h"
#include "../isr/serial0.h"
#include "../isr/serial1.h"
#include "../isr/serial2.h"
#include "../isr/serial3.h"
#include "../kernel/crc-16.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "ports.h"
#include "ports_devices.h"



void    Query(uint  cwIn, uchar  cbOut, bool  fMinor)
{
//  DebugOut(cwIn, cbOut);

  // ��� �������� ���� ������������� � ������� ����� �� ���������� ��������
  mpboLocal[ibPort] = false;

  // �������� �������� �������� ��������� � ��������� (����� ������������ � ��������� ������� ����� �� ��������)
  if (cwIn != SERIAL_LOCAL) cbWaitQuery = bMAXWAITQUERY;

  switch (ibPort)
  {
    case 0:  Query0(cwIn, cbOut, fMinor);  break;
    case 1:  Query1(cwIn, cbOut, fMinor);  break;
    case 2:  Query2(cwIn, cbOut, fMinor);  break;
    case 3:  Query3(cwIn, cbOut, fMinor);  break;
    default: ASSERT(false);
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
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
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



#ifndef SKIP_C

// �������� ������� �� ���������� (�� ��������� ������)
void    RevQueryIO(uint  cwIn, uchar  cbOut)
{
  MakeCRC16OutBuff(0,cbOut-2);

  InitPush(0);
  bOutputC0 = SkipChar();
  bOutputC1 = SkipChar();
  bOutputC2 = SkipChar();

  InitPush(0);
  Skip(cbOut-2);

  PushChar(bCRCLo);
  PushChar(bCRCHi);

  Query(cwIn,cbOut,1);
}


bool    RevLinkErrors(void)
{
  if (InBuff(0) != bOutputC0) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  if ((InBuff(1) & 0x7F) != bOutputC1) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  if (InBuff(2) != bOutputC2) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  return 0;
}


serial  RevInput(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      MakeCRC16InBuff( 0, CountInBuff()-2 );

      if ((bCRCHi == InBuff( CountInBuff()-1 )) &&
          (bCRCLo == InBuff( CountInBuff()-2 ))) {

          if (RevLinkErrors() == 0)
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
          ChecksumError();
        }

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return( mpSerial[ibPort] );
}

#endif



void    PckQueryIO(uint  cwIn, uchar  cbOut)
{
  InitPush(0);
  Push((void *)szPacketCRC, bPACKET_HEADER);

  MakeCRC16OutBuff(bPACKET_HEADER,cbOut-2);

  InitPushPck();
  Skip(cbOut-2);

  PushChar(bCRCHi);
  PushChar(bCRCLo);

  Query(cwIn,bPACKET_HEADER+cbOut,1);
}



void    BccQueryIO1(uint  cwIn, uchar  cbOut, uchar  cbMaxHeader)
{
uchar	i,bT;

  cbHeaderBcc = cbMaxHeader;
  cwInBuffBcc = 0;

  InitPush(0);
  SkipChar();

  bT = 0;
  for (i=0; i<cbOut-2; i++) bT += SkipChar();
  PushChar1Bcc(bT);

  Query(cwIn,cbOut,1);
}


void    BccQueryIO2(uint  cwIn, uchar  cbOut, uchar  cbMaxHeader)
{
uchar	i,bT;

  cbHeaderBcc = cbMaxHeader;
  cwInBuffBcc = 0;

  InitPush(0);
  for (i=0; i<12; i++) SkipChar();

  bT = 0;
  for (i=0; i<cbOut-13; i++) bT += SkipChar();
  PushChar1Bcc(bT);

  Query(cwIn,cbOut,1);
}


bool    MakeBccInBuff(void)
{
uchar   bT;
uint    i;

  InitPop(1);

  bT = 0;
  for (i=0; i<CountInBuff()-2; i++) bT += PopChar0Bcc();

  return((bT & 0x7F) == PopChar0Bcc());
}


serial  BccInput(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == 1) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
      DecompressK(0);

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if ( MakeBccInBuff() )
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



#ifndef SKIP_P

void    ElsQueryIO(uint  cbIn, uchar  cbOut)
{
uchar	i,bT;

  InitPush();
  SkipChar();

  bT = 0;
  for (i=0; i<cbOut-2; i++) bT ^= SkipChar();
  PushChar(bT);

#ifdef  TRANSIT_ENABLED
  QueryT(cbIn,cbOut,1);
#else
  Query(cbIn,cbOut,1);
#endif
}


bool    MakeElsInBuff0(void)
{
uchar	i,bT;

//  DebugIn(); UnpackT(); DebugIn();

  if (IndexInBuff() < 2) return 0;

  InitPop(1);
  bT = 0;
  for (i=0; i<IndexInBuff()-2; i++) bT ^= PopChar();

  return (bT == PopChar());
}


bool    MakeElsInBuff1(void)
{
//  DebugIn(); UnpackT(); DebugIn();

  if (IndexInBuff() < 2) return 0;

  InitPop(IndexInBuff()-2);
  if (PopChar() != 0x0D) return 0;
  if (PopChar() != 0x0A) return 0;

  return 1;
}


bool    MakeElsInBuff2(void)
{
//  DebugIn(); UnpackT(); DebugIn();

  if (IndexInBuff() != 1) return 0;

  InitPop(0);
  return (PopChar() == 0x06);
}


serial  ElsInput(uchar  bMode)
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
      if (bMode == 0)
      {
        if ( MakeElsInBuff0() ) {
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
        }
      }
      else if (bMode == 1)
      {
        if ( MakeElsInBuff1() ) {
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
        }
      }
      else
      {
        if ( MakeElsInBuff2() ) {
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
        }
      }

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return( mpSerial[ibPort] );
}


serial  ElsInputRD(void)
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
      MakeCRCElsInBuff(0, CountInBuff());

      if (wCRC == 0) {
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else {
        mpSerial[ibPort] = SER_BADCHECK;
      }

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return( mpSerial[ibPort] );
}

#endif



void    ChecksumError(void)
{
  mpcwOutputC[ibDig]++;
}


void    TestResult(uchar  bT)
{
  if (bT != 0)
  {
    Clear();
    sprintf(szLo+1,"��� ������: %02X ",bT);
    DelayInf();
  }
}
