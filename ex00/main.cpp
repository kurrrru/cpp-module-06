#include "ScalarConverter.hpp"

#include <iostream>
#include <string>

int main(int argc, char *const *argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
        return 1;
    }

    const std::string input = argv[1];
    ScalarConverter::convert(input);

    return 0;
}