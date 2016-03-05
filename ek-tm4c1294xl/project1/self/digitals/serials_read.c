/*------------------------------------------------------------------------------
AUTOMATIC_8!C


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../../memory/mem_digitals.h"
#include "../digitals/digitals.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports_devices.h"
//#include "../../sensors/device_a.h"
//#include "../../sensors/device_b.h"
//#include "../../sensors/device_c.h"
//#include "../../sensors/device_k.h"
//#include "../../sensors/device_p.h"
//#include "../../sensors/device_s.h"
//#include "../../sensors/automatic_s.h"
//#include "../../sensors/device_u.h"
//#include "../../sensors/device_v.h"
//#include "../../sensors/automatic_v.h"
//#include "../../sensors/device_w.h"
//#include "../../sensors/automatic_w.h"
//#include "../../sensors/sensor31/device31.h"
//#include "../../sensors/sensor31/automatic31.h"
//#include "../../sensors/sensor32/device32.h"
//#include "../../sensors/sensor32/automatic32.h"
//#include "../../console.h"
#include "serials_read.h"



ulong2  ReadSerialCan(uchar  ibCan)
{
  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    default: return GetLong2Error();
  }
}
