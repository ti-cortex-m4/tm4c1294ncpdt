/*------------------------------------------------------------------------------
KEY_ENBL_DIAGRAM,C

 Отчет СЭМ-Cortex №49 от 16_07_2017
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/extended/diagram.h"
#include "../../common/key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Сохранять    ",
                        szMessage2[]     = "знач. счетчиков ",
                        szMessage3[]     = "  по получасам  ",
                        szMessage4[]     = "   за сутки ?   ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetEnblDiagram(void)
{
  key_SetBool(&chEnblDiagram, pszMessages);
}
