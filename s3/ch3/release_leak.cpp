//
// Created by 황정빈 on 11/25/26.
//

#include <cstddef>
#include <iostream>
#include <memory>

int main() {
    std::size_t sum = 0;
    for (int i = 0; i < 1000; ++i) {
        auto buf = std::make_unique<int[]>(16);
        int* raw = buf.release();
        sum += static_cast<std::size_t>(raw[0]);
        // delete raw;
        // 소유권 이전으로 인하여 위 줄이 없으면 메모리 누수 발생
    }
    std::cout << "sum=" << sum << "\n";
}