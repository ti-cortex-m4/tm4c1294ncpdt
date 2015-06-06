/*------------------------------------------------------------------------------
BOOLEAN,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "boolean.h"



bool    ValidBoolean(uchar  b)
{
  return (b == TRUE) || (b == FALSE);
}


boolean CharToBoolean(uchar  b)
{
  return (b == TRUE ? TRUE : FALSE);
}


boolean InvertBoolean(boolean  bo)
{
  return (bo == TRUE ? FALSE : TRUE);
}
