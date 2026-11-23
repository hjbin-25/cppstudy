//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Loud {
    MoveTracer t;

    explicit Loud(std::string v) : t(std::move(v)) {}

    Loud(const Loud&) = default;

    Loud(Loud&& other) : t(std::move(other.t)) {}
};

struct Quiet {
    MoveTracer t;

    explicit Quiet(std::string v) : t(std::move(v)) {}

    Quiet(const Quiet&) = default;

    Quiet(Quiet&& other) noexcept : t(std::move(other.t)) {}
};

int main() {
    {
        std::cout << "=== Loud (noexcept 없음) ===\n";
        std::vector<Loud> v;
        v.reserve(2);
        v.push_back(Loud("a"));
        v.push_back(Loud("b"));
        std::cout << "--- 3번째 push_back: 재할당 ---\n";
        v.push_back(Loud("c"));
        std::cout << "--- 블록 끝 ---\n";
    }
    {
        std::cout << "=== Quiet (noexcept 있음) ===\n";
        std::vector<Quiet> v;
        v.reserve(2);
        v.push_back(Quiet("a"));
        v.push_back(Quiet("b"));
        std::cout << "--- 3번째 push_back: 재할당 ---\n";
        v.push_back(Quiet("c"));
        std::cout << "--- 블록 끝 ---\n";
    }
}