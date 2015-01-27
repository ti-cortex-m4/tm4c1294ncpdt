/*------------------------------------------------------------------------------
PRIVATE.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "mem_settings.h"
#include        "flash/files.h"



bool    SavePrivate(void)
{
  OpenOut(wFLA_PRIVATE);

  if (Save(&wPrivate, sizeof(uint)) == 0)
    return 0;

  return CloseOut();
}


bool    LoadPrivate(void)
{
  OpenIn(wFLA_PRIVATE);
  return Load(&wPrivate, sizeof(uint));
}
