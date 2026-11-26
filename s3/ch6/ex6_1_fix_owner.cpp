//
// Created by 황정빈 on 11/26/26.
//

#include "base/noisy.h"
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<Noisy> s1 = std::make_shared<Noisy>("x");
    std::shared_ptr<Noisy> s2 = s1;
    std::cout << "s1.count=" << s1.use_count() << " s2.count=" << s2.use_count() << "\n";
    std::cout << "[end]\n";
}

//   Noisy(x)
// s1.count=2 s2.count=2
// [end]
//   ~Noisy(x)