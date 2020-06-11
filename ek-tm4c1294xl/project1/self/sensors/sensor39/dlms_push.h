/*------------------------------------------------------------------------------
dlms_push.h


------------------------------------------------------------------------------*/

void    PushFormatDLMS(uint  wSize);
void    PushOBIS_DLMS(const obis_t  obis);
void    PushTimeMonthYearDLMS(uchar  bMonth, uchar  bYear);
void    PushTimeDLMS(time  ti);
