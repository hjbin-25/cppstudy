//
// Created by 황정빈 on 11/23/26.
//

#include "../../common/move_tracer.h"
#include <iostream>
#include <utility>

class Holder {
public:
    explicit Holder(const MoveTracer&& t) : item_(std::move(t)) {}

private:
    MoveTracer item_;
};

int main() {
    const MoveTracer c("c");
    std::cout << "[1] MoveTracer d = std::move(c);\n";
    MoveTracer d = std::move(c);

    MoveTracer h("h");
    std::cout << "[2] Holder holder(std::move(h));\n";
    Holder holder(std::move(h));
    std::cout << "    h.value() = \"" << h.value() << "\"\n";
    std::cout << "[end]\n";
}

// ctor "c"
// 1
// copy ctor "c"
// ctor "h"
// 2
// copy ctor "h"
// h
// end
// dtor "h"
// dtor "h"
// dtor "c"
// dtor "c"