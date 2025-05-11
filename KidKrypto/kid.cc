// @author: Rodrigo Reyes
#include "kid.h"

#include <iostream>
#include <sstream>

/** @brief Computes the modulo operation ensuring a non-negative result.
* 
* @param a The integer to compute the modulo for.
* @return int The result of a modulo n, adjusted to be non-negative.
*/
int KidKrypto::mod(int a) {
    int r = a % n;
    return r >= 0 ? r : r + n;
}

/**
 * @brief Generates the encryption and decryption keys based on the provided context.
 * 
 * @param inputs The context containing the parameters a, b, A, B, and msg.
 */
void KidKrypto::generate_keys(kid_krypto_context inputs) {
    int M = inputs.a * inputs.b - 1;
    e = inputs.A * M + inputs.a;
    d = inputs.B * M + inputs.b;
    n = (e * d - 1) / M;
}

/**
 * @brief Encrypts a message using the KidKrypto algorithm.
 * 
 * @param inputs The context containing the parameters a, b, A, B, and the message to encrypt.
 * @return int The encrypted message.
 */
int KidKrypto::encrypt(kid_krypto_context inputs) {
    
    generate_keys(inputs);
    int cipher_msg = mod(inputs.msg * e);
    
    return cipher_msg;
}

/**
 * @brief Decrypts a message using the KidKrypto algorithm.
 * 
 * @param inputs The context containing the parameters a, b, A, B, and the message to decrypt.
 * @return int The decrypted message.
 */
int KidKrypto::decrypt(kid_krypto_context inputs) {
    
    generate_keys(inputs);
    int decrypted_msg = mod(inputs.msg * d);
    
    return decrypted_msg;
}

int main() {

    std::string mode;
    kid_krypto_context inputs;

    char buffer[256];
    if (!std::getline(std::cin, mode))
        return 1;
    if (!std::cin.getline(buffer, sizeof(buffer)) || !(std::istringstream(buffer) >> inputs.a))
        return 1;
    if (!std::cin.getline(buffer, sizeof(buffer)) || !(std::istringstream(buffer) >> inputs.b))
        return 1;
    if (!std::cin.getline(buffer, sizeof(buffer)) || !(std::istringstream(buffer) >> inputs.A))
        return 1;
    if (!std::cin.getline(buffer, sizeof(buffer)) || !(std::istringstream(buffer) >> inputs.B))
        return 1;
    if (!std::cin.getline(buffer, sizeof(buffer)) || !(std::istringstream(buffer) >> inputs.msg))
        return 1;

    KidKrypto instance_kidkrypto;

    int result = !mode.compare("E") ? instance_kidkrypto.encrypt(inputs) :
                 !mode.compare("D") ? instance_kidkrypto.decrypt(inputs) :
    []() { std::cout << "Error: Invalid operation" << std::endl; return 1;}();

    std::cout << result << std::endl;

    return 0;
}