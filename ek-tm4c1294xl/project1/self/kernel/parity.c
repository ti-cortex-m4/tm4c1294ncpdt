/*------------------------------------------------------------------------------
PARITY,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "parity.h"



static char const       nibble_parity[16] = {
                          0, 1, 1, 0,
                          1, 0, 0, 1,
                          1, 0, 0, 1,
                          0, 1, 1, 0 };



char    calc_even_parity(uchar  b)
{
  return nibble_parity[b & 0xf] ^ nibble_parity[(b >> 4) & 0xf];
}


char    calc_odd_parity(uchar  b)
{
  return !calc_even_parity(b);
}
