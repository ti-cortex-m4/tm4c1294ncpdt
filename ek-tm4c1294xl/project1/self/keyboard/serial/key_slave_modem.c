/*------------------------------------------------------------------------------
KEY_SLAVE_MODEM!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_ports.h"
#include "../../serial/slave_modem.h"
#include "../../nvram/cache.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "Выдавать модему ",
                        szMessage2[]     = "  команду AT ?  ";

static char const      *pszMessages[] = { szMessage1, szMessage2, "" };



static void Show(void)
{
  ShowBool(fSlaveModem);
}


void    key_SetSlaveModem(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszMessages);
      Show();
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        fSlaveModem = InvertBoolean(fSlaveModem);
        SaveCache(&chSlaveModem);
        Show();

        ResetSendAT_All();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
