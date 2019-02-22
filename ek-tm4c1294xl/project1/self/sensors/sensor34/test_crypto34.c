/*------------------------------------------------------------------------------
test_crypto34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../../openssl/include/openssl/md5.h"
#include "../../../openssl/include/openssl/aes.h"



static void assert(bool b) {
  while (!b) {
  }
}


uchar*  MD5(const uchar *d, size_t size, uchar *md)
{
  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, d, size);
  MD5_Final(md, &ctx);
  return md;
}


void    TestCrypto34(void) {
  const uchar *md5In = "111111";
  uchar md5Out[16];

  _MD5(md5In, 6, md5Out);

  uchar md5Out2[16] = {0x96,0xE7,0x92,0x18,0x96,0x5E,0xB7,0x2C,0x92,0xA5,0x49,0xDD,0x5A,0x33,0x01,0x12};
  uchar i;
  for (i=0; i<16; i++) {
    assert(md5Out[i] == md5Out2[i]);
  }

  uchar aesIn[] = {0x90,0x0B,0x9B,0xEF,0x21,0x4E,0xD4,0xB5,0xCA,0xB6,0xF1,0x93,0xFB,0x31,0x0E,0x84};
  uchar aesOut[16];

  AES_KEY key;
  AES_set_encrypt_key(md5Out, 128, &key);
  AES_encrypt(aesIn, aesOut, &key);

  uchar aesOut2[16] = {0xFB,0x41,0x50,0xDF,0x9A,0xC4,0x27,0x31,0xB0,0x44,0x6E,0x48,0x53,0x12,0x1C,0x7F};
  for (i=0; i<16; i++) {
    assert(aesOut[i] == aesOut2[i]);
  }
}



