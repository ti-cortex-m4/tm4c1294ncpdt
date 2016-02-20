/*------------------------------------------------------------------------------
entity.h


------------------------------------------------------------------------------*/

#ifndef __ENTITY_H__
#define __ENTITY_H__


typedef enum
{
  CHAR,
  INT,
  IP,
  STRING,
} entityType;


typedef struct
{
  ulong         dwEepRom;
  void         *pbRam;
  uint          wSize;
  entityType    eType;
  ulong         dwMin, dwMax, dwDef;
  const char    *szCode, *szName;
} entity;


#endif


err_t SaveEntity(const entity * const pen);
void LoadEntity(const entity * const pen);
void LoadEntityDef(const entity * const pen);
