/*------------------------------------------------------------------------------
UNI_EVENTS0.H


------------------------------------------------------------------------------*/

uint    GetPagesCount(uchar  ibClass);
uint    GetMaxRecordsCount(uchar  ibClass);
uint    GetRecordsCount(uchar  ibClass);
void    LoadEventsPage(uchar  ibClass, uint  iwPage);
time    ReadEventBlock(uchar  ibBlock);
