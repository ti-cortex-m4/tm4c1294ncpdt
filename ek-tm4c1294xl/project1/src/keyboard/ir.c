/*------------------------------------------------------------------------------
IR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "keyboard.h"
#include "../../irmp/irmp.h"
#include "ir.h"



void    RunIR(void)
{
  static IRMP_DATA irmp_data;

  if (irmp_get_data (&irmp_data))
  {
    bKey = (irmp_data).command;
    fKey = true;
  }
}
