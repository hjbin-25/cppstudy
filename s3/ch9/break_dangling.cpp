//
// Created by 황정빈 on 11/26/26.
//

#include "server_v1.h"
#include <iostream>

int main() {
    v1::Server server;
    v1::ChatRoom room;

    Connection& a = server.accept("/dev/null", "alice");
    Connection& b = server.accept("/dev/null", "bob");
    room.join(a);
    room.join(b);
    room.broadcast("hi");

    const int fa = a.fd();
    // room.leave(a);
    server.disconnect(fa);

    std::cout << "[broadcast after disconnect]\n";
    room.broadcast("bye");
    std::cout << "[end]\n";
}
// open  fd=3
// open  fd=4
//   -> alice: hi
//   -> bob: hi
// disconnect fd=3
// close fd=3 -> 0
// [broadcast after disconnect]
//   ->