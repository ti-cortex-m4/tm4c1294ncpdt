/*------------------------------------------------------------------------------
query_params_39.h


------------------------------------------------------------------------------*/

void    QueryGetRegisterValueDLMS(const obis_t  obis, runner39  r);
void    QueryGetRegisterSDLMS(const obis_t  obis, runner39  r);
void    QueryGetScalerDLMS(const obis_t  obis, uchar  bNS, uchar  bNR, uchar  bInvokeId);
uint    ReadType18ULong16(void);

ulong64_ ReadValueX(void);
schar2  ReadRegisterScaler(void);
