//
// Created by 황정빈 on 11/23/26.
//

#include <stdexcept>
#include "int_buffer.h"

IntBuffer make_or_throw_buffer() { throw std::runtime_error("fail"); }

class Two {
public:
    Two() : a_(100), b_(make_or_throw_buffer()) {}

private:
    IntBuffer a_;
    IntBuffer b_;
};

int main() {
    for (int i = 0; i < 10; ++i) {
        try {
            Two t;
        } catch (const std::exception& e) {}
    }
}