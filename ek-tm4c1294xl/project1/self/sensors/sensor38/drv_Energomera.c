/*
#include <drv_dev.h>
#include "include.h"
#include "info_param.h"
#include "mess_port.h"
#include "energomera_3xx.h"
#include "crc.h"
#include "info_3min.h"
#include "flash.h"
#include "uart_pt.h"
#include "devPassword.h"
#include "info_curr.h"
#include "info_day.h"

#define ERR_PARAMS      1  // Неверные параметры команды.
#define ERR_COMMAND     2  // Неизвестная команда.
#define ERR_NOTFOUND    3  // Не найден
#define ERR_BUSY        4  // Маршрутизатор занят, команду следует повторить позже
#define ERR_OUTOFMEMORY 5  // Недостаточно памяти
#define ERR_WRITE       6  // Ошибка записи
#define ERR_NOTREADY    7  // Данные не готовы
#define ERR_NOANSWER    8  // Нет ответа от оконечного устройства
#define ERR_CONNECT     9  // Ошибка связи.
#define ERR_READ        10 // Ошибка чтения из ПЗУ.
#define ERR_INTEGRITY   11 // Ошибка целостности данных в ПЗУ.

#pragma DATA_SECTION(".sdram_data")
uint32_t crc32_tab[] = {
   0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
   0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
   0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
   0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
   0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
   0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
   0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
   0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
   0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
   0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
   0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
   0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
   0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
   0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
   0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
   0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
   0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
   0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
   0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
   0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
   0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
   0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
   0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
   0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
   0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
   0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
   0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
   0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
   0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
   0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
   0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
   0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
   0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
   0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
   0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
   0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
   0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
   0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
   0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
   0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
   0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
   0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
   0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

/ *
 *  =======================================================
 *  =========  =======================
 *  =======================================================
 * /
int EncodeInt(int64_t value, uint8_t *send_buffer_position) {
  int num=0; // число записанных байт (лбф + 7 бит)
  char ch;

  //условие остановки кодирования: оставшиеся биты и последний записанный либо нули либо единицы
  while ((value>>(num*7-1)) != -1 && (value>>(num*7-1)) != 0 || num==0) {
    ch = (char)(value>>(num*7));                         // следующие 7 бит
    *send_buffer_position++ = ch | 0x80;                  // запись с флагом lbf
    num++; //записали очередные 7 бит
  }
  *(send_buffer_position-1) &= 0x7F;                      //убрать флаг у последнего байта
  return num;
}

/ *
 *  =======================================================
 *  =========  =======================
 *  =======================================================
 * /
int64_t DecodeInt(uint8_t *receive_buffer_position, MdUns *position) {
  uint64_t result=0;
  uint64_t ch;
  int num=0;

  receive_buffer_position += *position;

  do  {
    ch = (*receive_buffer_position & 0x7F);               // читаем очередные 7 бит
    result += ch<<(num*7);                                //добавляем к результату
    num++;                                                // можно num+=7;, тогда вместо (num*7) везде просто num
  }
  while((*(receive_buffer_position++) & 0x80));          //условие выхода нулевой флаг lbf

  if (ch>>6) //если последний принятый бит был 1 заполняем старшие разряды единицами
    result |= 0xffffffffffffffff<<(num*7);

  *position += num;
  return (int64_t)result;
}

/ *
 *  =======================================================
 *  ========= кодирование пароля ==========================
 *  =======================================================
   buff - буфер строки пароля
   size - количество символов в пароле
   random - случайное число, выданное сервером при запросе авторизации
 * /
uint32_t hash( uint8_t * buff, int size, uint32_t random ) {
  uint32_t crc = 0xffffffffLU;
  int i;

  for( i=0; i<size; i++ ) {
    if (buff[i] == 0x00) break;
    crc = crc32_tab[ (crc ^ buff[i]) & 0xff ] ^ (crc >> 8);
  }
  return crc ^ random ^ 0xffffffffLU;
}

/ *
 *  =======================================================
 *  ========= битовое кодирование =======================
 *  =======================================================
 * /
MdUns muCodeBitArr(unsigned char *pdataout, unsigned char *pdatain, MdUns length) {
  MdUns            wiId = 0, woId = 0;
  UINT8_BITS       in_data, out_data;

  if (length == 0) return 0;

  for (;;) {
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b0 = in_data.bits.b0;
    out_data.bits.b1 = in_data.bits.b1;
    out_data.bits.b2 = in_data.bits.b2;
    out_data.bits.b3 = in_data.bits.b3;
    out_data.bits.b4 = in_data.bits.b4;
    out_data.bits.b5 = in_data.bits.b5;
    out_data.bits.b6 = in_data.bits.b6;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b1 = in_data.bits.b0;
    out_data.bits.b2 = in_data.bits.b1;
    out_data.bits.b3 = in_data.bits.b2;
    out_data.bits.b4 = in_data.bits.b3;
    out_data.bits.b5 = in_data.bits.b4;
    out_data.bits.b6 = in_data.bits.b5;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b6;
    out_data.bits.b1 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b2 = in_data.bits.b0;
    out_data.bits.b3 = in_data.bits.b1;
    out_data.bits.b4 = in_data.bits.b2;
    out_data.bits.b5 = in_data.bits.b3;
    out_data.bits.b6 = in_data.bits.b4;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b5;
    out_data.bits.b1 = in_data.bits.b6;
    out_data.bits.b2 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b3 = in_data.bits.b0;
    out_data.bits.b4 = in_data.bits.b1;
    out_data.bits.b5 = in_data.bits.b2;
    out_data.bits.b6 = in_data.bits.b3;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b4;
    out_data.bits.b1 = in_data.bits.b5;
    out_data.bits.b2 = in_data.bits.b6;
    out_data.bits.b3 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b4 = in_data.bits.b0;
    out_data.bits.b5 = in_data.bits.b1;
    out_data.bits.b6 = in_data.bits.b2;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b3;
    out_data.bits.b1 = in_data.bits.b4;
    out_data.bits.b2 = in_data.bits.b5;
    out_data.bits.b3 = in_data.bits.b6;
    out_data.bits.b4 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b5 = in_data.bits.b0;
    out_data.bits.b6 = in_data.bits.b1;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b2;
    out_data.bits.b1 = in_data.bits.b3;
    out_data.bits.b2 = in_data.bits.b4;
    out_data.bits.b3 = in_data.bits.b5;
    out_data.bits.b4 = in_data.bits.b6;
    out_data.bits.b5 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b6 = in_data.bits.b0;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b1;
    out_data.bits.b1 = in_data.bits.b2;
    out_data.bits.b2 = in_data.bits.b3;
    out_data.bits.b3 = in_data.bits.b4;
    out_data.bits.b4 = in_data.bits.b5;
    out_data.bits.b5 = in_data.bits.b6;
    out_data.bits.b6 = in_data.bits.b7;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;
  }

  if (out_data.Val == 0) {
    woId--;
    out_data.Val = pdataout[woId];
  }
  out_data.bits.b7 = 0;
  pdataout[woId++] = out_data.Val;

  return woId;
}

/ *
 *  =======================================================
 *  ========= битовое декодирование =======================
 *  =======================================================
 * /
unsigned char * pucDecodeBitArr(unsigned char *pdataout, unsigned char *pdatain) {
  unsigned char  in_data, out_data = 0;
  MdUns            boId = 0, wiId = 0, woId = 0;

  for (;;) {
    in_data = pdatain[wiId++];
    for (MdUns biId=0; biId<8; biId++) {
      if (in_data & (0x01 << biId)) {
        if (biId != 7)
          out_data |= (0x01 << boId++);
      }
      else {
        if (biId == 7) {
          pdataout[woId] = out_data;
          return &(pdatain[wiId]);
        }
        out_data &= ~(0x01 << boId++);
      }
      if (boId >=8) {
        pdataout[woId++] = out_data;
        out_data = boId = 0;
      }
    }
    if (wiId > 256) break;
  }
  return NUL;
}

/ *
 *  =======================================================
 *  ===== проверяет на совпадение логического адреса ======
 *  =======================================================
 * /
Int CLdrvEM::drvTestNetAddr() {
  MdUns              *buf = (MdUns *)hInfo->pbuf;
  UartPortHandle     port  = &ports[hInfo->portId];
  MdUns              devId = port->currDevDrv->Id.dev;
  LgUns              addr;

  if (port->status == IOM_COMPLETED) {
    dataPackReadLong(buf, 2, &addr);
    if ( dataSwapByteInLong(hInfo->netAdress) != addr ) {
      messRecord(hInfo->portId, 84/ *<%d> сетевой адрес?* / , CL_MIDL,
                 devId);
      return IOM_WAIT_ANSWER_FAULT;
    }
    else return IOM_COMPLETED;
  }
  return port->status;
}
/ *
 *  =======================================================
 *  проверяет на длину ответа и наличие стар/стоповых байт
 *  =======================================================
 * /
Int CLdrvEM::drvTestSize(MdUns usDataLen) {
   MdUns               *buf = (MdUns *)hInfo->pbuf;
   UartPortHandle      port  = &ports[hInfo->portId];

   if (port->status == IOM_COMPLETED) {
      if (usDataLen < 10) {
         return IOM_DATA_ERROR;
      }
      else {
         if ((dataPackReadChar(buf, 0) == 0xC0)&&(dataPackReadChar(buf, usDataLen-1) == 0xC0))
            return IOM_COMPLETED;
         else
            return IOM_DATA_ERROR;
      }
   }
   return port->status;
}
/ *
 *  =======================================================
 *  ======== проверяет CRC ответа =========================
 *  =======================================================
 * /
Int CLdrvEM::drvTestCRC(MdUns usDataLen) {
   UartPortHandle      port  = &ports[hInfo->portId];
   MdUns               *buf = (MdUns *)hInfo->pbuf;

   if (port->status == IOM_COMPLETED) {
      // восстановление специальных символов
      hInfo->size = muRestoreEscSimv(buf, usDataLen);
      if ( EnergoMeraCRC( (unsigned char *)hInfo->pbuf, hInfo->size-2, 1) ) {
         SetIndStatusUarts(&ports[hInfo->portId], STATUS_UART_ERROR);
         return IOM_WAIT_ANSWER_FAULT;
      }
      else {
         if ((dataPackReadChar(buf, 0) == 0xC0)&&(dataPackReadChar(buf, hInfo->size-1) == 0xC0))
            return IOM_COMPLETED;
         else
            return IOM_DATA_ERROR;
      }
   }
   return port->status;
}
/ *
 *  =======================================================
 *  ===== проверяет на совпадение логического адреса ======
 *  =======================================================
 * /
Int CLdrvEM::drvTestTest() {
  UartPortHandle      port  = &ports[hInfo->portId];
  MdUns               *buf = (MdUns *)hInfo->pbuf;

  if (port->status == IOM_COMPLETED) {
    // приведение информации к нормальному виду
    for (MdUns id=0; id<hInfo->size/2 + 1; id++) {
      buf[id] = dataSwapByte(buf[id]);
    }
  }
  return port->status;
}

/ *
 *  =======================================================
 *  === заполняет заголовок пакета запроса информацией ====
 *  =======================================================
 * /
MdUns CLdrvEM::drvWrapperBegin() {
  MdUns             poz  = 0;
  MdUns             *buf = (MdUns *)hInfo->pbuf;

  // необходимо ждать ответ
  hInfo->waitAnswer = TRUE;
  hInfo->size = RXTXBUFSIZE;

  // очистка буфера перед заполнением
  memset(buf, 0, UARTBUFSIZE - hInfo->numChansInDev*2*(MAX_TARIF_COUNT+1 + 1) -
         hInfo->numChansInDev*2*6);

  // заголовок
  dataPack8toBuf(buf, &poz, 0x06);
  // логический адресс
  dataPack32toBuf(buf, &poz, dataSwapByteInLong(hInfo->netAdress));
  // постоянная часть
  dataPack8toBuf(buf, &poz, 0x00);
  dataPack8toBuf(buf, &poz, 0x06);

  return poz;
}

/ *
 *  =======================================================
 *  === заполняет окончание пакета запроса информацией ====
 *  =======================================================
 * /
MdUns CLdrvEM::drvWrapperEnd(MdUns poz) {
  MdUns             *buf = (MdUns *)hInfo->pbuf;
  char             c;

  dataPack16toBuf(buf, &poz, EnergoMeraCRC((unsigned char *)(buf), poz, 0));

  for (MdUns i=0; i<poz; i++) {
    c = dataPackReadChar(buf, poz-1 - i);
    dataPackWriteChar(buf, poz - i, c);
  }

  poz = muReplaceEscSimv(buf, poz+2);

  return poz;
}

/ *
 *  =======================================================
 *  =======================================================
 *  =======================================================
 * /

/ *
 *  =======================================================
 *  ===== проверяет на совпадение логического адреса ======
 *  =======================================================
 * /
Int CLdrvEM_M3172::drvTestNetAddr() {
  MdUns              *buf = (MdUns *)hInfo->pbuf;
  UartPortHandle     port  = &ports[hInfo->portId];
  MdUns              devId = port->currDevDrv->Id.dev;
  LgUns              addr;

  if (port->status == IOM_COMPLETED) {
    dataPackReadLong(buf, 2, &addr);
    hInfo->netAdressM = dataSwapByteInLong(addr);
    dataPackReadLong(buf, 8, &addr);
    if ( dataSwapByteInLong(hInfo->netAdress) != addr ) {
      messRecord(hInfo->portId, 84/ *<%d> сетевой адрес?* / , CL_MIDL,
                 devId);
      return IOM_WAIT_ANSWER_FAULT;
    }
    else return IOM_COMPLETED;
  }
  return port->status;
}

/ *
 *  =======================================================
 *  проверяет на длину ответа и наличие стар/стоповых байт
 *  =======================================================
 * /
Int CLdrvEM_M3172::drvTestSize(MdUns usDataLen) {
  MdUns               *buf = (MdUns *)hInfo->pbuf;
  UartPortHandle      port  = &ports[hInfo->portId];

  if (port->status == IOM_COMPLETED) {
    if (usDataLen < 10) {
      return IOM_DATA_ERROR;
    }
    else {
      if ((dataPackReadChar(buf, 0) == 0xC0)&&(dataPackReadChar(buf, usDataLen-1) == 0xC0))
        return IOM_COMPLETED;
      else
        return IOM_DATA_ERROR;
    }
  }
  return port->status;
}

/ *
 *  =======================================================
 *  ======== проверяет CRC ответа =========================
 *  =======================================================
 * /
Int CLdrvEM_M3172::drvTestCRC(MdUns usDataLen) {
  UartPortHandle      port  = &ports[hInfo->portId];
  MdUns               *buf = (MdUns *)hInfo->pbuf;

  if (port->status == IOM_COMPLETED) {
    // восстановление специальных символов
    hInfo->size = muRestoreEscSimv(buf, usDataLen);
    if ( EnergoMeraCRC_M( (unsigned char *)hInfo->pbuf, hInfo->size-1) ) {
      SetIndStatusUarts(&ports[hInfo->portId], STATUS_UART_ERROR);
      return IOM_CRC_ERROR;
    }
    else {
      if ((dataPackReadChar(buf, 0) == 0xC0)&&(dataPackReadChar(buf, hInfo->size-1) == 0xC0))
        return IOM_COMPLETED;
      else
        return IOM_DATA_ERROR;
    }
  }
  return port->status;
}

/ *
 *  =======================================================
 *  ===== проверяет на совпадение логического адреса ======
 *  =======================================================
 * /
Int CLdrvEM_M3172::drvTestTest() {
  UartPortHandle      port  = &ports[hInfo->portId];
  MdUns               *buf = (MdUns *)hInfo->pbuf;
//  MdUns               min_time, max_time;
  uint8_t             codErr, codCmd;

  if (port->status != IOM_COMPLETED) return port->status;

  // приведение информации к нормальному виду
  for (MdUns id=0; id<hInfo->size/2 + 1; id++) {
    buf[id] = dataSwapByte(buf[id]);
  }

  codCmd = ((uint8_t *)buf)[7];
  if (codCmd == 0x14) {
    // C002  7856 3412  8014   37F4 9303   3C00 3C 00     5A 92  C0
//    min_time = buf[6];
//    max_time = buf[7];
//    sprintf(strGlb0,"min = %d max = %d", min_time, max_time);
//    hotPrintf(hInfo->portId, strGlb0);
    hInfo->numQuery = CMD_M3172_TIME;
    port->status = IOM_EM_TIME;
  }
  else if (codCmd == 0x12) { // DATA_GET
    port->status = IOM_COMPLETED;
  }
  else if (codCmd == 0x13) { // ABORT
    port->status = IOM_COMPLETED;
  }
  else if (codCmd == 0x14) { // TIME
    port->status = IOM_COMPLETED;
  }
  else if (codCmd == 0x1F) { // ERROR
    codErr = ((uint8_t *)buf)[12];
    switch (codErr) {
      case ERR_PARAMS:
        messString(hInfo->portId, (String)"Неверные параметры команды");
        break;
      case ERR_COMMAND:
        messString(hInfo->portId, (String)"Неизвестная команда");
        break;
      case ERR_NOTFOUND:
        messString(hInfo->portId, (String)"Не найден");
        break;
      case ERR_BUSY:
        messString(hInfo->portId, (String)"Маршрутизатор занят");
        port->status = IOM_EM_ERR_BUSY;
        return port->status;
      case ERR_OUTOFMEMORY:
        messString(hInfo->portId, (String)"Недостаточно памяти");
        break;
      case ERR_WRITE:
        messString(hInfo->portId, (String)"Ошибка записи");
        break;
      case ERR_NOTREADY:
        messString(hInfo->portId, (String)"Данные не готовы");
        break;
      case ERR_NOANSWER:
        messString(hInfo->portId, (String)"Нет ответа от оконечного устройства");
        break;
      case ERR_CONNECT:
        messString(hInfo->portId, (String)"Ошибка связи");
        break;
      case ERR_READ:
        messString(hInfo->portId, (String)"Ошибка чтения из ПЗУ");
        break;
      case ERR_INTEGRITY:
        messString(hInfo->portId, (String)"Ошибка целостности данных в ПЗУ");
        break;
      default:
        sprintf(strGlb0,"Ошибка код: = %d", codErr);
        messString(hInfo->portId, strGlb0);
    }
    port->status = IOM_DATA_ERROR;
  }
  else {
    sprintf(strGlb0,"код команды: = %d", codCmd);
    messString(hInfo->portId, strGlb0);
  }
  return port->status;
}

/ *
 *  =======================================================
 *  === заполняет заголовок пакета запроса информацией ====
 *  =======================================================
 * /
MdUns CLdrvEM_M3172::drvWrapperBegin() {
  MdUns             poz  = 0;
  MdUns             *buf = (MdUns *)hInfo->pbuf;

  // необходимо ждать ответ
  hInfo->waitAnswer = TRUE;
  hInfo->size = RXTXBUFSIZE;

  // очистка буфера перед заполнением
  memset(buf, 0, UARTBUFSIZE - hInfo->numChansInDev*2*(MAX_TARIF_COUNT+1 + 1) -
         hInfo->numChansInDev*2*6);

  // C0  02  78 56 34 12  00  13  37 F4 93 03   D9 C3  C0

  // заголовок
  dataPack8toBuf(buf, &poz, 0xC0);
  dataPack8toBuf(buf, &poz, 0x02);
  // логический адресс
  dataPack32toBuf(buf, &poz, dataSwapByteInLong(hInfo->netAdressM));
  dataPack8toBuf(buf, &poz, 0x00);
  dataPack8toBuf(buf, &poz, 0x00); // место для кода команды

  // логический адресс
  dataPack32toBuf(buf, &poz, dataSwapByteInLong(hInfo->netAdress));

  return poz;
}

/ *
 *  =======================================================
 *  === заполняет окончание пакета запроса информацией ====
 *  =======================================================
 * /
MdUns CLdrvEM_M3172::drvWrapperEnd(MdUns poz) {
  MdUns             *buf = (MdUns *)hInfo->pbuf;

  dataPack16toBuf(buf, &poz, EnergoMeraCRC_M((unsigned char *)(buf), poz));

  poz = muReplaceEscSimv(buf, ++poz);

  return poz;
}

/ *
 *  =======================================================
 *  =======================================================
 *  =======================================================
 * /
 
*/
