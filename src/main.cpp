#include <iostream>
#include <string>

extern "C" {
#include "TripleDES.h"
}

int main() {
    std::string plain("12345678");
    std::string key1("01234567");
    std::string key2("01234567");
    std::string key3("01234567");
    std::cout << plain << std::endl;
    encryptionTripleDes(
        (uint8_t*)const_cast<char*>(plain.c_str()), 8,
        (uint8_t*)const_cast<char*>(key1.c_str()),
        (uint8_t*)const_cast<char*>(key2.c_str()),
        (uint8_t*)const_cast<char*>(key3.c_str())
	);

    std::cout << plain << std::endl;
    decryptionTripleDes(
	    (uint8_t*)const_cast<char*>(plain.c_str()), 8,
        (uint8_t*)const_cast<char*>(key1.c_str()),
        (uint8_t*)const_cast<char*>(key2.c_str()),
        (uint8_t*)const_cast<char*>(key3.c_str()));
    std::cout << plain << std::endl;

    std::cout << "hello world" << std::endl;

    return 0;
}
