/*------------------------------------------------------------------------------
query_params_39.h


------------------------------------------------------------------------------*/

void    QueryGetRequestDLMS(const obis_t  obis, uchar  bNS, uchar  bNR, uchar  bInvokeId);
void    QueryGetScalerDLMS(const obis_t  obis, uchar  bNS, uchar  bNR, uchar  bInvokeId);
uint    ReadType18ULong16(void);

ulong64_ ReadValueX(void);
schar2  ReadScaler(void);
