/*------------------------------------------------------------------------------
AT45.C


------------------------------------------------------------------------------*/

#include        "main.h"
//#include        "xdata.h"
#include        "flash.h"
//#include        "flash_control.h"
//#include        "rtc.h"
//#include        "delay.h"
//#include        "crc-16.h"
//#include        "lcd.h"
//#include        "access.h"
//#include        "nexttime.h"
//#include        "shift.h"
#i//nclude        "display.h"


/*
void    EnableFlash()
{
  Delay5mcs();

#ifdef  DS80C400
  sfSCK = 0;
  P6 &= ~bMASK_CS;
#else
//  sfSCK = 0;
  bP4 &= ~bMASK_SCK;

//  sfCS  = 0;
  bP4 &= ~bMASK_CS;
#endif

  Delay5mcs();
}


void    DisableFlash(void)
{
  Delay5mcs();

#ifdef  DS80C400
  P6 |= bMASK_CS;
#else
//  sfCS  = 1;
  bP4 |= bMASK_CS;
#endif

  Delay5mcs();
}



uchar   ReadStatus(void)
{
#ifdef  UPGRADE2
uchar   i;
#endif

  EnableFlash();

#ifdef  DS80C400
  CharOut(0xD7);
#else
  CharOut(0x57);
#endif

#ifdef  UPGRADE2
  for (i=0; i<2-1; i++) CharOut(0);
#endif

  bStatusFlash = CharIn();

  DisableFlash();      
  return(bStatusFlash);
}



bit     SafeReadStatus(void)
{
uint    i;
        
  i = 0;
  while ((ReadStatus() & 0x80) == 0)    
  {
    if (++i > wMAXBUSY) 
    {
      cwWrnBusy++;
      return(0);
    }
  }       

  return(1);
}



bit     PageErase(void)
{
uint    i;

#ifdef  UPGRADE2
#ifndef MODBUS
  IncFlashControl();
#endif
#endif

  if (SafeReadStatus() == 0) 
    return(0);
  else
  {
    EnableFlash();

#ifdef  DS80C400
    CharOut(0x81);

    i = (wPageOut << 3) & 0xFFF8;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);
#else
    CharOut(0x81);

    i = (wPageOut << 1) & 0x1FFE;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);
#endif

    DisableFlash();      
    return(1);
  }
}
  

bit     SafePageErase(void)
{
uchar   i;

  for (i=0; i<bMAXREPEAT; i++)
  {
    if (PageErase() == 0) 
    {
      cwWrnPageErase++; 
      continue;
    }
    else break;
  }

  if (i == bMAXREPEAT) 
  {
    cwErrPageErase++; 
    return(0);
  }
  else return(1);
}



bit     PageRead(void)
{
uint    i;

  if (SafeReadStatus() == 0) 
    return(0);
  else
  {
    EnableFlash();

#ifdef  DS80C400
    CharOut(0xD2);

    i = (wPageIn << 3) & 0xFFF8;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

#ifdef  UPGRADE2
    for (i=0; i<19-1; i++) CharOut(0);
#else
    for (i=0; i<60-1; i++) CharOut(0);
#endif

#else
    CharOut(0x52);

    i = (wPageIn << 1) & 0x1FFE;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    for (i=0; i<4; i++) CharOut(0);
#endif

    for (i=0; i<wPAGE_SIZE; i++) mpbPageIn[i] = CharIn();

    DisableFlash();      
    return(1);
  }
}
  


bit     PageWrite(void)
{
uint    i;

#ifdef  UPGRADE2
#ifndef MODBUS
  IncFlashControl();
#endif
#endif

  if (SafeReadStatus() == 0) 
    return(0);
  else                                  // запись 
  {
    EnableFlash();

#ifdef  DS80C400
    CharOut(0x82);

    i = (wPageOut << 3) & 0xFFF8;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);
#else
    CharOut(0x82);

    i = (wPageOut << 1) & 0x1FFE;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);
#endif

    for (i=0; i<wPAGE_SIZE; i++) CharOut(mpbPageOut[i]);

    DisableFlash();      
  }

  if (SafeReadStatus() == 0) 
    return(0);
  else                                  // проверка записи
  {
    EnableFlash();

#ifdef  DS80C400
    CharOut(0x60);

    i = (wPageOut << 3) & 0xFFF8;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);
#else
    CharOut(0x60);

    i = (wPageOut << 1) & 0x1FFE;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);
#endif

    DisableFlash();      
  }

  if (SafeReadStatus() == 0) 
  {
    cwErrCompare++;
    return(0);
  }
  else
  {
    if ((bStatusFlash & 0x40) != 0)
    {
      cwWrnCompare++;
      return(0); 
    } 
    else return(1);
  }
}



bit     SafePageRead(void)
{
uchar   i;

  for (i=0; i<bMAXREPEAT; i++)
  {
    if (PageRead() == 0) 
    {
      cwWrnPageRead++; 
      continue;
    }
    else break;
  }

  if (i == bMAXREPEAT) 
  {
    cwErrPageRead++; 
    return(0);
  }
  else return(1);
}



bit     SafePageWrite(void)
{
uchar   i;

  memcpy(&mpbPageOut[wFREEPAGE_SIZE+0], &wPrivate, sizeof(uint)); 
  memcpy(&mpbPageOut[wFREEPAGE_SIZE+2], &wPageOut, sizeof(uint)); 
  memcpy(&mpbPageOut[wFREEPAGE_SIZE+4], &tiCurr,   sizeof(time));

  MakeCRC16_XDATA(&mpbPageOut, wPAGE_SIZE-2);

  mpbPageOut[wPAGE_SIZE-2] = bCRCHi;
  mpbPageOut[wPAGE_SIZE-1] = bCRCLo;

  for (i=0; i<bMAXREPEAT; i++)
  {
    if (PageWrite() == 0) 
    {
      cwWrnPageWrite++; 
      continue;
    }
    else break;
  }
  
  if (i == bMAXREPEAT)
  {
    cwErrPageWrite++; 
    return(0);
  }
  else return(1);
}



void    InitFlash(void)
{                                       
#ifdef  DS80C400
  TA = 0xAA; TA = 0x55; P5CNT &= 0xF0;

  P6 |= bMASK_CS;
  sfSCK = 0;            
#else
//  sfCS  = 1;                          // Inactive Clock Polarity Low
  bP4 |= bMASK_CS;

//  sfSCK = 0;            
  bP4 &= ~bMASK_SCK;

//  sfSO  = 1;
  bP4 |= bMASK_SO;

//  sfSI  = 1;
  bP4 |= bMASK_SI;
#endif

//  if (SafeReadStatus() == 0) TestError(szBadFlash);
}



uint    GetFlashStatus(void)
{
uint    i;

  i = 0;

  if (cwErrCompare   != 0) i |= 0x0001;
  if (cwErrPageErase != 0) i |= 0x0002;
  if (cwErrPageRead  != 0) i |= 0x0004;
  if (cwErrPageWrite != 0) i |= 0x0008;

  return(i);
}


bit     GetFlashChecksum(void)
{
  MakeCRC16_XDATA(&mpbPageIn, wPAGE_SIZE);

  if ((bCRCHi != 0x00) && (bCRCLo != 0x00))
  {
    if ((bCRCHi != 0x70) && (bCRCLo != 0x7F))
      return(0);
  }

  return(1);
}
*/
