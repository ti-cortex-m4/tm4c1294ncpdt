/*------------------------------------------------------------------------------
udp_push,h


------------------------------------------------------------------------------*/

extern uint                    cwErrUPDPushCharOverflow;



void InitPush(void);
void PushChar(uchar b);
void PushString(const char *sz);
void PushBuff(buff bf);

void PushIP(ulong dw);
void PushMAC(uchar *pb, uchar bSize);
void PushSuffix(uint w);
