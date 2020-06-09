/*------------------------------------------------------------------------------
buffer_profile_38.h


------------------------------------------------------------------------------*/

void    InitPrfBuff38(void);
void    AddPrfBuff38(time  ti, uint64_t  ddw);

profile38 GetPrf38(uchar i);
uchar   GetPrfSize38(void);
bool    GetPrfOveflow38(void);
