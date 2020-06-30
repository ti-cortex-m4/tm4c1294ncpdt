/*------------------------------------------------------------------------------
dlms_read_register.h


------------------------------------------------------------------------------*/

#include "caller39.h"



double2 ReadRegisterScalerDLMS(void);

double2 ReadRegisterValue39(const obis_t  obis, caller39*  pc);
double2 ReadRegisterScaler39(const obis_t  obis, caller39*  pc);

double2 ReadRegisterValueWithScaler39(const obis_t  obis, caller39*  pc);
