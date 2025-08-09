#include <iostream>
#include <string>

#include <ex00/ScalarConverter.hpp>
#include <toolbox/StepMark.hpp>
#include <toolbox/color.hpp>

int main(int argc, char *const *argv) {
    toolbox::logger::StepMark::setLogFile("scalar_converter.log");
    toolbox::logger::StepMark::setLevel(toolbox::logger::INFO);
    if (argc != 2) {
        toolbox::logger::StepMark::error("Invalid number of arguments.");
        std::cerr << toolbox::color::red << "Usage: " << argv[0] << " <value>"
                << toolbox::color::reset
                << std::endl;
        return EXIT_FAILURE;
    }

    const std::string input = argv[1];
    ScalarConverter::convert(input);

    return EXIT_SUCCESS;
}
