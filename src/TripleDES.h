#ifndef __TRIPLEDES__
#define __TRIPLEDES__

#include <stdio.h>
#include <string.h>

/*
* 
*/
void encryptionTripleDes(char* plaintext, int len, char* key1, char* key2, char* key3);

/*
* 
*/
void decryptionTripleDes(char* ciphertext, int len, char* key1, char* key2, char* key3);

#endif //__TRIPLEDES__
