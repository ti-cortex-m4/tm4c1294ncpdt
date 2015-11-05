/*------------------------------------------------------------------------------
SERIAL4.H


------------------------------------------------------------------------------*/

#define wINBUFF_SIZE    0x1000
#define wOUTBUFF_SIZE   0x1000



extern volatile uchar          mpbIn[wINBUFF_SIZE], mpbOut[wOUTBUFF_SIZE];

extern volatile uint           iwOutStart, iwOutStop, cwOut;
extern volatile uint           iwInStart, iwInStop, cwIn;
