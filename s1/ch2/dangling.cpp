//
// Created by 황정빈 on 11/16/26.
//

#include <cstdio>

int* make_number() {
    int n = 10;
    return &n;
    // return new int{10};
}

const int& bigger(const int& a, const int& b) {
    return a > b ? a : b;
}

int main() {
    int* p = make_number();
    std::printf("%d\n", *p);

    const int &r = bigger(1, 2);
    std::printf("%d\n", r);
}
