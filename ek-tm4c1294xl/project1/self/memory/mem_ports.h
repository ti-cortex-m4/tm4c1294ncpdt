/*------------------------------------------------------------------------------
MEM_PORTS.H


------------------------------------------------------------------------------*/

extern  port                    mppoPorts[bPORTS];

extern  uint                    mpwInDelay[bPORTS];

extern  uint                    mpwMinorInDelay[bPORTS], mpwMajorInDelay[bPORTS];

extern  bool                    mpboLocal[bPORTS];

extern  bool                    mpboLocalDisable[bPORTS];

extern  uint                    mpwOutputDelay[bPORTS];

extern  uchar                   mpbCorrectLimit[bPORTS];

extern  uchar                   bInBuff0,
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

extern	uchar                   bQuery;

extern	uchar                   ibPortActive;



extern  uint                    iwPopSave;

extern  uint                    iwInBuffSave;

extern  uint                    cwInBuffSave;

extern  uchar                   mpbInBuffSave[wINBUFF_SIZE];



extern  uchar                   cbHeaderBcc;

extern  uint                    cwInBuffBcc;



extern  uchar                   bInputModeReset;

extern  time                    tiInputModeReset;

extern  ulong                   dwInputModeReset;



extern  bool                    fSlaveModem;

extern  bool                    fSendAT;

extern  uchar                   mpcbSendAT[bPORTS];

extern  send_at                 mpstSendAT[bPORTS];



extern  bool                    fBulkEnbl;

extern  uchar                   bBulkSize, cbBulk[bPORTS];

extern  uint                    wBulkMaxDelay, cwBulkDelay[bPORTS];

extern  serial                  mpSerial_Bulk[bPORTS];
