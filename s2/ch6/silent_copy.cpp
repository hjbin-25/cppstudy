//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <string>
#include <utility>

class Session {
public:
    explicit Session(std::string name) : name_(std::move(name)) {}

    ~Session() { std::cout << "  (~Session)\n"; }

private:
    MoveTracer name_;
};

class Session0 {
public:
    explicit Session0(std::string name) : name_(std::move(name)) {}

private:
    MoveTracer name_;
};

int main() {
    std::cout << "[Session: 소멸자 직접 선언]\n";
    Session a("a");
    Session b = std::move(a);

    std::cout << "[Session0: 아무것도 선언 안 함]\n";
    Session0 c("c");
    Session0 d = std::move(c);
    std::cout << "[end]\n";
}