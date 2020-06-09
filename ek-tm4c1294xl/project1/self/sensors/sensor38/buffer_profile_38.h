/*------------------------------------------------------------------------------
buffer_profile_38.h


------------------------------------------------------------------------------*/

void    InitBuffPrf38(void);
void    AddBuffPrf38(time  tiTime, uint64_t  ddwValue);

profile38 GetBuffPrf38(uchar  i);
uchar   GetBuffPrfSize38(void);
bool    GetBuffPrfOveflow38(void);
