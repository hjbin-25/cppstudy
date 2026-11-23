//
// Created by 황정빈 on 11/17/26.
//

#include <cstdio>
#include <cstddef>
#include <algorithm>
#include <new>
#include <utility>

class Buf {
public:
    explicit Buf(std::size_t n) : size_(n), data_(new int[n]{}) {}

    ~Buf() { delete[] data_; }

    Buf(const Buf& other) : size_(other.size_), data_(new int[other.size_]{}) {
        std::copy(other.data_, other.data_ + other.size_, this->data_);
    }

    Buf& operator=(const Buf& other) {
        if (this == &other)
            return *this;
        int* fresh = new int[other.size_];
        std::copy(other.data_, other.data_ + other.size_, fresh);

        delete [] data_;
        size_ = other.size_;
        data_ = fresh;
        return *this;
    }

    std::size_t size() const { return size_; }

    int& operator[](std::size_t i) { return data_[i]; }

private:
    std::size_t size_;
    int* data_;
};

int main() {
    Buf a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    Buf& r = a;
    a = r;
    std::printf("%d %d %d\n", a[0], a[1], a[2]);
}