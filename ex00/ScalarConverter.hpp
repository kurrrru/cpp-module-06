#pragma once

#include <string>

class ScalarConverter {
 public:
    static void convert(const std::string& input);

 private:
    ScalarConverter();
    ~ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);

    enum Type {
        CHAR,
        INT,
        FLOAT,
        DOUBLE,
        INVALID
    };

    static Type detectType(const std::string& input);
};
