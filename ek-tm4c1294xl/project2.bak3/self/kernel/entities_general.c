/*------------------------------------------------------------------------------
entities_general.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "settings.h"
#include "entities_general.h"



const entity enIP = {
  EEPROM_IP, &dwIP, sizeof(ulong), IP, FLAG_DONT_RESET,
  0, MAX_LONG, 0x01000001,
  "IP",
  "AI=IP;D=IP-address;T=STRING;C=IPCTRL;F=R*",
};

const entity enGateway = {
  EEPROM_GATEWAY, &dwGateway, sizeof(ulong), IP, 0,
  0, MAX_LONG, 0x00000001,
  "GI",
  "AI=GI;D=Gateway IP-address;T=STRING;C=IPCTRL;F=R*",
};

const entity enNetmask = {
  EEPROM_NETMASK, &dwNetmask, sizeof(ulong), IP, 0,
  0, MAX_LONG, 0x00000000,
  "NM",
  "AI=NM;D=Subnet mask;T=STRING;C=IPCTRL;F=R*",
};


const entity enOwnerName = {
  EEPROM_OWNER_NAME, &szOwnerName, NAME_SIZE, STRING, FLAG_DONT_RESET,
  0, 0, 0,
  "ON",
  "AI=ON;D=Owner name;T=STRING;C=EDIT;MAXLEN=8;F=R*",
};

const entity enDeviceName = {
  EEPROM_DEVICE_NAME, &szDeviceName, NAME_SIZE, STRING, FLAG_DONT_RESET,
  0, 0, 0,
  "DN",
  "AI=DN;D=Device name;T=STRING;C=EDIT;MAXLEN=8;F=R*",
};
