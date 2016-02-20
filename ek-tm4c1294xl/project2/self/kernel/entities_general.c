/*------------------------------------------------------------------------------
entities_general.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "../settings.h"
#include "entities_general.h"



const entity enIP = {
  EEPROM_IP, &dwIP, sizeof(ulong), IP,
  0, MAX_LONG, 0x01000001,
  "IP",
  "AI=IP;D=IP-address;T=STRING;C=IPCTRL;F=R*",
};


const entity enGateway = {
  EEPROM_GATEWAY, &dwGateway, sizeof(ulong), IP,
  0, MAX_LONG, 0x00000001,
  "GW",
  "AI=GI;D=Gateway IP-address;T=STRING;C=IPCTRL;F=R*",
};


const entity enNetmask = {
  EEPROM_NETMASK, &dwNetmask, sizeof(ulong), IP,
  0, MAX_LONG, 0x00000000,
  "NM",
  "AI=NM;D=Subnet mask;T=STRING;C=IPCTRL;F=R*",
};
