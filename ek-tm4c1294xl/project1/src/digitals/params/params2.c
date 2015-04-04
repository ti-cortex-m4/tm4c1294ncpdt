/*------------------------------------------------------------------------------
DEVICES_FAR.C


------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "params.h"


/*
//                                  0123456789ABCDEF
message         code    szRecP  =  "P, Âò           ",
                        szRecP1 =  "P1, Âò          ",
                        szRecP2 =  "P2, Âò          ",
                        szRecP3 =  "P3, Âò          ",
                        szRecQ  =  "Q, ÂÀÐ          ",
                        szRecQ1 =  "Q1, ÂÀÐ         ",
                        szRecQ2 =  "Q2, ÂÀÐ         ",
                        szRecQ3 =  "Q3, ÂÀÐ         ",
                        szRecS  =  "S, ÂÀ           ",
                        szRecS1 =  "S1, ÂÀ          ",
                        szRecS2 =  "S2, ÂÀ          ",
                        szRecS3 =  "S3, ÂÀ          ",
                        szRecU  =  "U, Â            ",
                        szRecU1 =  "U1, Â           ",
                        szRecU2 =  "U2, Â           ",
                        szRecU3 =  "U3, Â           ",
                        szRecI  =  "I, ìÀ           ",
                        szRecI1 =  "I1, ìÀ          ",
                        szRecI2 =  "I2, ìÀ          ",
                        szRecI3 =  "I3, ìÀ          ",
                        szRecC  =  "cos            ",
                        szRecC1 =  "cos  1         ",
                        szRecC2 =  "cos  2         ",
                        szRecC3 =  "cos  3         ",
                        szRecF  =  "f, Ãö           ",
                        szRecF1 =  "f1, Ãö          ",
                        szRecF2 =  "f2, Ãö          ",
                        szRecF3 =  "f3, Ãö          ",
                        szRecNo =  "Íåò ïàðàìåòðà   ";



#ifndef SKIP_A

void    QueryArrayA(uchar  bT)
{
  InitPush();

  PushChar(diCurr.bAddress);
  PushChar(0x08);

  PushChar(0x11);
  PushChar(bT);

  QueryIO(1+3+2, 2+2+2);
}


uchar   ReadArrayA(void)
{
uchar   i;

  InitPop(1);

  coEnergy.mpbBuff[0] = 0;

  i = PopChar();
  coEnergy.mpbBuff[1] = i & 0x3F;

  coEnergy.mpbBuff[2] = PopChar();
  coEnergy.mpbBuff[3] = PopChar();

  reBuffA = (real)coEnergy.dwBuff / reParamDiv;
  return(i);
}


bit     ReadParamA(void)
{
uchar   i;

  Clear();

  if (boBeginParam == FALSE)
  {
    DelayOff();
    QueryOpenA();

    if (Input() != SER_GOODCHECK) return(0);
    boBeginParam = boTrue;
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

    default:     return(0); break;
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
    case PAR_P3 : if (ReadArrayA() & 0x80) reBuffA *= -1; break;

    case PAR_Q  : 
    case PAR_Q1 : 
    case PAR_Q2 : 
    case PAR_Q3 : if (ReadArrayA() & 0x40) reBuffA *= -1; break;
  }

  return(1);
}

#endif



#ifndef SKIP_B

void    QueryArrayB(uchar  bT)
{
  InitPush();

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

  coEnergy.mpbBuff[0] = 0;

  i = PopChar();
  coEnergy.mpbBuff[1] = i & 0x3F;

  coEnergy.mpbBuff[3] = PopChar();
  coEnergy.mpbBuff[2] = PopChar();

  reBuffA = (real)coEnergy.dwBuff / reParamDiv;
  return(i);
}


bit     ReadParamB(void)
{
uchar   i;

  Clear();

  if (boBeginParam == FALSE)
  {
    DelayOff();
    QueryOpenB();

    if (Input() != SER_GOODCHECK) return(0);
    boBeginParam = boTrue;
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

    default:     return(0); break;
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
    case PAR_P3 : if (ReadArrayB() & 0x80) reBuffA *= -1; break;

    case PAR_Q  : 
    case PAR_Q1 : 
    case PAR_Q2 : 
    case PAR_Q3 : if (ReadArrayB() & 0x40) reBuffA *= -1; break;

    case PAR_I1 : 
    case PAR_I2 : 
    case PAR_I3 : if (boFixParamBugs != FALSE) reBuffA *= 1000; break;
  }

  return(1);
}

#endif



#ifndef SKIP_C

void    QueryArrayC(uchar  bT, uchar  bSize)
{
  InitPush();

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(bT);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+4*bSize+2, 3+3+2);
}


void    ReadArrayC(uchar  bT)
{
  InitPop(bT);

  coEnergy.mpbBuff[3] = PopChar();
  coEnergy.mpbBuff[2] = PopChar();
  coEnergy.mpbBuff[1] = PopChar();
  coEnergy.mpbBuff[0] = PopChar();

  reBuffA = coEnergy.reBuff / reParamDiv;
}


bit     ReadParamC(void)
{
  Clear();

  if (boBeginParam == FALSE)
  {
    DelayOff();
    QueryOpenC();

    if (RevInput() != SER_GOODCHECK) return(0);
    boBeginParam = boTrue;
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

    default:              return(0); break;
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

    default:           return(0); break;
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
    case PAR_Q3 : if (boFixParamBugs == FALSE) reBuffA /= 1000; break;

    case PAR_I  :
    case PAR_I1 :
    case PAR_I2 :
    case PAR_I3 : if (boFixParamBugs != FALSE) reBuffA *= 1000; break;
  }

  return(1);
}

#endif


#ifndef SKIP_G

void    QueryArrayG(void)
{
  InitPush();

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x0D);

  CodQueryIO(3+110+1, 3+1);
}


void    ReadRealG(void)
{
  PopRealExt_G(); 
  if (reBuffA == 2) reBuffA = 0;
}


void    ReadIntG(void)
{
  reBuffA = PopIntExtG()/100;
}


void    CalsParS_G(uchar ibP, uchar ibQ)
{
  InitPop(ibP); ReadRealG(); reP = reBuffA;
  InitPop(ibQ); ReadRealG(); reQ = reBuffA;
  reQ = sqrt(reP*reP + reQ*reQ);
  reBuffA = reQ;
}


void    CalsParC_G(uchar ibP, uchar ibQ)
{
  CalsParS_G(ibP, ibQ);
  reBuffA = (reQ == 0) ? 0 : reP/reQ;
}


bit     ReadParamG(void)
{
  Clear();

  if (boBeginParam == FALSE)
  {
    DelayOff();
    QueryOpenG();

    if (CodInput() != SER_GOODCHECK) return(0);

    if (ReadOpenG() == 0) return(0);
    if (!ExtVersionCod()) return(0);

    DelayOff();
    QueryArrayG();

    if (CodInput() != SER_GOODCHECK) return(0);

    boBeginParam = boTrue;
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

    case PAR_I1 : InitPop(3+8*9);   ReadRealG(); reBuffA *= 1000; break;
    case PAR_I2 : InitPop(3+8*10);  ReadRealG(); reBuffA *= 1000; break;
    case PAR_I3 : InitPop(3+8*11);  ReadRealG(); reBuffA *= 1000; break;

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
  InitPush();
  Push(&mpdwAddress1[diCurr.bAddress-1], sizeof(ulong));
  PushChar(0x26);

  QueryIO(4+3+2, 4+1+2);
}


void    ReadArrayM(void)
{
  InitPop(5);  
  reBuffA = 0.01*(FromBCD(PopChar())*100 + FromBCD(PopChar()));
}


bit     ReadParamM(void)
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
  InitPush();
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
  InitPush();
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

  dwBuffC = PopChar4Els();
  dwBuffC <<= 16;
  dwBuffC |= PopChar4Els();
  reBuffA = (slong)dwBuffC;
}


void    ReadArray2P(uchar  i)
{
  InitPop(2 + i*4);

  dwBuffC = PopChar4Els();
  reBuffA = (slong)dwBuffC;
}


bit     ReadParamP(void)
{
  Clear();

  if (boBeginParam == FALSE)
  {
    if (OpenDeviceP() == 0) return(0);


    DelayOff();
    QueryArray2P();

    if (ElsInput(0) != SER_GOODCHECK) return(0); 

    ReadArray2P(0); mpreParamP[0] = reBuffA/10;
    ReadArray2P(1); mpreParamP[1] = reBuffA/10;
    ReadArray2P(2); mpreParamP[2] = reBuffA/10;


    DelayOff();
    QueryArrayP();

    if (ElsInput(0) != SER_GOODCHECK) return(0); 

    QueryCloseP();
    boBeginParam = boTrue;
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

    case PAR_I1 : ReadArrayP(12); reBuffA *= 100; break;
    case PAR_I2 : ReadArrayP(13); reBuffA *= 100; break;
    case PAR_I3 : ReadArrayP(14); reBuffA *= 100; break;

    case PAR_F  : ReadArrayP(15); reBuffA /= 10; break;

    case PAR_U1 : reBuffA = mpreParamP[0]; break;
    case PAR_U2 : reBuffA = mpreParamP[1]; break;
    case PAR_U3 : reBuffA = mpreParamP[2]; break;

    default: return(0); break;
  }

  return(1);
}

#endif



#ifndef SKIP_T

void    ReadParamT1(void)
{
  InitPop(6);

  PopParamT1(0); mpreParam[PAR_P]  = reBuffA;
  PopParamT1(1); mpreParam[PAR_P1] = reBuffA;
  PopParamT1(1); mpreParam[PAR_P2] = reBuffA;
  PopParamT1(1); mpreParam[PAR_P3] = reBuffA;

  PopParamT1(0); mpreParam[PAR_Q]  = reBuffA;
  PopParamT1(1); mpreParam[PAR_Q1] = reBuffA;
  PopParamT1(1); mpreParam[PAR_Q2] = reBuffA;
  PopParamT1(1); mpreParam[PAR_Q3] = reBuffA;
}


void    ReadParamT2(void)
{
  InitPop(6);

  PopParamT2(10); mpreParam[PAR_I1] = reBuffA;
  PopParamT2(10); mpreParam[PAR_I2] = reBuffA;
  PopParamT2(10); mpreParam[PAR_I3] = reBuffA;

  PopParamT2(1000); mpreParam[PAR_U1] = reBuffA;
  PopParamT2(1000); mpreParam[PAR_U2] = reBuffA;
  PopParamT2(1000); mpreParam[PAR_U3] = reBuffA;
}


void    ReadParamT3(void)
{
  InitPop(6);

  PopParamT3(); mpreParam[PAR_F] = reBuffA;
}


bit     ReadParamT(void)
{
  Clear();

  if (boBeginParam == FALSE)
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

    boBeginParam = boTrue;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P  : reBuffA = mpreParam[PAR_P];   break;
    case PAR_P1 : reBuffA = mpreParam[PAR_P1];  break;
    case PAR_P2 : reBuffA = mpreParam[PAR_P2];  break;
    case PAR_P3 : reBuffA = mpreParam[PAR_P3];  break;
                                                 
    case PAR_Q  : reBuffA = mpreParam[PAR_Q];   break;
    case PAR_Q1 : reBuffA = mpreParam[PAR_Q1];  break;
    case PAR_Q2 : reBuffA = mpreParam[PAR_Q2];  break;
    case PAR_Q3 : reBuffA = mpreParam[PAR_Q3];  break;

    case PAR_I1 : reBuffA = mpreParam[PAR_I1];  break;
    case PAR_I2 : reBuffA = mpreParam[PAR_I2];  break;
    case PAR_I3 : reBuffA = mpreParam[PAR_I3];  break;

    case PAR_U1 : reBuffA = mpreParam[PAR_U1];  break;
    case PAR_U2 : reBuffA = mpreParam[PAR_U2];  break;
    case PAR_U3 : reBuffA = mpreParam[PAR_U3];  break;

    case PAR_F  : reBuffA = mpreParam[PAR_F];   break;

    default: return(0); break;
  }

  return(1);
}

#endif



#ifndef SKIP_U

void    ReadParamU1(void)
{
  InitPop(1);

  PopRealQ(); mpreParam[PAR_I1] = reBuffA*1000;
  PopRealQ(); mpreParam[PAR_I2] = reBuffA*1000;
  PopRealQ(); mpreParam[PAR_I3] = reBuffA*1000;
}


void    ReadParamU2(void)
{
  InitPop(1);

  PopRealQ(); mpreParam[PAR_U1] = reBuffA;
  PopRealQ(); mpreParam[PAR_U2] = reBuffA;
  PopRealQ(); mpreParam[PAR_U3] = reBuffA;
}


void    ReadParamU3(void)
{
  InitPop(1);

  PopRealQ(); mpreParam[PAR_P1] = reBuffA*1000;
  PopRealQ(); mpreParam[PAR_P2] = reBuffA*1000;
  PopRealQ(); mpreParam[PAR_P3] = reBuffA*1000;
}


void    ReadParamU4(void)
{
  InitPop(1);

  PopRealQ(); mpreParam[PAR_F] = reBuffA;
}


bit     ReadParamU(void)
{
  Clear();

  if (boBeginParam == FALSE)
  {
    QueryCloseU();
    QueryParamU1();

    if (BccInput() != SER_GOODCHECK) return(0);
    ReadParamU1();


    QueryCloseU();
    QueryParamU2();

    if (BccInput() != SER_GOODCHECK) return(0);
    ReadParamU2();


    QueryCloseU();
    QueryParamU3();

    if (BccInput() != SER_GOODCHECK) return(0);
    ReadParamU3();


    QueryCloseU();
    QueryParamU4();

    if (BccInput() != SER_GOODCHECK) return(0);
    ReadParamU4();


    boBeginParam = boTrue;
  }

  switch (diCurr.ibLine)
  {
    case PAR_P1 : reBuffA = mpreParam[PAR_P1];  break;
    case PAR_P2 : reBuffA = mpreParam[PAR_P2];  break;
    case PAR_P3 : reBuffA = mpreParam[PAR_P3];  break;

    case PAR_I1 : reBuffA = mpreParam[PAR_I1];  break;
    case PAR_I2 : reBuffA = mpreParam[PAR_I2];  break;
    case PAR_I3 : reBuffA = mpreParam[PAR_I3];  break;

    case PAR_U1 : reBuffA = mpreParam[PAR_U1];  break;
    case PAR_U2 : reBuffA = mpreParam[PAR_U2];  break;
    case PAR_U3 : reBuffA = mpreParam[PAR_U3];  break;

    case PAR_F  : reBuffA = mpreParam[PAR_F];   break;

    default: return(0); break;
  }

  return(1);
}

#endif



bit     ReadParam(uint  iwPrm)
{
  Clear();

  LoadCurrParam(iwPrm);
  ibPort = diCurr.ibPort;

  reParamDiv = mpreParamDiv[iwPrm];

  switch (diCurr.bDevice)
  {
    case 0:  reBuffA = 0; return(1);  break;

#ifndef SKIP_A
    case 15:
    case 1:  return( ReadParamA() );  break;
#endif

#ifndef SKIP_B
    case 12:
    case 8:
    case 2:  return( ReadParamB() );  break;
#endif

#ifndef SKIP_C
    case 3:  return( ReadParamC() );  break;
#endif

#ifndef SKIP_G
    case 9:  return( ReadParamG() );  break;
#endif

#ifndef SKIP_M
    case 18: return( ReadParamM() );  break;
#endif

#ifndef SKIP_P
    case 21: return( ReadParamP() );  break;
#endif

#ifndef SKIP_T
    case 25: return( ReadParamT() );  break;
#endif

#ifndef SKIP_U
    case 26: return( ReadParamU() );  break;
#endif

    default: reBuffA = 0; return(0);  break;
  }
}



void    MakeExtended2(void)
{
uchar   i;
uint    j;

  if (boEnableParam == boTrue)
  {
    ShowHi(szDirectParam); Clear();
    sprintf(szLo+14,"%2bu",ibDig+1); DelayInf();

    boBeginParam = FALSE;

    LoadPrevDigital(ibDig);
    for (j=0; j<wPARAMS; j++)
    {
      if (fKey == 1) break;

      LoadCurrParam(j);
      if ( (diPrev.ibPort   == diCurr.ibPort)   &&
           (diPrev.ibPhone  == diCurr.ibPhone)  &&
           (diPrev.bDevice  == diCurr.bDevice)  &&
           (diPrev.bAddress == diCurr.bAddress) )
      {
        sprintf(szHi+13,"%3u",j+1);

        if (mpboEnblPar[j] == FALSE)
          reBuffA = 0;
        else
        {
          for (i=0; i<bMINORREPEATS; i++)
          {
            if (fKey == 1) break;
            if (ReadParam(j) == 1) break;
          }

          if (i == bMINORREPEATS) 
          {
            coFloat.dwBuff = 0xFFFFFFFF; 
            reBuffA = coFloat.reBuff;
          }
        }

        mpreParBuff[ibSoftTim][j] = reBuffA;
        mptiParBuff[j] = tiCurr;
      }
    }
  }


  ShowDigitalHi(); Clear();
}
*/


