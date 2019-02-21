/*------------------------------------------------------------------------------
md5.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "inc/hw_memmap.h"
#include "driverlib/shamd5.h"



uint32_t                mpbHash[16];



void    MD5(uint32_t *pui32DataSrc, uint32_t ui32DataLength, uint32_t *pui32HashResult)
{
  SHAMD5ConfigSet(SHAMD5_BASE, SHAMD5_ALGO_MD5); // MAP_ ?
  SHAMD5DataProcess(SHAMD5_BASE, pui32DataSrc, ui32DataLength, pui32HashResult);
}


