/*------------------------------------------------------------------------------
OLDTARIFFS.H

 Подпрограммы управления тарифами (старый вариант)
------------------------------------------------------------------------------*/

#include        "../main.h"



extern  bool                    fEnergy;



void    MakeAllOldModes(uchar  bT);

void    SetCharEngMonths(uchar  ibBeg, uchar  ibEnd);
void    SetCharPowMonths(uchar  ibBeg, uchar  ibEnd);
