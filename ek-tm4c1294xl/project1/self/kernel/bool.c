/*------------------------------------------------------------------------------
BOOL.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "bool.h"



bool    ValidBool(uchar  b)
{
  return (b == true) || (b == false);
}


bool    CharToBool(uchar  b)
{
  return (b == 0xFF ? true : false);
}


bool    InvertBool(bool  f)
{
  return (f == true ? false : true);
}
