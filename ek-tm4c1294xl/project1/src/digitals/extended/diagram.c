/*------------------------------------------------------------------------------
DIAGRAM.C

 График значений счетчиков по получасам за сутки
------------------------------------------------------------------------------*/

#include "../../main.h"



/*static*/ diagram          mpDiagram[bCANALS], dgBuff;



/*
void    LoadDiaHou(uint  iwHouFrom)
{
  OpenIn(wFLA_DIAGRAM + iwHouFrom/2);
  memcpy(mpDiagram, mpbPageIn + (iwHouFrom%2)*wDIAGRAM_LENGTH, wDIAGRAM_LENGTH);
}


void    SaveDiaHou(uint  iwHouTo)
{
  OpenOut(wFLA_DIAGRAM + iwHouTo/2);
  memcpy(mpbPageOut, mpbPageIn, wFREEPAGE_SIZE);
  memcpy(mpbPageOut + (iwHouTo%2)*wDIAGRAM_LENGTH, mpDiagram, wDIAGRAM_LENGTH);
  CloseOut();
}



void    NextHouDiagram(void)
{
  LoadDiaHou(iwHardHou);

  memset(&mpDiagram, 0xFF, sizeof(mpDiagram));

  for (ibCan=0; ibCan<16; ibCan++)
  {
    if (GetDigitalDevice(ibCan) == 0)
    {
      reBuffA  = *PGetCanImpAll(mpimAbsCan,ibCan);
      reBuffA *= *PGetCanReal(mpreValueCntHou,ibCan);
      reBuffA += *PGetCanReal(mpreCount,ibCan);

      dgBuff.dbValue = reBuffA;

      tiAlt = *PGetCurrTimeDate();
      dgBuff.stValuef.bSecond = tiAlt.bSecond;
      dgBuff.stValuef.bMinute = tiAlt.bMinute;
      dgBuff.stValuef.bHour   = tiAlt.bHour;

      mpDiagram[ibCan] = dgBuff;
    }
  }

  SaveDiaHou(iwHardHou);
}


void    MakeDiagram(uchar  ibCanal) 
{
  LoadDiaHou(iwHardHou);

  dgBuff.dbValue = reBuffA;

  tiAlt = *PGetCurrTimeDate();
  dgBuff.stValuef.bSecond = tiAlt.bSecond;
  dgBuff.stValuef.bMinute = tiAlt.bMinute;
  dgBuff.stValuef.bHour   = tiAlt.bHour;

  mpDiagram[ibCanal] = dgBuff;

  SaveDiaHou(iwHardHou);
}                        



void    OutDiagram(void)
{
uchar   i,j;

  iwHou = PrevDayIndex(bInBuff6);
            
  InitPushPtr();
  wBuffD = 0;

  for (j=0; j<48; j++)
  {
    LoadDiaHou(iwHou);

    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
      {
        if ((bInBuff6 == 0) && (j > GetHouIndex())) 
        {
          PushChar(0xFF); PushChar(0xFF); PushChar(0xFF); PushChar(0xFF);
          PushChar(0xFF); PushChar(0xFF); PushChar(0xFF);
        }
        else
        {
          Push(&mpDiagram[ i ], sizeof(diagram) );
        }

        wBuffD += sizeof(diagram);
        if (wBuffD >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
      } 
    }
          
    if (++iwHou >= wHOURS) iwHou = 0;
  }      

  OutptrOutBuff(wBuffD);
}
*/
