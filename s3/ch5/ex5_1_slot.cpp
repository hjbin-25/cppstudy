//
// Created by 황정빈 on 11/26/26.
//

#include "base/noisy.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

class Slot {
public:
    void put(std::unique_ptr<Noisy> noisy) {
        noisy_ = std::move(noisy);
    }

    std::unique_ptr<Noisy> take() {
        return std::move(noisy_);
    }

    const Noisy* peek() const {
        return noisy_.get();
    }

    bool empty() const {
        return noisy_ == nullptr;
    }

private:
    std::unique_ptr<Noisy> noisy_;
};

int main() {
    Slot s;
    std::cout << "[1] put a\n";
    s.put(std::make_unique<Noisy>("a"));
    assert(s.peek() && s.peek()->name() == "a");

    std::cout << "[2] put b\n";
    s.put(std::make_unique<Noisy>("b"));

    std::cout << "[3] take\n";
    std::unique_ptr<Noisy> got = s.take();
    assert(s.empty() && got->name() == "b");

    std::cout << "[4] got 버림\n";
    got.reset();

    std::cout << "[5] put c\n";
    s.put(std::make_unique<Noisy>("c"));
    std::cout << "[end]\n";
}

//   Noisy()
// [1] put a
//   Noisy(a)
// [2] put b
//   Noisy(b)
//   ~Noisy(b)
// [3] take
// [4] got 버림
//   ~Noisy(b)
// [5] put c
//   Noisy(c)
// [end]
//   ~Noisy(c)