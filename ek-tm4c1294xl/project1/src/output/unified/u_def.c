/*------------------------------------------------------------------------------
U_DEF.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
//#include        "../../memory/mem_settings.h"
//#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_energy.h"
//#include        "../../keyboard/keyboard.h"
//#include        "../../keyboard/key_timedate.h"
//#include        "../../display/display.h"
//#include        "../../serial/ports.h"
#include        "../../realtime/realtime.h"
//#include        "../../include/queries_uni.h"
//#include        "../../time/rtc.h"
#include        "../../groups.h"
//#include        "u_config.h"
//#include        "u_hou.h"
//#include        "u_energy.h"
#include        "u_def.h"



bool    GetDefCan(uchar  ibCan)
{
  return (mpwImpHouCan[ PrevSoftHou() ][ibCan] == 0xFFFF);
}


bool    GetDefGrp(uchar  ibGrp)
{
uchar   i;

  if (GetGroupsSize(ibGrp) == 0)
    return 0;

  for (i=0; i<GetGroupsSize(ibGrp); i++)
    if (mpwImpHouCan[ PrevSoftHou() ][ GetGroupsNodeCanal(ibGrp, i) ] == 0xFFFF)
      return 1;

  return 0;
}
