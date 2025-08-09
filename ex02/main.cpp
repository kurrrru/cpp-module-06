#include <iostream>

#include <ex02/A.hpp>
#include <ex02/B.hpp>
#include <ex02/C.hpp>
#include <ex02/Base.hpp>
#include <ex02/funcs.hpp>

int main() {
    Base* instance = generate();
    identify(instance);
    identify(*instance);

    delete instance;
    return 0;
}
