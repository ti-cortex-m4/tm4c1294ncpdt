/*------------------------------------------------------------------------------
FILES.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/flash.h"



void OpenOut(uint const  wPage);
void ClearOut(void);
bool Save(void  *pbBase, uint  wSize);
bool Clean(uint  wSize);
bool CloseOut(void);

bool OpenIn(uint const  wPage);
void ClearIn(void);
bool Load(void  *pbBase, uint  wSize);

bool SaveBuff(uint wPage, void *pbBuff, uint wSize);
bool CleanBuff(uint wPage, uint wSize);
bool LoadBuff(uint wPage, void *pbBuff, uint wSize);

bool SaveFile(file const *pfl);
bool LoadFile(file const *pfl);
