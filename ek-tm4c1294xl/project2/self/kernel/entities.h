/*------------------------------------------------------------------------------
entities.h


------------------------------------------------------------------------------*/

#ifndef __ENTITIES_H__
#define __ENTITIES_H__


typedef enum
{
  ROUTING_MODE_SERVER = 0,
  ROUTING_MODE_CLIENT = 1,
  ROUTING_MODE_CLIENT_MODEM = 2,
} routingMode;


typedef enum
{
  CONNECTION_MODE_IMMEDIATELY = 0,
  CONNECTION_MODE_ON_DATA = 1,
} connectionMode;


typedef enum
{
  DEBUG_MODE_NONE = 0,
  DEBUG_MODE_UDP = 1,
  DEBUG_MODE_UART = 2,
} debugMode;


typedef enum
{
  LED_MODE_LINK = 0,
  LED_MODE_RXTX = 1,
  LED_MODE_TX = 2,
  LED_MODE_RX = 3,
  LED_MODE_COLLISION = 4,
  LED_MODE_100_BASE_TX = 5,
  LED_MODE_10_BASE_TX = 6,
  LED_MODE_FULL_DUPLEX = 7,
  LED_MODE_LINK_RXTX = 8,
} ledMode;


#endif


#include "entity.h"
#include "entities_general.h"
#include "entities_channels.h"
#include "entities_setup.h"
#include "entities_debug.h"


extern const entity * const mpenEntities[];
extern const uchar bEntitiesSize;


extern const entity * const mpenRoutingModes[UART_COUNT];
