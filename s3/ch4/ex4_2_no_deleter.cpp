//
// Created by 황정빈 on 11/25/26.
//

#include <cstdio>
#include <iostream>
#include <memory>

int main() {
    std::cout << std::boolalpha;
    // deleter를 빼먹음: 기본 deleter는 delete. fopen이 준 메모리를 fclose가 아니라 delete로 지움
    std::unique_ptr<std::FILE> f(std::fopen("/dev/null", "r"));
    std::cout << "opened: " << (f != nullptr) << '\n';
}