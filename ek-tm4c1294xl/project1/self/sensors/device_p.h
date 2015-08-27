/*------------------------------------------------------------------------------
DEVICE_P.H
              
 
------------------------------------------------------------------------------*/

#ifndef SKIP_P

uchar   PopChar1Els(void);
uint    PopChar4Els(void);
void    QueryCloseP(void);
void    QueryOpenP(void);
void    QueryCorrectP(void);
void    QueryTimeP(void);
void    ReadTimeAltP(void);
void    QueryEngAbsP(uchar  bPart);
void    ReadEngAbsP(uchar  bPart);
void    ReadEngAbsP_RD(void);
void    QueryTransP(void);
void    ReadTransP(void);
void    QueryModeP(void);
void    QueryPasswordP(void);
void    QueryRepasswordP(void);
void    QueryRegisterP(void);
void    ReadRegisterP(void);
void    Setup1P(void);
void    QuerySetValueP(void);
void    QueryGetValueP(void);
void    ReadGetValueP(void);
void    QueryProfileP(void);
void    Setup2P(void);
void    ReadProfileP(void);
bool    BreakP(void);
void    ReadCurrentP(void);
bool    QueryEnergyP_Full(uchar  bPart);

#endif

