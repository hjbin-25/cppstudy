//
// Created by 황정빈 on 11/16/26.
//

#include "../../common/tracer.h"

Tracer g("global");

void f() {
    Tracer local("f-local");
    std::puts("in f");
}

int main() {
    std::puts("main start");
    Tracer a("a");
    {
        Tracer b("b");
        std::puts("inner block end");
    }
    f();
    for (int i = 0; i < 10; ++i)
        Tracer* h = new Tracer("heap");
    Tracer c("c");
    // delete h;
    std::puts("main end");
}

//     ctor global
// main start
//     ctor a
//     ctor b
// inner block end
//     dtor b
//     ctor f-local
// in f
//     dtor f-local
//     ctor heap
//     ctor c
//     dtor heap
// main end
//     dtor c
//     dtor a
//     dtor global
