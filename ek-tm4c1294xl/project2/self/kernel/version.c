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
  CONSOLE("version %u.%u.%04u.%04x %2u.%2u.%2u %2u:%2u:%2u\n",
    MAJOR_VERSION, MINOR_VERSION,
    GetROMBuildNumber(),
    GetROMChecksum(),
    td.bDay, td.bMonth, td.bYear, td.bHour, td.bMinute, td.bSecond
  );
}
