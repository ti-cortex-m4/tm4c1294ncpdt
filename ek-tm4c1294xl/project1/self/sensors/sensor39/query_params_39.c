/*------------------------------------------------------------------------------
query_params_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/wrappers.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc.h"
#include "dlms_push.h"
#include "query_params_39.h"



// class 3, attribute 2: value
// class 3, attribute 3: scaler_unit
void    QueryGetRequestDLMS(const obis_t  obis, uchar  bClass, uchar  bAttribute, runner39  r)
{
  uint wSize = 23 + GetHdlcAddressesSize(); // 0x19 25

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar((r.bNR << 5) | 0x10 | (r.bNS << 1) | 0x00);

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0x80 | (r.bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00);
  PushChar(bClass); // class

  PushOBIS_DLMS(obis);

  PushChar(bAttribute); // attribute
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2); // 27
}



void    QueryGetRegisterValueDLMS(const obis_t  obis, runner39  r)
{
  QueryGetRequestDLMS(obis, 3, 2, r);
}

void    QueryGetRegisterScalerDLMS(const obis_t  obis, runner39  r)
{
  QueryGetRequestDLMS(obis, 3, 3, r);
}


uint    ReadType18ULong16(void)
{
  InitPop(14 + GetHdlcAddressesSize());
  return PopIntBig();
}



// Blue Book: 4.1.5 Common data types
ulong64_ PopUnsignedValueDLSM(void)
{
  uchar bDataType = PopChar();
#ifdef MONITOR_39  
  MonitorString("\n bDataType="); MonitorCharDec(bDataType);
#endif  

  if (bDataType == 17) // unsigned [17] Unsigned8 0…255
  {
    uchar value = PopIntBig();
    return GetLong64(value, true, 0);
  }
  if (bDataType == 18) // long-unsigned [18] Unsigned16 0…65_535
  {
    uint value = PopIntBig();
    return GetLong64(value, true, 0);
  }
  if (bDataType == 6) // double-long-unsigned [6] Unsigned32 0…4_294_967_295
  {
    ulong value = PopLongBig();
    return GetLong64(value, true, 0);
  }
  if (bDataType == 21) // long64-unsigned [21] Unsigned64 0…2^64-1
  {
    uint64_t value = PopLongBig()*0x100000000 + PopLongBig();
    return GetLong64(value, true, 0);
  }

  // error(unknown_data_type, bDataType)
  return GetLong64Error(1);
}


ulong64_ ReadUnsignedValueDLSM(void)
{
  InitPop(12 + GetHdlcAddressesSize());

  uchar bDataAccessResult = PopChar();
#ifdef MONITOR_39
  MonitorString("\n bDataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif
  if (bDataAccessResult != 0) {
    // error(no_success, bDataAccessResult)
    return GetLong64Error(0);
  }

  return PopUnsignedValueDLSM();
}


// 7e a0 16 03 03 96 3b 99 e6 e7 00 c4 01 83  00 02 02 0f 00 16 1e  ff ba 7e
schar2  ReadRegisterScaler(void)
{
  InitPop(16 + GetHdlcAddressesSize());

//  uchar bDataAccessResult = PopChar();
//#ifdef MONITOR_39
//  MonitorString("\n bDataAccessResult="); MonitorCharDec(bDataAccessResult);
//#endif
//  if (bDataAccessResult != 0) {
//    // TODO error(no_success, bDataAccessResult)
//    return GetLong64Error(0);
//  }

  schar bScaler = PopChar();
  uchar bUnit = PopChar();
#ifdef MONITOR_39
  MonitorString("\n bScaler="); MonitorCharHex(bScaler);
  MonitorString("\n bUnit="); MonitorCharDec(bUnit);
#endif

  return GetSChar2(bScaler, true);
}



// The Blue Book: 4.3.2 Register (class_id = 3, version = 0)
schar   ReadScalerUnitDLMS(bool*  pfValid) {

  InitPop(12 + GetHdlcAddressesSize());

  uchar bDataAccessResult = PopChar();
#ifdef MONITOR_39  
  MonitorString("\n bDataAccessResult="); MonitorCharDec(bDataAccessResult);
#endif  
  if (bDataAccessResult != 0) {
    // TODO error(no_success, bDataAccessResult)
    (*pfValid) = false;
    return 0;
  }

  schar bScaler = PopChar();
  uchar bUnit = PopChar();
#ifdef MONITOR_39  
  MonitorString("\n bScaler="); MonitorCharHex(bScaler);
  MonitorString("\n bUnit="); MonitorCharDec(bUnit);
#endif    
  (*pfValid) = true;
  return bScaler;
}




/*
<GetRequest>
  <GetRequestNormal>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 10-->
    <InvokeIdAndPriority Value="8A" />
    <AttributeDescriptor>
      <!--REGISTER-->
      <ClassId Value="0003" />
      <!--1.0.72.7.0.255-->
      <InstanceId Value="0100480700FF" />
      <AttributeId Value="02" />
    </AttributeDescriptor>
  </GetRequestNormal>
</GetRequest>
11-06-2020 18:37:40.897  HDLC -> 7E A0 19 03 03 54 DC CE E6 E6 00 C0 01 8A 00 03 01 00 48 07 00 FF 02 00 70 AA 7E
<GetResponse>
  <GetResponseNormal>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 10-->
    <InvokeIdAndPriority Value="8A" />
    <Result>
      <Data>
        <UInt16 Value="08CA" /> 2250
      </Data>
    </Result>
  </GetResponseNormal>
</GetResponse>
11-06-2020 18:37:41.147  HDLC <- 7E A0 13 03 03 74 70 33 E6 E7 00 C4 01 8A 00 12 08 CA 5B 90 7E
*/


// check return type
// 00 0x12 success ?, ulong 16
