#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#include <ex01/Serializer.hpp>
#include <ex01/Data.hpp>
#include <toolbox/StepMark.hpp>
#include <toolbox/color.hpp>

int main() {
    toolbox::logger::StepMark::setLogFile("serializer.log");
    toolbox::logger::StepMark::setLevel(toolbox::logger::INFO);
    Data data(42);
    std::cout << "Original Data value: "
            << toolbox::color::green << data.getValue()
            << toolbox::color::reset
            << std::endl;
    std::stringstream ss;
    ss << "Serializing Data with value: " << data.getValue();
    toolbox::logger::StepMark::info(ss.str());

    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized Data to raw pointer: "
            << toolbox::color::green << raw
            << toolbox::color::reset
            << std::endl;
    ss.str("");
    ss << "Deserializing raw pointer: " << raw;
    toolbox::logger::StepMark::info(ss.str());

    Data* deserializedData = Serializer::deserialize(raw);
    std::cout << "Deserialized Data value: "
            << toolbox::color::green << deserializedData->getValue()
            << toolbox::color::reset
            << std::endl;
    ss.str("");
    ss << "Deserialized Data value: " << deserializedData->getValue();
    toolbox::logger::StepMark::info(ss.str());

    return 0;
}
