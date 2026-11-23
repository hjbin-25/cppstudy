//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <utility>

struct Packet {
    const MoveTracer header;
    MoveTracer body;
};

int main() {
    Packet p{MoveTracer("header"), MoveTracer("body")};
    std::cout << "before\n";
    Packet q = std::move(p);
    std::cout << "after\n";
    std::cout << "p.header.value: " << p.header.value() << std::endl;
    std::cout << "p.body.value: " << p.body.value() << std::endl;
}

// ctor "header"
// ctor "body"
// before
// copy ctor "header"
// move ctor "body"
// after
// p.header.value: "header"
// p.body.value: ""
// dtor "body"
// dtor "header"
// dtor ""
// dtor "header"
