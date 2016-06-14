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


uchar2 GetChar2Success(uchar b);
uchar2 GetChar2Error(void);
bool InvalidChar2(uchar2 b2);

uint2 GetInt2Success(uint w);
uint2 GetInt2Error(void);
bool InvalidInt2(uint2 w2);

ulong2 GetLong2Success(ulong dw);
ulong2 GetLong2Error(void);
bool InvalidLong2(ulong2 dw2);

err_t GetSuccess(void);
err_t GetError(void);

#endif
