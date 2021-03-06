/*------------------------------------------------------------------------------
NEXT_MONTH!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_tariffs.h"
#include "../memory/mem_energy.h"
#include "../energy.h"
#include "../energy2.h"
#include "../special/defects.h"
#include "../special/recalc_def.h"
#include "../digitals/extended/extended_4.h"
#include "../digitals/extended/extended_4t.h"
#include "../digitals/extended/extended_6.h"
#include "../time/correct1.h"
#include "../tariffs/tariffs.h"
#include "realtime_storage.h"



void    NextMonth(void)
{
  Realtime1.cwMonths++;

  NextMonTariffs();

  SaveImpMon(0,ibHardMon,ibSoftMon);
  SavePowMon(0,ibHardMon,ibSoftMon);
  SaveCntMon(0,ibHardMon,ibSoftMon);

  if (++ibHardMon >= bMONTHS) ibHardMon = 0;
  if (++ibSoftMon >= 2)       ibSoftMon = 0;
  SavePointersMon();

  memset(&mpimMonCan[ibSoftMon],    0, sizeof(impulse)*bCANALS);
  memset(&mppoMonGrp[ibSoftMon],    0, sizeof(power)*bGROUPS);
  memset(&mpdbCntMonCan[ibSoftMon], 0, sizeof(double)*bCANALS);

  NextMonExtended4();
  NextMonExtended4T();
  NextMonExtended6();

  MakeCntMonCan();

  // ��������� ����� �� �������
  MakeDefectMon(0, tiCurr);

  // ��������� ������������� �� �������
  NextMonDef();

  NextMonCorrect1();
}
