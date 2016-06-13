/*------------------------------------------------------------------------------
udp_push,h


------------------------------------------------------------------------------*/

#define UDP_PUSH_SIZE   0x200

extern uchar                   mbUDPPush[UDP_PUSH_SIZE];
extern uint                    iwUDPPush;


extern uint                    cwErrUPDPushCharOverflow;



void InitPush(void);
void PushChar(const uchar b);
void PushString(const char *pcsz);
void PushBuff(buff bf);

void PushIP(const ulong dw);
void PushMAC(const uchar *pb, const uchar bSize);
void PushSuffix(const uint w);
