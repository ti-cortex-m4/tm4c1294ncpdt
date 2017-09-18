/*------------------------------------------------------------------------------
PARAMS_U,C


------------------------------------------------------------------------------*/

#include "../../main.h"




void    QueryParamU1(void)
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

  BccQueryIO(1+3*28+2, n+8+1, 3);
}


void    ReadParamU1(void)
{
  InitPop(1);

  mpreParam[PAR_I1] = PopDoubleQ()*1000;
  mpreParam[PAR_I2] = PopDoubleQ()*1000;
  mpreParam[PAR_I3] = PopDoubleQ()*1000;
}



void    QueryParamU2(void)
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

  BccQueryIO(1+3*28+2, n+8+1, 3);
}


void    ReadParamU2(void)
{
  InitPop(1);

  mpreParam[PAR_U1] = PopDoubleQ();
  mpreParam[PAR_U2] = PopDoubleQ();
  mpreParam[PAR_U3] = PopDoubleQ();
}



void    QueryParamU3(void)
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

  BccQueryIO(1+3*28+2, n+8+1, 3);
}


void    ReadParamU3(void)
{
  InitPop(1);

  mpreParam[PAR_P1] = PopDoubleQ()*1000;
  mpreParam[PAR_P2] = PopDoubleQ()*1000;
  mpreParam[PAR_P3] = PopDoubleQ()*1000;
}



void    QueryParamU4(void)
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

  BccQueryIO(1+1*28+2, n+8+1, 1);
}


void    ReadParamU4(void)
{
  InitPop(1);

  mpreParam[PAR_F] = PopDoubleQ();
}
