//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <type_traits>
#include <utility>

struct Plain {
    MoveTracer t{"plain"};
};

struct Defaulted {
    MoveTracer t{"defaulted"};

    Defaulted() = default;

    Defaulted(Defaulted&&) = default;
};

struct Handwritten {
    MoveTracer t{"handwritten"};

    Handwritten() = default;

    Handwritten(Handwritten&& other) : t(std::move(other.t)) {};
};

struct WithDtor {
    MoveTracer t{"withdtor"};

    ~WithDtor() {}
};

int main() {
    std::cout << std::boolalpha;
    std::cout << "Plain       nothrow move: " << std::is_nothrow_move_constructible_v<Plain> << '\n';
    std::cout << "Defaulted   nothrow move: " << std::is_nothrow_move_constructible_v<Defaulted> << '\n';
    std::cout << "Handwritten nothrow move: " << std::is_nothrow_move_constructible_v<Handwritten> << '\n';
    std::cout << "WithDtor    nothrow move: " << std::is_nothrow_move_constructible_v<WithDtor> << '\n';
    std::cout << "WithDtor    move 가능?  : " << std::is_move_constructible_v<WithDtor> << '\n';
}
