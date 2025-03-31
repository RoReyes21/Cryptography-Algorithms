#include "md2.h"

std::string MD2Algorithm::excecute_algorithm() {
    std::string hash = plain_text;
    
    int padding_len = 16 - (hash.length() % 16);
    hash.append(padding_len, static_cast<char>(padding_len));

    //int checksum[16] = {0};
    //int L = 0;
    //int X[48] = {0};

    //for (int i = 0; i < hash.length(); i + 16) {
        
    //}

    std::vector<unsigned char> checksum(16, 0);
    unsigned char L = 0;

    std::vector<unsigned char> X(48, 0);
    for (size_t i = 0; i < hash.size(); i += 16) {
        std::vector<unsigned char> block(hash.begin() + i, hash.begin() + i + 16);

        for (int j = 0; j < 16; ++j) {
            unsigned char c = block[j];
            checksum[j] ^= S[c ^ L];
            L = checksum[j];
        }

        std::copy(block.begin(), block.end(), X.begin() + 16);

        for (int j = 0; j < 16; ++j) {
            X[32 + j] = block[j] ^ X[j];
        }

        unsigned char t = 0;
        for (int j = 0; j < 18; ++j) {
            for (int k = 0; k < 48; ++k) {
                t = X[k] ^ S[t];
                X[k] = t;
            }
            t = (t + j) % 256;
        }
    }

    hash.append(checksum.begin(), checksum.end());

    X.assign(48, 0);
    for (size_t i = 0; i < hash.size(); i += 16) {
        std::vector<unsigned char> block(hash.begin() + i, hash.begin() + i + 16);

        std::copy(block.begin(), block.end(), X.begin() + 16);

        for (int j = 0; j < 16; ++j) {
            X[32 + j] = block[j] ^ X[j];
        }

        unsigned char t = 0;
        for (int j = 0; j < 18; ++j) {
            for (int k = 0; k < 48; ++k) {
                t = X[k] ^ S[t];
                X[k] = t;
            }
            t = (t + j) % 256;
        }
    }

    std::ostringstream result;
    for (int i = 0; i < 16; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(X[i]);
    }
    return result.str();

    return hash;
}

int main(int argc, char const *argv[])
{
    std::string plain_txt_input;

    if (!std::getline(std::cin, plain_txt_input))
        return -1;

    MD2Algorithm md2_instance(plain_txt_input);
    
    std::string hash = md2_instance.excecute_algorithm();

    std::cout << hash << std::endl;
    
    return 0;
}
