/*------------------------------------------------------------------------------
storage.h


------------------------------------------------------------------------------*/

ulong InitStorage(void);

ulong SaveChar(uchar *pb, ulong dwEepRom);
ulong SaveInt(uint *pw, ulong dwEepRom);
ulong SaveLong(ulong *pdw, ulong dwEepRom);
ulong SaveString(char *sz, ulong dwEepRom);

void LoadChar(uchar *pb, ulong dwEepRom);
void LoadInt(uint *pw, ulong dwEepRom);
void LoadLong(ulong *pdw, ulong dwEepRom);
void LoadString(char *sz, ulong dwEepRom);
