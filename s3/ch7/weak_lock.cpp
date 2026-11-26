//
// Created by 황정빈 on 11/26/26.
//

#include "base/noisy.h"
#include <iostream>
#include <memory>

void notify(const std::weak_ptr<Noisy>& p) {
    if (std::shared_ptr<Noisy> s = p.lock())
        std::cout << "  notify " << s->name() << " (count=" << s.use_count() << ")\n";
    else
        std::cout << "  notify: 이미 사라짐\n";
}

int main() {
    std::cout << std::boolalpha;
    std::cout << "[1]\n";
    std::shared_ptr<Noisy> session = std::make_shared<Noisy>("s1");
    std::weak_ptr<Noisy> w = session;
    std::cout << "count=" << session.use_count() << " expired=" << w.expired() << '\n';

    std::cout << "[2]\n";
    notify(w);

    std::cout << "[3] 연결 끊김\n";
    session.reset();
    std::cout << "expired=" << w.expired() << " count=" << w.use_count() << '\n';

    std::cout << "[4]\n";
    notify(w);
    std::cout << "[end]\n";
}

// [1]
//   Noisy(s1)
// count=1 expired=false
// [2]
//   notify s1 (count=2)
// [3] 연결 끊김
//   ~Noisy(s1)
// expired=true count=0
// [4]
//   notify: 이미 사라짐
// [end]