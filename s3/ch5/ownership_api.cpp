//
// Created by 황정빈 on 11/25/26.
//

#include "base/noisy.h"
#include <iostream>
#include <string>
#include <memory>
#include <utility>

void inspect(const Noisy& n) {
    std::cout << "  inspect " << n.name() << '\n';
}

void maybe_inspect(const Noisy* n) {
    if (n)
        std::cout << "  maybe_inspect " << n->name() << '\n';
    else
        std::cout << "  maybe_inspect (없음)\n";
}

void adopt(std::unique_ptr<Noisy> p) {
    std::cout << "  adopt " << p->name() << '\n';
}

void refill(std::unique_ptr<Noisy>& slot, std::string name) {
    slot = std::make_unique<Noisy>(std::move(name));
}

std::unique_ptr<Noisy> create(std::string name) {
    return std::make_unique<Noisy>(name);
}

Noisy pick(bool first) {
    Noisy x("x");
    Noisy y("y");

    if (first)
        return x;
    return y;
}

int main() {
    std::cout << "[1]\n";
    std::unique_ptr<Noisy> p = create("a");
    std::cout << "[2]\n";
    inspect(*p);
    maybe_inspect(p.get());
    std::cout << "[3]\n";
    adopt(std::move(p));
    std::cout << "[4]\n";
    maybe_inspect(p.get());
    std::cout << "[5]\n";
    refill(p, "b");
    std::cout << "[6]\n";
    refill(p, "c");
    std::cout << "[7]\n";
    Noisy y = pick(false);
    std::cout << "[end]\n";
}

// [1]
//   Noisy(a)
// [2]
//   inspect a
//   maybe_inspect a
// [3]
//   adopt a
//   ~Noisy(a)
// [4]
//   maybe_inspect (없음)
// [5]
//   Noisy(b)
// [6]
//   Noisy(c)
//   ~Noisy(b)
// [7]
//   Noisy(x)
//   Noisy(y)
//   move(y)
//   Noisy(-)
//   ~Noisy(x)
// [end]
//   ~Noisy(x)
//   ~Noisy(c)