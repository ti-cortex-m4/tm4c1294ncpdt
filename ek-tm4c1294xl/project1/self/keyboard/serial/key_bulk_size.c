/*------------------------------------------------------------------------------
KEY_BULK_SIZE.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../common/key_char_blocked.h"
#include "../../serial/bulk.h"



#ifdef ENABLE_BULK

//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Размер пакетной ",
                        szMessage2[]    = "    передачи    ";
                        
static char const       *pszMessages[]  = { szMessage1, szMessage2, szNumberLimits, "" };



void    key_SetBulkSize(void)
{
  key_SetCharBlocked(&chBulkSize, pszMessages, 1, 250, bBulkSize, wSET_BULK_ENBL);
}

#endif

