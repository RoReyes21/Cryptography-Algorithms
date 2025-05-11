#include "rc4.h"

/**
 * @brief Construct a new Algorithm_RC4::Algorithm_RC4 object
 * 
 * @param k 
 * @param plain_txt 
 */
Algorithm_RC4::Algorithm_RC4(const char* k, const char* plain_txt) {
    strncpy(key, k, sizeof(key) - 1);
    key[sizeof(key) - 1] = '\0';
    strncpy(plain_text, plain_txt, sizeof(plain_text) - 1);
    plain_text[sizeof(plain_text) - 1] = '\0';

    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }

    int j = 0;
    int key_length = strlen(key);

    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_length]) % 256;
        std::swap(S[i], S[j]);
    }

    key_stream_length = strlen(plain_text);
}

/**
 * @brief Function of RC4 algorithm
 * 
 */
void Algorithm_RC4::RC4() {
    generation_PRGA();

    for (int i = 0; i < key_stream_length; i++) {
        cipher_text[i] = (plain_text[i] ^ key_stream[i]);
    }
}

/**
 * @brief Print cipher text
 * 
 */
void Algorithm_RC4::print_cipher_text() {
    for (size_t i = 0; i < key_stream_length; i++) {
        std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << cipher_text[i];
    }
    std::cout << std::endl;
}

/**
 * @brief Function to generation prga
 * 
 */
void Algorithm_RC4::generation_PRGA() {
    int i = 0;
    int j = 0;

    for (int h = 0; h < key_stream_length; h++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        key_stream[h] = S[(S[i] + S[j]) % 256];
    }
}

int main(int argc, char* argv[]) {
    
    char key[256];
    char plain_text[256];

    if (!std::cin.getline(key, sizeof(key)))
        return 1;

    if (!std::cin.getline(plain_text, sizeof(plain_text)))
        return 1;

    Algorithm_RC4 instance(key, plain_text);
    instance.RC4();
    instance.print_cipher_text();

    return 0;
}