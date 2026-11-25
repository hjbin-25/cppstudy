//
// Created by 황정빈 on 11/25/26.
//

#include "base/noisy.h"
#include <iostream>
#include <memory>
#include <utility>

Noisy make_value() {
    return Noisy("v");
}

Noisy make_named() {
    Noisy n("n");
    return n;
}

std::unique_ptr<Noisy> make_ptr() {
    auto p = std::make_unique<Noisy>("p");
    return p;
}

int main() {
    std::cout << "[1]\n";
    Noisy v = make_value();
    std::cout << "[2]\n";
    Noisy n = make_named();
    std::cout << "[3]\n";
    std::unique_ptr<Noisy> p = make_ptr();
    std::cout << "[4]\n";
    std::unique_ptr<Noisy> q = std::move(p);
    std::cout << "[end]\n";
}

// [1]
//   Noisy(v)
// [2]
//   Noisy(n)
// [3]
//   Noisy(p)
// [4]
// [end]
//   ~Noisy(p)
//   ~Noisy(n)
//   ~Noisy(v)