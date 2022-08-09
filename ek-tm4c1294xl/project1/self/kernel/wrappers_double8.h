/*------------------------------------------------------------------------------
WRAPPERS,H


------------------------------------------------------------------------------*/

#ifndef __WRAPPERS_DOUBLE8
#define __WRAPPERS_DOUBLE8


typedef struct
{
  double        mdbValue[8];
  bool          fValid;
  uchar         bError;
} double8;


double8 GetDouble8(double  mdbValue[8], bool  fValid);
double8 GetDouble8Ok(double  mdbValue[8]);
double8 GetDouble8Error(void);
double8 GetDouble8Error1(uchar  bError);


#endif
