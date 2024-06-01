/*------------------------------------------------------------------------------
QUERIES2!H


------------------------------------------------------------------------------*/

#define wUNI_GETCURRTIME               0x0001
#define wUNI_GETCORRECTTIME            0x0002
#define wUNI_GETCORRECTIONS            0x0003

#define wUNI_GETENGCANDAY              0x0040
#define wUNI_GETENGGRPDAY              0x0041
#define wUNI_GETENGCANMON              0x0042
#define wUNI_GETENGGRPMON              0x0043

#define wUNI_GETENGCANDAY_X2           0x1040
#define wUNI_GETENGGRPDAY_X2           0x1041
#define wUNI_GETENGCANMON_X2           0x1042
#define wUNI_GETENGGRPMON_X2           0x1043

#define wUNI_GETPOWCANMNT              0x0050
#define wUNI_GETPOWGRPMNT              0x0051

#define wUNI_GETPOWCANHOU              0x0052
#define wUNI_GETPOWGRPHOU              0x0053
#define wUNI_GETPOWCANHOU48            0x0054
#define wUNI_GETPOWGRPHOU48            0x0055

#define wUNI_GETCNTCANMON              0x0080
#define wUNI_GETCNTCAN                 0x0085

#define wUNI_GETCNTCANMON_X2           0x1080
#define wUNI_GETCNTCAN_X2              0x1085

#define wUNI_GETMAXGRPDAY              0x00A1
#define wUNI_GETMAXGRPMON              0x00A3

#define wUNI_GETDEFCANDAY              0x00B0
#define wUNI_GETDEFGRPDAY              0x00B1

#define wUNI_GETEVENTS_COUNTS          0x00C2
#define wUNI_GETEVENTS                 0x00C0
#define wUNI_GETEVENTS_FIX             0x10C0
#define wUNI_GETEVENTS_MESSAGES        0x00C1

#define wUNI_GETCONFIG                 0x00D0
#define wUNI_GETSENSORS                0x00D1
#define wUNI_GETDIGITALS               0x00D2
#define wUNI_GETSERIALS                0x8012
#define wUNI_GETCANALS                 0x00D3
#define wUNI_GETGROUPS                 0x00D4

#define wUNI_GETOPEN                   0x00E0

#define wUNI_GETPARAMS1                0x00F1
#define wUNI_GETPARAMS2                0x80F1

#define wUNI_GETTRANSIT                0x00F8

#define wUNI_TRANSIT_EXECUTE1          0xFFE0
#define wUNI_TRANSIT_EXECUTE3          0xFFE2
#define wUNI_TRANSIT_EXECUTE4          0xFFE3
#define wUNI_TRANSIT_W                 0xFFE4
#define wUNI_TRANSIT_DEVICE40          0xFFE5

#define wUNI_GETQUERY_CRC              0xFFF0


#define bUNI_OK                        0
#define bUNI_DEFECT                    1
#define bUNI_NOTREADY                  2
#define bUNI_BADCOMMAND                3
#define bUNI_BADACCESS                 4
#define bUNI_GOODPASSWORD              6
#define bUNI_BADPASSWORD               7
#define bUNI_BADDATA                   8
#define bUNI_GOODTRANSIT               9
#define bUNI_BADTRANSIT                10
#define bUNI_OUTOVERFLOW               12
#define bUNI_BADTIME                   13
