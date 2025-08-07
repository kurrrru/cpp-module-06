#include <ex00/ScalarConverter.hpp>

#include <iostream>
#include <limits>
#include <string>
#include <cerrno>
#include <cmath>
#include <cstdlib>

#include <toolbox/stepmark.hpp>
#include <toolbox/color.hpp>

namespace {
bool isChar(const std::string& input);
bool isInt(const std::string& input);
bool isFloat(const std::string& input);
bool isDouble(const std::string& input);

void convertChar(const std::string& input);
void convertInt(const std::string& input);
void convertFloat(const std::string& input);
void convertDouble(const std::string& input);
void Invalid();

void printChar(const char c);
void printInt(const int i);
void printFloat(const float f);
void printDouble(const double d);
}  // namespace

void ScalarConverter::convert(const std::string& input) {
    Type type = detectType(input);
    switch (type) {
        case CHAR:
            convertChar(input);
            break;
        case INT:
            convertInt(input);
            break;
        case FLOAT:
            convertFloat(input);
            break;
        case DOUBLE:
            convertDouble(input);
            break;
        default:
            Invalid();
            break;
    }
}

ScalarConverter::ScalarConverter() {}
ScalarConverter::~ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) {
    (void)other;
}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return *this;
}

ScalarConverter::Type ScalarConverter::detectType(const std::string& input) {
    if (isInt(input)) {
        return INT;
    } else if (isChar(input)) {
        return CHAR;
    } else if (isFloat(input)) {
        return FLOAT;
    } else if (isDouble(input)) {
        return DOUBLE;
    }
    return INVALID;
}

namespace {

bool isChar(const std::string& input) {
    if (input.size() == 1) {
        return true;
    }
    return false;
}

bool isInt(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    size_t pos = 0;
    if (input[0] == '-' || input[0] == '+') {
        pos++;
    }
    if (input.size() == pos) {
        return false;
    }
    if (input.find_first_not_of("0123456789", pos) == std::string::npos) {
        if (input[pos] == '0' && input.size() > pos + 1) {
            return false;  // No leading zeros allowed
        }
        return true;
    }
    return false;
}

bool isFloat(const std::string& input) {
    if (input.size() < 2) {
        return false;
    }
    std::string prefix = input.substr(0, input.size() - 1);
    if (isDouble(prefix)
        && (*input.rbegin() == 'f' || *input.rbegin() == 'F')) {
        return true;
    }
    return false;
}

/*
    * Check if the string is a valid double
    * - It can be in the form of "-inf", "+inf", "nan"
    * - It can contain a decimal point and an exponent part
    * - It can have leading and trailing spaces
    *
    * Special cases:
    * - "-inf", "+inf", "nan" are valid
    * - ".4", "4." are valid
    * - "4e", "4e+", "3.5e-" are invalid
    */
bool isDouble(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    std::string capitalInput = input;
    for (size_t i = 0; i < input.size(); ++i) {
        capitalInput[i] = std::toupper(input[i]);
    }
    if (capitalInput == "-INF" || capitalInput == "+INF"
        || capitalInput == "INF" || capitalInput == "NAN") {
        return true;
    }
    size_t pos = 0;
    if (input[0] == '-' || input[0] == '+') {
        pos++;
    }
    if (input.size() == pos || input[pos] == 'e' || input[pos] == 'E') {
        return false;
    }
    bool dotSeen = false;
    bool expSeen = false;
    while (true) {
        if (expSeen && input.size() == pos) {
            return false;
        }
        pos = input.find_first_not_of("0123456789", pos);
        if (pos == std::string::npos) {
            break;
        }
        if (input[pos] == '.') {
            if (dotSeen || expSeen) {
                return false;
            }
            if ((pos == 0 || !std::isdigit(input[pos - 1]))
                && (pos + 1 == input.size() || !std::isdigit(input[pos + 1]))) {
                return false;
            }

            dotSeen = true;
            pos++;
            continue;
        }
        if (input[pos] == 'e' || input[pos] == 'E') {
            if (expSeen) {
                return false;
            }
            expSeen = true;
            pos++;
            if (input.size() == pos) {
                return false;
            }
            if (input[pos] == '-' || input[pos] == '+') {
                pos++;
            }
            continue;
        }
        return false;
    }
    return (dotSeen || expSeen);
}

void convertChar(const std::string& input) {
    char c = input[0];
    printChar(c);
    printInt(static_cast<int>(c));
    printFloat(static_cast<float>(c));
    printDouble(static_cast<double>(c));
}

void convertInt(const std::string& input) {
    long longValue = std::strtol(input.c_str(), NULL, 10);
    if (errno == ERANGE || longValue < std::numeric_limits<int>::min()
        || longValue > std::numeric_limits<int>::max()) {
        Invalid();
        return;
    }
    int intValue = static_cast<int>(longValue);
    if (intValue < std::numeric_limits<char>::min()
        || intValue > std::numeric_limits<char>::max()) {
        std::cout << "char: impossible" << std::endl;
    } else {
        printChar(static_cast<char>(intValue));
    }
    printInt(intValue);
    printFloat(static_cast<float>(intValue));
    printDouble(static_cast<double>(intValue));
}

void convertFloat(const std::string& input) {
    float f = std::strtof(input.c_str(), NULL);
    if (errno == ERANGE) {
        Invalid();
        return;
    }
    if (std::isnan(f) || f < std::numeric_limits<char>::min()
        || f > std::numeric_limits<char>::max()) {
        std::cout << "char: impossible" << std::endl;
    } else {
        printChar(static_cast<char>(f));
    }
    if (std::isnan(f) || f < std::numeric_limits<int>::min()
        || f > std::numeric_limits<int>::max()) {
        std::cout << "int: impossible" << std::endl;
    } else {
        printInt(static_cast<int>(f));
    }
    printFloat(f);
    printDouble(static_cast<double>(f));
}

void convertDouble(const std::string& input) {
    double d = std::strtod(input.c_str(), NULL);
    if (errno == ERANGE) {
        Invalid();
        return;
    }
    if (std::isnan(d) || d < std::numeric_limits<char>::min()
        || d > std::numeric_limits<char>::max()) {
        std::cout << "char: impossible" << std::endl;
    } else {
        printChar(static_cast<char>(d));
    }
    if (std::isnan(d) || d < std::numeric_limits<int>::min()
        || d > std::numeric_limits<int>::max()) {
        std::cout << "int: impossible" << std::endl;
    } else {
        printInt(static_cast<int>(d));
    }
    printFloat(static_cast<float>(d));  // No undefined behavior here
    printDouble(d);
}

void Invalid() {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

void printChar(const char c) {
    std::cout << "char: ";
    if (std::isprint(c)) {
        std::cout << "'" << c << "'" << std::endl;
    } else {
        std::cout << "Non displayable" << std::endl;
    }
}

void printInt(const int i) {
    std::cout << "int: " << i << std::endl;
}

void printFloat(const float f) {
    std::cout << "float: " << f;
    if ((std::abs(f) > 1e-6 || f == 0)
        && std::abs(f) < 1e6 && f == static_cast<int>(f)) {
        std::cout << ".0";
    }
    std::cout << "f" << std::endl;
}

void printDouble(const double d) {
    std::cout << "double: " << d;
    if ((std::abs(d) > 1e-6 || d == 0)
        && std::abs(d) < 1e6 && d == static_cast<int>(d)) {
        std::cout << ".0";
    }
    std::cout << std::endl;
}
}  // namespace
