//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <utility>

void which(MoveTracer&) {
    std::cout << "  -> MoveTracer&\n";
}

void which(const MoveTracer&) {
    std::cout << "  -> const MoveTracer&\n";
}

void which(MoveTracer&&) {
    std::cout << "  -> MoveTracer&&\n";
}

MoveTracer make(const std::string& v) {
    return MoveTracer(v);
}

int main() {
    MoveTracer a("a");
    const MoveTracer c("c");

    std::cout << "[1] which(a)\n";
    which(a);
    std::cout << "[2] which(c)\n";
    which(c);
    std::cout << "[3] which(make(\"t\"))\n";
    which(make("t"));
    std::cout << "[4] which(std::move(a))\n";
    which(std::move(a));

    MoveTracer&& r = std::move(a);
    std::cout << "[5] which(r)\n";
    which(r);
    std::cout << "[6] which(std::move(r))\n";
    which(std::move(r));
    std::cout << "[end]\n";
}

// ctor a
// ctor c
// print 1
// MoveTracer&
// print 2
// const MoveTracer&
// print 3
// ctor t
// MoveTracer&&
// dtor t
// print 4
// MoveTracer&&
// print 5
// MoveTracer&
// print 6
// MoveTracer&&
// end
// dtor c
// dtor a