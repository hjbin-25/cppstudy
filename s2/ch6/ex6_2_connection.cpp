//
// Created by 황정빈 on 11/23/26.
//

#include "../ch4/fd.h"
#include "move_tracer.h"
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

class Connection {
public:
    Connection(const char* path, std::string peer) : fd_(path), peer_(std::move(peer)) {}

    int fd() const { return fd_.get(); }

    const std::string& peer() const { return peer_.value(); }

private:
    Fd fd_;
    MoveTracer peer_;
};

int main() {
    std::cout << std::boolalpha;
    std::cout << "copy 가능?         " << std::is_copy_constructible_v<Connection> << '\n';
    std::cout << "nothrow move 가능? " << std::is_nothrow_move_constructible_v<Connection> << '\n';
    std::cout << "move 대입 가능?    " << std::is_move_assignable_v<Connection> << '\n';

    Connection a("/dev/null", "peer-1");
    std::cout << "[Connection b = std::move(a);]\n";
    Connection b = std::move(a);
    std::cout << "a.fd()=" << a.fd() << " b.fd()=" << b.fd() << " b.peer()=" << b.peer() << '\n';
    // Connection c = b;  // 컴파일 에러: Fd의 복사가 delete라서 Connection의 복사도 delete
    std::cout << "[end]\n";
}