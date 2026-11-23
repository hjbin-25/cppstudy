//
// Created by 황정빈 on 11/16/26.
//

#include "tracer.h"

void counter() {
    static Tracer s("static-local");
    std::puts("    counter called");
}

int main() {
    std::puts("main start");
    counter();
    counter();

    std::puts("before temp");
    Tracer("temp");
    std::puts("after temp");

    std::puts("main end");
}

// main start
//     ctor static-local
//     counter called
//     counter called
// before temp
//     ctor temp
//     dtor temp
// after temp
// main end
//     dtor static-local
