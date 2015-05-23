/*------------------------------------------------------------------------------
FILES2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "files.h"
#include "files2.h"



void    LoadFileBoolean(file const  *pfl, boolean  boDef)
{
  LoadFile(pfl);
  boolean *pboVal = (boolean *) pfl->pbBuff;

  if (!((*pboVal == TRUE) || (*pboVal == FALSE)))
  {
    *pboVal = boDef;
    SaveFile(pfl);
  }
}


void    LoadFileChar(file const  *pfl, uchar  bMin, uchar  bMax, uchar  bDef)
{
  LoadFile(pfl);
  uchar *pbVal = (uchar *) pfl->pbBuff;

  if (!((*pbVal >= bMin) && (*pbVal <= bMax)))
  {
    *pbVal = bDef;
    SaveFile(pfl);
  }
}
