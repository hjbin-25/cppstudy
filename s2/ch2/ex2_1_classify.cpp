//
// Created by 황정빈 on 11/23/26.
//

#include <iostream>
#include <utility>

void cat(int&) {
    std::cout << "lvalue\n";
}

void cat(int&&) {
    std::cout << "rvalue\n";
}

int get_value() {
    return 1;
}

int& get_ref() {
    static int value = 0;
    return value;
}

int main() {
    int x;
    int arr[2];
    int&& rr = 5;

    cat(x);
    cat(x + 1);
    cat(++x);
    cat(x++);
    cat(arr[0]);
    cat(get_value());
    cat(get_ref());
    cat(std::move(x));
    cat(rr);
}

// lvalue
// rvalue
// lvalue
// rvalue
// lvalue
// rvalue
// lvalue
// rvalue
// lvalue