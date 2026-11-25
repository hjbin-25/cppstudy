//
// Created by 황정빈 on 11/25/26.
//

#include "base/int_buffer.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

int main() {
    std::cout << std::boolalpha;

    IntBuffer a(4);
    IntBuffer b = std::move(a);

    try {
        std::cout << "a.size()=" << a.size() << ", a.at(0)=" << a.at(0) << "\n";
    } catch (std::out_of_range& e) {
        std::cout << "\nout of range: " << e.what() << "\n";
    }

    a = IntBuffer(2);
    std::cout << "a.size()=" << a.size() << ", a.at(0)=" << a.at(0) << "\n";

    auto p = std::make_unique<int>(7);
    auto q = std::move(p);

    std::cout << "(p==nullptr)=" << (p == nullptr) << "\n";

    p = std::make_unique<int>(10);
    std::cout << "(p==nullptr)=" << (p==nullptr) << ", *p=" << *p << "\n";
}