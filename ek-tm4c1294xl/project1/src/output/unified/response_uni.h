/*------------------------------------------------------------------------------
RESPONSE_UNI.H


------------------------------------------------------------------------------*/

void    RunResponseUNI_All(void);

void    Output2(uint  wSize);
void    Output2_Code(uint  wSize, uchar  bCode, time  *mptiCode);
void    Result2(uchar  bT);
void    Result2_Info(uchar  bT, uchar  bInfo);
void    Common2(void  *pbData, uint  wSize);

//void    SetDelayUni(void);
//
//bit     GetDefCan(uchar  ibCanal);
//bit     GetDefGrp(uchar  ibGroup);
//
//void    PushRealUni(status4  status, real  *preT);
