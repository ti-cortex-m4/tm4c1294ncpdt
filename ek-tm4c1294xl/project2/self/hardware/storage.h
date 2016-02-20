/*------------------------------------------------------------------------------
storage,H


------------------------------------------------------------------------------*/

#include "../kernel/entities.h"



ulong SaveLong(ulong *pdw, ulong dwEepRom);
err_t SaveEntity(entity const *pen);

void LoadLong(ulong *pdw, ulong dwEepRom);
void LoadEntity(entity const *pen);
