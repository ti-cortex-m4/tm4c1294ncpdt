/*------------------------------------------------------------------------------
fragment_cntmon_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../serial/ports_pop.h"
#include "dlms.h"
#include "dlms_obis.h"
#include "error40.h"
#include "io40.h"
#include "query_register_39.h"
#include "query_billing_period_40.h"
#include "read_engmon_39.h"
#include "hdlc_address.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "fragment_cntmon_40.h"



static double8 Fault(uchar  bError)
{
  return GetDouble8Error1(Error40(bError));
}



double8 FragmentCntMonCan40(const obis_t  obisBillingPeriod, const obis_t  obisScaler, caller40  *pc, date  dt)
{
  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryBillingPeriod40(obisBillingPeriod, *pc, dt);
  if (Input40() != SER_GOODCHECK) return Fault(125+0);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(125+1);


  bool present = (IsEngMonPresent40() == 0);
#ifdef MONITOR_40
  MonitorString("\n present="); MonitorBool(present);
#endif

  ulong64_ mddw[8];
  if (present)
  {
    uchar i;
    for (i=0; i<8; i++)
    {
      mddw[i] = PopUnsignedValueDLSM();
#ifdef MONITOR_40
      MonitorString("\n mddw[");
      MonitorCharDec(i);
      MonitorString("]=");
      MonitorLongDec(mddw[i].ddwValue);
#endif
    }
  }


  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input40() != SER_GOODCHECK) return Fault(125+2);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(125+3);


  double2 scaler = ReadRegisterScaler39(obisScaler, pc);
  if (!scaler.fValid) return Fault(125+4);


  if (present)
  {
    double mdb[8];

    uchar i;
    for (i=0; i<8; i++)
    {
      mdb[i] = (double)mddw[i].ddwValue * scaler.dbValue / 1000;
#ifdef MONITOR_40
      MonitorString("\n mdb[");
      MonitorCharDec(i);
      MonitorString("]=");
      MonitorDouble6(mdb[i]);
#endif
    }

    return GetDouble8Ok(mdb);
  }
  else
  {
#ifdef MONITOR_40
  MonitorString("\n not presented");
#endif
    return GetDouble8Error1(ERROR_NOT_PRESENTED);
  }
}
