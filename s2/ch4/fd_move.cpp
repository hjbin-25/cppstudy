//
// Created by 황정빈 on 11/23/26.
//

#include "fd.h"
#include <iostream>
#include <utility>

int main() {
    Fd a("/dev/null");
    std::cout << "[Fd b = std::move(a);]\n";
    Fd b = std::move(a);
    std::cout << "a.get()=" << a.get() << " b.get()=" << b.get() << '\n';
    // Fd c = b;
    std::cout << "[end]\n";
}

// open fd=3
// [Fd b = std::move(a);]
// move fd=3
// a.get()=-1 b.get()=3
// end
// close fd=3 -> 0