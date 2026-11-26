//
// Created by 황정빈 on 11/26/26.
//

#include "check.h"
#include "server_v1.h"
#include <type_traits>

int main() {
    std::cout << "== 타입 성질 ==\n";
    CHECK(!std::is_copy_constructible_v<v1::Server>);
    CHECK(!std::is_copy_assignable_v<v1::Server>);

    std::cout << "== accept / find ==\n";
    v1::Server server;
    Connection& a = server.accept("/dev/null", "alice");
    Connection& b = server.accept("/dev/null", "bob");
    const int fa = a.fd();
    const int fb = b.fd();
    CHECK(server.size() == 2);
    CHECK(server.find(fa) == &a);
    CHECK(server.find(fb) == &b);
    CHECK(server.find(-1) == nullptr);

    std::cout << "== accept가 늘어나도 앞의 참조는 유효 ==\n";
    for (int i = 0; i < 20; ++i)
        server.accept("/dev/null", "extra");
    CHECK(server.find(fa) == &a && a.peer() == "alice");

    std::cout << "== ChatRoom: leave 후 disconnect ==\n";
    v1::ChatRoom room;
    room.join(a);
    room.join(b);
    CHECK(room.broadcast("hi") == 2);
    room.leave(a);
    CHECK(room.size() == 1);
    CHECK(server.disconnect(fa));
    CHECK(!fd_is_open(fa));          // Connection이 사라지면서 Fd가 close
    CHECK(server.find(fa) == nullptr);
    CHECK(room.broadcast("bye") == 1);
    CHECK(!server.disconnect(fa));   // 두 번 끊기는 false

    std::cout << "== Server가 사라지면 남은 Connection의 fd도 close ==\n";
    int ft = -1;
    {
        v1::Server temp;
        ft = temp.accept("/dev/null", "temp").fd();
        CHECK(fd_is_open(ft));
    }
    CHECK(!fd_is_open(ft));

    return report();
}
