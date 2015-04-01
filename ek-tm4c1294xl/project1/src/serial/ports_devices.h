/*------------------------------------------------------------------------------
PORTS_DEVICES.H


------------------------------------------------------------------------------*/

void    Query(uint  cwIn, uchar  cbOut, bool  fMinor);

void    QueryIO(uint  cwIn, uchar  cbOut);
serial  Input(void);

void    RevQueryIO(uint  cwIn, uchar  cbOut);
serial  RevInput(void);

void    TestResult(uchar  bT);
