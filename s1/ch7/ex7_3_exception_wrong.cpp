//
// Created by 황정빈 on 11/17/26.
//

#include <cstdio>
#include <cstddef>
#include <algorithm>
#include <new>
#include <utility>

bool g_fail = false;

int* alloc_int(std::size_t size) {
    if (g_fail)
        throw std::bad_alloc();

    return new int[size];
}

class Buf {
public:
    explicit Buf(std::size_t n) : size_(n), data_(new int[n]{}) {}

    ~Buf() { delete[] data_; }

    Buf(const Buf& other) : size_(other.size_), data_(new int[other.size_]{}) {
        std::copy(other.data_, other.data_ + other.size_, this->data_);
    }

    Buf& operator=(const Buf& other) {
        delete[] data_;
        size_ = other.size_;
        data_ = alloc_int(size_);
        std::copy(other.data_, other.data_ + other.size_, this->data_);
        return *this;
    }

    std::size_t size() const { return size_; }

    int& operator[](std::size_t i) { return data_[i]; }

private:
    std::size_t size_;
    int* data_;
};

int main() {
    Buf a(3); a[0] = 7;
    Buf b(5); b[0] = 8;
    g_fail = true;
    try {
        a = b;
    } catch (const std::bad_alloc&) {
        std::puts("alloc failed");
    }
    g_fail = false;
    std::printf("a.size = %zu, a[0] = %d\n", a.size(), a[0]);
}