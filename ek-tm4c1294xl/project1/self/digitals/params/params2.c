/*------------------------------------------------------------------------------
PARAMS2!C


------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "../../memory/mem_digitals.h"
#include    "../../memory/mem_realtime.h"
#include    "../../memory/mem_params.h"
#include    "../../serial/ports.h"
#include    "../../serial/ports_devices.h"
#include    "../../digitals/digitals.h"
#include    "../../digitals/digitals_display.h"
#include    "../../digitals/digitals_messages.h"
#include    "../../devices/devices.h"
#include    "../../sensors/automatic1.h"
#include    "../../sensors/automatic_v.h"
#include    "../../sensors/automatic_w.h"
#include    "../../sensors/device_a.h"
#include    "../../sensors/device_b.h"
#include    "../../sensors/sensor3/device_c.h"
#include    "../../sensors/device_k.h"
#include    "../../sensors/sensor21/input_p.h"
#include    "../../sensors/sensor21/device_p.h"
#include    "../../sensors/sensor21/automatic_p.h"
#include    "../../sensors/sensor24/device_s.h"
#include    "../../sensors/sensor24/automatic_s.h"
#include    "../../sensors/device_q.h"
#include    "../../sensors/sensor26/device_u.h"
#include    "../../sensors/sensor26/params26.h"
#include    "../../sensors/sensor26/params28.h"
#include    "../../sensors/device_v.h"
#include    "../../sensors/device_w.h"
#include    "../../sensors/sensor31/params31.h"
#include    "../../sensors/sensor32/params32.h"
#include    "../../sensors/sensor33/params33.h"
#include    "../../sensors/sensor34/params34.h"
#include    "../../sensors/sensor35/params35.h"
#include    "../../sensors/sensor36/params36.h"
#include    "../../sensors/sensor36/params37.h"
#include    "../../sensors/sensor38/params38.h"
#include    "../../time/delay.h"
#include    "../../console.h"
#include    "../../flash/files.h"
#include    "params.h"
#include    "params2.h"



bool                    fBeginParam;

static float            reParamDiv;

static float            reValue;



#ifndef SKIP_A

void    QueryArrayA(uchar  bT)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x08);

  PushChar(0x11);
  PushChar(bT);

  QueryIO(1+3+2, 2+2+2);
}


uchar   ReadArrayA(void)
{
  InitPop(1);

  uchar b = PopChar();

  ulong dw = (b & 0x3F)*0x1000000;
  dw += PopChar()*0x10000;
  dw += PopChar();

  reValue = (float)dw / reParamDiv;
  return b;
}


bool    ReadParamA(void)
{
uchar   i;

  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryOpenA();

    if (Input() != SER_GOODCHECK) return(0);
    fBeginParam = true;
  }

  ShowPercent(100);

  switch (diCurr.ibLine)
  {
    case PAR_P  : i = 0x00; break;
    case PAR_P1 : i = 0x01; break;
    case PAR_P2 : i = 0x02; break;
    case PAR_P3 : i = 0x03; break;

    case PAR_Q  : i = 0x04; break;
    case PAR_Q1 : i = 0x05; break;
    case PAR_Q2 : i = 0x06; break;
    case PAR_Q3 : i = 0x07; break;

    case PAR_S  : i = 0x08; break;
    case PAR_S1 : i = 0x09; break;
    case PAR_S2 : i = 0x0A; break;
    case PAR_S3 : i = 0x0B; break;

    case PAR_U  : i = 0x10; break;
    case PAR_U1 : i = 0x11; break;
    case PAR_U2 : i = 0x12; break;
    case PAR_U3 : i = 0x13; break;

    case PAR_I  : i = 0x20; break;
    case PAR_I1 : i = 0x21; break;
    case PAR_I2 : i = 0x22; break;
    case PAR_I3 : i = 0x23; break;

    case PAR_C  : i = 0x30; break;
    case PAR_C1 : i = 0x31; break;
    case PAR_C2 : i = 0x32; break;
    case PAR_C3 : i = 0x33; break;

    case PAR_F  : i = 0x40; break;
    case PAR_F1 : i = 0x41; break;
    case PAR_F2 : i = 0x42; break;
    case PAR_F3 : i = 0x43; break;

    default:     return(0);
  }

  DelayOff();
  QueryArrayA(i);

  if (Input() != SER_GOODCHECK) return(0);

  ReadArrayA();

  switch (diCurr.ibLine)
  {
    case PAR_P  :
    case PAR_P1 :
    case PAR_P2 :
    case PAR_P3 : if (ReadArrayA() & 0x80) reValue *= -1; break;

    case PAR_Q  :
    case PAR_Q1 :
    case PAR_Q2 :
    case PAR_Q3 : if (ReadArrayA() & 0x40) reValue *= -1; break;
  }

  return(1);
}

#endif



#ifndef SKIP_B

void    QueryArrayB(uchar  bT)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x08);

  PushChar(0x11);
  PushChar(bT);

  QueryIO(1+3+2, 2+2+2);
}


uchar   ReadArrayB(void)
{
uchar   i;

  InitPop(1);

  coEnergy.mpbBuff[3] = 0;

  i = PopChar();
  coEnergy.mpbBuff[2] = i & 0x3F;

  coEnergy.mpbBuff[0] = PopChar();
  coEnergy.mpbBuff[1] = PopChar();

  reValue = (float)coEnergy.dwBuff / reParamDiv;
  return(i);
}


bool    ReadParamB(void)
{
uchar   i;

  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryOpenB();

    if (Input() != SER_GOODCHECK) return(0);
    fBeginParam = true;
  }

  ShowPercent(100);

  switch (diCurr.ibLine)
  {
    case PAR_P  : i = 0x00; break;
    case PAR_P1 : i = 0x01; break;
    case PAR_P2 : i = 0x02; break;
    case PAR_P3 : i = 0x03; break;

    case PAR_Q  : i = 0x04; break;
    case PAR_Q1 : i = 0x05; break;
    case PAR_Q2 : i = 0x06; break;
    case PAR_Q3 : i = 0x07; break;

    case PAR_S  : i = 0x08; break;
    case PAR_S1 : i = 0x09; break;
    case PAR_S2 : i = 0x0A; break;
    case PAR_S3 : i = 0x0B; break;

    case PAR_U  : i = 0x10; break;
    case PAR_U1 : i = 0x11; break;
    case PAR_U2 : i = 0x12; break;
    case PAR_U3 : i = 0x13; break;

    case PAR_I  : i = 0x20; break;
    case PAR_I1 : i = 0x21; break;
    case PAR_I2 : i = 0x22; break;
    case PAR_I3 : i = 0x23; break;

    case PAR_C  : i = 0x30; break;
    case PAR_C1 : i = 0x31; break;
    case PAR_C2 : i = 0x32; break;
    case PAR_C3 : i = 0x33; break;

    case PAR_F  : i = 0x40; break;
    case PAR_F1 : i = 0x41; break;
    case PAR_F2 : i = 0x42; break;
    case PAR_F3 : i = 0x43; break;

    default:     return(0);
   }

  DelayOff();
  QueryArrayB(i);

  if (Input() != SER_GOODCHECK) return(0);

  ReadArrayB();

  switch (diCurr.ibLine)
  {
    case PAR_P  :
    case PAR_P1 :
    case PAR_P2 :
    case PAR_P3 : if (ReadArrayB() & 0x80) reValue *= -1; break;

    case PAR_Q  :
    case PAR_Q1 :
    case PAR_Q2 :
    case PAR_Q3 : if (ReadArrayB() & 0x40) reValue *= -1; break;

    case PAR_I1 :
    case PAR_I2 :
    case PAR_I3 : if (boFixParamsBugs != false) reValue *= 1000; break;
  }

  return(1);
}

#endif



#ifndef SKIP_C

void    QueryArrayC(uchar  bT, uchar  bSize)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(bT);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+4*bSize+2, 3+3+2);
}


void    ReadArrayC(uchar  i)
{
  InitPop(i);

  combo32 co;
  co.mpbBuff[0] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[3] = PopChar();

  reValue = co.flBuff / reParamDiv;
}


bool    ReadParamC(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryOpenC();

    if (RevInput() != SER_GOODCHECK) return(0);
    fBeginParam = true;
  }

  ShowPercent(100);


  DelayOff();

  switch (diCurr.ibLine)
  {
    case PAR_P  :
    case PAR_P1 :
    case PAR_P2 :
    case PAR_P3 : QueryArrayC(8,4);  break;

    case PAR_Q  :
    case PAR_Q1 :
    case PAR_Q2 :
    case PAR_Q3 : QueryArrayC(9,4);  break;

    case PAR_U1 :
    case PAR_U2 :
    case PAR_U3 : QueryArrayC(10,3); break;

    case PAR_I1 :
    case PAR_I2 :
    case PAR_I3 : QueryArrayC(11,3); break;

    case PAR_C1 :
    case PAR_C2 :
    case PAR_C3 : QueryArrayC(12,3); break;

    case PAR_F  : QueryArrayC(13,1); break;

    default: return(0);
   }


  if (RevInput() != SER_GOODCHECK) return(0);

  switch (diCurr.ibLine)
  {
    case PAR_P  : ReadArrayC(4);  break;
    case PAR_P1 : ReadArrayC(8);  break;
    case PAR_P2 : ReadArrayC(12); break;
    case PAR_P3 : ReadArrayC(16); break;

    case PAR_Q  : ReadArrayC(4);  break;
    case PAR_Q1 : ReadArrayC(8);  break;
    case PAR_Q2 : ReadArrayC(12); break;
    case PAR_Q3 : ReadArrayC(16); break;

    case PAR_U1 : ReadArrayC(4);  break;
    case PAR_U2 : ReadArrayC(8);  break;
    case PAR_U3 : ReadArrayC(12); break;

    case PAR_I1 : ReadArrayC(4);  break;
    case PAR_I2 : ReadArrayC(8);  break;
    case PAR_I3 : ReadArrayC(12); break;

    case PAR_C1 : ReadArrayC(4);  break;
    case PAR_C2 : ReadArrayC(8);  break;
    case PAR_C3 : ReadArrayC(12); break;

    case PAR_F  : ReadArrayC(4);  break;

    default: return(0);
   }

  switch (diCurr.ibLine)
  {
    case PAR_P  :
    case PAR_P1 :
    case PAR_P2 :
    case PAR_P3 :

    case PAR_Q  :
    case PAR_Q1 :
    case PAR_Q2 :
    case PAR_Q3 : if (boFixParamsBugs == false) reValue /= 1000; break;

    case PAR_I  :
    case PAR_I1 :
    case PAR_I2 :
    case PAR_I3 : if (boFixParamsBugs != false) reValue *= 1000; break;
  }

  return(1);
}

#endif


#ifndef SKIP_G

void    QueryArrayG(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x0D);

  CodQueryIO(3+110+1, 3+1);
}


void    ReadRealG(void)
{
  PopRealExt_G();
  if (reValue == 2) reValue = 0;
}


void    ReadIntG(void)
{
  reValue = PopIntExtG()/100;
}


void    CalsParS_G(uchar ibP, uchar ibQ)
{
  InitPop(ibP); ReadRealG(); reP = reValue;
  InitPop(ibQ); ReadRealG(); reQ = reValue;
  reQ = sqrt(reP*reP + reQ*reQ);
  reValue = reQ;
}


void    CalsParC_G(uchar ibP, uchar ibQ)
{
  CalsParS_G(ibP, ibQ);
  reValue = (reQ == 0) ? 0 : reP/reQ;
}


bool    ReadParamG(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryOpenG();

    if (CodInput() != SER_GOODCHECK) return(0);

    if (ReadOpenG() == 0) return(0);
    if (!ExtVersionCod()) return(0);

    DelayOff();
    QueryArrayG();

    if (CodInput() != SER_GOODCHECK) return(0);

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P1 : InitPop(3+8*0);   ReadRealG(); break;
    case PAR_P2 : InitPop(3+8*1);   ReadRealG(); break;
    case PAR_P3 : InitPop(3+8*2);   ReadRealG(); break;

    case PAR_Q1 : InitPop(3+8*3);   ReadRealG(); break;
    case PAR_Q2 : InitPop(3+8*4);   ReadRealG(); break;
    case PAR_Q3 : InitPop(3+8*5);   ReadRealG(); break;

    case PAR_S1 : CalsParS_G(3+8*0, 3+8*3); break;
    case PAR_S2 : CalsParS_G(3+8*1, 3+8*4); break;
    case PAR_S3 : CalsParS_G(3+8*2, 3+8*5); break;

    case PAR_U1 : InitPop(3+8*6);   ReadRealG(); break;
    case PAR_U2 : InitPop(3+8*7);   ReadRealG(); break;
    case PAR_U3 : InitPop(3+8*8);   ReadRealG(); break;

    case PAR_I1 : InitPop(3+8*9);   ReadRealG(); reValue *= 1000; break;
    case PAR_I2 : InitPop(3+8*10);  ReadRealG(); reValue *= 1000; break;
    case PAR_I3 : InitPop(3+8*11);  ReadRealG(); reValue *= 1000; break;

    case PAR_F1 : InitPop(3+8*12+0);  ReadIntG(); break;
    case PAR_F2 : InitPop(3+8*12+2);  ReadIntG(); break;
    case PAR_F3 : InitPop(3+8*12+4);  ReadIntG(); break;

    case PAR_C1 : CalsParC_G(3+8*0, 3+8*3); break;
    case PAR_C2 : CalsParC_G(3+8*1, 3+8*4); break;
    case PAR_C3 : CalsParC_G(3+8*2, 3+8*5); break;

    default: return(0); break;
   }

  return(1);
}

#endif


#ifndef SKIP_M

void    QueryArrayM(void)
{
  InitPush(0);
  Push(&mpdwAddress1[diCurr.bAddress-1], sizeof(ulong));
  PushChar(0x26);

  QueryIO(4+3+2, 4+1+2);
}


void    ReadArrayM(void)
{
  InitPop(5);
  reValue = 0.01*(FromBCD(PopChar())*100 + FromBCD(PopChar()));
}


bool    ReadParamM(void)
{
  Clear();
  DelayOff();

  if (diCurr.ibLine != PAR_P) return(0);

  QueryArrayM();
  if (Input() != SER_GOODCHECK) return(0);
  ReadArrayM();

  return(1);
}

#endif



#ifndef SKIP_P

void    QueryArrayP(void)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('6');
  PushChar('0');
  PushChar('6');
  PushChar('0');
  PushChar('0');
  PushChar('1');
  PushChar('(');
  PushChar('4');
  PushChar('0');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+131+1, 4+11+1);
}


void    QueryArray2P(void)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('6');
  PushChar('0');
  PushChar('6');
  PushChar('0');
  PushChar('0');
  PushChar('2');
  PushChar('(');
  PushChar('2');
  PushChar('3');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+73+1, 4+11+1);
}


void    ReadArrayP(uchar  i)
{
  InitPop(2 + i*8);

  ulong dw = PopChar4Els();
  dw <<= 16;
  dw |= PopChar4Els();
  reValue = (slong)dw;
}


void    ReadArray2P(uchar  i)
{
  InitPop(2 + i*4);

  ulong dw = PopChar4Els();
  reValue = (slong)dw;
}


bool    ReadParamP(void)
{
  Clear();

  if (fBeginParam == false)
  {
    if (OpenOpenP_Full() == 0) return(0);


    DelayOff();
    QueryArray2P();

    if (ElsInput(0) != SER_GOODCHECK) return(0);

    ReadArray2P(0); mpreParamP[0] = reValue/10;
    ReadArray2P(1); mpreParamP[1] = reValue/10;
    ReadArray2P(2); mpreParamP[2] = reValue/10;


    DelayOff();
    QueryArrayP();

    if (ElsInput(0) != SER_GOODCHECK) return(0);

    QueryCloseP();
    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P  : ReadArrayP(0);  break;
    case PAR_P1 : ReadArrayP(1);  break;
    case PAR_P2 : ReadArrayP(2);  break;
    case PAR_P3 : ReadArrayP(3);  break;

    case PAR_Q  : ReadArrayP(4);  break;
    case PAR_Q1 : ReadArrayP(5);  break;
    case PAR_Q2 : ReadArrayP(6);  break;
    case PAR_Q3 : ReadArrayP(7);  break;

    case PAR_S  : ReadArrayP(8);  break;
    case PAR_S1 : ReadArrayP(9);  break;
    case PAR_S2 : ReadArrayP(10); break;
    case PAR_S3 : ReadArrayP(11); break;

    case PAR_I1 : ReadArrayP(12); reValue *= 100; break;
    case PAR_I2 : ReadArrayP(13); reValue *= 100; break;
    case PAR_I3 : ReadArrayP(14); reValue *= 100; break;

    case PAR_F  : ReadArrayP(15); reValue /= 10; break;

    case PAR_U1 : reValue = mpreParamP[0]; break;
    case PAR_U2 : reValue = mpreParamP[1]; break;
    case PAR_U3 : reValue = mpreParamP[2]; break;

    default: return(0);
  }

  return(1);
}

#endif



#ifndef SKIP_S

void    QueryParamS1(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x32);

  QueryS(100+14, 15);
}


void    ReadParamS1(void)
{
  InitPop(9);

  ulong dw = PopChar();
  dw += PopChar()*100;
  dw += PopChar()*10000;

  reValue = dw*10;
}


bool    ReadParamS(void)
{
  Clear();

  QueryParamS1();
  if (InputS() != SER_GOODCHECK) return(0);

  switch (diCurr.ibLine)
  {
    case PAR_P : ReadParamS1(); break;

    default: return(0);
  }

  return(1);
}

#endif



#ifndef SKIP_T

void    ReadParamT1(void)
{
  InitPop(6);

  PopParamT1(0); mpreParam[PAR_P]  = reValue;
  PopParamT1(1); mpreParam[PAR_P1] = reValue;
  PopParamT1(1); mpreParam[PAR_P2] = reValue;
  PopParamT1(1); mpreParam[PAR_P3] = reValue;

  PopParamT1(0); mpreParam[PAR_Q]  = reValue;
  PopParamT1(1); mpreParam[PAR_Q1] = reValue;
  PopParamT1(1); mpreParam[PAR_Q2] = reValue;
  PopParamT1(1); mpreParam[PAR_Q3] = reValue;
}


void    ReadParamT2(void)
{
  InitPop(6);

  PopParamT2(10); mpreParam[PAR_I1] = reValue;
  PopParamT2(10); mpreParam[PAR_I2] = reValue;
  PopParamT2(10); mpreParam[PAR_I3] = reValue;

  PopParamT2(1000); mpreParam[PAR_U1] = reValue;
  PopParamT2(1000); mpreParam[PAR_U2] = reValue;
  PopParamT2(1000); mpreParam[PAR_U3] = reValue;
}


void    ReadParamT3(void)
{
  InitPop(6);

  PopParamT3(); mpreParam[PAR_F] = reValue;
}


bool    ReadParamT(void)
{
  Clear();

  if (fBeginParam == false)
  {
    DelayOff();
    QueryParamT1();

    if (TxtInput() != SER_GOODCHECK) return(0);
    ReadParamT1();

    DelayOff();
    QueryParamT2();

    if (TxtInput() != SER_GOODCHECK) return(0);
    ReadParamT2();

    DelayOff();
    QueryParamT3();

    if (TxtInput() != SER_GOODCHECK) return(0);
    ReadParamT3();

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P  : reValue = mpreParam[PAR_P];   break;
    case PAR_P1 : reValue = mpreParam[PAR_P1];  break;
    case PAR_P2 : reValue = mpreParam[PAR_P2];  break;
    case PAR_P3 : reValue = mpreParam[PAR_P3];  break;

    case PAR_Q  : reValue = mpreParam[PAR_Q];   break;
    case PAR_Q1 : reValue = mpreParam[PAR_Q1];  break;
    case PAR_Q2 : reValue = mpreParam[PAR_Q2];  break;
    case PAR_Q3 : reValue = mpreParam[PAR_Q3];  break;

    case PAR_I1 : reValue = mpreParam[PAR_I1];  break;
    case PAR_I2 : reValue = mpreParam[PAR_I2];  break;
    case PAR_I3 : reValue = mpreParam[PAR_I3];  break;

    case PAR_U1 : reValue = mpreParam[PAR_U1];  break;
    case PAR_U2 : reValue = mpreParam[PAR_U2];  break;
    case PAR_U3 : reValue = mpreParam[PAR_U3];  break;

    case PAR_F  : reValue = mpreParam[PAR_F];   break;

    default: return(0); break;
  }

  return(1);
}

#endif



#ifndef SKIP_V

void    QueryParamV1(void)
{
  InitPush(2);

  PushChar(0x20);
  PushChar(0x00);

  PushAddressV(0x2D);

  QueryV(100+20, 15);
}


void    ReadParamV1(void)
{
  InitPop(13);

  ulong dw = PopChar();
  dw += PopChar()*0x100;
  dw += PopChar()*0x10000;

  reValue = dw * 10;
}


bool    ReadParamV(void)
{
  Clear();

  QueryParamV1();
  if (InputV() != SER_GOODCHECK) return(0);

  switch (diCurr.ibLine)
  {
    case PAR_P : ReadParamV1(); break;

    default: return(0);
  }

  return(1);
}

#endif



#ifndef SKIP_W

void    QueryParamW1(char  *psz)
{
  PushAddressW_DirectRead();

  PushStringBcc("1-0:");
  PushStringBcc(psz);
  PushChar1Bcc(0x03);

  QueryW(1000, 1);
}


bool    ReadParamW1(char  *psz, uint  wMul)
{
  QueryCloseW();
  QueryParamW1(psz);

  if (InputW() != SER_GOODCHECK) return false;

  InitPop(1);
  reValue = PopDoubleW()*wMul;

  return true;
}


bool    ReadParamW2(char  *psz1, char  *psz2)
{
  QueryCloseW();
  QueryParamW1(psz1);

  if (InputW() != SER_GOODCHECK) return false;

  InitPop(1);
  double db1 = PopDoubleW();


  QueryCloseW();
  QueryParamW1(psz2);

  if (InputW() != SER_GOODCHECK) return false;

  InitPop(1);
  double db2 = PopDoubleW();


  reValue = db1 - db2;

  return true;
}



bool    ReadParam29(void)
{
  Clear();

  switch (diCurr.ibLine)
  {
    case PAR_P  : ReadParamW2("21.7.0","22.7.0"); break;

    case PAR_Q  : ReadParamW2("23.7.0","24.7.0"); break;

    case PAR_U  : ReadParamW1("32.7.0",1); break;

    case PAR_I  : ReadParamW1("31.7.0",1000); break;

    case PAR_C  : ReadParamW1("33.7.0",1); break;

    case PAR_F  : ReadParamW1("14.7.0",1); break;

    default: return false;
  }

  return true;
}


bool    ReadParam30(void)
{
  Clear();

  switch (diCurr.ibLine)
  {
    case PAR_P  : ReadParamW2("1.7.0","2.7.0"); break;
    case PAR_P1 : ReadParamW2("21.7.0","22.7.0"); break;
    case PAR_P2 : ReadParamW2("41.7.0","42.7.0"); break;
    case PAR_P3 : ReadParamW2("61.7.0","62.7.0"); break;

    case PAR_Q  : ReadParamW2("3.7.0","4.7.0"); break;
    case PAR_Q1 : ReadParamW2("23.7.0","24.7.0"); break;
    case PAR_Q2 : ReadParamW2("43.7.0","44.7.0"); break;
    case PAR_Q3 : ReadParamW2("63.7.0","64.7.0"); break;

    case PAR_U1 : ReadParamW1("32.7.0",1); break;
    case PAR_U2 : ReadParamW1("52.7.0",1); break;
    case PAR_U3 : ReadParamW1("72.7.0",1); break;

    case PAR_I1 : ReadParamW1("31.7.0",1000); break;
    case PAR_I2 : ReadParamW1("51.7.0",1000); break;
    case PAR_I3 : ReadParamW1("71.7.0",1000); break;

    case PAR_C  : ReadParamW1("13.7.0",1); break;
    case PAR_C1 : ReadParamW1("33.7.0",1); break;
    case PAR_C2 : ReadParamW1("53.7.0",1); break;
    case PAR_C3 : ReadParamW1("73.7.0",1); break;

    case PAR_F  : ReadParamW1("14.7.0",1); break;

    default: return false;
  }

  return true;
}

#endif



float2  ReadParam(uint  iwPrm)
{
  Clear();

  LoadCurrParam(iwPrm);
  ibPort = diCurr.ibPort;

  reParamDiv = mpreParamsDiv[iwPrm];

  switch (diCurr.bDevice)
  {
    case 0:  return GetFloat2(0, true);

#ifndef SKIP_A
    case 15:
    case 1:  return GetFloat2(reValue, ReadParamA());
#endif

#ifndef SKIP_B
    case 12:
    case 8:
    case 2:  return GetFloat2(reValue, ReadParamB());
#endif

#ifndef SKIP_C
    case 3:  return GetFloat2(reValue, ReadParamC());
#endif

#ifndef SKIP_G
    case 9:  return( ReadParamG() );  break;
#endif

#ifndef SKIP_M
    case 18: return( ReadParamM() );  break;
#endif

#ifndef SKIP_P
    case 21: return GetFloat2(reValue, ReadParamP());
#endif

#ifndef SKIP_S
    case 24: return GetFloat2(reValue, ReadParamS());
#endif

#ifndef SKIP_T
    case 25: return( ReadParamT() );  break;
#endif

#ifndef SKIP_U
    case 26: return ReadParam26();
    case 28: return ReadParam28();
#endif

#ifndef SKIP_V
    case 27: return GetFloat2(reValue, ReadParamV());
#endif

#ifndef SKIP_W
    case 29: return GetFloat2(reValue, ReadParam29());
    case 30: return GetFloat2(reValue, ReadParam30());
#endif

#ifndef SKIP_31
    case 31: return ReadParam31();
#endif

#ifndef SKIP_32
    case 32: return ReadParam32();
#endif

#ifndef SKIP_33
    case 33: return ReadParam33();
#endif

#ifndef SKIP_34
    case 34: return ReadParam34();
#endif

#ifndef SKIP_35
    case 35: return ReadParam35();
#endif

#ifndef SKIP_36
    case 36: return ReadParam36();
    case 37: return ReadParam37();
#endif

#ifndef SKIP_38
    case 38: return ReadParam38();
#endif

    default: return GetFloat2Error();
  }
}


float2  ReadParamRepeat(uint  iwPrm)
{
  uchar i;
  for (i=0; i<MaxRepeatsFixed(); i++)
  {
    if (fKey == true) return GetFloat2Error();

    float2 fl2 = ReadParam(iwPrm);
    if (fl2.fValid == true) return fl2;
  }

  return GetFloat2Error();
}



void    MakeExtended2(void)
{
  if (boParamsFlag == true)
  {
    ShowHi(szDirectParam);
    Clear(); sprintf(szLo+14,"%2u",ibDig+1);
    DelayInf();

    fBeginParam = false;

    LoadPrevDigital(ibDig);

    uint p;
    for (p=0; p<wPARAMS; p++)
    {
      if (fKey == true) break;

      LoadCurrParam(p);
      if ( (diPrev.ibPort   == diCurr.ibPort)   &&
           (diPrev.ibPhone  == diCurr.ibPhone)  &&
           (diPrev.bDevice  == diCurr.bDevice)  &&
           (diPrev.bAddress == diCurr.bAddress) )
      {
        sprintf(szHi+13,"%3u",p+1);

        float2 fl2 = (mpboEnblParams[p] == false) ? GetFloat2(0, true) : ReadParamRepeat(p);

        mpreParamsBuff[ibSoftTim][p] = (fl2.fValid) ? fl2.flValue : GetFloatNAN();
        mptiParamsBuff[p] = tiCurr;
      }
    }
  }


  ShowCanalNumber(ibDig);
  Clear();
}



uint    GetParamIndex(digital  di)
{
  uint p;
  for (p=0; p<wPARAMS; p++)
  {
    if ((mpdiParam[p].ibPort   == di.ibPort) &&
        (mpdiParam[p].ibPhone  == di.ibPhone) &&
        (mpdiParam[p].bDevice  == di.bDevice) &&
        (mpdiParam[p].bAddress == di.bAddress) &&
        (mpdiParam[p].ibLine   == di.ibLine)) return p;
  }

  return 0xFFFF;
}
