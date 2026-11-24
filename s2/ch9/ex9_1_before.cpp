//
// Created by 황정빈 on 11/24/26.
//

#include "int_buffer.h"
#include <iostream>
#include <type_traits>
#include <utility>

int main() {
    // main: 크기 3인 a를 만들고 a[0] = 42. &a[0](a가 소유한 배열의 주소)을 저장해 둔 뒤 IntBuffer b = std::move(a);.
    IntBuffer a(3);
    a[0] = 42;
    const int* add_a = &a[0];
    IntBuffer b = std::move(a);

    std::cout << "add_a=" << add_a << ", &b[0]=" << &b[0] << "\n";
    std::cout << "a.size()=" << a.size() << "\n";
    std::cout << "is_move_constructible_v<IntBuffer>=" << std::is_move_constructible_v<IntBuffer> << "\n";
    std::cout << "is_nothrow_move_constructible_v<IntBuffer>=" << std::is_nothrow_move_constructible_v<IntBuffer> << "\n";
}
