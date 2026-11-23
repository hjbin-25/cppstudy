//
// Created by 황정빈 on 11/23/26.
//

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include <utility>

class BadFd {
public:
    explicit BadFd(const char* path) : fd_(::open(path, O_RDONLY)) {
        if (fd_ == -1)
            throw std::runtime_error("open 실패");
        std::cout << "open  fd=" << fd_ << '\n';
    }

    BadFd(const BadFd&) = delete;

    BadFd& operator=(const BadFd&) = delete;

    BadFd(BadFd&& other) noexcept : fd_(other.fd_) {
        std::cout << "move  fd=" << fd_ << '\n';
    }

    ~BadFd() { close_if_open(); }

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

static int count = 1;

void log(BadFd& a, BadFd& b) {
    std::cout << count++ << ". a.get()=" << a.get() << " c.get()=" << b.get() << "\n";
}

int main() {
    BadFd a("/dev/null");
    {
        BadFd b = std::move(a);
    }
    BadFd c("/dev/null");
    log(a, c);
}

// open  fd=3
// move  fd=3
// close fd=3 -> 0
// open  fd=3
// 1. a.get()=3 b.get()=3
// close fd=3 -> 0
// close fd=3 -> -1