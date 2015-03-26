/*------------------------------------------------------------------------------
DEVICE_B.H
              
 
------------------------------------------------------------------------------*/

#ifndef SKIP_B

//bit     ReadAddressB(void);
bool    ReadResultB(void);

void    QueryOpenB(void);

//void    QueryVersionB(void);
//void    ReadVersionB(void);
//bit     TestVersionB710(void);

void    QueryIdB(void);
bool    ReadIdB(void);

void    QueryEnergyB(uchar  bTime);
void    ReadEnergyB(void);

//void    QueryControlB(void);
////void    QueryManageB(void);

void    QueryTimeB(void);
void    ReadTimeAltB(void);
//void    ReadTimeDigB(void);
//
//void    QueryTopB(void);
//void    ReadTopBOld(void);
//
//void    QueryHeaderB(void);
//void    QueryHeaderB_Plus(uchar  bSize);
//bit     TestHeaderB(uchar  ibBlock);
//bit     ReadHeaderB(uchar  ibBlock, bit  fDelay);

void    ReadCurrentB(void);

#endif
