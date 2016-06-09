/*------------------------------------------------------------------------------
wrappers.h


------------------------------------------------------------------------------*/

#ifndef __WRAPPERS
#define __WRAPPERS


#include "lwip/err.h"



typedef struct
{
  uchar          b;
  err_t          err;
} uchar2;

typedef struct
{
  uint           w;
  err_t          err;
} uint2;

typedef struct
{
  ulong          dw;
  err_t          err;
} ulong2;


uchar2 GetChar2(uchar b, err_t err);
uchar2 GetChar2Error(void);

uint2 GetInt2(uint w, err_t err);
uint2 GetInt2Error(void);

ulong2 GetLong2(ulong dw, err_t err);
ulong2 GetLong2Error(void);


#endif
