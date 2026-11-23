//
// Created by 황정빈 on 11/17/26.
//

#include <stdexcept>

int* make_or_throw() {
    throw std::runtime_error("fail");
}

class Two {
public:
    Two() : a(new int[100]), b(make_or_throw()) {}

    ~Two() {
        delete[] a;
        delete[] b;
    }

private:
    int* a;
    int* b;
};

int main() {
    for (int i = 0; i < 10; ++i) {
        try {
            Two t;
        } catch (const std::exception& e) {}
    }
}