/*------------------------------------------------------------------------------
params36_common,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_params.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../display/display.h"
#include "../../sensors/device_k.h"
#include "../../sensors/device_q.h"
#include "io36.h"
#include "params36_common.h"



void    QueryParam36_I123(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('C');
  PushChar1Bcc('U');
  PushChar1Bcc('R');
  PushChar1Bcc('R');
  PushChar1Bcc('E');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+3*28+2, n+8+1, 3);
}


void    ReadParam36_I123(void)
{
  InitPop(1);

  mpreParam[PAR_I1] = PopDoubleQ()*1000;
  mpreParam[PAR_I2] = PopDoubleQ()*1000;
  mpreParam[PAR_I3] = PopDoubleQ()*1000;
}



void    QueryParam36_U123(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('V');
  PushChar1Bcc('O');
  PushChar1Bcc('L');
  PushChar1Bcc('T');
  PushChar1Bcc('A');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+3*28+2, n+8+1, 3);
}


void    ReadParam36_U123(void)
{
  InitPop(1);

  mpreParam[PAR_U1] = PopDoubleQ();
  mpreParam[PAR_U2] = PopDoubleQ();
  mpreParam[PAR_U3] = PopDoubleQ();
}



void    QueryParam36_Pt_1Direction(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('P');
  PushChar1Bcc('O');
  PushChar1Bcc('W');
  PushChar1Bcc('E');
  PushChar1Bcc('P');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+1*28+2, n+8+1, 1);
}


void    ReadParam36_Pt_1Direction(void)
{
  InitPop(1);

  mpreParam[PAR_P] = PopDoubleQ()*1000;
}



void    QueryParam36_Pt_2Directions(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('P');
  PushChar1Bcc('O');
  PushChar1Bcc('W');
  PushChar1Bcc('E');
  PushChar1Bcc('P');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+2*28+2, n+8+1, 2);
}


void    ReadParam36_Pt_2Directions(void)
{
  InitPop(1);

  mpreParam[PAR_P] = PopDoubleQ()*1000 - PopDoubleQ()*1000;
}



void    QueryParam36_P123(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('P');
  PushChar1Bcc('O');
  PushChar1Bcc('W');
  PushChar1Bcc('P');
  PushChar1Bcc('P');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+3*28+2, n+8+1, 3);
}


void    ReadParam36_P123(void)
{
  InitPop(1);

  mpreParam[PAR_P1] = PopDoubleQ_WithSign()*1000;
  mpreParam[PAR_P2] = PopDoubleQ_WithSign()*1000;
  mpreParam[PAR_P3] = PopDoubleQ_WithSign()*1000;
}



void    QueryParam36_Qt(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('P');
  PushChar1Bcc('O');
  PushChar1Bcc('W');
  PushChar1Bcc('E');
  PushChar1Bcc('Q');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+2*28+2, n+8+1, 2);
}


void    ReadParam36_Qt(void)
{
  InitPop(1);

  mpreParam[PAR_Q] = PopDoubleQ()*1000 - PopDoubleQ()*1000;
}



void    QueryParam36_Q123(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('P');
  PushChar1Bcc('O');
  PushChar1Bcc('W');
  PushChar1Bcc('P');
  PushChar1Bcc('Q');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+3*28+2, n+8+1, 3);
}


void    ReadParam36_Q123(void)
{
  InitPop(1);

  mpreParam[PAR_Q1] = PopDoubleQ_WithSign()*1000;
  mpreParam[PAR_Q2] = PopDoubleQ_WithSign()*1000;
  mpreParam[PAR_Q3] = PopDoubleQ_WithSign()*1000;
}



void    QueryParam36_Ct123(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('C');
  PushChar1Bcc('O');
  PushChar1Bcc('S');
  PushChar1Bcc('_');
  PushChar1Bcc('f');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+4*28+2, n+8+1, 4);
}


void    ReadParam36_Ct123(void)
{
  InitPop(1);

  mpreParam[PAR_C] = PopDoubleQ_WithSign();
  mpreParam[PAR_C1] = PopDoubleQ_WithSign();
  mpreParam[PAR_C2] = PopDoubleQ_WithSign();
  mpreParam[PAR_C3] = PopDoubleQ_WithSign();
}



void    QueryParam36_Ft(void)
{
  uchar n = PushAddress2Bcc();

  PushChar1Bcc('F');
  PushChar1Bcc('R');
  PushChar1Bcc('E');
  PushChar1Bcc('Q');
  PushChar1Bcc('U');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQuery36(1+1*28+2, n+8+1, 1);
}


void    ReadParam36_Ft(void)
{
  InitPop(1);

  mpreParam[PAR_F] = PopDoubleQ();
}
