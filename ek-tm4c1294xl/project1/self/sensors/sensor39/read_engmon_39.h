/*------------------------------------------------------------------------------
query_engmon_39.h


------------------------------------------------------------------------------*/

#include "device39_obis.h"



void    QueryEngMon39(const obis_t  obis, uchar  bNS, uchar  bNR, uchar  bInvokeId, uchar  bMonth, uchar  bYear);
uint64_t ReadEngMon39(void);

uchar   IsEngMonPresent39(void);
uchar   IsEngMonAbsent39(void);
