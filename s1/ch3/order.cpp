//
// Created by 황정빈 on 11/16/26.
//

#include "tracer.h"

class Room {
public:
    Room() : c("c"), a("a"), b("b") {
        std::puts("    Room ctor body");
    }

    ~Room() {
        std::puts("    Room dtor body");
    }

private:
    Tracer a;
    Tracer b;
    Tracer c;
};

int main() {
    Room r;
    std::puts("main end");
}

//     ctor a
//     ctor b
//     ctor c
//     Room ctor body
// main end
//     Room dtor body
//     dtor c
//     dtor b
//     dtor a
