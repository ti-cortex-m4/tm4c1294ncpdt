/*------------------------------------------------------------------------------
storage,H


------------------------------------------------------------------------------*/

#include "../kernel/entities.h"



uchar SaveChar(uchar *pb, ulong dwEepRom);
uchar SaveInt(uint *pw, ulong dwEepRom);
uchar SaveLong(ulong *pdw, ulong dwEepRom);
uchar SaveString(char *sz, ulong dwEepRom);
uchar SaveEntity(entity const *pen);

void LoadChar(uchar *pb, ulong dwEepRom);
void LoadInt(uint *pw, ulong dwEepRom);
void LoadLong(ulong *pdw, ulong dwEepRom);
void LoadString(char *sz, ulong dwEepRom);
void LoadEntity(entity const *pen);
