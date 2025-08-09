#include <iostream>

#include <ex01/Serializer.hpp>
#include <ex01/Data.hpp>

int main() {
    Data data(42);
    std::cout << "Original Data value: " << data.getValue() << std::endl;

    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized Data pointer: " << raw << std::endl;

    Data* deserializedData = Serializer::deserialize(raw);
    std::cout << "Deserialized Data value: "
        << deserializedData->getValue() << std::endl;

    return 0;
}
