/*------------------------------------------------------------------------------
correct39_wrapper.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../kernel/tuples.h"
//#include "../../serial/monitor.h"
//#include "../../serial/monitor_settings.h"
//#include "include39.h"
//#include "dlms.h"
//#include "dlms_obis.h"
//#include "caller39.h"
//#include "time39.h"
//#include "hdlc_address.h"
//#include "hdlc_monitor.h"
//#include "buffer_record_39.h"
//#include "query_profile_39.h"
//#include "query_next_block_39.h"
//#include "dlms_read_data.h"
//#include "dlms_read_register.h"
//#include "query_register_39.h"
//#include "profile39.h"
#include "correct39_wrapper.h"


static uchar            cbCorrects;
static uint             wDeltaOld;
static uint             wDeltaNew;



uchar   GetCounter_Correct39(void)
{
  return cbCorrects;
}



void    Init_Current39(void)
{
  cbCorrects = 0; // TODO
  wDeltaOld = 0;
  wDeltaNew = 0;
}



void    Write_Current39(uint  wDelta)
{
  cbCorrects++;
  wDeltaOld = (uint)dwDelta;
}



void    Read1_Current39(uint  wDelta)
{
  cbCorrects++;
  wDeltaOld = wDeltaNew;
}

void    Read2_Current39(uint  wDelta)
{
}

void    Read3_Current39(uint  wDelta)
{
}
