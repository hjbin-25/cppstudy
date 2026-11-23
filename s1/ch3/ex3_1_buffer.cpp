//
// Created by 황정빈 on 11/16/26.
//

#include <cstddef>
#include <cstdio>

class Buffer {
public:
    explicit Buffer(std::size_t size) : size(size), data(new int[size]) {}

    ~Buffer() {
        delete[] data;
    }

private:
    int* data;
    std::size_t size;
};

class Inner {
public:
    explicit Inner(int count) {
        std::printf("%d\n", count);

        this->count = count;
    }
private:
    int count;
};

void send(Buffer b) {}

int main() {
    Buffer b(std::size_t(10));
    send(Buffer(std::size_t(42)));

    // Inner inner(10);
}