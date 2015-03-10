/*------------------------------------------------------------------------------
SPEEDS_STORAGE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../flash/files.h"



file const              flPorts = {FLS_SPEEDS, &mppoPorts, sizeof(mppoPorts)};



boolean SavePorts(void)
{
  return SaveFile(&flPorts);
}


boolean LoadPorts(void)
{
  return LoadFile(&flPorts);
}
