/*------------------------------------------------------------------------------
test_crypto.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../../openssl/include/openssl/md5.h"
#include "../../../openssl/include/openssl/aes.h"
//#include "../../../aes/TI_aes_128_encr_only.h"



unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md)
{
  MD5_CTX c;
  MD5_Init(&c);
  MD5_Update(&c, d, n);
  MD5_Final(md, &c);
  return md;
}


void    assert(bool b) {
  while (!b) {
  }
}


void    TestCrypto(void) {
  const unsigned char* pass = "111111";
  unsigned char rgbKey[16];

  MD5(pass, 6, rgbKey);

  unsigned char rgbKey2[16] = {0x96,0xE7,0x92,0x18,0x96,0x5E,0xB7,0x2C,0x92,0xA5,0x49,0xDD,0x5A,0x33,0x01,0x12};
  uchar i;
  for (i=0;i<16;i++) {
    assert (rgbKey[i] == rgbKey2[i]);
  }

  unsigned char in[] = {0x90, 0x0B, 0x9B, 0xEF, 0x21, 0x4E, 0xD4, 0xB5, 0xCA, 0xB6, 0xF1, 0x93, 0xFB, 0x31, 0x0E, 0x84};
  unsigned char out[16];

  AES_KEY encryptKey;
  AES_set_encrypt_key(rgbKey, 128, &encryptKey);
  AES_encrypt(in, out, &encryptKey);

  unsigned char out2[16] ={0xFB,0x41,0x50,0xDF,0x9A,0xC4,0x27,0x31,0xB0,0x44,0x6E,0x48,0x53,0x12,0x1C,0x7F};
  for (i=0;i<16;i++) {
    assert (out[i] == out2[i]);
  }
}



