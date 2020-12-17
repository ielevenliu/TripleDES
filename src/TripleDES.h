#ifndef __TRIPLEDES__
#define __TRIPLEDES__

#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*
* 
*/
void encryptionTripleDes(uint8_t* plaintext, int len, uint8_t* key1, uint8_t* key2, uint8_t* key3);

/*
* 
*/
void decryptionTripleDes(uint8_t* ciphertext, int len, uint8_t* key1, uint8_t* key2, uint8_t* key3);

#endif //__TRIPLEDES__
