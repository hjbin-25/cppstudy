//
// Created by 황정빈 on 11/23/26.
//


#include "move_tracer.h"
#include <iostream>
#include <string>
#include <utility>

class Slot2 {
public:
    explicit Slot2(std::string v) : t_(std::move(v)) {}

    Slot2(const Slot2&) = default;

    Slot2(Slot2&&) noexcept = default;

    Slot2& operator=(const Slot2&) = default;

    Slot2& operator=(Slot2&&) noexcept = default;

private:
    MoveTracer t_;
};

class Slot1 {
public:
    explicit Slot1(std::string v) : t_(std::move(v)) {}

    Slot1(const Slot1&) = default;

    Slot1(Slot1&&) noexcept = default;

    Slot1& operator=(Slot1 other) noexcept {
        swap(t_, other.t_);
        return *this;
    }

private:
    MoveTracer t_;
};

int main() {
    std::cout << "===== Slot2 (따로) =====\n";
    {
        Slot2 a("a");
        Slot2 b("b");
        std::cout << "[a = b]\n";
        a = b;
        std::cout << "[a = std::move(b)]\n";
        a = std::move(b);
        std::cout << "[a = Slot2(\"t\")]\n";
        a = Slot2("t");
        std::cout << "[블록 끝]\n";
    }
    std::cout << "===== Slot1 (값으로 받기) =====\n";
    {
        Slot1 a("a");
        Slot1 b("b");
        std::cout << "[a = b]\n";
        a = b;
        std::cout << "[a = std::move(b)]\n";
        a = std::move(b);
        std::cout << "[a = Slot1(\"t\")]\n";
        a = Slot1("t");
        std::cout << "[블록 끝]\n";
    }
}