#include "md2.h"

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
