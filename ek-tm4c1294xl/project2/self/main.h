/*------------------------------------------------------------------------------
MAIN.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_H__
#define __MAIN_H__


#include <stdbool.h>
#include <stdint.h>


typedef uint8_t         uchar;
typedef uint16_t        uint;
typedef uint32_t        ulong;


typedef union
{
  uchar         mpbBuff[4];
  ulong         dwBuff;
} combo32;


#define ERR_SIZE       -20   /* Message size too small.  */
#define ERR_CODE       -21   /* No message code.         */
#define ERR_SKIP       -22   /* Skip message.            */


#endif
