//
// Created by 황정빈 on 11/27/26.
//

#pragma once
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <system_error>
#include <utility>

// 파일 디스크립터 하나를 소유한다 (move-only)
// 소멸자에서 close. 옮겨진 뒤(moved-from)에는 -1을 들고 있고 close하지 않는다
// get()이 돌려준 정수는 이 Fd가 살아 있는 동안만 의미가 있다
class Fd {
public:
    explicit Fd(const char* path) : fd_(::open(path, O_RDONLY)) {
        if (fd_ < 0)
            throw std::system_error(errno, std::generic_category(), path);
    }

    ~Fd() {
        if (fd_ >= 0)
            ::close(fd_);
    }

    Fd(const Fd&) = delete;
    Fd& operator=(const Fd&) = delete;

    Fd(Fd&& other) noexcept : fd_(std::exchange(other.fd_, -1)) {}

    Fd& operator=(Fd&& other) noexcept {
        if (this != &other) {
            if (fd_ >= 0)
                ::close(fd_);
            fd_ = std::exchange(other.fd_, -1);
        }
        return *this;
    }

    int get() const noexcept { return fd_; }

private:
    int fd_;
};