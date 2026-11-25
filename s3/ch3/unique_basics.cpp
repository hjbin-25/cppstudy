//
// Created by 황정빈 on 11/24/26.
//

#include "base/noisy.h"
#include <iostream>
#include <memory>
#include <utility>

int main() {
    std::cout << "[1] make_unique\n";
    std::unique_ptr<Noisy> a = std::make_unique<Noisy>("a");

    std::cout << "[2] move\n";
    std::unique_ptr<Noisy> b = std::move(a);
    std::cout << "a=" << (a ? "있음" : "nullptr") << " b=" << b->name() << '\n';

    std::cout << "[3] 새 객체 대입\n";
    b = std::make_unique<Noisy>("b");

    std::cout << "[4] reset()\n";
    b.reset();
    std::cout << "b=" << (b ? "있음" : "nullptr") << '\n';

    std::cout << "[5] get\n";
    auto c = std::make_unique<Noisy>("c");
    Noisy* raw = c.get();
    std::cout << "raw->name()=" << raw->name() << '\n';

    std::cout << "[end]\n";
}

// [1] make_unique
//   Noisy(a)
// [2] move
// a=nullptr b=a
// [3] 새 객체 대입
//   Noisy(b)
//   ~Noisy(a)
// [4] reset()
//   ~Noisy(b)
// b=nullptr
// [5] get
//   Noisy(c)
// raw->name()=c
// [end]
//   ~Noisy(c)