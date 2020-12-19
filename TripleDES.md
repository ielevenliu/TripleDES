```c++
/*
* Triple DES encryption API
* Encrypt an integer multiple of 8 of the uint8_t(unsigned char) character, and finally less than 8 unencrypted
* @param[in/out] In: plaintext; Out: ciphertext
* @param Plaintext length
* @param Key 1 of length 8
* @param Key 2 of length 8
* @param Key 3 of length 8
*/
void encryptionTripleDes(uint8_t* plaintext, int len, uint8_t* key1, uint8_t* key2, uint8_t* key3);

/*
* Triple DES decryption API
* Decryption an integer multiple of 8 of the uint8_t(unsigned char) character, and finally do not decrypt less than 8
* @param[in/out] In: ciphertext; Out: plaintext
* @param Ciphertext length
* @param Key 1 of length 8
* @param Key 2 of length 8
* @param Key 3 of length 8
*/
void decryptionTripleDes(uint8_t* ciphertext, int len, uint8_t* key1, uint8_t* key2, uint8_t* key3);
```

使用方法：

方法1：直接将 .cpp和.h 文件添加到工程中，然后调用加密或者解密函数

方法2：利用cmake工具通过CMakeLists.txt文件生成动态库和静态库添加到工程中，然后调用加密或者解密函数(目前测试支持Linux/macOS/Windows)