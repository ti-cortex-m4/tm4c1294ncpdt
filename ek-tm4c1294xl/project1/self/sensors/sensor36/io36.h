/*------------------------------------------------------------------------------
IO36!H


------------------------------------------------------------------------------*/

void    Query36(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax);
void    BccQuery36(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax);

void    Query36Repeat(void);

serial  Input36_(bool  fIgnoreChecksumError);
serial  Input36(void);

bool    NoData36(void);
