#include <iostream>
#include <string>

#include <ex00/ScalarConverter.hpp>
#include <toolbox/stepmark.hpp>
#include <toolbox/color.hpp>

int main(int argc, char *const *argv) {
    toolbox::logger::StepMark::setLogFile("scalar_converter.log");
    toolbox::logger::StepMark::setLevel(toolbox::logger::INFO);
    if (argc != 2) {
        toolbox::logger::StepMark::error("Invalid number of arguments.");
        std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
        return 1;
    }

    const std::string input = argv[1];
    ScalarConverter::convert(input);

    return 0;
}
