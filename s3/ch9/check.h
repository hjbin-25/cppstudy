//
// Created by 황정빈 on 11/26/26.
//

#pragma once
#include <fcntl.h>
#include <iostream>

inline int g_fail = 0;

#define CHECK(cond)                                                          \
    do {                                                                     \
        if (cond) {                                                          \
            std::cout << "PASS " << #cond << '\n';                           \
        } else {                                                             \
            std::cout << "FAIL " << #cond << " (line " << __LINE__ << ")\n"; \
            ++g_fail;                                                        \
        }                                                                    \
    } while (0)

// fd가 아직 열려 있으면 true. 닫힌 fd 번호는 다음 open에서 다시 쓰일 수 있으니
// 닫은 직후, 새로 open 하기 전에 확인할 것
inline bool fd_is_open(int fd) { return ::fcntl(fd, F_GETFD) != -1; }

inline int report() {
    std::cout << (g_fail == 0 ? "ALL PASS" : "SOME FAILED") << '\n';
    return g_fail == 0 ? 0 : 1;
}