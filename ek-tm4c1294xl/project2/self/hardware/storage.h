/*------------------------------------------------------------------------------
storage.h


------------------------------------------------------------------------------*/

#include "../kernel/entities.h"



ulong SaveLong(ulong *pdw, ulong dwEepRom);
err_t SaveEntity(const entity * const pen);

void LoadLong(ulong *pdw, ulong dwEepRom);
void LoadEntity(const entity * const pen);
