/*------------------------------------------------------------------------------
MAIN_PARAMS,H


------------------------------------------------------------------------------*/

#include "main_basic.h"



// тип мгновенного параметра
typedef enum
{
  PAR_P                 = 10,
  PAR_P1                = 11,
  PAR_P2                = 12,
  PAR_P3                = 13,

  PAR_Q                 = 20,
  PAR_Q1                = 21,
  PAR_Q2                = 22,
  PAR_Q3                = 23,

  PAR_S                 = 30,
  PAR_S1                = 31,
  PAR_S2                = 32,
  PAR_S3                = 33,

  PAR_U                 = 40,
  PAR_U1                = 41,
  PAR_U2                = 42,
  PAR_U3                = 43,

  PAR_I                 = 50,
  PAR_I1                = 51,
  PAR_I2                = 52,
  PAR_I3                = 53,

  PAR_C                 = 60,
  PAR_C1                = 61,
  PAR_C2                = 62,
  PAR_C3                = 63,

  PAR_F                 = 70,
  PAR_F1                = 71,
  PAR_F2                = 72,
  PAR_F3                = 73
} param;
