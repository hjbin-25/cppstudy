//
// Created by 황정빈 on 11/16/26.
//

#include <cstdio>
#include <stdexcept>
#include "tracer.h"

void level2() {
    Tracer t2("t2");
    throw std::runtime_error("boom");
    Tracer never("never");
}

void level1() {
    Tracer t1("t1");
    level2();
    std::puts("after level2");
}

int main() {
    Tracer m("m");
    level1();

    std::puts("main end");
}

//     ctor m
//     ctor t1
//     ctor t2
//     dtor t2
//     dtor t1
// caught: boom
// main end
//     dtor m