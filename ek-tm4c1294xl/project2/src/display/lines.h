/*------------------------------------------------------------------------------
LINES.H


------------------------------------------------------------------------------*/

extern  uchar const             szDigits[0x10];



void    ShiftHi(uchar  ibBeg, uchar  ibEnd);
void    ShiftLo(uchar  ibBeg, uchar  ibEnd);
uchar   ToChar(uchar  chT);

ulong   GetLongHi(uchar  ibBeg, uchar  ibEnd);
ulong   GetLongLo(uchar  ibBeg, uchar  ibEnd);
uint    GetIntLo(uchar  ibBeg, uchar  ibEnd);
uchar   GetCharLo(uchar  ibBeg, uchar  ibEnd);
real    GetRealLo(uchar  ibBeg, uchar  ibEnd);

void    Hi(uchar  i, uchar  bT);
void    Lo(uchar  i, uchar  bT);

uchar   FromBCD(uchar  bT);
uchar   ToBCD(uchar  bT);
