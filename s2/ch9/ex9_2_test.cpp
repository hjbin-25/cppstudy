//
// Created by 황정빈 on 11/24/26.
//

#include "int_buffer.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace {

int failures = 0;

void check(bool ok, const char* what) {
    // std::endl로 매번 내보낸다: ASan이 중간에 프로그램을 멈춰도 앞의 결과는 보이게
    std::cout << (ok ? "PASS " : "FAIL ") << what << std::endl;
    if (!ok)
        ++failures;
}

IntBuffer make_filled(std::size_t n, int base) {
    IntBuffer b(n);
    for (std::size_t i = 0; i < n; ++i)
        b[i] = base + static_cast<int>(i);
    return b;
}

}  // namespace

int main() {
    // 1. 이동 생성: 배열을 새로 만들지 않고 그대로 넘겨받는다
    {
        IntBuffer a = make_filled(3, 10);
        const int* p = &a[0];
        IntBuffer b = std::move(a);
        check(&b[0] == p, "move ctor: b가 a의 배열을 넘겨받음");
        check(b.size() == 3 && b[2] == 12, "move ctor: 내용 유지");
        check(a.size() == 0, "move ctor: a는 빈 버퍼(size 0)");
    }

    // 2. moved-from 객체에서 at()은 예외를 던진다 (UB가 아니어야 함)
    {
        IntBuffer a(2);
        IntBuffer b = std::move(a);
        bool thrown = false;
        try {
            (void)a.at(0);
        } catch (const std::out_of_range&) {
            thrown = true;
        }
        check(thrown, "moved-from: at(0)은 out_of_range");
    }

    // 3. moved-from 객체에 다시 대입해서 쓸 수 있다
    {
        IntBuffer a(2);
        IntBuffer b = std::move(a);
        a = make_filled(4, 0);
        check(a.size() == 4 && a[3] == 3, "moved-from: 다시 대입해서 사용");
    }

    // 4. 이동 대입: 내 옛 배열은 해제되고(누수는 도구로 확인), 상대 배열을 넘겨받는다
    {
        IntBuffer a = make_filled(2, 0);
        IntBuffer b = make_filled(5, 100);
        const int* p = &b[0];
        a = std::move(b);
        check(&a[0] == p && a.size() == 5 && a[4] == 104, "move assign: a가 b의 배열을 넘겨받음");
        check(b.size() == 0, "move assign: b는 빈 버퍼");
    }

    // 5. 복사는 여전히 깊은 복사
    {
        IntBuffer a = make_filled(3, 1);
        IntBuffer b = a;
        b[0] = 99;
        check(a[0] == 1 && &a[0] != &b[0], "copy ctor: 깊은 복사");
        IntBuffer c(1);
        c = a;
        check(c.size() == 3 && c[2] == 3 && &c[0] != &a[0], "copy assign: 깊은 복사");
    }

    // 6. 자기 대입, 자기 이동
    {
        IntBuffer a = make_filled(3, 7);
        IntBuffer& same = a;
        a = same;
        check(a.size() == 3 && a[0] == 7, "self copy assign");
        a = std::move(same);
        check(a.size() == 3 && a[0] == 7, "self move assign");
    }

    // 7. noexcept
    check(std::is_nothrow_move_constructible_v<IntBuffer>, "move ctor는 noexcept");
    check(std::is_nothrow_move_assignable_v<IntBuffer>, "move assign은 noexcept");

    // 8. vector 재할당 때 복사가 아니라 이동이 쓰인다
    {
        std::vector<IntBuffer> v;
        v.reserve(1);
        v.push_back(make_filled(2, 0));
        const int* p = &v[0][0];
        v.push_back(make_filled(2, 10));  // 용량 1 -> 재할당
        check(&v[0][0] == p, "vector 재할당: 요소가 이동됨(배열 주소 그대로)");
    }

    std::cout << (failures == 0 ? "ALL PASS" : "SOME FAILED") << '\n';
    return failures == 0 ? 0 : 1;
}