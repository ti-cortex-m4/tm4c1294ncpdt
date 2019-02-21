/*------------------------------------------------------------------------------
md5.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "inc/hw_memmap.h"
#include "driverlib/shamd5.h"
#include "md5.h"



void    MD5(uint32_t *pui32DataSrc, uint32_t ui32DataLength, uint32_t *pui32HashResult)
{
  SHAMD5ConfigSet(SHAMD5_BASE, SHAMD5_ALGO_MD5); // MAP_ ?
  SHAMD5DataProcess(SHAMD5_BASE, pui32DataSrc, ui32DataLength, pui32HashResult);
}


void    RunMD5(void) {
  uint8_t pass[] = {'1','1','1','1','1','1'};
  uint32_t hash[4];
  MD5((uint32_t *)pass, 6, &hash);
}



