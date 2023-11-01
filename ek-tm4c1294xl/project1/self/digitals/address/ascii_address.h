/*------------------------------------------------------------------------------
ascii_address.h

------------------------------------------------------------------------------*/

extern  line                    mpphAsciiAddress[bCANALS];
extern  cache const             chAsciiAddress;

extern  bool                    fHexAddresses;
extern  cache const             chHexAddresses;



void    InitAsciiAddress(void);
void    ResetAsciiAddress(void);
