/*------------------------------------------------------------------------------
md5.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "inc/hw_memmap.h"
#include "driverlib/shamd5.h"



uint32_t                mpbHash[16];



void    Md5(void)
{
  SHAMD5ConfigSet(SHAMD5_BASE, SHAMD5_ALGO_MD5); // MAP_ ?
  uchar mpbPass[] = {'1', '1', '1', '1', '1', '1'};
  SHAMD5DataProcess(SHAMD5_BASE, (uint32_t *)mpbPass, 6, (uint32_t *)mpbHash);
}


