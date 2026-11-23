//
// Created by 황정빈 on 11/17/26.
//

#include <cstdio>
#include <cstddef>

class Shallow {
public:
    explicit Shallow(std::size_t n) : size_(n), data_(new int[n]{}) {}

    ~Shallow() { delete[] data_; }

    Shallow(const Shallow& other) : size_(other.size_), data_(new int[size_]{}) {}

    int& at(std::size_t n) {
        return data_[n];
    }

    std::size_t size() const {
        return size_;
    }

private:
    std::size_t size_;
    int* data_;
};

int main() {
    Shallow a(3);
    Shallow b(5);
    b = a;
}