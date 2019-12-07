/*------------------------------------------------------------------------------
auto_transit.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "auto_transit.h"



auto_transit            stAutoTransit;
cache const             chAutoTransit = {AUTO_TRANSIT, &stAutoTransit, sizeof(stAutoTransit)};
