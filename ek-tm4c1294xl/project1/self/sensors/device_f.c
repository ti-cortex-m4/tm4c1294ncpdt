/*------------------------------------------------------------------------------
DEVICE_F!C

 ���+2 CRC
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "device_f.h"


/*
#ifndef SKIP_F
*/
// ������� � ������� �����
void    QueryBreakF(void)
{
  InitPush(0);
  PushChar(0x1A);          
  Query(0, 1, 1);

  Delay(50);
}


/*
// �������� �������� ������
bool    ReadAddressF(void)
{
  return(InBuff(0) == diCurr.bAddress);
}


// �������� ���������� ��������
bool    ReadResultF(void)
{
  TestResult(InBuff(5));
  return(ReadAddressF() && (InBuff(5) == 0));
}



// ������ �� �������/����
void    QueryTimeF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (0+7) % 0x100 );
  PushChar( (0+7) / 0x100 );

  PushChar(bINQ_GETCURRTIME);         

  PckQueryIO(sizeof(time)+7, 0+7);
}


// ������ �������/����
void    ReadTimeAltF(void)
{
  InitPop(5);

  tiAlt.bSecond = PopChar();
  tiAlt.bMinute = PopChar();
  tiAlt.bHour   = PopChar();
  tiAlt.bDay    = PopChar();
  tiAlt.bMonth  = PopChar();
  tiAlt.bYear   = PopChar();
}



void    QueryIdF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);
  PushChar(0);

  PushChar( (0+7) % 0x100 );
  PushChar( (0+7) / 0x100 );

  PushChar(bINQ_GETLOGICAL);

  PckQueryIO(2+7, 0+7);
}


bool    ReadIdF(void)
{
  InitPop(0);
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;
  if (PopChar() != ((2+7) % 0x100)) return 0;
  if (PopChar() != ((2+7) / 0x100)) return 0;
  if (PopChar() != bINQ_GETLOGICAL) return 0;
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;

  return 1;
}



// ������ �� ������ �������� ��������� ���������
void    QueryRealExtendedF(uchar  bQuery)
{
uchar   i;

  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (1+bCANALS/8+7) % 0x100 );
  PushChar( (1+bCANALS/8+7) / 0x100 );

  PushChar(0xFF);
  PushChar(bQuery);         

  for (i=0; i<bCANALS/8; i++) 
    PushChar(0xFF);

  PckQueryIO(bHEADER+sizeof(float)*bCANALS+2, 1+bCANALS/8+7);
}


// ������ �������� ��������� ���������
void    ReadRealExtendedF(void)
{
uchar   i;

  InitPop(bHEADER);

  for (i=0; i<bCANALS; i++)
  {
    PopReal();

    SetCanReal(mpreChannelsB, i);
    mpboChannelsA[i] = true;
  }

  reBuffA = GetCanReal(&mpreChannelsB, diCurr.ibLine);
}



// ������ �� ������ �������������
void    QueryKoeffF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (1+7) % 0x100 );
  PushChar( (1+7) / 0x100 );

  PushChar(bINQ_GETKOEFF);         
  PushChar(diCurr.ibLine);          

  PckQueryIO(sizeof(float)*4+7, 1+7);
}


// ������ �������������
void    ReadKoeffF(void)
{
  InitPop(5);

  PopReal();
  SetCanReal(mpreTransEng,ibDig);
  PopReal();
  SetCanReal(mpreTransCnt,ibDig);
  PopReal();
  SetCanReal(mprePulseHou,ibDig);
  PopReal();
  SetCanReal(mprePulseMnt,ibDig);
}



// ������� ������� �� ��������� ������� ��� ��������� ���+2
void    QueryControlF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (7+7) % 0x100 );
  PushChar( (7+7) / 0x100 );

  PushChar(0xFF);       
  PushChar(bEXT_CORRECT2);         

  PushChar( tiCurr.bSecond );
  PushChar( tiCurr.bMinute );
  PushChar( tiCurr.bHour   );
  PushChar( tiCurr.bDay    );
  PushChar( tiCurr.bMonth  );
  PushChar( tiCurr.bYear   );

  PckQueryIO(1+7, 7+7);
}



void    QueryHeaderF(void)
{
uchar   i;

  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (1+bCANALS/8+7) % 0x100 );
  PushChar( (1+bCANALS/8+7) / 0x100 );

  PushChar(0xFF);
  PushChar(bEXT_GETSTOPCAN);

  for (i=0; i<bCANALS/8; i++) 
    PushChar(0xFF);

  PckQueryIO(bHEADER+sizeof(uint)*bCANALS+2, 1+bCANALS/8+7);
}


void    ReadHeaderF(void)
{
  InitPop(bHEADER);
    
  for (ibCan=0; ibCan<bCANALS; ibCan++)
    mpwChannels[ibCan] = PopChar()*0x100 + PopChar();


  Clear(); sprintf(szLo+1,"%04u",mpcwStopCan[ibDig]);

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      if (mpcwStopCan[ibCan] < mpwChannels[diPrev.ibLine])
        mpcwStopCan[ibCan] = mpwChannels[diPrev.ibLine];

      if (ibCan == ibDig) sprintf(szLo+6,"%04u",mpwChannels[diPrev.ibLine]);
    }
  }

  sprintf(szLo+11,"%04u",mpcwStopCan[ibDig]); DelayMsg();
}


void    InitEnergyF(void)
{
  if (!UseBounds())
    iwMajor = 0;
  else 
  {
    iwMajor = mpcwStartRelCan[ibDig];
    sprintf(szLo," ������ %04u:%02bu ",iwMajor,(uchar)(iwMajor/48 + 1));
    DelayMsg();
  }
}


void    QueryEnergyF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (4+7) % 0x100 );
  PushChar( (4+7) / 0x100 );

  PushChar(0xFF);       
  PushChar(bEXT_GETIMPCANHOU);         

  PushChar( iwMajor / 0x100 );
  PushChar( iwMajor % 0x100 );

  PushChar(bBLOCKS_F);

  PckQueryIO(bHEADER+bBLOCKS_F*(sizeof(time)+sizeof(uint)*bCANALS)+2, 4+7);
}


bool    ReadEnergyF(uchar  ibBlock)
{
  HideCurrTime(1);                                        
  

  InitPop(bHEADER+ibBlock*(sizeof(time)+sizeof(uint)*bCANALS));

  tiDig.bSecond = PopChar();                            // �����/���� �������� �����
  tiDig.bMinute = PopChar();
  tiDig.bHour   = PopChar();
  tiDig.bDay    = PopChar();
  tiDig.bMonth  = PopChar();
  tiDig.bYear   = PopChar();

  sprintf(szLo," %02bu:%02bu %02bu.%02bu.%02bu",        // ���������� �����/���� �������� �����
          tiDig.bHour,tiDig.bMinute, tiDig.bDay,tiDig.bMonth,tiDig.bYear);
  

  tiAlt = tiDig;
  if (SearchDefHouIndex() == 0) return(0);              // �����: ������� ���� �� ������� � ������� ������������ �����
  
  ShowProgressDigHou();      

    
  for (ibCan=0; ibCan<bCANALS; ibCan++)                 // ������ ���������� ��������� �� �������
    mpwChannels[ibCan] = PopChar()*0x100 + PopChar();

  tiAlt = tiDig;
  MakeSpecial();  
  return(MakeStopHou(0));
}



void    QueryCurrentF(void)
{
  InitPushPck();
  PushChar(diCurr.bAddress);          
  PushChar(0);

  PushChar( (4+4) % 0x100 );
  PushChar( (4+4) / 0x100 );

  PushChar(0xFF);       
  PushChar(bEXT_GETIMPCANMNT);         

  PckQueryIO(bHEADER+sizeof(uint)*bCANALS+2, 4+4);
}


void    ReadCurrentF(void)
{
uchar   i;

  InitPop(bHEADER);

  for (i=0; i<bCANALS; i++)
  {
    mpdwChannelsB[i] = (ulong)(PopChar()*0x100 + PopChar());
  }


  ShowLo(szPowerOK); Delay(200);

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      mpboReadyCan[ibCan] = true;

      dwBuffC = mpdwChannelsB[ diPrev.ibLine ];
      mpwImpMntCan[ (bMINUTES+ibSoftMnt-1) % bMINUTES ][ibCan] = (uint)dwBuffC;
    }
  }

  NextCurrent();
}

#endif
*/
