/*------------------------------------------------------------------------------
fragment_cntmon_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../serial/ports_pop.h"
#include "../../digitals/digitals.h" // TODO
#include "dlms.h"
#include "dlms_obis.h"
#include "error39.h"
#include "io39.h"
#include "query_register_39.h"
#include "query_billing_period_39.h"
#include "read_engmon_39.h"
#include "hdlc_address.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "fragment_cntmon_39.h"




static double2 Fault(uchar  bError)
{
  return GetDouble2Error1(Error39(bError));
}



double2 FragmentCntMonCan(const obis_t  obisBillingPeriod, const obis_t  obisScaler, caller39  *pc, date  dt)
{
  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryBillingPeriod39(obisBillingPeriod, (*pc).bNS, (*pc).bNR, (*pc).bInvokeId, dt);
  if (Input39() != SER_GOODCHECK) return Fault(125+0);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(125+1);


  bool present = (EngMonPresent39() == 0);

  ulong64_ counter[4];
  if (present)
  {
    counter[0] = PopUnsignedValueDLSM();
    PopUnsignedValueDLSM();
    PopUnsignedValueDLSM();
    PopUnsignedValueDLSM();
    PopUnsignedValueDLSM();
    counter[1] = PopUnsignedValueDLSM();
    counter[2] = PopUnsignedValueDLSM();
    counter[3] = PopUnsignedValueDLSM();
  }

#ifdef MONITOR_39
  MonitorString("\n present="); MonitorBool(present);
  MonitorString("\n counter[0]="); MonitorLongDec(counter[0].ddwValue);
  MonitorString("\n counter[1]="); MonitorLongDec(counter[1].ddwValue);
  MonitorString("\n counter[2]="); MonitorLongDec(counter[2].ddwValue);
  MonitorString("\n counter[3]="); MonitorLongDec(counter[3].ddwValue);
#endif


  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Fault(125+2);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(125+3);


  double2 scaler = ReadRegisterScaler39(obisScaler, pc);
  if (!scaler.fValid) return Fault(125+4);


  if (present) {
      mpdbChannelsC[0] = (double)counter[0].ddwValue * scaler.dbValue / 1000;
      mpdbChannelsC[1] = (double)counter[1].ddwValue * scaler.dbValue / 1000;
      mpdbChannelsC[2] = (double)counter[2].ddwValue * scaler.dbValue / 1000;
      mpdbChannelsC[3] = (double)counter[3].ddwValue * scaler.dbValue / 1000;
#ifdef MONITOR_39
    //MonitorString("\n result="); MonitorDouble6(db);
#endif
    return GetDouble0(-1);
  }

  if (!present) {
#ifdef MONITOR_39
    MonitorString("\n result is absent");
#endif
    return GetDouble2Error1(ERROR_NOT_PRESENTED);
  }

  return Fault(125+5);
}
