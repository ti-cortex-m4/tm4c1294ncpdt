/*------------------------------------------------------------------------------
MODEMS!H


------------------------------------------------------------------------------*/

void    KeyBreakConnect(void);

uchar   GetModemAnswer(void);

void    QueryModemBaud(bool  fShow);
void    QueryModemCommon(bool  fShow);
void    QueryModemCustom(void);
void    QueryModemConnect(void);

bool    ShowModemConnect(void);

void    QueryModemEscape(void);
void    QueryModemHookOff(void);

void    ModemDTROff(void);

void    RunLocal(void);
void    RunLocal_All(void);

//bool    SafeConnect(void);
//bool    SafeDisconnect(void);

void    InitConnectKey(void);

//void    InitConnectQue(void);
//void    DoneConnectQue(void);

bool    LoadConnect(uchar  ibCanal);
void    SaveConnect(void);

bool    IsModemDisconnect(void);
