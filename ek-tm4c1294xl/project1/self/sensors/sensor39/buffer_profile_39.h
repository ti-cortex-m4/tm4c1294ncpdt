/*------------------------------------------------------------------------------
buffer_profile_39.h


------------------------------------------------------------------------------*/

void    InitBuffPrf39(void);
void    AddBuffPrf39(time  tiTime, uint64_t  ddwValue);

void    DeltaBuffPrf39(void);
profile39 GetBuffPrf39(uchar  i);
uchar   GetBuffPrfSize39(void);
bool    GetBuffPrfOveflow39(void);
