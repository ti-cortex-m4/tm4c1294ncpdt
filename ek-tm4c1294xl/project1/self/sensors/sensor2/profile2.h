/*------------------------------------------------------------------------------
PROFILE_2!H


------------------------------------------------------------------------------*/

void    QueryTopB(void);
void    ReadTopBOld(void);

void    QueryHeaderB(void);
void    QueryHeaderB_Plus(uchar  bSize);
bool    TestHeaderB(uchar  ibBlock);
bool    ReadHeaderB(uchar  ibBlock, bool  fDelay);
