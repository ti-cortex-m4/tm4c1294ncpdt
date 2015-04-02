/*------------------------------------------------------------------------------
MEM_PORTS.H


------------------------------------------------------------------------------*/

extern  port                mppoPorts[bPORTS];

extern  uint                mpwInDelay[bPORTS];

extern  uint                mpwMinorInDelay[bPORTS], mpwMajorInDelay[bPORTS];

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
                            bInBuffA,
                            bInBuffB,
                            bInBuffC,
                            bInBuffD,
                            bInBuffE,
                            bInBuffF;

extern	uchar               bQuery;

extern	uchar              ibPortActive;



extern  uint                    iwPopSave;

extern  uint                    iwInBuffSave;

extern  uint                    cwInBuffSave;

extern  uchar                   mpbInBuffSave[wINBUFF_SIZE];
