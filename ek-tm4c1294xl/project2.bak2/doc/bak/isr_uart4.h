#if 0
/*------------------------------------------------------------------------------
ISR_UART4,H


------------------------------------------------------------------------------*/

#define INBUFF_SIZE     0x800
#define OUTBUFF_SIZE    0x800



extern volatile uchar          mbIn[INBUFF_SIZE], mbOut[OUTBUFF_SIZE];

extern volatile uint           iwOutStart, iwOutStop, cwOut;
extern volatile uint           iwInStart, iwInStop, cwIn;

extern volatile uint           wInTimer;
#endif
