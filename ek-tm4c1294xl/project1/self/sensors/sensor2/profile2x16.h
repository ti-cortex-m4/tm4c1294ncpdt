/*------------------------------------------------------------------------------
PROFILE2X16!H


------------------------------------------------------------------------------*/

#ifndef __PROFILE2X16
#define __PROFILE2X16


#define PROFILE2X16_SIZE    16

#define PROFILE2X16_1       0
#define PROFILE2X16_16      1
#define PROFILE2X16_AUTO    2


#endif



extern  char const              szProfile2x1[],
                                szProfile2x16[];



void    QueryTopBx16(void);
void    ReadTopBx16(void);

void    QueryHeaderBx16(void);
bool    ReadHeaderBx16(uchar  ibBlock, bool  fDelay);
