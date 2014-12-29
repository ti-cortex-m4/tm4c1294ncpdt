/*------------------------------------------------------------------------------
MEM_PORTS.H


------------------------------------------------------------------------------*/

extern  port                mppoPorts[bPORTS];

extern	boolean				boSendAT;

extern  uchar               mpcbSendAT[bPORTS];

extern  answer              mpanSendAT[bPORTS];

extern  uint                mpwInDelay[bPORTS];

extern  uint                mpwMinInDelay[bPORTS], mpwMajInDelay[bPORTS];

extern  boolean             mpboLocal[bPORTS];

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
