/*------------------------------------------------------------------------------
BULK!C

 ('Отчет №81 от 10.03.2012')
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "bulk.h"



cache const             chBulkEnbl = {BULK_ENBL, &fBulkEnbl, sizeof(bool)};
cache const             chBulkSize = {BULK_SIZE, &bBulkSize, sizeof(uchar)};
cache const             chBulkMaxDelay = {BULK_MAX_DELAY, &wBulkMaxDelay, sizeof(uint)};



void    InitBulk(void)
{
  LoadCacheBool(&chBulkEnbl, false);
  LoadCacheChar(&chBulkSize, 1, 250, 100);
  LoadCacheInt(&chBulkMaxDelay, 1, wFREQUENCY_T0, wFREQUENCY_T0);
}


void    ResetBulk(void)
{
  fBulkEnbl = false;
  SaveCache(&chBulkEnbl);

  bBulkSize = 100;
  SaveCache(&chBulkSize);

  wBulkMaxDelay = wFREQUENCY_T0;
  SaveCache(&chBulkMaxDelay);
}



#ifdef ENABLE_BULK
bool    BulkEnabled(void)
{
  return (fBulkEnbl == true) && (bBulkSize > 0);
}
#endif



void    AnswerBulk0(void)
{
#ifdef ENABLE_BULK
  cbBulk[0] = 0;
#endif
}


void    AnswerBulk1(void)
{
#ifdef ENABLE_BULK
  cbBulk[1] = 0;
#endif
}


void    AnswerBulk2(void)
{
#ifdef ENABLE_BULK
  cbBulk[2] = 0;
#endif
}


void    AnswerBulk3(void)
{
#ifdef ENABLE_BULK
  cbBulk[3] = 0;
#endif
}



void    OutByteBulk0(void)
{
#ifdef ENABLE_BULK
  if (BulkEnabled() && (++cbBulk[0] >= bBulkSize))
  {
    cbBulk[0] = 0;
    cwBulkDelay[0] = wBulkMaxDelay;

    mpSerial_Bulk[0] = mpSerial[0];
    mpSerial[0] = SER_BULK;
  }
#endif
}


void    OutByteBulk1(void)
{
#ifdef ENABLE_BULK
  if (BulkEnabled() && (++cbBulk[1] >= bBulkSize))
  {
    cbBulk[1] = 0;
    cwBulkDelay[1] = wBulkMaxDelay;

    mpSerial_Bulk[1] = mpSerial[1];
    mpSerial[1] = SER_BULK;
  }
#endif
}


void    OutByteBulk2(void)
{
#ifdef ENABLE_BULK
  if (BulkEnabled() && (++cbBulk[2] >= bBulkSize))
  {
    cbBulk[2] = 0;
    cwBulkDelay[2] = wBulkMaxDelay;

    mpSerial_Bulk[2] = mpSerial[2];
    mpSerial[2] = SER_BULK;
  }
#endif
}


void    OutByteBulk3(void)
{
#ifdef ENABLE_BULK
  if (BulkEnabled() && (++cbBulk[3] >= bBulkSize))
  {
    cbBulk[3] = 0;
    cwBulkDelay[3] = wBulkMaxDelay;

    mpSerial_Bulk[3] = mpSerial[3];
    mpSerial[3] = SER_BULK;
  }
#endif
}



void    RunBulk0(void)
{
#ifdef ENABLE_BULK
  if (BulkEnabled())
  {
    if (cwBulkDelay[0] == 0)
    {
      mpSerial[0] = mpSerial_Bulk[0];
      IntPendSet(INT_UART0);
    }
    else cwBulkDelay[0]--;
  }
#endif
}


void    RunBulk1(void)
{
#ifdef ENABLE_BULK
  if (BulkEnabled())
  {
    if (cwBulkDelay[1] == 0)
    {
      mpSerial[1] = mpSerial_Bulk[1];
      IntPendSet(INT_UART1);
    }
    else cwBulkDelay[1]--;
  }
#endif
}


void    RunBulk2(void)
{
#ifdef ENABLE_BULK
  if (BulkEnabled())
  {
    if (cwBulkDelay[2] == 0)
    {
      mpSerial[2] = mpSerial_Bulk[2];
      IntPendSet(INT_UART2);
    }
    else cwBulkDelay[2]--;
  }
#endif
}


void    RunBulk3(void)
{
#ifdef ENABLE_BULK
  if (BulkEnabled())
  {
    if (cwBulkDelay[3] == 0)
    {
      mpSerial[3] = mpSerial_Bulk[3];
      IntPendSet(INT_UART3);
    }
    else cwBulkDelay[3]--;
  }
#endif
}



#ifdef ENABLE_BULK
void    OutBulk(void)
{
  InitPushCRC();

  PushBool(fBulkEnbl);
  PushChar(bBulkSize);
  Push(&cbBulk, sizeof(cbBulk));

  PushInt(wBulkMaxDelay);
  PushInt(cwBulkDelay[0]);
  PushInt(cwBulkDelay[1]);
  PushInt(cwBulkDelay[2]);
  PushInt(cwBulkDelay[3]);

  Push(&mpSerial, sizeof(mpSerial));
  Push(&mpSerial_Bulk, sizeof(mpSerial_Bulk));

  Output(1+1+4*1+2+4*2+4*1+4*1);
}
#endif
