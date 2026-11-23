//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <utility>

struct CopyOnly {
    MoveTracer t;

    explicit CopyOnly(const char* v) : t(v) {}

    CopyOnly(const CopyOnly& other) : t(other.t) {}
};

struct MoveOnly {
    MoveTracer t;

    explicit MoveOnly(const char* v) : t(v) {}

    MoveOnly(MoveOnly&& other) noexcept : t(std::move(other.t)) {}
};

struct CopyFixed {
    MoveTracer t;

    explicit CopyFixed(const char* v) : t(v) {}

    CopyFixed(const CopyFixed& other) : t(other.t) {}

    CopyFixed(CopyFixed&& other) noexcept = default;
};

int main() {
    std::cout << "CopyOnly\n";
    CopyOnly copy_only("copy_only");
    CopyOnly copy_only2 = std::move(copy_only);

    std::cout << "MoveOnly\n";
    MoveOnly move_only("move_only");
    MoveOnly move_only2 = std::move(move_only);

    std::cout << "CopyFixed\n";
    CopyFixed copy_fixed("copy_fixed");
    CopyFixed copy_fixed2 = std::move(copy_fixed);

    std::cout << "end\n";
}