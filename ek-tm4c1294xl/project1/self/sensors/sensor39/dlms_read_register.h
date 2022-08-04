/*------------------------------------------------------------------------------
dlms_read_register.h


------------------------------------------------------------------------------*/

double2 ReadRegisterScalerDLMS(void);

double2 ReadRegisterUnsignedValue39(const obis_t  obis, caller39*  pc);
double2 ReadRegisterScaler39(const obis_t  obis, caller39*  pc);

double2 ReadRegisterValueWithScaler39(const obis_t  obis, caller39*  pc);
double2 ReadRegisterValueWithScaler39_Signed(const obis_t  obis, caller39*  pc);
