//
// Created by 황정빈 on 11/24/26.
//

#include "move_tracer.h"
#include <iostream>
#include <utility>

MoveTracer make_moved() {
    MoveTracer t("moved");
    return std::move(t);
}

int main() {
    std::cout << "[make_moved]\n";
    { MoveTracer a = make_moved(); }
    std::cout << "[end]\n";
}

// make_moved
// ctor moved
// move ctor moved
// dtor ""
// dtor moved
// end