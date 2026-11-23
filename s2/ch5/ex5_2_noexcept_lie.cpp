//
// Created by 황정빈 on 11/23/26.
//

#include <iostream>
#include <stdexcept>
#include <vector>

void may_throw(int n) {
    if (n == 2)
        throw std::runtime_error("n이 2입니다.");
}

struct Liar {
    int n;

    explicit Liar(int n) : n(n) {}

    Liar(const Liar&) = default;

    Liar(Liar&& other) noexcept : n(other.n) {
        may_throw(n);
    }
};

int main() {
    try {
        std::vector<Liar> v;

        v.reserve(1);

        v.push_back(Liar(1));
        v.push_back(Liar(2));
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << '\n';
    }
}
