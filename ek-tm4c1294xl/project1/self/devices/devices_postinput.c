/*------------------------------------------------------------------------------
DEVICES_POSTINPUT,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../kernel/crc-16.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../serial/monitor.h"
#include "../serial/input_wrapper.h"
#include "../sensors/unpack_k.h"
#include "../sensors/sensor24/unpack_s.h"
#include "../sensors/unpack_v.h"
#include "../sensors/sensor31/unpack31.h"
#include "../sensors/automatic_w.h"
#include "../sensors/sensor21/input_p.h"
#include "../sensors/sensor35/io35.h"
#include "../sensors/sensor35/router35.h"
#include "../sensors/sensor35/postinput35.h"
#include "../sensors/sensor36/io36.h"
#include "../sensors/sensor36/router36.h"
#include "../sensors/sensor36/postinput36.h"
#include "../sensors/sensor39/hdlc_monitor.h"
#include "../digitals/digitals_status.h"
#include "devices_postinput.h"



void    DevicesPostInput(void)
{
    if ((diCurr.bDevice ==  1) || (diCurr.bDevice == 15) ||
        (diCurr.bDevice ==  2) || (diCurr.bDevice ==  8) || (diCurr.bDevice == 12) ||
        (diCurr.bDevice ==  6) ||
        (diCurr.bDevice == 18) ||
        (diCurr.bDevice == 19) ||
        (diCurr.bDevice == 34))
    {
      MonitorIn();
      MakeCRC16InBuff( 0, CountInBuff() );

      if ((bCRCHi == 0) && (bCRCLo == 0))
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }

#ifndef SKIP_C
    else if (diCurr.bDevice == 3)
    {
      MonitorIn();
      MakeCRC16InBuff( 0, CountInBuff()-2 );

      if ((bCRCHi == InBuff( CountInBuff()-1 )) &&
          (bCRCLo == InBuff( CountInBuff()-2 ))) {

        if (RevLinkErrors() == 0) {
          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
        }
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
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_E
    else if ((diCurr.bDevice == 5) || (diCurr.bDevice == 7))
    {
      if ( MakeEscInBuff() )
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_31
    else if ((diCurr.bDevice == 9)  || (diCurr.bDevice == 10) ||
             (diCurr.bDevice == 31) || (diCurr.bDevice == 32) || (diCurr.bDevice == 33))
    {
      uchar bCrc = MakeCrc8Bit31InBuff(1, CountInBuff()-1);
      if (bCrc == 0)
      {
        Unpack31();
        InputGoodCheck();
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
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_K
    else if ((diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
             (diCurr.bDevice == 16) || (diCurr.bDevice == 17))
    {
      if ( MakeBccInBuff() )
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
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
          InputGoodCheck();
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
          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
        }
      }
      else
      {
        if ( MakeElsInBuff0() ) {
          InputGoodCheck();
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
      if ( MakeBccInBuff() ) {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_R
    else if (diCurr.bDevice == 23)
    {
      InputGoodCheck();
      mpSerial[ibPort] = SER_GOODCHECK;
    }
#endif

#ifndef SKIP_S
    else if (diCurr.bDevice == 24)
    {
      if (ChecksumS() == 0)
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_U
    else if ((diCurr.bDevice == 26) || (diCurr.bDevice == 28))
    {
      if (MakeBccInBuff())
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_V
    else if (diCurr.bDevice == 27)
    {
      if (ChecksumV() == 0)
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_W
    else if ((diCurr.bDevice == 29) || (diCurr.bDevice == 30))
    {
      MonitorIn();
      if (ChecksumW())
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_35
    else if (diCurr.bDevice == 35)
    {
      if (ChecksumRouter35() == 0) {
        PostInput35();
      } else {
        Query35Repeat();
      }
    }
#endif

#ifndef SKIP_36
    else if ((diCurr.bDevice == 36) || (diCurr.bDevice == 37))
    {
      if (ChecksumRouter36() == 0) {
        PostInput36();
      } else {
        Query36Repeat();
      }
    }
#endif

#ifndef SKIP_38
    else if ((diCurr.bDevice == 38) || (diCurr.bDevice == 39))
    {
      MonitorIn();
      if (MakeCrc35InBuff(1, IndexInBuff()-2) == 0) {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      } else {
        mpSerial[ibPort] = SER_BADCHECK;
      }
    }
#endif

#ifndef SKIP_39
    else if (diCurr.bDevice == 39)
    {
      if (ValidateInputHDLC())
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif
}
