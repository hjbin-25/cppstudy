//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <string>
#include <utility>

class Both {
public:
    explicit Both(std::string v) : t_(std::move(v)) {}

    Both(const Both& other) : t_(other.t_) {}

    Both(Both&& other) noexcept : t_(std::move(other.t_)) {}

    Both& operator=(Both other) noexcept {
        swap(t_, other.t_);
        return *this;
    }

    Both& operator=(Both&& other) noexcept {
        t_ = std::move(other.t_);
        return *this;
    }

private:
    MoveTracer t_;
};

int main() {
    Both a("a");
    Both b("b");
    a = b;
    // a = std::move(b);
}