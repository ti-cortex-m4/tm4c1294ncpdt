/*------------------------------------------------------------------------------
WRAPPERS,H


------------------------------------------------------------------------------*/

#ifndef __WRAPPERS
#define __WRAPPERS


typedef struct
{
  float         flValue;
  bool          fValid;
} float2;


typedef struct
{
  double        dbValue;
  bool          fValid;
} double2;



float2  GetFloat2(float  flValue, bool  fValid);
double2 GetDouble2(double  dbValue, bool  fValid);


#endif
