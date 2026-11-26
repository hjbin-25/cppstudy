//
// Created by 황정빈 on 11/26/26.
//

#include "base/noisy.h"
#include <iostream>
#include <memory>
#include <utility>

void by_value(std::shared_ptr<Noisy> p) {
    std::cout << "  by_value count=" << p.use_count() << '\n';
}

void by_ref(const std::shared_ptr<Noisy>& p) {
    std::cout << "  by_ref count=" << p.use_count() << '\n';
}

void by_obj(const Noisy& n) {
    std::cout << "  by_obj   " << n.name() << '\n';
}

int main() {
    std::cout << "sizeof(shared_ptr)=" << sizeof(std::shared_ptr<Noisy>)
              << " sizeof(unique_ptr)=" << sizeof(std::unique_ptr<Noisy>) << '\n';

    std::cout << "[1] make_shared\n";
    std::shared_ptr<Noisy> a = std::make_shared<Noisy>("a");
    std::cout << "count=" << a.use_count() << '\n';

    std::cout << "[2] 복사\n";
    {
        std::shared_ptr<Noisy> b = a;
        std::cout << "count=" << a.use_count() << '\n';
    }
    std::cout << "count=" << a.use_count() << '\n';

    std::cout << "[3] 함수에 넘기기\n";
    by_value(a);
    by_ref(a);
    by_obj(*a);

    std::cout << "[4] move\n";
    std::shared_ptr<Noisy> c = std::move(a);
    std::cout << "a=" << (a ? "있음" : "nullptr") << " count=" << c.use_count() << '\n';

    std::cout << "[5] reset\n";
    c.reset();
    std::cout << "[end]\n";
}

// sizeof(shared_ptr<Noisy>)=16 sizeof(unique_ptr<Noisy>)=8
// [1] make_shared
//   Noisy(a)
// count=1
// [2] 복사
// count=2
// count=1
// [3] 함수에 넘기기
//   by_value count=2
//   by_ref count=1
//   by_obj   a
// [4] move
// a=nullptr count=1
// [5] reset
//   ~Noisy(a)
// [end]