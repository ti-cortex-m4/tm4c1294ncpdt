/*------------------------------------------------------------------------------
query_params_39.h


------------------------------------------------------------------------------*/

void    QueryGetRegisterValueDLMS(const obis_t  obis, runner39  r);
void    QueryGetRegisterScalerDLMS(const obis_t  obis, runner39  r);

uint    ReadType18ULong16(void);

ulong2  ReadValueX(void);
schar2  ReadRegisterScaler(void);
