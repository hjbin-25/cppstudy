//
// Created by 황정빈 on 11/25/26.
//

#pragma once
#include <unistd.h>
#include <cstddef>
#include <iostream>
#include <memory>

struct FdHandle {
    int fd = -1;

    FdHandle() = default;

    FdHandle(std::nullptr_t) {}

    explicit FdHandle(int fd) : fd(fd) {}

    explicit operator bool() const {
        return fd != -1;
    }

    friend bool operator==(FdHandle, FdHandle) = default;

    friend bool operator==(FdHandle h, std::nullptr_t) {
        return h.fd == -1;
    }
};

struct FdCloser {
    using pointer = FdHandle;

    void operator()(FdHandle h) const {
        const int r = ::close(h.fd);
        std::cout << "close fd=" << h.fd << " -> " << r << "\n";
    }
};

using UniqueFd = std::unique_ptr<FdHandle, FdCloser>;