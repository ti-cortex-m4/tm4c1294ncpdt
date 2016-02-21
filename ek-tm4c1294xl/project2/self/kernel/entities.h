/*------------------------------------------------------------------------------
entities.h


------------------------------------------------------------------------------*/

#ifndef __ENTITIES_H__
#define __ENTITIES_H__


typedef enum
{
  ROUTING_MODE_SERVER = 0,
  ROUTING_MODE_CLIENT = 1,
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


#endif


#include "entity.h"
#include "entities_general.h"
#include "entities_channels.h"
#include "entities_setup.h"
#include "entities_debug.h"


extern const entity * const mpenEntities[];
extern const uchar bEntitiesSize;
