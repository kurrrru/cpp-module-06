#include <ex02/funcs.hpp>

#include <ctime>
#include <exception>
#include <iostream>

#include <ex02/A.hpp>
#include <ex02/B.hpp>
#include <ex02/C.hpp>
#include <ex02/Base.hpp>

namespace {
    Base* createA();
    Base* createB();
    Base* createC();

    unsigned long xorshift32();
}


Base* generate(void) {
    static Base* (*creators[])(void) = {createA, createB, createC};
    static int numCreators = sizeof(creators) / sizeof(creators[0]);
    int index = xorshift32() % numCreators;
    std::cout << "Generating instance of type: " << 'A' + index << std::endl;
    return creators[index]();
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p)) {
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "C" << std::endl;
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}

void identify(Base& p) {
    try {
        A& a = dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        (void)a;
        return;
    } catch (const std::exception& e) {
    }
    try {
        B& b = dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        (void)b;
        return;
    } catch (const std::exception& e) {
    }
    try {
        C& c = dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        (void)c;
        return;
    } catch (const std::exception& e) {
    }
    std::cout << "Unknown type" << std::endl;
}

namespace {
    Base* createA() {
        return new A();
    }

    Base* createB() {
        return new B();
    }

    Base* createC() {
        return new C();
    }

    unsigned long xorshift32() {
        static unsigned long state = static_cast<unsigned long>(std::time(NULL))
            & 0xFFFFFFFF;
        state ^= (state << 13);
        state &= 0xFFFFFFFF;
        state ^= (state >> 17);
        state &= 0xFFFFFFFF;
        state ^= (state << 5);
        state &= 0xFFFFFFFF;
        return state;
    }
}
