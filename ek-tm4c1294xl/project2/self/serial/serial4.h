/*------------------------------------------------------------------------------
SERIAL1!H


------------------------------------------------------------------------------*/

#include <stdint.h>

#define wINBUFF_SIZE    0x1000
#define wOUTBUFF_SIZE   0x1000

extern volatile u8_t                    mpbIn[wINBUFF_SIZE], mpbOut[wOUTBUFF_SIZE];

extern volatile uint32_t                   iwOutStart,iwOutStop,cwOut;
extern volatile uint32_t                   iwInStart,iwInStop,cwIn;
