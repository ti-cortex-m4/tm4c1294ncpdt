/*------------------------------------------------------------------------------
udp_push,h


------------------------------------------------------------------------------*/

#define UDP_PUSH_SIZE   0x200

extern uchar                   mbUDPPush[UDP_PUSH_SIZE];
extern uint                    iwUDPPush;



extern uint                    cwErrUPDPushCharOverflow;



void InitPush(void);
void PushChar(uchar b);
void PushString(const char *sz);
void PushBuff(buff bf);

void PushIP(ulong dw);
void PushMAC(uchar *pb, uchar bSize);
void PushSuffix(uint w);
