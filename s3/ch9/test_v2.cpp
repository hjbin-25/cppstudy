//
// Created by 황정빈 on 11/26/26.
//

#include "check.h"
#include "server_v2.h"
#include <memory>
#include <type_traits>

int main() {
    std::cout << "== 타입 성질 ==\n";
    CHECK(!std::is_copy_constructible_v<v2::Server>);

    std::cout << "== accept / find ==\n";
    v2::Server server;
    std::weak_ptr<Connection> a = server.accept("/dev/null", "alice");
    std::weak_ptr<Connection> b = server.accept("/dev/null", "bob");
    const int fa = a.lock()->fd();
    const int fb = b.lock()->fd();
    CHECK(server.size() == 2);
    CHECK(a.use_count() == 1);              // 오래 소유하는 건 Server 하나
    CHECK(server.find(fb).lock() == b.lock());
    CHECK(server.find(-1).expired());

    std::cout << "== leave 없이 disconnect 해도 안전 ==\n";
    v2::ChatRoom room;
    room.join(a);
    room.join(b);
    CHECK(room.broadcast("hi") == 2);
    CHECK(server.disconnect(fa));
    CHECK(a.expired());
    CHECK(!fd_is_open(fa));                 // ChatRoom이 붙잡지 않으니 바로 close
    // CHECK(room.size() == 2);                // 아직 목록에는 남아 있음 -> 로직을 고침
    CHECK(room.broadcast("bye") == 1);      // 끊긴 쪽은 건너뜀
    CHECK(room.size() == 1);                // 그리고 정리됨

    std::cout << "== lock()으로 잡고 있는 동안에는 살아 있음 ==\n";
    {
        std::shared_ptr<Connection> hold = b.lock();
        CHECK(server.disconnect(fb));
        CHECK(!b.expired());                // hold가 아직 소유
        CHECK(fd_is_open(fb));
        CHECK(hold->peer() == "bob");
    }
    CHECK(b.expired());
    CHECK(!fd_is_open(fb));
    CHECK(room.broadcast("anyone?") == 0);
    CHECK(room.size() == 0);

    return report();
}