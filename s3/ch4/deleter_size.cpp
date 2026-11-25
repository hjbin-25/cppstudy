//
// Created by 황정빈 on 11/25/26.
//

#include <cstdio>
#include <iostream>
#include <memory>
#include <sys/fcntl.h>

struct FileCloser {
    void operator()(std::FILE* f) const {
        std::fclose(f);
    }
};

void close_file(std::FILE* f) {
    std::fclose(f);
}

int main() {
    auto lambda = [](std::FILE* f) { std::fclose(f); };

    using ByStruct = std::unique_ptr<std::FILE, FileCloser>;
    using ByFuncPtr = std::unique_ptr<std::FILE, void (*)(std::FILE*)>;
    using ByLambda = std::unique_ptr<std::FILE, decltype(lambda)>;

    std::cout << "raw pointer : " << sizeof(std::FILE*) << '\n';
    std::cout << "struct      : " << sizeof(ByStruct) << '\n';
    std::cout << "함수 포인터 : " << sizeof(ByFuncPtr) << '\n';
    std::cout << "lambda      : " << sizeof(ByLambda) << '\n';

    ByStruct a(std::fopen("/dev/null", "r"));
    ByFuncPtr b(std::fopen("/dev/null", "r"), close_file);
    ByFuncPtr c(std::fopen("/dev/null", "r"), lambda);

    std::cout << std::boolalpha << "all open: " << (a && b && c) << '\n';
}
