/*------------------------------------------------------------------------------
DIGITALS_RUN.C
              

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_phones.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../keyboard/key_timedate.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_status.h"
#include        "../digitals/digitals_pause.h"
#include        "../digitals/digitals_messages.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/wait_answer.h"
#include        "../digitals/wait_query.h"
#include        "../digitals/current_run.h"
#include        "../digitals/profile_run.h"
#include        "../digitals/checkup_run.h"
#include        "../digitals/max_repeats.h"
#include        "../special/recalc_def.h"
#include        "../devices/device_b.h"
#include        "../serial/ports.h"
#include        "../serial/ports_modems.h"
#include        "../serial/modems.h"
#include        "../serial/speeds_display.h"
#include        "../digitals/answer.h"
#include        "../flash/files.h"
#include        "../flash/records.h"
#include        "../time/delay.h"
#include        "../crc-16.h"



// счётчик повторов
uchar                   cbRepeat;
/*
// признак прекращения опроса профиля нагрузки
bit                     fBreakRead;
*/
// индекс текущего цифрового счетчика
uchar                   ibDig;

// вид опроса счётчиков
extended                exExtended;

// признак нахождени в режимах connect модема
bool                    fConnect;

// счетчик
uchar                   cbWaitOnline;

// признак разрыва соединеия при нажатии кнопки
bool                    fKeyOn;



file const              flSeparateCan = {FLS_SEPARATE_CAN, &boSeparateCan, sizeof(boolean)};
file const              flHideMessages = {FLS_HIDE_MESSAGES, &boHideMessages, sizeof(boolean)};



void    InitDevices(void)
{
  LoadFile(&flSeparateCan);
  LoadFile(&flHideMessages);

//uchar   i,j;
//
//  if (GetLabelXDATA() == 0)
//  {
//    MakeDigitals();
//
//    for (i=0; i<bCANALS; i++) mpboBase[i] = boFalse;
//
//    for (i=0; i<bCANALS; i++) mpreEngFrac[i] = 0;
//
//    for (i=0; i<bCANALS; i++)
//      for (j=0; j<6; j++) mpreEngFracDigCan[i][j] = 0;
//  }

  SetCurr(DEV_BEGIN);
  SetPause(DEV_BEGIN);

  InitWaitAnswer();
  InitWaitQuery();
  cbWaitOnline = 0;

  fConnect = 0;
  InitConnectKey();

  ibPortPause = 0xFF;

  EnableAnswer();

  InitMaxRepeats();
  InitDef();
}


void    ResetDevices(void)
{
  boSeparateCan = FALSE;
  SaveFile(&flSeparateCan);

  boHideMessages = FALSE;
  SaveFile(&flHideMessages);

  ResetMaxRepeats();
  ResetDef();
}



void    ShowProgressRepeat(void)
{
  Clear();
  sprintf(szLo+3,"повтор: %u",cbRepeat); DelayInf();
}


/*
void    ShowProgressDigHou(void)
{
uint    i;

  i = (ulong)100*((wHOURS+iwHardHou-iwDigHou)%wHOURS)/mpcwStopCan[ibDig];
  if (i > 100) i = 100;

  ShowProgress(12,i);
  InfoProgress(i);
}
*/


void    ErrorLink(void)
{
  ShowLo(szNoLink);
  sprintf(szLo+14,"%2u",cbRepeat); DelayInf();
}


