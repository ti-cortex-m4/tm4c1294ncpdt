/*------------------------------------------------------------------------------
EXTENDED_5.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_extended_5.h"
//#include        "../display/display.h"
//#include        "../keyboard/keyboard.h"
//#include        "../hardware/watchdog.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
//#include        "../digitals/digitals_messages.h"
#include        "../devices/devices.h"
//#include        "../sensors/automatic2.h"
#include        "../serial/ports.h"
//#include        "../time/timedate.h"
#include        "../time/rtc.h"
#include        "../console.h"
//#include        "../engine.h"
//#include        "../energy.h"
//#include        "../flash/files.h"
#include        "extended_5_b.h"
#include        "extended_5_c.h"
#include        "extended_5.h"



//                                         0123456789ABCDEF
static char const       szExtended5[]   = "Опрос данных: 5 ";



bool    ReadCntAbsTariff(uchar  ibCanal, uchar  bTariff)
{
  Clear();

  LoadCurrDigital(ibCanal);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  return( ReadCntAbsTariffA(bTariff) );
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return( ReadCntAbsTariffB(bTariff) );
#endif

#ifndef SKIP_C
    case 3:  return( ReadCntAbsTariffC(bTariff) );
#endif

#ifndef SKIP_H
    case 10: return( ReadCntAbsTariffH(bTariff) );
#endif
  }
}


bool    CoreExtended5(void)
{
uchar i,j;

  memset(&mpvaValue50, 0, sizeof(mpvaValue50));  

  for (i=0; i<bTARIFFS; i++)
  {
    if (fKey == 1) return (0);
    Clear();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  
    if (ReadCntAbsTariff(ibDig,i+1) == 0) return (0);

    for (j=0; j<4; j++)
      mpvaValue50[j].mpreSelf[i] = mpreChannelsB[j];
  }

  return (1);
}


void    MakeExtended5(void)
{ 
  if ((boExt5Flag == TRUE) && ((mpvaValue51[ibDig].boSelf == FALSE) || (boManualProfile == TRUE)))
  {
    ShowHi(szExtended5); Clear();
   
    if (CoreExtended5() == 1)
    {
      LoadCurrDigital(ibDig);

      uchar ibCan;
      for (ibCan=0; ibCan<bCANALS; ibCan++)
      {
        LoadPrevDigital(ibCan);
        if (CompareCurrPrevLines(ibDig, ibCan) == 1)
        {
          mpvaValue51[ibCan].cwOK++;
          mpvaValue51[ibCan].tiSelf = *GetCurrTimeDate();
          mpvaValue51[ibCan].vaValue50 = mpvaValue50[diPrev.ibLine];
          mpvaValue51[ibCan].boSelf = TRUE;
        }
      }
    }
    else
    {
      LoadCurrDigital(ibDig);

      uchar ibCan;
      for (ibCan=0; ibCan<bCANALS; ibCan++)
      {
        LoadPrevDigital(ibCan);
        if (CompareCurrPrevLines(ibDig, ibCan) == 1)
        {
          mpvaValue51[ibCan].cwError++;
        }
      } 
      Error(); DelayInf();
    }  

    ShowCanalNumber(ibDig);
    Clear();
  }
}


void    NextDayExtended5(void)
{
  uchar ibCan;
  for (ibCan=0; ibCan<bCANALS; ibCan++)
    mpvaValue51[ibCan].boSelf = FALSE;
}


#ifndef MODBUS

void    OutExtended50(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();            
    PushChar(boExt5Flag);
    uint wBuffD = 1;

    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
      {
        Push(&mpvaValue51[i], sizeof(value51));
        wBuffD += sizeof(value51);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}


void    OutExtended51(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();            
    PushChar(boExt5Flag);
    uint wBuffD = 1;

    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
      {
        Push(&mpvaValue51[i].vaValue50, sizeof(value50));
        wBuffD += sizeof(value50);
        Push(&mpvaValue51[i].tiSelf, sizeof(time));
        wBuffD += sizeof(time);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}

#endif
