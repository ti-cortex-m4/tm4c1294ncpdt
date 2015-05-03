/*------------------------------------------------------------------------------
BOOLEAN.Ñ


------------------------------------------------------------------------------*/

#include "../main.h"



boolean CharToBoolean(uchar  b)
{
  return (b == TRUE ? TRUE : FALSE);
}


boolean InvertBoolean(boolean  bo)
{
  return (bo == TRUE ? FALSE : TRUE);
}
