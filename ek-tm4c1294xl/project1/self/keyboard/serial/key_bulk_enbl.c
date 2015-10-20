/*------------------------------------------------------------------------------
KEY_BULK_ENBL.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_program.h"
#include "../../serial/bulk.h"
#include "../common/key_bool.h"
#include "key_bulk_enbl.h"



#ifdef ENABLE_BULK

//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Разрешение   ",
                        szMessage2[]     = "    пакетной    ",
                        szMessage3[]     = "   передачи ?   ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetBulkEnable(void)
{
  key_SetBool(&chBulkEnbl, pszMessages);
}

#endif
