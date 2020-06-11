/*------------------------------------------------------------------------------
buffer_profile_39.h


------------------------------------------------------------------------------*/

void    InitBuffPrf38(void);
void    AddBuffPrf38(time  tiTime, uint64_t  ddwValue);

void    DeltaBuffPrf38(void);
profile39 GetBuffPrf38(uchar  i);
uchar   GetBuffPrfSize38(void);
bool    GetBuffPrfOveflow38(void);
