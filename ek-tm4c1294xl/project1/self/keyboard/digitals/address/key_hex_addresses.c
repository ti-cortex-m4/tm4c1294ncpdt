/*------------------------------------------------------------------------------
key_hex_addresses.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../common/key_flag.h"
#include "../../../digitals/address/ascii_address.h"
#include "key_hex_addresses.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Тип задания   ",
                        szMessage2[]    = "    адресов     ",
                        szTrue[]        = " байты          ",
                        szFalse[]       = " символы        ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetHexAddresses(void)
{
  key_SetFlag(&chHexAddresses, pszMessages, szTrue, szFalse);
}
