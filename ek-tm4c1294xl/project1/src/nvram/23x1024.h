/*------------------------------------------------------------------------------
23x1024.H


------------------------------------------------------------------------------*/

void Init_EOZU(void);
void LoadBytes_EOZU(unsigned char *ptrMass, unsigned long lgAddr, unsigned long lgSize);
unsigned char SaveBytes_EOZU(unsigned char *ptrMass, unsigned long lgAddr, unsigned long lgSize);
unsigned char ReadModeReg_EOZU(void);