void    MakeParamDividers(uint  iwPrm)
{
  reBuffA = 1;

  if (GetParamDevice(iwPrm) == 1)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_P  :
      case PAR_P1 :
      case PAR_P2 :
      case PAR_P3 :

      case PAR_Q  :
      case PAR_Q1 :
      case PAR_Q2 :
      case PAR_Q3 :

      case PAR_S  :
      case PAR_S1 :
      case PAR_S2 :
      case PAR_S3 : reBuffA = 1000; break;

      case PAR_I  : 
      case PAR_I1 : 
      case PAR_I2 : 
      case PAR_I3 : reBuffA = 10;   break;

      default:      reBuffA = 100;  break;
    }
  }
  else if ((GetParamDevice(iwPrm) == 2) ||
           (GetParamDevice(iwPrm) == 8) ||
           (GetParamDevice(iwPrm) == 12))
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_I  : mpboEnblPar[iwPrm] = FALSE; break;

      case PAR_I1 : 
      case PAR_I2 : 
      case PAR_I3 : reBuffA = 1000; break;

      case PAR_U  : mpboEnblPar[iwPrm] = FALSE; break;

      case PAR_C  :
      case PAR_C1 :
      case PAR_C2 :
      case PAR_C3 : reBuffA = 1000; break;

      default:      reBuffA = 100;  break;
    }
  }
  else if (GetParamDevice(iwPrm) == 3)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_S  :
      case PAR_S1 :
      case PAR_S2 :
      case PAR_S3 : 

      case PAR_U  : 
      case PAR_I  : 
      case PAR_C  : 

      case PAR_F1 :
      case PAR_F2 :
      case PAR_F3 : mpboEnblPar[iwPrm] = FALSE; break;

      default:      reBuffA = 1;    break;
    }
  }
  else if (GetParamDevice(iwPrm) == 9)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_P  :
      case PAR_Q  :
      case PAR_S  :

      case PAR_U  : 
      case PAR_I  : 

      case PAR_C  : 

      case PAR_F  : mpboEnblPar[iwPrm] = FALSE; break;

      default:      reBuffA = 1;    break;
    }
  }
  else if (GetParamDevice(iwPrm) == 18)
  {
    if (GetParamLine(iwPrm) != PAR_P) 
      mpboEnblPar[iwPrm] = FALSE;
    else
    {
      reBuffA = 1;
      mpboEnblPar[iwPrm] = boTrue;
    }
  }
  else if (GetParamDevice(iwPrm) == 21)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_U  : 

      case PAR_I  : 

      case PAR_C  : 
      case PAR_C1 : 
      case PAR_C2 : 
      case PAR_C3 : 

      case PAR_F1 : 
      case PAR_F2 : 
      case PAR_F3 : mpboEnblPar[iwPrm] = FALSE; break;

      default:      reBuffA = 1;    break;
    }
  }
  else if (GetParamDevice(iwPrm) == 25)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_S  : 
      case PAR_S1 : 
      case PAR_S2 : 
      case PAR_S3 : 

      case PAR_U  : 

      case PAR_I  : 

      case PAR_C  : 
      case PAR_C1 : 
      case PAR_C2 : 
      case PAR_C3 : 

      case PAR_F1 : 
      case PAR_F2 : 
      case PAR_F3 : mpboEnblPar[iwPrm] = FALSE; break;

      default:      reBuffA = 1;    break;
    }
  }
  else if (GetParamDevice(iwPrm) == 26)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_P  : 

      case PAR_Q  : 
      case PAR_Q1 : 
      case PAR_Q2 : 
      case PAR_Q3 : 

      case PAR_S  : 
      case PAR_S1 : 
      case PAR_S2 : 
      case PAR_S3 : 

      case PAR_U  : 

      case PAR_I  : 

      case PAR_C  : 
      case PAR_C1 : 
      case PAR_C2 : 
      case PAR_C3 : 

      case PAR_F1 : 
      case PAR_F2 : 
      case PAR_F3 : mpboEnblPar[iwPrm] = FALSE; break;

      default:      reBuffA = 1;    break;
    }
  }

  mpreParamDiv[iwPrm] = reBuffA;
}

/*
#ifndef MODBUS
void    MakeAllDividers(void)
{
uint  i;

  for (i=0; i<wPARAMS; i++) 
    MakeDividers(i);   
}
#endif



uint    GetParamIndex(void)
{
uint    i;

  for (i=0; i<wPARAMS; i++)
  {
    if ((mpdiParam[i].ibPort   == diT.ibPort) &&
        (mpdiParam[i].ibPhone  == diT.ibPhone) &&
        (mpdiParam[i].bDevice  == diT.bDevice) &&
        (mpdiParam[i].bAddress == diT.bAddress) &&
        (mpdiParam[i].ibLine   == diT.ibLine)) return i;
  }

  return 0xFFFF;
}
*/
