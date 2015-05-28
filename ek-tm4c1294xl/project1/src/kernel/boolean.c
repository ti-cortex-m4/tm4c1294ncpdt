/*------------------------------------------------------------------------------
BOOLEAN,Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "boolean.h"



bool    ValidBoolean(uchar  b)
{
  return (b == true) || (b == false);
}


bool    CharToBoolean(uchar  b)
{
  return (b == true ? true : false);
}


bool    InvertBoolean(bool  bo)
{
  return (bo == true ? false : true);
}
