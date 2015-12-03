/*------------------------------------------------------------------------------
DEVICE_Q!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
//#include        "xdata.h"
//#include        "timer0.h"
//#include        "delay.h"
//#include        "display.h"
//#include        "engine.h"
//#include        "energy.h"
//#include        "watchdog.h"
//#include        "timedate.h"
//#include        "ports.h"
//#include        "limits.h"
//#include        "digitals.h"
//#include        "essential.h"
//#include        "device_k.h"
//#include        "device_q.h"
//#include        "_timedate.h"



#ifndef SKIP_Q

double  PopDoubleQ(void)
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

      if ((bT == ')') || (bT == ','))
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

/*
void    QueryCloseQ(void)
{
  QueryCloseK();
}



void    QueryOptionQ(void)
{
uchar   i;

  InitPush(0);
  PushChar1Bcc(0x06);

  switch (mppoPorts[ diCurr.ibPort ].ibSpeed)
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

  Query(1+6+2, 4+2, 1);
}


void    QueryCorrectQ(void)
{
  InitPush(0);

  PushChar1Bcc('/');
  PushChar1Bcc('?');

  PushChar1Bcc('C');
  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');

  PushChar1Bcc('(');
  PushChar2Bcc(tiCurr.bHour);
  PushChar1Bcc(':');
  PushChar2Bcc(tiCurr.bMinute);
  PushChar1Bcc(':');
  PushChar2Bcc(tiCurr.bSecond);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO(1000, 2+16+1, 0);
}


void    QueryEnergyAbsQ(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('T');
  PushChar1Bcc('0');
  PushChar1Bcc('0');

  PushChar1Bcc('(');
  PushChar1Bcc('1');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, n+9+1, 6);
}


void    QueryEnergyDayQ(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('D');
  PushChar1Bcc('0');
  PushChar1Bcc('0');

  PushChar1Bcc('(');
  PushChar2Bcc(tiAlt.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiAlt.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiAlt.bYear);
  PushChar1Bcc(',');
  PushChar1Bcc('1');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, n+18+1, 6);
}


void    QueryEnergyMonQ(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('M');
  PushChar1Bcc('0');
  PushChar1Bcc('0');

  PushChar1Bcc('(');
  PushChar2Bcc(tiAlt.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiAlt.bYear);
  PushChar1Bcc(',');
  PushChar1Bcc('1');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, n+15+1, 6);
}


void    QueryEnergySpecQ(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('T');
  PushChar1Bcc('0');
  PushChar1Bcc('0');

  PushChar1Bcc('(');
  PushChar1Bcc('1');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO(1+6*28+2, 4+9+1, 6);
}


void    ReadEnergyQ(void)
{
uchar   i;

  InitPop(1);

  for (i=0; i<Q_LINES; i++)
  {
    PopFloatQ();
    mpreChannelsB[i] = reBuffA;
  }
}


void    InitHeaderQ(void)
{
  if (!UseBounds())
    wBaseCurr = 0;
  else
  {
    wBaseCurr = mpcwStartRelCan[ibDig];
    sprintf(szLo," начало %04u:%02bu ",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
    DelayMsg();
  }

  tiDigPrev = tiCurr;
}


void    QueryHeaderQ_22(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('V');
  PushChar1Bcc('P');
  PushChar1Bcc('R');

  if (ibMinor == 0)
  {
    PushChar1Bcc('0');
    PushChar1Bcc('1');
  }
  else if (ibMinor == 1)
  {
    PushChar1Bcc('0');
    PushChar1Bcc('2');
  }
  else if (ibMinor == 2)
  {
    PushChar1Bcc('0');
    PushChar1Bcc('3');
  }
  else if (ibMinor == 3)
  {
    PushChar1Bcc('0');
    PushChar1Bcc('4');
  }

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bYear);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO(2000, 4+16+1, 48);
}


void    QueryHeaderQ(void)
{
  HideCurrTime(1);


  tiAlt = tiDigPrev;
  dwBuffC = DateToHouIndex();

  dwBuffC -= wBaseCurr;

  HouIndexToDate(dwBuffC);
  tiDig = tiAlt;


  szHi[10] = 'A' + ibMinor;


  ibMinorMax = 4;
  QueryHeaderQ_22();
}


void    ReadHeaderQ(void)
{
uchar   j;

  InitPop(1);

  for (j=0; j<48; j++)
  {
    PopFloatQ();
    mpreBuffCanHou[ibMinor][j] = reBuffA/2;
  }
}



void    MakeDataQ(uchar  ibHou)
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



bit     ReadDataQ(void)
{
uchar   i,j;

  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",           // показываем время/дату часового блока
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
    MakeDataQ(47-i);

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


void    ReadCurrentQ(void)
{
uchar   i;

  reBuffB = mprePulseHou[ibDig];

  for (i=0; i<Q_LINES; i++)
  {
    dwBuffC = mpreChannelsB[i] * reBuffB;
    mpdwBaseDig[i] = dwBuffC;
  }

  MakeCurrent();
}
*/
#endif

