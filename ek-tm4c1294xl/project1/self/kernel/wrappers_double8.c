/*------------------------------------------------------------------------------
WRAPPERS_DOUBLE8,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "wrappers_double8.h"



double8 GetDouble8(double  mdbValue[8], bool  fValid)
{
  double8 db8;

  db8.mdbValue = mdbValue;
  db8.fValid = fValid;
  db8.bError = 0;

  return db8;
}


double8 GetDouble8Ok(double  mdbValue[8])
{
  return GetDouble8(mdbValue, true);
}


double8 GetDouble8Error(void)
{
  return GetDouble8(-1, false);
}


double8 GetDouble8Error1(uchar  bError)
{
  double8 db8;

  db8.mdbValue = {-1, -1, -1, -1, -1, -1, -1, -1};
  db8.fValid = false;
  db8.bError = bError;

  return db8;
}
