#include <iostream>
#include <exception>
#include <sstream>
#include <string>

#include <ex02/A.hpp>
#include <ex02/B.hpp>
#include <ex02/C.hpp>
#include <ex02/Base.hpp>
#include <ex02/funcs.hpp>
#include <toolbox/StepMark.hpp>
#include <toolbox/color.hpp>

int main() {
    toolbox::logger::StepMark::setLogFile("dynamic_cast.log");
    toolbox::logger::StepMark::setLevel(toolbox::logger::INFO);
    Base* instance = generate();
    identify(instance);
    identify(*instance);
    delete instance;

    try {
        Base* base = new Base();
        toolbox::logger::StepMark::info("Generating a instance of Base");
        identify(base);
        identify(*base);
        delete base;
    } catch (const std::exception& e) {
        std::stringstream ss;
        ss << "Exception caught: " << e.what();
        toolbox::logger::StepMark::error(ss.str());
        std::cerr << toolbox::color::red << "Error: " << e.what()
            << toolbox::color::reset
            << std::endl;
    }
    return 0;
}
