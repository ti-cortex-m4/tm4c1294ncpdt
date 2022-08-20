/*------------------------------------------------------------------------------
PROFILE2X16!H


------------------------------------------------------------------------------*/

#ifndef __PROFILE2X16
#define __PROFILE2X16


#define PROFILE2X16_SIZE    16


#endif



extern  char const              szProfile2x1[],
                                szProfile2x16[];



void    QueryHeaderBx16(void);
bool    ReadHeaderBx16(uchar  ibBlock, bool  fDelay);
