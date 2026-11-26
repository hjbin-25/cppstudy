//
// Created by 황정빈 on 11/26/26.
//

#include "base/noisy.h"
#include <iostream>
#include <memory>

int main() {
    Noisy* raw = new Noisy("x");
    std::shared_ptr<Noisy> s1(raw);
    std::shared_ptr<Noisy> s2(raw);
    std::cout << "s1 count=" << s1.use_count() << " s2 count=" << s2.use_count() << '\n';
    std::cout << "[end]\n";
}

//   Noisy(x)
// s1 count=1 s2 count=1
// [end]
//   ~Noisy(x)
// double free