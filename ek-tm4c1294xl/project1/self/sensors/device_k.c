/*------------------------------------------------------------------------------
DEVICE_K!C

Ёнергомера ÷Ё6850ћ
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
#include "../digitals/current/current_run.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "device_k.h"



#ifndef SKIP_K

double  PopDoubleK(void)
{
double  dbA,dbB;

  uchar a = 0;
  uchar b = 0;

  uchar i;
  for (i=0; i<40; i++)
  {
    uchar bT = PopChar() & 0x7F;

    if (a == 0)
    { 
      if (bT == '(') a = i+1;

      dbA = 0;
      dbB = 1;
    }
    else
    {
      if (bT == '.') { b = i-1; continue; }

      if (bT == ')') 
      {
        for (i=a; i<b; i++) dbA *= 10;
        return dbA;
      }

      if ((bT >= '0') && (bT <= '9'))
        bT -= '0';
      else 
        break;

      dbA += dbB*bT;
      dbB /= 10;
    }
  }

  return 0;
}



// запись адреса
void    PushAddress1Bcc(void)
{
uint    i;

  InitPush(0);
  PushChar1Bcc('/');
  PushChar1Bcc('?');

  i = mpdwAddress1[diCurr.bAddress-1] / 10000;

  PushChar1Bcc(szDigits[ i/1000 ]);
  PushChar1Bcc(szDigits[ (i/100) % 10 ]);
  PushChar1Bcc(szDigits[ (i%100) / 10 ]);
  PushChar1Bcc(szDigits[ i%10 ]);

  i = mpdwAddress1[diCurr.bAddress-1] % 10000;

  PushChar1Bcc(szDigits[ i/1000 ]);
  PushChar1Bcc(szDigits[ (i/100) % 10 ]);
  PushChar1Bcc(szDigits[ (i%100) / 10 ]);
  PushChar1Bcc(szDigits[ i%10 ]);

  PushChar1Bcc('!');
}


// запись адреса
void    PushAddress2Bcc(void)
{
  PushAddress1Bcc();

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);
}



void    PushLineBcc(uchar  ibLine)
{
  switch (ibLine) 
  {
    case 0:  PushChar1Bcc('P'); PushChar1Bcc('E'); break;
    case 1:  PushChar1Bcc('P'); PushChar1Bcc('I'); break;
    case 2:  PushChar1Bcc('Q'); PushChar1Bcc('E'); break;
    default: PushChar1Bcc('Q'); PushChar1Bcc('I'); break;
  }
}



void    QueryCloseK(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('B');
  PushChar1Bcc('0');
  PushChar1Bcc(0x03);

  BccQueryIO1(0, 4+1, 0);
  DelayOff();
}


void    QueryOpenK(void)
{
  QueryCloseK();

  PushAddress1Bcc();

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(2000, 11+2, 1);
}


void    ReadOpenK(void)
{
uchar   i,bT;

  Clear();
  InitPop(1);

  for (i=0; i<16; i++)
  {
    bT = PopChar0Bcc();

    if ((bT == '\r') || (bT == '\n')) break;
    szLo[i] = bT;
  }
}


/*
// посылка запроса на чтение энергии
void    QueryEnergySpecK(uchar  ibLine)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO1(1+6*28+2, 4+8+1, 6);
}
*/

// посылка запроса на чтение энергии
void    QueryEnergyAbsK(uchar  ibLine)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');

  PushLineBcc(ibLine);

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+8+1, 6);
}


void    ReadEnergyK(uchar  ibLine)
{
  InitPop(1);
  
  mpdbChannelsC[ibLine] = PopDoubleK();
  mpboChannelsA[ibLine] = true;
}



void    QueryOptionK(void)
{
uchar   i;

  InitPush(0);
  PushChar1Bcc(0x06);

  switch (mppoPorts[ diCurr.ibPort ].ibBaud)
  {
    case 0:  i = '2'; break;
    case 1:  i = '3'; break;
    case 2:  i = '4'; break;
    case 3:  i = '5'; break;
    case 4:  i = '6'; break;
    default: i = '7'; break;
  }

  PushChar1Bcc('0');
  PushChar1Bcc(i);
  PushChar1Bcc('1');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(1+13+2, 4+2, 1);
}



// посылка запроса с паролем доступа
void    QueryPasswordK(void)
{ 
uint    i;

  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('P');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);
  PushChar1Bcc('(');

  i = mpdwAddress2[diCurr.bAddress-1] / 1000;

  PushChar1Bcc(szDigits[ (i/100) % 10 ]);
  PushChar1Bcc(szDigits[ (i%100) / 10 ]);
  PushChar1Bcc(szDigits[ i%10 ]);

  i = mpdwAddress2[diCurr.bAddress-1] % 1000;

  PushChar1Bcc(szDigits[ (i/100) % 10 ]);
  PushChar1Bcc(szDigits[ (i%100) / 10 ]);
  PushChar1Bcc(szDigits[ i%10 ]);

  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO1(1+1, 4+9+1, 0);
}




