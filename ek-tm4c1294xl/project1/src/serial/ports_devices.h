/*------------------------------------------------------------------------------
PORTS_DEVICES.H


------------------------------------------------------------------------------*/

void    Query(uint  cwIn, uchar  cbOut, bool  fMinor);

void    QueryIO(uint  cwIn, uchar  cbOut);
serial  Input(void);

void    RevQueryIO(uint  cwIn, uchar  cbOut);
bool    RevLinkErrors(void);
serial  RevInput(void);

void    ChecksumError(void);
void    TestResult(uchar  bT);
