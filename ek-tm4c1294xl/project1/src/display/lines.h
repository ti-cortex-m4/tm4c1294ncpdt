/*------------------------------------------------------------------------------
LINES.H


------------------------------------------------------------------------------*/

extern  uchar const             szDigits[0x10];



void    ShiftHi(uchar  ibBeg, uchar  ibEnd);
void    ShiftLo(uchar  ibBeg, uchar  ibEnd);
uchar   ToChar(uchar  chT);

ulong   GetLongHi(uchar  ibBeg, uchar  ibEnd);
ulong   GetLong(uchar  ibBeg, uchar  ibEnd);
uint    GetInt(uchar  ibBeg, uchar  ibEnd);
uchar   GetChar(uchar  ibBeg, uchar  ibEnd);
real    *PGetReal(uchar  ibBeg, uchar  ibEnd);

void    Hi(uchar  i, uchar  bT);
void    Lo(uchar  i, uchar  bT);

uchar   FromBCD(uchar  bT);
uchar   ToBCD(uchar  bT);
