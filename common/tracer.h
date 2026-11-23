//
// Created by 황정빈 on 11/16/26.
//

#pragma once
#include <cstdio>

class Tracer {
public:
    explicit Tracer(const char* name) : name_(name) {
        std::printf("    ctor %s\n", name_);
    }

    ~Tracer() {
        std::printf("    dtor %s\n", name_);
    }

    explicit Tracer(const Tracer& other) : name_(other.name_) {
        std::printf("    copy-ctor %s\n", name_);
    }

    Tracer& operator=(const Tracer& other) {
        this->name_ = other.name_;
        std::printf("    copy-assign %s\n", name_);
        return *this;
    }

private:
    const char *name_;
};