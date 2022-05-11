/*------------------------------------------------------------------------------
settings.h


------------------------------------------------------------------------------*/

#include "entities.h"
#include "entities_default.h"



extern const ulong             mdwBaudRates[BAUD_RATE_COUNT];



extern uchar                   mbMAC[6];

extern uint                    wSerialNumber;

extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;

extern char                    szOwnerName[NAME_SIZE];
extern char                    szDeviceName[NAME_SIZE];

extern uchar                   mbConnectionTimeout[UART_COUNT];
extern uchar                   mbRoutingMode[UART_COUNT];
extern uint                    mwPort[UART_COUNT];
extern uchar                   mbConnectionMode[UART_COUNT];
extern ulong                   mdwDestinationIP[UART_COUNT];
extern uint                    mwDestinationPort[UART_COUNT];

extern bool                    mfServerToModem[UART_COUNT];
extern uchar                   mbModemToServerTimeout[UART_COUNT];

extern uchar                   mibBaudRate[UART_COUNT];
extern uchar                   mibParity[UART_COUNT];
extern uchar                   mibDataBits[UART_COUNT];
extern uchar                   mibStopBits[UART_COUNT];
extern bool                    mfLoopback[UART_COUNT];

extern bool                    fWatchdogFlag;
extern bool                    fWatchdogReset;

extern bool                    ibDebugMode;

extern ulong                   dwUDPDebugIP;
extern uint                    wUDPDebugPort;

extern bool                    fLWIPDebugFlag;
extern uint                    wLWIPDebugTimeout;

extern bool                    fTCPEchoFlag;
extern uint                    wTCPEchoPort;

extern bool                    fDataDebugFlag;
extern bool                    fIOModeDebugFlag;

extern ledMode                 bLED0Mode;
extern ledMode                 bLED1Mode;

extern uint                    cwPowerUpResetCount;
extern uint                    cwWatchdogResetCount;

extern uint                    cwPeriodicResetCount;
extern bool                    fPeriodicResetFlag;
extern uchar                   bPeriodicResetPeriod;

extern uchar                   mbCustomerSettings[UART_COUNT];
extern uchar                   mbCustomerSetting1_Delay[UART_COUNT];
extern uint                    mwCustomerSetting1_Timeout[UART_COUNT];

extern uint                    cwErrSettingsInitStorage;
extern uint                    cwErrSettingsSaveEntity;
extern uint                    cwErrSettingsLoadIP;



void InitSettings(void);
void ResetSettings(void);
