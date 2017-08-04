/*------------------------------------------------------------------------------
PARITY,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "parity.h"



static char const       mpbNibbleParity[16] = {
                          0, 1, 1, 0,
                          1, 0, 0, 1,
                          1, 0, 0, 1,
                          0, 1, 1, 0 };



bool    EvenParity(uchar  b)
{
  return mpbNibbleParity[b & 0xf] ^ mpbNibbleParity[(b >> 4) & 0xf];
}


bool    OddParity(uchar  b)
{
  return !EvenParity(b);
}
