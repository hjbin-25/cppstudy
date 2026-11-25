//
// Created by 황정빈 on 11/25/26.
//

#include "int_buffer_up.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

static int g_fail = 0;

#define CHECK(cond)                                                    \
    do {                                                               \
        if (cond) {                                                    \
            std::cout << "PASS " << #cond << '\n';                     \
        } else {                                                       \
            std::cout << "FAIL " << #cond << " (line " << __LINE__ << ")\n"; \
            ++g_fail;                                                  \
        }                                                              \
    } while (0)

static bool throws_out_of_range(const IntBuffer& b, std::size_t i) {
    try {
        (void)b.at(i);
    } catch (const std::out_of_range&) {
        return true;
    }
    return false;
}

int main() {
    // 타입 성질
    CHECK(std::is_copy_constructible_v<IntBuffer>);
    CHECK(std::is_nothrow_move_constructible_v<IntBuffer>);
    CHECK(std::is_nothrow_move_assignable_v<IntBuffer>);  // 인자를 noexcept 이동 생성자로 만들고, operator=도 noexcept
    CHECK(std::is_copy_assignable_v<IntBuffer>);

    // 생성: 0으로 초기화
    IntBuffer a(3);
    CHECK(a.size() == 3);
    CHECK(a[0] == 0 && a[1] == 0 && a[2] == 0);

    // 깊은 복사
    a[0] = 10;
    IntBuffer b = a;
    b[0] = 20;
    CHECK(a[0] == 10 && b[0] == 20);

    // 이동: moved-from 약속
    IntBuffer c = std::move(a);
    CHECK(c.size() == 3 && c[0] == 10);
    CHECK(a.size() == 0);
    CHECK(throws_out_of_range(a, 0));

    // moved-from 복사 (size 0 복사)
    IntBuffer d = a;
    CHECK(d.size() == 0);

    // moved-from에 대입하면 다시 쓸 수 있음
    a = b;
    CHECK(a.size() == 3 && a[0] == 20);

    // 자기 대입, 자기 이동 대입
    IntBuffer& ra = a;   // a = a;라고 쓰면 clang이 -Wself-assign-overloaded 경고를 냄
    a = ra;
    CHECK(a.size() == 3 && a[0] == 20);
    a = std::move(ra);
    CHECK(a.size() == 3 && a[0] == 20);

    // swap
    IntBuffer e(1);
    swap(a, e);
    CHECK(a.size() == 1 && e.size() == 3 && e[0] == 20);

    std::cout << (g_fail == 0 ? "ALL PASS" : "SOME FAILED") << '\n';
    return g_fail == 0 ? 0 : 1;
}