void    QueryTimeK(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+17+2, 15+8+1, 0);
}


// посылка запроса на чтение времени
void    QueryTimeSpecK(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO1(1+17+2, 4+8+1, 0);
}



time    ReadTimeK(void)
{
  InitPop(7);

  time ti;
  ti.bHour   = PopChar2Bcc(); PopChar();
  ti.bMinute = PopChar2Bcc(); PopChar();
  ti.bSecond = PopChar2Bcc(); PopChar();

  return ti;
}



void    QueryDateK(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+20+2, 15+8+1, 0);
}



void    QueryDateSpecK(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('D');
  PushChar1Bcc('A');
  PushChar1Bcc('T');
  PushChar1Bcc('E');
  PushChar1Bcc('_');
  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO1(1+20+2, 4+8+1, 0);
}



time    ReadDateK(time  ti)
{
  InitPop(7+3);

  ti.bDay   = PopChar2Bcc(); PopChar();
  ti.bMonth = PopChar2Bcc(); PopChar();
  ti.bYear  = PopChar2Bcc(); PopChar();

  return ti;
}


void    QueryCorrectK(void)
{
  InitPush(0);

  PushChar1Bcc('/');
  PushChar1Bcc('?');

  PushChar1Bcc('C');
  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('!');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(1000, 2+6+2, 1);
}


// посылка запроса на коррекцию времени
void    QueryControlK(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('W');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('_');

  PushChar1Bcc('(');
  PushChar2Bcc(tiCurr.bHour);
  PushChar1Bcc(':');
  PushChar2Bcc(tiCurr.bMinute);
  PushChar1Bcc(':');
  PushChar2Bcc(tiCurr.bSecond);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO1(1+1, 4+16+1, 0);
}



void    QueryHeaderK_13(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('G');
  PushChar1Bcc('R');
  PushChar1Bcc('A');

  PushLineBcc(ibMinor);

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bYear);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO1(2000, 4+16+1, 48);
}


void    QueryHeaderK_14(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('G');
  PushChar1Bcc('R');
  PushChar1Bcc('A');

  PushLineBcc(ibMinor);

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO1(2000, 4+13+1, 48);
}



void    QueryHeaderK(void)
{
  HideCurrTime(1);


  tiAlt = tiDigPrev;
  dwBuffC = DateToHouIndex();

  dwBuffC -= wBaseCurr;

  HouIndexToDate(dwBuffC);
  tiDig = tiAlt;


  szHi[10] = 'A' + ibMinor;


  if (diCurr.bDevice == 14)
    ibMinorMax = 1;
  else
    ibMinorMax = 4;

  if (diCurr.bDevice == 14)
    QueryHeaderK_14();
  else
    QueryHeaderK_13();
}


void    ReadHeaderK(void)
{
uchar   j;

  InitPop(1);

  for (j=0; j<48; j++)
  {
    PopRealK();
    mpreBuffCanHou[ibMinor][j] = reBuffA/2;
  }
}


/*
void    MakeDataK(uchar  ibHou)
{
  ShowProgressDigHou();      
  reBuffB = mprePulseHou[ibDig];

  for (ibCan=0; ibCan<ibMinorMax; ibCan++)        
  {
    reBuffA = mpreBuffCanHou[ibCan][ibHou];   
    mpreEngFracDigCan[ibDig][ibCan] += reBuffA;

    wBuffD = (uint)(mpreEngFracDigCan[ibDig][ibCan]*reBuffB);
    mpwChannels[ibCan] = wBuffD;

    mpreEngFracDigCan[ibDig][ibCan] -= (float)wBuffD/reBuffB;
  }

  wBaseCurr++;
}



bit     ReadDataK(void)
{
uchar   i,j;

  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",           // показываем врем€/дату часового блока
          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  tiAlt = tiDig;
  if (SearchDefHouIndex() == 0) return(1); 


  if ((tiDig.bDay   == tiCurr.bDay)   &&
      (tiDig.bMonth == tiCurr.bMonth) &&
      (tiDig.bYear  == tiCurr.bYear))    
    j = 47-(tiCurr.bHour*2+tiCurr.bMinute/30); 
  else 
    j = 0;

  for (i=j; i<48; i++) 
  {
    ResetWatchdog();
    MakeDataK(47-i);

    tiAlt = tiDig;
    MakeSpecial();
    if (MakeStopHou(0) == 0) return(0);


    tiAlt = tiDigPrev;
    dwBuffC = DateToHouIndex();

    dwBuffC -= wBaseCurr;

    HouIndexToDate(dwBuffC);
    tiDig = tiAlt;


    iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;
  }

  return(1);
}
*/


void    ReadCurrentK(uchar  bMaxLine)
{
  uchar i;
  for (i=0; i<bMaxLine; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseHou[ibDig];
  }

  MakeCurrent();
}

#endif
