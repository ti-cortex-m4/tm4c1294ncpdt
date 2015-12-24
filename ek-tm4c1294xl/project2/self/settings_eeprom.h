/*------------------------------------------------------------------------------
SETTINGS_EEPROM.H


------------------------------------------------------------------------------*/

uchar SaveChar(uchar *pb, ulong dwAddr);
uchar SaveInt(uint *pw, ulong dwAddr);
uchar SaveLong(ulong *pdw, ulong dwAddr);
uchar SaveString(char *sz, ulong dwAddr);

void LoadChar(uchar *pb, ulong dwAddr);
void LoadInt(uint *pw, ulong dwAddr);
void LoadLong(ulong *pdw, ulong dwAddr);
void LoadString(char *sz, ulong dwAddr);