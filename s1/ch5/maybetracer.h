//
// Created by 황정빈 on 11/17/26.
//

#pragma once
#include <cstring>
#include <stdexcept>

class MaybeTracer {
public:
    explicit MaybeTracer(const char* name) : name(name) {
        if (std::strcmp(name, "bad") == 0)
            throw std::runtime_error("name is bad");

        std::printf("    ctor %s\n", name);
    }

    ~MaybeTracer() {
        std::printf("    dtor %s\n", name);
    }

private:
    const char* name;
};
