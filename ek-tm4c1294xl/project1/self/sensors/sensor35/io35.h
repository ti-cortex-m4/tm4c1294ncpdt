/*------------------------------------------------------------------------------
IO35!H


------------------------------------------------------------------------------*/

#define NNCL2_DATA_SET  17
#define NNCL2_DATA_GET  18
#define NNCL2_TIME      20
#define NNCL2_ERROR     31



void    Query35Internal(uchar  cbIn, uchar  cbOut, uchar  bCommand);
void    Query35Repeat(void);
void    Query35(uchar  cbIn, uchar  cbOut);

serial  Input35(void);
