#include <ex02/funcs.hpp>

#include <ctime>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include <ex02/A.hpp>
#include <ex02/B.hpp>
#include <ex02/C.hpp>
#include <ex02/Base.hpp>
#include <toolbox/StepMark.hpp>
#include <toolbox/color.hpp>

namespace {
Base* createA();
Base* createB();
Base* createC();

unsigned long xorshift32();
}  // namespace


Base* generate(void) {
    static Base* (*creators[])(void) = {createA, createB, createC};
    static int numCreators = sizeof(creators) / sizeof(creators[0]);
    int index = xorshift32() % numCreators;
    std::stringstream ss;
    toolbox::logger::StepMark::debug(
        "Using xorshift32 for random index generation");
    ss << "Generating instance of type: " << static_cast<char>('A' + index);
    toolbox::logger::StepMark::info(ss.str());
    return creators[index]();
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p)) {
        toolbox::logger::StepMark::info("the pointer is of type A");
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        toolbox::logger::StepMark::info("the pointer is of type B");
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        toolbox::logger::StepMark::info("the pointer is of type C");
        std::cout << "C" << std::endl;
    } else {
        toolbox::logger::StepMark::warning("the pointer is of unknown type");
        std::cout << "Unknown type" << std::endl;
    }
}

void identify(Base& p) {
    try {
        A& a = dynamic_cast<A&>(p);
        toolbox::logger::StepMark::info("the reference is of type A");
        std::cout << "A" << std::endl;
        (void)a;
        return;
    } catch (const std::exception& e) {
    }
    try {
        B& b = dynamic_cast<B&>(p);
        toolbox::logger::StepMark::info("the reference is of type B");
        std::cout << "B" << std::endl;
        (void)b;
        return;
    } catch (const std::exception& e) {
    }
    try {
        C& c = dynamic_cast<C&>(p);
        toolbox::logger::StepMark::info("the reference is of type C");
        std::cout << "C" << std::endl;
        (void)c;
        return;
    } catch (const std::exception& e) {
    }
    toolbox::logger::StepMark::warning("the reference is of unknown type");
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
}  // namespace
