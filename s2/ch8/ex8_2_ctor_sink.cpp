//
// Created by 황정빈 on 11/24/26.
//

#include "move_tracer.h"
#include <iostream>
#include <utility>

class Room {
public:
    explicit Room(MoveTracer v) : title_(std::move(v)) {}

private:
    MoveTracer title_;
};

int main() {
    MoveTracer name("lobby");

    std::cout << "1\n";
    Room a(name);
    std::cout << "2\n";
    Room b(MoveTracer("prvalue"));
    std::cout << "3\n";
    Room c(std::move(name));
    std::cout << "end\n";
}

// #1 ctor "lobby"
// 1
// #2 copy ctor "lobby"
// #3 move ctor "lobby"
// #2 dtor ""
// 2
// #4 ctor "prvalue"
// #5 move ctor "prvalue"
// #4 dtor ""
// 3
// #6 move ctor "lobby"
// #7 move ctor "lobby"
// #6 dtor ""
// end
// #7 dtor "lobby"
// #5 dtor "prvalue"
// #3 dtor "lobby"
// #1 dtor ""