// базовая подпрограмма опроса цифоровых счётчиков
void    RunDevices(void)
{
  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;


  if ((fConnect == 1) && (bProgram != 0))
  {
    if ((cbWaitOnline > 0) && (cbWaitOnline % 10 == 5))
    {
      SaveDisplay();
      ShowHi(szManual); Clear();

      if (cbWaitOnline <= bMAXWAITONLINE)
        sprintf(szLo,"  осталось: %u c ",(uchar)(bMAXWAITONLINE-cbWaitOnline));
      else
        sprintf(szLo,"окончились: %u c ",(uchar)bMAXWAITONLINE);

      DelayMsg();
      LoadDisplay();

      if (cbWaitOnline > bMAXWAITONLINE) KeyBreakConnect();
    }
  }



  switch (GetPause())
  {
#ifndef SKIP_E
    case DEV_OPENCANAL_E2:
#endif

    case DEV_MODEM_CONNECT:
      cbWaitQuery = bMAXWAITQUERY;
      sprintf(szLo+13,"%3u",cbWaitAnswer); HideCurrentTime(1);
      break;

#ifndef SKIP_E
    case DEV_ENERGY_E2:      
      cbWaitQuery = bMAXWAITQUERY;
      sprintf(szLo+13,"%3bu",cbWaitAnswer); HideCurrentTime(1);
      if (IndexInBuff() > 0) sprintf(szLo," прием: %-4u ",IndexInBuff());
      break;
#endif
  }


  if ((mpSerial[ibPort] == SER_INPUT_MASTER))
  {

#ifndef SKIP_C
    if (diCurr.bDevice == 3)
    {
      if (GetCurr() == DEV_HEADER_1_C2)
        DecompressC();
    }
#endif

#ifndef SKIP_G
    if ((diCurr.bDevice == 9) || (diCurr.bDevice == 10))
    {
      if ((InBuff(0) == 0x7E) && (IndexInBuff() > 3) && (IndexInBuff() == InBuff(1)+4))
        mpSerial[ibPort] = SER_BADLINK;
    }
#endif

#ifndef SKIP_K
    else if ((diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
             (diCurr.bDevice == 16) || (diCurr.bDevice == 17))
    {
      if ((GetCurr() == DEV_OPENCANAL_K2) || (GetCurr() == DEV_OPENCANAL_K3))
      {
        bT = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((bT == '\r') || (bT == '\n'))   
          mpSerial[ibPort] = SER_BADLINK;
      }

      else if (GetCurr() == DEV_PASSWORD_K2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_POSTCONTROL_K2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_HEADER_K2)
        DecompressK(1);
    }
#endif

#ifndef SKIP_Q
    else if (diCurr.bDevice == 22)
    {
      if ((GetCurr() == DEV_OPENCANAL_Q2) || (GetCurr() == DEV_OPENCANAL_Q3))
      {
        bT = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((bT == '\r') || (bT == '\n'))   
          mpSerial[ibPort] = SER_BADLINK;
      }

      else if (GetCurr() == DEV_PASSWORD_Q2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_POSTCONTROL_Q2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_HEADER_Q2)
        DecompressK(1);

      else if (GetCurr() == DEV_ENERGY_Q3)
        DecompressK(1);
    }
#endif

#ifndef SKIP_S
    else if (diCurr.bDevice == 24)
    {
      DecompressS();
    }
#endif

#ifndef SKIP_U
    else if (diCurr.bDevice == 26)
    {
      if ((GetCurr() == DEV_OPENCANAL_U2) || (GetCurr() == DEV_OPENCANAL_U3))
      {
        bT = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((bT == '\r') || (bT == '\n'))   
          mpSerial[ibPort] = SER_BADLINK;
      }

      else if (GetCurr() == DEV_PASSWORD_U2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_POSTCONTROL_U2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if ((GetCurr() == DEV_OPTION_U2) || (GetCurr() == DEV_OPTION_U3))
        DecompressK2(1, 4);

      else if ((GetCurr() == DEV_HEADER_U2) || (GetCurr() == DEV_HEADER_U4))
        DecompressK(1);

      else if (GetCurr() == DEV_ENERGY_U3)
        DecompressK(1);
    }
#endif
  }


  if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
  {
    if ((diCurr.bDevice ==  1) || (diCurr.bDevice == 15) ||
        (diCurr.bDevice ==  2) || (diCurr.bDevice ==  8) || (diCurr.bDevice == 12) ||
        (diCurr.bDevice ==  6) || 
        (diCurr.bDevice == 18) ||
        (diCurr.bDevice == 19))
    {
      MakeCRC16InBuff( 0, CountInBuff() );

      if ((bCRCHi == 0) && (bCRCLo == 0))
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }

#ifndef SKIP_C
    else if (diCurr.bDevice == 3)
    {
      MakeCRC16InBuff( 0, CountInBuff()-2 );

      if ((bCRCHi == InBuff( CountInBuff()-1 )) &&
          (bCRCLo == InBuff( CountInBuff()-2 ))) {

        if (RevLinkErrors() == 0) 
          mpSerial[ibPort] = SER_GOODCHECK;
        else
          mpSerial[ibPort] = SER_BADCHECK;
      }
      else {
        mpSerial[ibPort] = SER_BADCHECK;
        ChecksumError();
      }
    }
#endif

#ifndef SKIP_D
    else if (diCurr.bDevice == 4)
    {
      MakeCRC12InBuff( 0, CountInBuff() );

      if (wCRC == 0)
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_E
    else if ((diCurr.bDevice == 5) || (diCurr.bDevice == 7))
    {
      if ( MakeEscInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_G
    else if ((diCurr.bDevice == 9) || (diCurr.bDevice == 10))
    {
      MakeCRC8InBuff( 1, CountInBuff()-1 );

      if (bCRC == 0)
      {
        DecompressG();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_I
    else if ((diCurr.bDevice == 11) || (diCurr.bDevice == 20) || (diCurr.bDevice == 25))
    {
      InitPop(0);

      bT = 0;
      for (i=0; i<CountInBuff()-3; i++) bT += PopChar();

      if ((bT/0x10 == PopChar1Txt()) && (bT%0x10 == PopChar1Txt()))
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_K
    else if ((diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
             (diCurr.bDevice == 16) || (diCurr.bDevice == 17))  
    {
      if ( MakeBccInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_P
    else if (diCurr.bDevice == 21)
    {
      if ((GetCurr() == DEV_PASSWORD_P3) ||
          (GetCurr() == DEV_PASSWORD_P2) || (GetCurr() == DEV_REPASSWORD_P2) || (GetCurr() == DEV_SETVALUE_P2) ||
          (GetCurr() == DEV_CORRECT_P2))
      {
        if ( MakeElsInBuff2() ) {
          mpSerial[ibPort] = SER_GOODCHECK; 
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK; 
        }
      } 
      else if ((GetCurr() == DEV_OPENCANAL_P3) || 
               (GetCurr() == DEV_OPENCANAL_P2))
      {
        if ( MakeElsInBuff1() ) {
          mpSerial[ibPort] = SER_GOODCHECK; 
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK; 
        }
      } 
      else
      {
        if ( MakeElsInBuff0() ) {
          mpSerial[ibPort] = SER_GOODCHECK; 
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK; 
        }
      }
    }
#endif

#ifndef SKIP_Q
    else if (diCurr.bDevice == 22)
    {
      if ( MakeBccInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_R
    if (diCurr.bDevice == 23)
    {
      mpSerial[ibPort] = SER_GOODCHECK;
    }
#endif

#ifndef SKIP_S
    if (diCurr.bDevice == 24)
    {
      if (ChecksumS() == 0)
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_U
    else if (diCurr.bDevice == 26)
    {
      if ( MakeBccInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_Z
    else if (diCurr.bDevice == 99)
    {
      if ( MakeZetInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif
  }
  else if ((mpSerial[ibPort] == SER_OVERFLOW) || 
           (mpSerial[ibPort] == SER_BADLINK)  ||
           (mpSerial[ibPort] == SER_POSTANSWER_MODEM)  ||
           (mpSerial[ibPort] == SER_PAUSE))
  {
    // пустой оператор

#ifndef SKIP_G
    if ((diCurr.bDevice == 9) || (diCurr.bDevice == 10))
    {
      if ((mpSerial[ibPort] == SER_BADLINK) && (fFlow == 0)) 
      {
        MakeCRC8InBuff( 1, IndexInBuff()-1 );

        if (bCRC == 0)
        {
          DecompressG();
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else 
          mpSerial[ibPort] = SER_BADCHECK;
      }
    }
#endif

#ifndef SKIP_K
    else if ((diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
             (diCurr.bDevice == 16) || (diCurr.bDevice == 17))
    {
      if ((mpSerial[ibPort] == SER_BADLINK) && (fFlow == 0)) 
      {
        if ((GetCurr() == DEV_OPENCANAL_K2) || (GetCurr() == DEV_OPENCANAL_K3))
        {
          bT = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((bT == '\r') || (bT == '\n')) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_K2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))   
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_K2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06)) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_HEADER_K2)
        {
          if (IndexInBuff() == 10)
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

#ifndef SKIP_Q
    else if (diCurr.bDevice == 22)
    {
      if ((mpSerial[ibPort] == SER_BADLINK) && (fFlow == 0)) 
      {
        if ((GetCurr() == DEV_OPENCANAL_Q2) || (GetCurr() == DEV_OPENCANAL_Q3))
        {
          bT = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((bT == '\r') || (bT == '\n')) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_Q2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))   
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_Q2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06)) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_HEADER_Q2)
        {
          if (IndexInBuff() == 10)
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

#ifndef SKIP_U
    else if (diCurr.bDevice == 26)
    {
      if ((mpSerial[ibPort] == SER_BADLINK) && (fFlow == 0)) 
      {
        if ((GetCurr() == DEV_OPENCANAL_U2) || (GetCurr() == DEV_OPENCANAL_U3))
        {
          bT = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((bT == '\r') || (bT == '\n')) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_U2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))   
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_U2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06)) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if ((GetCurr() == DEV_HEADER_U2) || (GetCurr() == DEV_HEADER_U4))
        {
          if (IndexInBuff() == 3)
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

  }
  else return;



  switch (GetCurr())
  {
    case DEV_PAUSE:
      if (mpSerial[ibPort] == SER_POSTANSWER_MODEM) 
        SetCurr(GetPause());
      break;



    case DEV_MODEM_START:
      if ((exExtended == EXT_CURRENT_3MIN) && (diCurr.ibPhone != 0)) 
      {
        ShowLo(szPowerNo); DelayInf();
        cbWaitQuery = 3;
        NextCurrent();
      }
      else
      {
        fConnect = 0;
        if (StreamPortCan(diCurr.ibPort,ibDig) == 0) 
        {
          fKeyOn = 0;
          MakePause(DEV_MODEM_STOP);

          AddModRecord(EVE_MODEM_ERROR); 
        }
        else if (diCurr.ibPhone != 0) 
          MakePause(DEV_MODEM_POSTSTART);
        else
          MakePause(DEV_MODEM_POSTCONNECT);
      }
      break;

    case DEV_MODEM_POSTSTART:
      cbRepeat = bMINORREPEATS;

      QueryModemBaud(1);
      MakeLongPause(DEV_MODEM_BAUD,1);        

      AddDigRecord(EVE_MODEMCONNECT1);
      AddModRecord(EVE_MODEMBAUD); 
      break;

    case DEV_MODEM_BAUD:
      if (ModSerialOK() == 1)
      {
        ShowLo(szBaudOK); DelayInf();
        mpcwBaud[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTBAUD);

        AddModRecord(EVE_MODEMBAUD_OK); 
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTBAUD); 
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
  
          QueryModemBaud(1);
          MakeLongPause(DEV_MODEM_BAUD,1);        

          AddModRecord(EVE_MODEMBAUD_NEXT);
        } 
      }
      break;

    case DEV_MODEM_POSTBAUD:
      cbRepeat = bMINORREPEATS;

      QueryModemCommon(1);
      MakeLongPause(DEV_MODEM_COMMON,1);

      AddModRecord(EVE_MODEMCOMMON1);
      break;

    case DEV_MODEM_COMMON:
      if (ModSerialOK() == 1)
      {
        ShowLo(szCommonOK); DelayInf();
        mpcwCommon[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCOMMON);

        AddModRecord(EVE_MODEMCOMMON1_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          if (cbRepeat == bMINORREPEATS-1)
          {
            QueryModemCommon(1);
            MakeLongPause(DEV_MODEM_COMMON,1);        

            AddModRecord(EVE_MODEMCOMMON1_NEXT);
          }
          else
          {
            QueryModemEscape();
            MakeLongPause(DEV_MODEM_ONLINE,1);        

            AddModRecord(EVE_MODEMESCAPE1_NEXT);
          }
        }
      }
      break;

    case DEV_MODEM_ONLINE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szEscapeOK); DelayInf();
        mpcwEscape[diCurr.ibPort]++;

        QueryModemHookOff();
        MakeLongPause(DEV_MODEM_POSTONLINE,1);        

        AddModRecord(EVE_MODEMHOOKOFF1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowProgressRepeat();

          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_POSTONLINE,1);        

          AddModRecord(EVE_MODEMHOOKOFF1_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTONLINE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();
        mpcwHookOff[diCurr.ibPort]++;

        QueryModemCommon(1);
        MakeLongPause(DEV_MODEM_COMMON,1);        

        AddModRecord(EVE_MODEMCOMMON2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowProgressRepeat();

          QueryModemCommon(1);
          MakeLongPause(DEV_MODEM_COMMON,1);        

          AddModRecord(EVE_MODEMCOMMON2_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCOMMON:
      if (boCustomModem == TRUE)
        MakePause(DEV_MODEM_NORMAL);
      else
        MakePause(DEV_MODEM_POSTCUSTOM);
      break;

    case DEV_MODEM_NORMAL:
      cbRepeat = bMINORREPEATS;

      QueryModemCustom();
      MakeLongPause(DEV_MODEM_CUSTOM,1);

      AddModRecord(EVE_MODEMCUSTOM);
      break;

    case DEV_MODEM_CUSTOM:
      if (ModSerialOK() == 1)
      {
        ShowLo(szCustomOK); DelayInf();
        mpcwCustom[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCUSTOM);

        AddModRecord(EVE_MODEMCUSTOM_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          QueryModemCustom();
          MakeLongPause(DEV_MODEM_CUSTOM,1);

          AddModRecord(EVE_MODEMCUSTOM_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCUSTOM:
      InitWaitAnswer();

      cbRepeat = bMINORREPEATS;

      fConnect = 1;
      QueryModemConnect();
      MakeLongPause(DEV_MODEM_CONNECT,bMaxConnect);

      AddModRecord(EVE_MODEMCONNECT);
      break;

    case DEV_MODEM_CONNECT:
      if ((mpSerial[ibPort] == SER_POSTANSWER_MODEM) && (ShowModemConnect() == 1)) 
      {
        ShowCanalNumber(ibDig);

        cbWaitOnline = 0;

        mpcwConnect[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCONNECT);

        AddDigRecord(EVE_MODEMCONNECT2);
        AddModRecord(EVE_MODEMCONNECT_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          InitWaitAnswer();

          fConnect = 1;
          QueryModemConnect();
          MakeLongPause(DEV_MODEM_CONNECT, bMaxConnect);

          AddModRecord(EVE_MODEMCONNECT_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCONNECT:
/*
      if (exExtended == EXT_PROFILE_30MIN)
      {
        MakeExtended1();
        MakeExtended4();
        MakeExtended5();
        MakeExtended3();
        MakeExtended4T();
      }

      if ((exExtended == EXT_PROFILE_30MIN) && (boQuickParam == boFalse)) 
        MakeExtended2();

      if ((exExtended == EXT_CURRENT_3MIN) && (boQuickParam == boTrue)) 
        MakeExtended2();
*/
      HideCurrentTime(1);
      MakePause(GetNext());
      break;



    case DEV_MODEM_STOP:
      if (fKeyOn == 0)
        ShowCanalNumber(ibDig);
      else
        ShowHi(szManual);

      if ((diCurr.ibPhone != 0) && (fConnect == 1))
        MakePause(DEV_MODEM_POSTSTOP);
      else 
        MakePause(DEV_MODEM_POSTBREAK);
      break;

    case DEV_MODEM_POSTSTOP:
      cbRepeat = bMINORREPEATS;

      QueryModemEscape();
      MakeLongPause(DEV_MODEM_ESCAPE,3);        

      AddDigRecord(EVE_MODEMBREAK1);
      AddModRecord(EVE_MODEMESCAPE2);
      break;

    case DEV_MODEM_ESCAPE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szEscapeOK); DelayInf();

        mpcwEscape[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTESCAPE);

        AddModRecord(EVE_MODEMESCAPE2_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTESCAPE);
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_PREVHOOKOFF,1);        

          AddModRecord(EVE_MODEMHOOKOFF2_NEXT);
        }
      }
      break;

    case DEV_MODEM_PREVHOOKOFF:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();

        mpcwHookOff[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTHOOKOFF);

        AddModRecord(EVE_MODEMHOOKOFF2_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTESCAPE);
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          QueryModemEscape();
          MakeLongPause(DEV_MODEM_ESCAPE,3);

          AddModRecord(EVE_MODEMESCAPE3_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTESCAPE:
      cbRepeat = bMINORREPEATS;

      QueryModemHookOff();
      MakeLongPause(DEV_MODEM_HOOKOFF,1);        

      AddModRecord(EVE_MODEMHOOKOFF3);
      break;

    case DEV_MODEM_HOOKOFF:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();

        mpcwHookOff[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTHOOKOFF);

        AddDigRecord(EVE_MODEMBREAK2);
        AddModRecord(EVE_MODEMHOOKOFF3_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_BREAK);
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_HOOKOFF,1);

          AddModRecord(EVE_MODEMHOOKOFF3_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTHOOKOFF:
      MakePause(DEV_MODEM_POSTBREAK);
      break;

    case DEV_MODEM_BREAK:
      ModemDTROff();
      mpcwDTROff[diCurr.ibPort]++;

      MakePause(DEV_MODEM_POSTBREAK);

      AddModRecord(EVE_MODEMDTROFF);
      break;

    case DEV_MODEM_POSTBREAK:
      fConnect = 0;
      mpSerial[diCurr.ibPort] = SER_BEGIN;
      if (fKeyOn == 1)
      {
        SetCurr(DEV_BEGIN);
        SetPause(DEV_BEGIN);

        Work(); OK();  
      }
      else 
      {
        if (exExtended == EXT_PROFILE_30MIN)
          NextProfile();
        else
          NextCheckup();
      }
      break;
/*
#ifndef SKIP_B

    case DEV_START_B2:                     
      cbCorrects = 0;

      cbRepeat = bMINORREPEATS;
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B2);
      break;

    case DEV_OPENCANAL_B2:                     
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
      {
        if (fCurrCtrlHou == 1)
          MakePause(DEV_POSTOPENCANAL_B2);
        else
          MakePause(DEV_POSTCORRECT_B2);  
      }
      else                                      
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B2);
        }
      }  
      break;

    case DEV_POSTOPENCANAL_B2:                  
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1bu",cbCorrects+1); DelayInf();

      cbRepeat = bMINORREPEATS;
      QueryTimeB();                          
      SetCurr(DEV_TIME_B2);          
      break;

    case DEV_TIME_B2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltB();                  
        ReadTimeDigB();                  
        MakePause(DEV_POSTTIME_B2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeB();
          SetCurr(DEV_TIME_B2);
        }
      } 
      break;


    case DEV_POSTTIME_B2:
      wBuffD  = GetDayIndex();              // количество дней с начала года ведомого счётчика
      dwBuffC = GetSecondIndex();           // количество секунд ведомого счётчика

      tiAlt = tiCurr;                       // текущие время/дата сумматора

      if (wBuffD != GetDayIndex())          
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
      else 
      {
        if (dwBuffC > GetSecondIndex())                                         // необходима коррекция времени ведомого счётчика назад
          ShowDeltaNeg();
        else
          ShowDeltaPos();

        if (dwBuffC < MinorCorrect())                                           // без коррекции
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }     
        else if (dwBuffC < bMAJORCORRECT_B)                                     // простая коррекция
        {
          if (cbCorrects == 0)
          { 
            bDeltaOld = (uchar)dwBuffC;
            (boShowMessages == boTrue) ? DelayMsg() : DelayInf();
            ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_B2); 
          }
          else
          {
            bDeltaNew = (uchar)dwBuffC;
            if ((bDeltaNew < bDeltaOld) && (cbCorrects < 100))
            {
              bDeltaOld = bDeltaNew;
              cbCorrects++;
              MakePause(DEV_POSTOPENCANAL_B2);
            }
            else if (GetHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))
            { ShowLo(szCorrectNext); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }     
            else
            { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
          }
        } 
        else                                                                    
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
      }
      break;


    case DEV_CONTROL_B2: 
      if (++cbCorrects > bMINORREPEATS)          
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = bMINORREPEATS;                         
        QueryControlB();                          
        SetCurr(DEV_POSTCONTROL_B2);
      }
      break;

    case DEV_POSTCONTROL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_B2);   // да !
        else
        {
          DelayOff(); // ErrorLink();
          cbRepeat--;
          
          QueryControlB();
          SetCurr(DEV_POSTCONTROL_B2);
        }
      } 
      break;
/ *
    case DEV_MANAGE_B2:                  
      if (++cbCorrects > bMINORREPEATS)          
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryManageB();                          
        SetCurr(DEV_POSTMANAGE_B2);
      }
      break;

    case DEV_POSTMANAGE_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_B2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryManageB();
          SetCurr(DEV_POSTMANAGE_B2);
        }
      } 
      break;
* /

    case DEV_POSTCORRECT_B2:                  
      Clear();

      cbRepeat = bMINORREPEATS;
      QueryVersionB();
      SetCurr(DEV_VERSION_B2);
      break;

    case DEV_VERSION_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionB();
        MakePause(DEV_POSTVERSION_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryVersionB();
          SetCurr(DEV_VERSION_B2);
        }
      } 
      break;

    case DEV_POSTVERSION_B2:
      Clear();

      cbRepeat = bMINORREPEATS;
      QueryTopB();                          
      SetCurr(DEV_TOP_B2);
      break;

    case DEV_TOP_B2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (TestVersionB710()) ReadTopBNew(); else ReadTopBOld();
        MakePause(DEV_POSTTOP_B2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTopB();
          SetCurr(DEV_TOP_B2);
        }
      } 
      break;

    case DEV_POSTTOP_B2:              
      cbRepeat2 = 0;
      if (diCurr.bDevice == 2)
      {
        if (TestVersionB710())
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
        else
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
      }
      else
      { 
        cbRepeat = bMINORREPEATS;
        QueryHeaderB_Plus(bBLOCKS_B);                         
        SetCurr(DEV_HEADER_B2PLUS);
      }
      break;

    case DEV_HEADER_B2:                    
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2);
      else                                  
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_B2);
/ *
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }* /
      } 
      break;

    case DEV_ERROR_B2: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else 
      {
        cbRepeat = bMINORREPEATS;
        QueryIdB();
        SetCurr(DEV_POSTERROR_B2);
      }
      break;

    case DEV_POSTERROR_B2: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdB() == 1)
        {
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_B2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdB();
          SetCurr(DEV_POSTERROR_B2);
        }
      } 
      break;

    case DEV_POSTHEADER_B2:                   
      cbRepeat2 = 0;
      NewBoundsAbs(wBaseCurr);
      if (ReadHeaderB(0,0) == 0)
        DoneProfile();  
      else 
      { 
        (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);

        cbRepeat = bMINORREPEATS;
        QueryHeaderB();
        SetCurr(DEV_HEADER_B2);
      }
      break;

    case DEV_HEADER_B2PLUS:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2PLUS);
      else                                  
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      } 
      break;

    case DEV_POSTHEADER_B2PLUS:
      for (i=0; i<bBLOCKS_B; i++)
        if (TestHeaderB(i) == 0) break;

      if (i != bBLOCKS_B)
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
      else
      {
        NewBoundsAbs(wBaseCurr);
        for (i=0; i<bBLOCKS_B; i++)
        {
          if (ReadHeaderB(i,1) == 0) break;
          (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
        }

        if (i != bBLOCKS_B)
          DoneProfile();
        else 
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
      break;

    case DEV_HEADER_B2NEXT:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2NEXT);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
      } 
      break;

    case DEV_POSTHEADER_B2NEXT:
        NewBoundsAbs2(dwBaseCurr);
        for (i=0; i<17; i++)
        {
          if (ReadHeaderBNew(i,1) == 0) break;
          (dwBaseCurr == 0) ? (dwBaseCurr = 0x1FFF0) : (dwBaseCurr -= 0x0010);
        }

        if (i != 17)
          DoneProfile();
        else 
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
      break;

#endif
*/
#ifndef SKIP_B

    case DEV_START_B3:
      cbRepeat = GetMaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B3);             
      break;

    case DEV_OPENCANAL_B3:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_B3:
      cbRepeat = GetMaxRepeats();
      QueryEnergyB(0);
      SetCurr(DEV_ENERGY_B3);
      break;

    case DEV_ENERGY_B3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentB();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyB(0);
          SetCurr(DEV_ENERGY_B3);
        }
      } 
      break;

#endif

  }

}

