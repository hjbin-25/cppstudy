//
// Created by 황정빈 on 11/26/26.
//

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>

static int g_allocs = 0;

void* operator new(std::size_t n) {
    ++g_allocs;
    if (void* p = std::malloc(n))
        return p;
    throw std::bad_alloc();
}

void operator delete(void* p) noexcept {
    std::free(p);
}

void operator delete(void* p, std::size_t) noexcept {
    std::free(p);
}

struct Point {
    int x = 0;
    int y = 0;
};

int main() {
    int before = g_allocs; // 0
    auto a = std::make_shared<Point>();
    int after_make_shared = g_allocs; // 1

    auto b = std::shared_ptr<Point>(new Point);
    int after_new = g_allocs; // 2

    auto c = a;   // 복사는 할당하지 않음. 카운트만 올림
    int after_copy = g_allocs;

    std::cout << "make_shared      : " << after_make_shared - before << "회\n";
    std::cout << "shared_ptr(new)  : " << after_new - after_make_shared << "회\n";
    std::cout << "shared_ptr 복사  : " << after_copy - after_new << "회\n";
    std::cout << "count=" << c.use_count() << ' ' << b.use_count() << '\n';
}

// make_shared      : 1회
// shared_ptr(new)  : 2회
// shared_ptr 복사   : 0회
// count=2 1