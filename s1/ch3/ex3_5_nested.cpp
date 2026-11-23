//
// Created by 황정빈 on 11/16/26.
//

#include "tracer.h"

class Inner {
public:
    Inner() : x("inner.x") {
        std::puts("    Inner body");
    }

    ~Inner() {
        std::puts("    ~Inner body");
    }

private:
    Tracer x;
};

class Outer {
public:
    Outer() : a("outer.a") {
        std::puts("    Outer body");
    }

    ~Outer() {
        std::puts("    ~Outer body");
    }

private:
    Tracer a;
    Inner in;
};

int main() {
    Outer o;
}

//     ctor outer.a
//     ctor inner.x
//     Inner body
//     Outer body
//     ~Outer body
//     ~Inner body
//     dtor inner.x
//     dtor outer.a