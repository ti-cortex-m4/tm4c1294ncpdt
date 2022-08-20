/*------------------------------------------------------------------------------
dlms_read_register.h


------------------------------------------------------------------------------*/

double2 ReadRegisterScalerDLMS(void);

double2 ReadRegisterUnsignedValue39(const obis_t  obis, caller39*  pc);
double2 ReadRegisterSignedValue39(const obis_t  obis, caller39*  pc);
double2 ReadRegisterScaler39(const obis_t  obis, caller39*  pc);

double2 ReadRegisterUnsignedValueWithScaler39(const obis_t  obis, caller39*  pc);
double2 ReadRegisterSignedValueWithScaler39(const obis_t  obis, caller39*  pc);
