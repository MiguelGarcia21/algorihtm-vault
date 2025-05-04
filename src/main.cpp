#include <iostream>
#include "../include/md5_hash.h"

int main() {
    std::string input;
    std::cout << "Enter a string to hash: ";
    std::getline(std::cin, input);

    std::string hash = compute_md5(input);
    std::cout << "MD5 Hash: " << hash << std::endl;

    return 0;
}
