/*------------------------------------------------------------------------------
md5.h


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


void    RunMD5(void) {
  const unsigned char* string = "111111";
  unsigned char digest[16];
  MD5(string, 6, digest);

  unsigned char in[] = {0x90, 0x0B, 0x9B, 0xEF, 0x21, 0x4E, 0xD4, 0xB5, 0xCA, 0xB6, 0xF1, 0x93, 0xFB, 0x31, 0x0E, 0x84};
  unsigned char out[16];

  AES_KEY encryptKey;
  AES_set_encrypt_key(digest, 128, &encryptKey);

  AES_encrypt(in, out, &encryptKey);
//  aes_encrypt(state,digest);
//  for (i=0;i<16;i++) {
//    if (state[i] != ciphertext[i]) {
//      err_count++;
//    }
//  }

}



