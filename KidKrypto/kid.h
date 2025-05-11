// @author: Rodrigo Reyes 
#ifndef KID_H
#define KID_H

typedef struct KidKryptoContext {
    int a, b, A, B, msg;
} kid_krypto_context;

class KidKrypto {

public:
    KidKrypto() {}
    int encrypt(kid_krypto_context inputs);
    int decrypt(kid_krypto_context inputs);

    void generate_keys(kid_krypto_context inputs);
    int mod(int a);

private:
    int e;
    int d;
    int n;
};

#endif