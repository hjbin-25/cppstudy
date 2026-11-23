//
// Created by 황정빈 on 11/17/26.
//

#include <cstdio>
#include <cstddef>

class Shallow {
public:
    explicit Shallow(std::size_t n) : size_(n), data_(new int[n]{}) {}

    ~Shallow() { delete[] data_; }

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
    {
        Shallow b = a;
        b.at(0) = 99;
        std::printf("a[0] = %d\n", a.at(0));
    }
    // a.at(1) = 1;
}