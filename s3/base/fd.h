//
// Created by 황정빈 on 11/24/26.
//

#pragma once
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include <utility>

class Fd {
public:
    explicit Fd(const char* path) : fd_(::open(path, O_RDONLY)) {
        if (fd_ == -1)
            throw std::runtime_error("open 실패");
        std::cout << "open  fd=" << fd_ << '\n';
    }

    Fd(const Fd&) = delete;

    Fd& operator=(const Fd&) = delete;

    Fd(Fd&& other) noexcept : fd_(std::exchange(other.fd_, -1)) {
        std::cout << "move  fd=" << fd_ << '\n';
    }

    ~Fd() { close_if_open(); }

    int get() const { return fd_; }

    bool valid() const { return fd_ != -1; }

private:
    void close_if_open() {
        if (fd_ != -1) {
            const int r = ::close(fd_);
            std::cout << "close fd=" << fd_ << " -> " << r << '\n';
        }
    }

    int fd_;
};