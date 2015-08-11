/*------------------------------------------------------------------------------
FLOAT,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "float.h"



bool    IsFloatNAN(float  fl)
{
  combo32 co;
  co.flBuff = fl;
  return co.dwBuff == 0xFFFFFFFF;
}


float   GetFloatNAN(void)
{
  combo32 co;
  co.dwBuff = 0xFFFFFFFF;
  return co.flBuff;
}


bool    ValidFloat(float  fl)
{
  return !IsFloatNAN(fl);
}



double  GetDoubleNAN(void)
{
  combo64 co;
  co.qwBuff = 0xFFFFFFFFFFFFFFFF;
  return co.dbBuff;
}
