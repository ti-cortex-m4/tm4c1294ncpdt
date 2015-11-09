/*------------------------------------------------------------------------------
SERIAL4.H


------------------------------------------------------------------------------*/

#define INBUFF_SIZE     0x1000
#define OUTBUFF_SIZE    0x1000



extern volatile uchar          mpbIn[INBUFF_SIZE], mpbOut[OUTBUFF_SIZE];

extern volatile uint           iwOutStart, iwOutStop, cwOut;
extern volatile uint           iwInStart, iwInStop, cwIn;

extern volatile ulong          dwInTimer;
