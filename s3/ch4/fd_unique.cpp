//
// Created by 황정빈 on 11/25/26.
//

#include "base/fd.h"
#include "unique_fd.h"
#include <fcntl.h>
#include <iostream>
#include <type_traits>
#include <utility>

int main() {
    std::cout << std::boolalpha;
    std::cout << "sizeof(Fd)=" << sizeof(Fd) << " sizeof(UniqueFd)=" << sizeof(UniqueFd) << '\n';
    std::cout << "copy 가능? " << std::is_copy_constructible_v<UniqueFd> << "\n";

    std::cout << "[1] open\n";
    UniqueFd a(FdHandle(::open("/dev/null", O_RDONLY)));
    std::cout << "a.get().fd=" << a.get().fd << "\n";

    std::cout << "[2] move\n";
    UniqueFd b = std::move(a);
    std::cout << "a.get().fd=" << a.get().fd << " b.get().fd=" << b.get().fd << "\n";

    std::cout << "[3] open 실패\n";
    UniqueFd bad(FdHandle(::open("/no/such/file", O_RDONLY)));
    std::cout << "bad 비었나? " << !bad << '\n';   // -1이면 빈 값. close가 안 불림

    std::cout << "[4] 비교: 손으로 짠 Fd\n";
    {
        Fd f("/dev/null");
        Fd g = std::move(f);
    }
    std::cout << "[end]\n";
}

// sizeof(Fd)=4 sizeof(UniqueFd)=4
// copy 가능? false
// [1] open
// a.get().fd=3
// [2] move
// a.get().fd=-1, b.get().fd=3
// [3] open 실패
// bad 비었나? true
// [4] 비교: 손으로 짠 Fd
// open  fd=4
// move  fd=4
// close fd=4 -> 0
// [end]
// close fd=3 -> 0