//
// Created by 황정빈 on 11/24/26.
//

#include "base/noisy.h"
#include <iostream>

int main() {
    std::cout << "[1] new\n";
    Noisy* p = new Noisy("a");
    std::cout << "[2] 포인터 복사\n";
    Noisy* q = p;
    std::cout << "[3] 객체 복사\n";
    Noisy c = *q;
    std::cout << "[4] delete\n";
    delete q;
    // delete p; double free
    std::cout << "[end]\n";
}

// [1] new
//   Noisy(a)
// [2] 포인터 복사
// [3] 객체 복사
//   copy(a)
// [4] delete
//   ~Noisy(a)
// [end]
//   ~Noisy(a)