/*------------------------------------------------------------------------------
wrappers.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "wrappers.h"



static uchar2 GetChar2(uchar b, err_t err) {
  uchar2 b2;

  b2.b = b;
  b2.err = err;

  return b2;
}

uchar2 GetChar2Success(uchar b) {
  return GetChar2(b, ERR_OK);
}

uchar2 GetChar2Error(void) {
  return GetChar2(MAX_CHAR, ERR_VAL);
}

bool InvalidChar2(uchar2 b2) {
  return b2.err != ERR_OK;
}


static uint2 GetInt2(uint w, err_t err) {
  uint2 w2;

  w2.w = w;
  w2.err = err;

  return w2;
}

uint2 GetInt2Success(uint w) {
  return GetInt2(w, ERR_OK);
}

uint2 GetInt2Error(void) {
  return GetInt2(MAX_INT, ERR_VAL);
}

bool InvalidInt2(uint2 w2) {
  return w2.err != ERR_OK;
}



static ulong2 GetLong2(ulong dw, err_t err) {
  ulong2 dw2;

  dw2.dw = dw;
  dw2.err = err;

  return dw2;
}

ulong2 GetLong2Success(ulong dw) {
  return GetLong2(dw, ERR_OK);
}

ulong2 GetLong2Error(void) {
  return GetLong2(MAX_LONG, ERR_VAL);
}

bool InvalidLong2(ulong2 dw2) {
  return dw2.err != ERR_OK;
}



err_t GetSuccess(void) {
  return ERR_OK;
}

err_t GetError(void) {
  return ERR_VAL;
}
