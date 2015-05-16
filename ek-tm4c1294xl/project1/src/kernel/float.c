/*------------------------------------------------------------------------------
FLOAT,Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "float.h"



bool    IsFloatNAN(float  fl)
{
  combo32 co;
  co.reBuff = fl;
  return co.dwBuff == 0xFFFFFFFF;
}


float   GetFloatNAN(void)
{
  combo32 co;
  co.dwBuff = 0xFFFFFFFF;
  return co.reBuff;
}


bool    ValidFloat(float  fl)
{
  return !IsFloatNAN(fl);
}



float   DoubleToFloat(double  db)
{
  return (float)db;
}
