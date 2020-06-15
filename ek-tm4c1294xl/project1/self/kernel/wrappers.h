/*------------------------------------------------------------------------------
WRAPPERS,H


------------------------------------------------------------------------------*/

#ifndef __WRAPPERS
#define __WRAPPERS


typedef struct
{
  schar         bValue;
  bool          fValid;
} schar2;


typedef struct
{
  ulong         dwValue;
  bool          fValid;
} ulong2;


typedef struct
{
  uint64_t      ddwValue;
  bool          fValid;
  uchar         bError;
} ulong64_;


typedef struct
{
  int64_t       ddwValue;
  bool          fValid;
  uchar         bError;
} slong64_;


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



schar2  GetSChar2(schar  bValue, bool  fValid);
schar2  GetSChar2Error(void);

ulong2  GetLong2(ulong  dwValue, bool  fValid);
ulong2  GetLong2Error(void);

ulong64_ GetLong64(uint64_t  ddwValue, bool  fValid, uchar  bError);
ulong64_ GetLong64Error(uchar  bError);

slong64_ GetSignedLong64(int64_t  ddwValue, bool  fValid, uchar  bError);
slong64_ GetSignedLong64Error(uchar  bError);

float2  GetFloat2(float  flValue, bool  fValid);
float2  GetFloat2Error(void);

double2 GetDouble2(double  dbValue, bool  fValid);
double2 GetDouble2Error(void);

time2   GetTime2(time  tiValue, bool  fValid);
time2   GetTime2Error(void);

factors2 GetFactors2(factors  fcValue, bool  fValid);
factors2 GetFactors2Error(void);

#endif
