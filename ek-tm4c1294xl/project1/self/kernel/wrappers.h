/*------------------------------------------------------------------------------
WRAPPERS,H


------------------------------------------------------------------------------*/

#ifndef __WRAPPERS
#define __WRAPPERS


#define ERROR_NOT_PRESENTED     3


typedef struct
{
  bool          fValue;
  bool          fValid;
} bool2;


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
  uchar         bError;
} float2;


typedef struct
{
  double        dbValue;
  bool          fValid;
  uchar         bError;
} double2;


typedef struct
{
  time          tiValue;
  bool          fValid;
  uchar         bError;
} time2;


typedef struct
{
  factors       fcValue;
  bool          fValid;
} factors2;


bool2   GetBool2(bool  fValue, bool  fValid);
bool2   GetBool2Error(void);

schar2  GetSChar2(schar  bValue, bool  fValid);
schar2  GetSChar2Error(void);

ulong2  GetLong2(ulong  dwValue, bool  fValid);
ulong2  GetLong2Error(void);

ulong64_ GetULong64(uint64_t  ddwValue, bool  fValid, uchar  bError);
ulong64_ GetULong64Ok(uint64_t  ddwValue);
ulong64_ GetULong64Error(uchar  bError);

slong64_ GetSLong64(int64_t  ddwValue, bool  fValid, uchar  bError);
slong64_ GetSLong64Ok(int64_t  ddwValue);
slong64_ GetSLong64Error(uchar  bError);

float2  GetFloat2(float  flValue, bool  fValid);
float2  GetFloat0(float  flValue);
float2  GetFloat2Error(void);
float2  GetFloat2Error1(uchar  bError);

double2 GetDouble2(double  dbValue, bool  fValid);
double2 GetDouble0(double  dbValue);
double2 GetDouble2Error(void);
double2 GetDouble2Error1(uchar  bError);

time2   GetTime2(time  tiValue, bool  fValid);
time2   GetTime0(time  tiValue);
time2   GetTime2Error(void);
time2   GetTime2Error1(uchar  bError);

factors2 GetFactors2(factors  fcValue, bool  fValid);
factors2 GetFactors2Error(void);

#endif
