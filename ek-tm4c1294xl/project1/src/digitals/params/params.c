/*------------------------------------------------------------------------------
PARAMS,C

 ћгновенные параметры
------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "../../display/display.h"
#include    "../../flash/files.h"
#include    "../../nvram/cache.h"
#include    "params.h"



param const             mppaParamsLines[bPARAM_BLOCK] =
{
  PAR_P , PAR_P1 , PAR_P2 , PAR_P3 ,
  PAR_Q , PAR_Q1 , PAR_Q2 , PAR_Q3 ,
  PAR_S , PAR_S1 , PAR_S2 , PAR_S3 ,
  PAR_U , PAR_U1 , PAR_U2 , PAR_U3 ,
  PAR_I , PAR_I1 , PAR_I2 , PAR_I3 ,
  PAR_C , PAR_C1 , PAR_C2 , PAR_C3 ,
  PAR_F , PAR_F1 , PAR_F2 , PAR_F3 ,
  (param) 0
};



cache const             chParamsFlag = {PARAMS_FLAG, &boParamsFlag, sizeof(bool)};
cache const             chMntParams = {MNT_PARAMS, &boMntParams, sizeof(bool)};

file const              flParams = {PARAMS, &mpdiParam, sizeof(mpdiParam)};
file const              flParamsDiv = {PARAMS_DIV, &mpreParamsDiv, sizeof(mpreParamsDiv)};
file const              flEnblParams = {ENBL_PARAMS, &mpboEnblParams, sizeof(mpboEnblParams)};

file const              flFixParamsBugs = {FIX_PARAMS_BUGS, &boFixParamsBugs, sizeof(bool)};
file const              flUseParamsDiv = {USE_PARAMS_DIV, &boUseParamsDiv, sizeof(bool)};



void    InitParams(void)
{
  LoadCache(&chParamsFlag);
  LoadCache(&chMntParams);

  LoadFile(&flParams);
  LoadFile(&flParamsDiv);
  LoadFile(&flEnblParams);

  LoadFile(&flFixParamsBugs);
  LoadFile(&flUseParamsDiv);
}


void    ResetParams(void)
{
  boParamsFlag = false;
  SaveCache(&chParamsFlag);

  boMntParams = false;
  SaveCache(&chMntParams);

  memset(&mpdiParam, 0, sizeof(mpdiParam));
  SaveFile(&flParams);


  uint i;
  for (i=0; i<wPARAMS; i++)
  {
    mpreParamsDiv[i] = 1;
    mpboEnblParams[i] = true;
  }

  SaveFile(&flParamsDiv);
  SaveFile(&flEnblParams);


  boFixParamsBugs = false;
  SaveFile(&flFixParamsBugs);

  boUseParamsDiv = false;
  SaveFile(&flUseParamsDiv);
}



void    LoadCurrParam(uint  iwPrm)
{
  diCurr = mpdiParam[iwPrm];
}



bool    ValidParam(digital  *pdi)
{
  return true;
}


bool    ValidParamLine(uchar  ibLine)
{
  switch (ibLine)
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
    case PAR_S3 :

    case PAR_U  :
    case PAR_U1 :
    case PAR_U2 :
    case PAR_U3 :

    case PAR_I  :
    case PAR_I1 :
    case PAR_I2 :
    case PAR_I3 :

    case PAR_C  :
    case PAR_C1 :
    case PAR_C2 :
    case PAR_C3 :

    case PAR_F  :
    case PAR_F1 :
    case PAR_F2 :
    case PAR_F3 : return true;

    default:      return false;
   }
}



void    SetParam(uint  iwPrm, digital  *pdi)
{
  mpdiParam[iwPrm] = *pdi;
  SaveFile(&flParams);
}



uchar   GetParamPort(uint  iwPrm)
{
  return mpdiParam[iwPrm].ibPort;
}


uchar   GetParamPhone(uint  iwPrm)
{
  return mpdiParam[iwPrm].ibPhone;
}


uchar   GetParamDevice(uint  iwPrm)
{
  return mpdiParam[iwPrm].bDevice;
}


uchar   GetParamAddress(uint  iwPrm)
{
  return mpdiParam[iwPrm].bAddress;
}


uchar   GetParamLine(uint  iwPrm)
{
  return mpdiParam[iwPrm].ibLine;
}



void    ShowParam(uint  iwPrm)
{
  Clear();
  sprintf(szLo,"%1u.%02u.%02u.%03u.%02u",
               GetParamPort(iwPrm) + 1,
               GetParamPhone(iwPrm),
               GetParamDevice(iwPrm),
               GetParamAddress(iwPrm),
               GetParamLine(iwPrm));

  sprintf(szHi+13,"%03u",iwPrm + 1);

  (mpboEnblParams[iwPrm] == true) ? (szHi[12] = '+') : (szHi[12] = '-');
}

