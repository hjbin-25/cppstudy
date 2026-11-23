//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <utility>

int main() {
    MoveTracer a("a");

    std::cout << "[1] (void)std::move(a);\n";
    (void)std::move(a);
    std::cout << "    a.value() = \"" << a.value() << "\"\n";

    std::cout << "[2] MoveTracer&& r = std::move(a);\n";
    MoveTracer&& r = std::move(a);
    std::cout << "    a.value() = \"" << a.value() << "\"\n";

    std::cout << "[3] MoveTracer b = std::move(r);\n";
    MoveTracer b = std::move(r);
    std::cout << "    a.value() = \"" << a.value() << "\"\n";

    std::cout << "[4] MoveTracer c = static_cast<MoveTracer&&>(b);\n";
    MoveTracer c = static_cast<MoveTracer&&>(b);
    std::cout << "[end]\n";
}

// ctor "a"
// 1
// a
// 2
// a
// 3
// move ctor "a"
// ""
// 4
// move ctor "a"
// end
// dtor "a"
// dtor ""
// dtor ""