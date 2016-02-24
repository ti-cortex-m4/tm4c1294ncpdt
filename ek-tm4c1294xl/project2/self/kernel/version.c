/*------------------------------------------------------------------------------
version.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/rom.h"
#include "log.h"
#include "version.h"



void ConsoleVersion(void)
{
  timedate td = GetROMBuildTimeDate();
  CONSOLE("version %u.%04x %u.%u.%u %u:%u:%u\n",
    GetROMBuildNumber(),
    GetROMChecksum(),
    td.bDay, td.bMonth, td.bYear, td.bHour, td.bMinute, td.bSecond
  );
}
