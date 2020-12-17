#ifndef __TRIPLEDES__
#define __TRIPLEDES__

#include <stdio.h>
#include <string.h>

/*
* 
*/
void encryptionTripleDes(uint8_t* plaintext, int len, char* key1, char* key2, char* key3);

/*
* 
*/
void decryptionTripleDes(uint8_t* ciphertext, int len, char* key1, char* key2, char* key3);

#endif //__TRIPLEDES__
