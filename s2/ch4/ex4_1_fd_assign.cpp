//
// Created by 황정빈 on 11/23/26.
//

#include "ex4_1_fd.h"
#include <iostream>
#include <utility>

static int count = 1;

void log(Fd& a, Fd& b) {
    std::cout << count++ << ". a.get()=" << a.get() << " b.get()=" << b.get() << "\n";
}

int main() {
    Fd a("/dev/null");
    Fd b("/dev/null");
    log(a, b);
    a = std::move(b);
    log(a, b);
    Fd& same = a;
    log(a, b);
    a = std::move(same);
    log(a, b);
    b = Fd("/dev/null");
    log(a, b);
}

// open  fd=3
// open  fd=4
// 1. a.get()=3 b.get()=4
// close fd=3 -> 0
// move= fd=4
// 2. a.get()=4 b.get()=-1
// 3. a.get()=4 b.get()=-1
// move= fd=4
// 4. a.get()=4 b.get()=-1
// open  fd=3
// move= fd=3
// 5. a.get()=4 b.get()=3
// close fd=3 -> 0
// close fd=4 -> 0