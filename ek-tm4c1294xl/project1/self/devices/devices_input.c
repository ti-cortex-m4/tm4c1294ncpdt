/*------------------------------------------------------------------------------
DEVICES_INPUT,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../digitals/digitals_status.h"
#include "../sensors/unpack_c.h"
#include "../sensors/unpack_k.h"
#include "../sensors/unpack_s.h"
#include "../sensors/unpack_v.h"
#include "../sensors/unpack_w.h"
#include "../serial/ports.h"
#include "devices_input.h"



void    DevicesInput(void)
{
#ifndef SKIP_C
    if (diCurr.bDevice == 3)
    {
      if (GetCurr() == DEV_HEADER_1_C2)
        DecompressC();
    }
#endif

#ifndef SKIP_G
    else if ((diCurr.bDevice == 9) || (diCurr.bDevice == 10))
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
        uchar b = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((b == '\r') || (b == '\n'))
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
        uchar b = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((b == '\r') || (b == '\n'))
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
    else if ((diCurr.bDevice == 26) || (diCurr.bDevice == 28))
    {
      if ((GetCurr() == DEV_OPENCANAL_U2) || (GetCurr() == DEV_OPENCANAL_U3))
      {
        uchar b = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((b == '\r') || (b == '\n'))
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

#ifndef SKIP_V
    else if (diCurr.bDevice == 27)
    {
      UnpackV();
    }
#endif

#ifndef SKIP_W
    else if (diCurr.bDevice == 29)
    {
      if ((GetCurr() == DEV_OPENCANAL_W2) || (GetCurr() == DEV_OPENCANAL_W3))
      {
        uchar b = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((b == '\r') || (b == '\n'))
          mpSerial[ibPort] = SER_BADLINK;
      }

      else if ((GetCurr() == DEV_PASSWORD_W2) ||
               (GetCurr() == DEV_POSTCONTROL_W2) ||
               (GetCurr() == DEV_POSTSETCORRECT_W2))
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      }

      else if ((GetCurr() == DEV_OPTION_W2) || (GetCurr() == DEV_OPTION_W3) ||
               (GetCurr() == DEV_POSTGETCORRECT_W2) ||
               (GetCurr() == DEV_HEADER_W2) ||
               (GetCurr() == DEV_ENERGY_W3))
      {
        UnpackW(true, 3);
      }
    }
#endif
}
