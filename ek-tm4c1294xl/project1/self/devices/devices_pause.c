/*------------------------------------------------------------------------------
DEVICES_PAUSE,C

TODO / *else* /
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../digitals/digitals_status.h"
#include "devices_pause.h"



void    DevicesPause(void)
{
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
    /*else*/ if (diCurr.bDevice == 26)
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
