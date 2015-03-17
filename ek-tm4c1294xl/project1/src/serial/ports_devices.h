/*------------------------------------------------------------------------------
PORTS_DEVICES.H


------------------------------------------------------------------------------*/

void    Query(uint  cwIn, uchar  cbOut, bool  fMinor);
void    QueryIO(uint  cwIn, uchar  cbOut);

serial  Input(void);

void    TestResult(uchar  bT);
