//
// Created by 황정빈 on 11/23/26.
//

// ch8/int_buffer_test.cpp
#include <cassert>
#include <cstdio>
#include <stdexcept>
#include "int_buffer.h"

static void fill(IntBuffer& b, int base) {
    for (std::size_t i = 0; i < b.size(); ++i) b[i] = base + static_cast<int>(i);
}

int main() {
    // 1. 생성: 0으로 초기화
    IntBuffer a(4);
    assert(a.size() == 4);
    for (std::size_t i = 0; i < a.size(); ++i) assert(a[i] == 0);

    // 2. 복사 생성: 내용은 같고 메모리는 따로
    fill(a, 10);                       // a = {10, 11, 12, 13}
    IntBuffer b = a;
    assert(b.size() == 4 && b[2] == 12);
    b[0] = 99;
    assert(a[0] == 10);

    // 3. 복사 대입: 크기가 다른 객체에 대입
    IntBuffer c(2);
    c = a;
    assert(c.size() == 4 && c[3] == 13);
    c[3] = -1;
    assert(a[3] == 13);

    // 4. 자기 대입: 내용 유지
    IntBuffer& alias = a;
    a = alias;
    assert(a.size() == 4 && a[1] == 11);

    // 5. 연쇄 대입
    IntBuffer d(1), e(1);
    d = e = a;
    assert(d[2] == 12 && e[2] == 12);

    // 6. at(): 범위 검사
    bool thrown = false;
    try { a.at(4) = 0; } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // 7. const 접근
    const IntBuffer& ca = a;
    assert(ca[0] == 10 && ca.at(3) == 13);

    // 8. 크기 0
    IntBuffer z(0);
    IntBuffer z2 = z;
    z = a;
    assert(z.size() == 4 && z2.size() == 0);

    std::puts("all tests passed");
}