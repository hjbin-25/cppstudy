//
// Created by 황정빈 on 11/24/26.
//

#include "move_tracer.h"
#include <iostream>

MoveTracer make_prvalue() {
    return MoveTracer("prvalue");
}

MoveTracer make_named() {
    MoveTracer t("named");
    return t;
}

MoveTracer make_branch(bool first) {
    MoveTracer x("x");
    MoveTracer y("y");

    if (first)
        return x;
    return y;
}

MoveTracer pass_through(MoveTracer p) {
    return p;
}

int main() {
    std::cout << "[1] make_prvalue\n";
    { MoveTracer a = make_prvalue(); }
    std::cout << "[2] make_named\n";
    { MoveTracer b = make_named(); }
    std::cout << "[3] make_branch\n";
    { MoveTracer c = make_branch(true); }
    std::cout << "[4] pass_through\n";
    { MoveTracer d = pass_through(MoveTracer("p")); }
    std::cout << "[end]\n";
}

// 1
// ctor "prvalue"
// dtor "prvalue"
// 2
// ctor "named"
// dtor "named"
// 3
// ctor "x"
// ctor "y"
// move ctor "x"
// dtor "y"
// dtor ""
// dtor "x"
// 4
// ctor "p"
// move ctor p
// dtor ""
// dtor "p"