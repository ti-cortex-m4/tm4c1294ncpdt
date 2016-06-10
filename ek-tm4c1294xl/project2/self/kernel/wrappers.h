/*------------------------------------------------------------------------------
wrappers.h


------------------------------------------------------------------------------*/

#ifndef __WRAPPERS
#define __WRAPPERS


#include "lwip/err.h"



typedef struct
{
  uchar          b;
  err_t          err2;
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
bool InvalidChar2(uchar2 b2);

uint2 GetInt2(uint w, err_t err);
uint2 GetInt2Error(void);
bool InvalidInt2(uint2 w2);

ulong2 GetLong2(ulong dw, err_t err);
ulong2 GetLong2Error(void);
bool InvalidLong2(ulong2 dw2);

#endif
