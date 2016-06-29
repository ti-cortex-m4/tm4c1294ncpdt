/*------------------------------------------------------------------------------
version.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/rom.h"
#include "log.h"
#include "version.h"



void ConsoleVersion(void)
{
  timedate_t td = GetROMBuildTimeDate();
  CONSOLE("version %u.%u.%u.%04x %02u.%02u.%02u %02u:%02u:%02u\n",
    MAJOR_VERSION, MINOR_VERSION,
    GetROMBuildNumber(),
    GetROMChecksum(),
    td.bDay, td.bMonth, td.bYear, td.bHour, td.bMinute, td.bSecond
  );
}
