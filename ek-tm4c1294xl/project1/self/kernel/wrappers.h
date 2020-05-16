/*------------------------------------------------------------------------------
WRAPPERS,H


------------------------------------------------------------------------------*/

#ifndef __WRAPPERS
#define __WRAPPERS


typedef struct
{
  ulong         dwValue;
  bool          fValid;
} ulong2;


typedef struct
{
  uint64_t      ddwValue;
  bool          fValid;
} ulonglong2;


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


typedef struct
{
  time          tiValue;
  bool          fValid;
} time2;


typedef struct
{
  factors       fcValue;
  bool          fValid;
} factors2;



ulong2  GetLong2(ulong  dwValue, bool  fValid);
ulong2  GetLong2Error(void);

ulonglong2 GetLongLong2(uint64_t  ddwValue, bool  fValid);
ulonglong2 GetLongLong2Error(void);

float2  GetFloat2(float  flValue, bool  fValid);
float2  GetFloat2Error(void);

double2 GetDouble2(double  dbValue, bool  fValid);
double2 GetDouble2Error(void);

time2   GetTime2(time  tiValue, bool  fValid);
time2   GetTime2Error(void);

factors2 GetFactors2(factors  fcValue, bool  fValid);
factors2 GetFactors2Error(void);

#endif
