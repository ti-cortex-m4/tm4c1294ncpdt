/*------------------------------------------------------------------------------
BULK.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "bulk.h"



#ifdef  BULK
bit     BulkEnabled(void)
{
  return (boEnableBulk == true) && (bMaxBulk > 0);
}
#endif



void    AnswerBulk0(void)
{
#ifdef  BULK
  cbBulk[0] = 0;
#endif
}


void    AnswerBulk1(void)
{
#ifdef  BULK
  cbBulk[1] = 0;
#endif
}


void    AnswerBulk2(void)
{
#ifdef  BULK
  cbBulk[2] = 0;
#endif
}


void    AnswerBulk3(void)
{
#ifdef  BULK
  cbBulk[3] = 0;
#endif
}



void    OutByteBulk0(void)
{
#ifdef  BULK
  if (BulkEnabled() && (++cbBulk[0] >= bMaxBulk))
  {
    cbBulk[0] = 0;
    cwBulkDelay[0] = wMaxBulkDelay;

    mpSerial_Bulk[0] = mpSerial[0];
    mpSerial[0] = SER_BULK; 
  }
#endif
}


void    OutByteBulk1(void)
{
#ifdef  BULK
  if (BulkEnabled() && (++cbBulk[1] >= bMaxBulk))
  {
    cbBulk[1] = 0;
    cwBulkDelay[1] = wMaxBulkDelay;

    mpSerial_Bulk[1] = mpSerial[1];
    mpSerial[1] = SER_BULK; 
  }
#endif
}


void    OutByteBulk2(void)
{
#ifdef  BULK
  if (BulkEnabled() && (++cbBulk[2] >= bMaxBulk))
  {
    cbBulk[2] = 0;
    cwBulkDelay[2] = wMaxBulkDelay;

    mpSerial_Bulk[2] = mpSerial[2];
    mpSerial[2] = SER_BULK; 
  }
#endif
}


void    OutByteBulk3(void)
{
#ifdef  BULK
  if (BulkEnabled() && (++cbBulk[3] >= bMaxBulk))
  {
    cbBulk[3] = 0;
    cwBulkDelay[3] = wMaxBulkDelay;

    mpSerial_Bulk[3] = mpSerial[3];
    mpSerial[3] = SER_BULK;
  }
#endif
}



void    RunBulk0(void)
{
#ifdef  BULK
  if (BulkEnabled())
  {
    if (cwBulkDelay[0] == 0)
    {
      mpSerial[0] = mpSerial_Bulk[0];
      TI = 1;  
    }
    else cwBulkDelay[0]--;
  }
#endif
}


void    RunBulk1(void)
{
#ifdef  BULK
  if (BulkEnabled())
  {
    if (cwBulkDelay[1] == 0)
    {
      mpSerial[1] = mpSerial_Bulk[1];
      EXIF |= 0x10;
    }
    else cwBulkDelay[1]--;
  }
#endif
}


void    RunBulk2(void)
{
#ifdef  BULK
  if (BulkEnabled())
  {
    if (cwBulkDelay[2] == 0)
    {
      mpSerial[2] = mpSerial_Bulk[2];
      TI1 = 1;
    }
    else cwBulkDelay[2]--;
  }
#endif
}


void    RunBulk3(void)
{
#ifdef  BULK
  if (BulkEnabled())
  {
    if (cwBulkDelay[3] == 0)
    {
      mpSerial[3] = mpSerial_Bulk[3];
      EXIF |= 0x40;
    }
    else cwBulkDelay[3]--;
  }
#endif
}



void    ResetBulk(void)
{
//  bMaxBulk = 100;
//  wMaxBulkDelay = wFREQUENCY_T0;
}
