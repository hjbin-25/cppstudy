//
// Created by 황정빈 on 11/25/26.
//

#include <cstdio>
#include <iostream>
#include <memory>

struct FileCloser {
    void operator()(std::FILE* f) const {
        std::cout << "close fd=" << std::fclose(f) << "\n";
    }
};

using UniqueFile = std::unique_ptr<std::FILE, FileCloser>;

UniqueFile open_file(const char* path, const char* mode) {
    return UniqueFile(std::fopen(path, mode));
}

int main() {
    std::cout << std::boolalpha;

    std::cout << "[1]\n";
    UniqueFile a = open_file("/dev/null", "w");
    if (a)
        std::cout << "fputs -> " << (std::fputs("hello\n", a.get()) != EOF) << "\n";

    std::cout << "[2]\n";
    UniqueFile b = open_file("/no/such/file", "w");
    std::cout << "b가 존재함? " << (b == nullptr) << "\n";

    std::cout << "[3]\n";
    UniqueFile c = std::move(a);
    std::cout << "a가 비었음? " << (a == nullptr) << "\n";

    std::cout << "[end]\n";
}