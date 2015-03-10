/*------------------------------------------------------------------------------
MEM_PORTS.H


------------------------------------------------------------------------------*/

extern  port                mppoPorts[bPORTS];

extern  uint                mpwInDelay[bPORTS];

extern  uint                mpwMinInDelay[bPORTS], mpwMajInDelay[bPORTS];

extern  boolean             mpboLocal[bPORTS];

extern  boolean             mpboLocalDisable[bPORTS];

extern	uchar               bInBuff0,
                            bInBuff1,
                            bInBuff2,
                            bInBuff3,
                            bInBuff4,
                            bInBuff5,
                            bInBuff6,
                            bInBuff7,
                            bInBuff8,
                            bInBuff9,
                            bInBuffA;

extern	uchar               bQuery;

extern	uchar              ibPortActive;
