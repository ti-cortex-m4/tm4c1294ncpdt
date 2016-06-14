/*------------------------------------------------------------------------------
udp_log.h


------------------------------------------------------------------------------*/


extern uint                    cwErrUDPLogPbufAlloc;
extern uint                    cwErrUDPLogSend;



void InitUDPLog(void);

void UDPLog(uchar *pb, uint wSize);
