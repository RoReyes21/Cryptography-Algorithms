#ifndef RC4_H
#define RC4_H

#include <iostream>
#include <iomanip>
#include <cstring>

class Algorithm_RC4 {
public:
    Algorithm_RC4(const char* k, const char* plain_txt);

    void RC4();
    void print_cipher_text();

private:
    void generation_PRGA();

    int S[256];
    int key_stream_length;
    int cipher_text[256];
    int key_stream[256];
    char key[256];
    char plain_text[256];
};

#endif