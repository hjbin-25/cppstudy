//
// Created by 황정빈 on 11/26/26.
//

#include <iostream>
#include <memory>
#include <string>

static int g_session_dtor = 0;
static int g_room_dtor = 0;

struct Room;

struct Session {
    std::string name;
    std::shared_ptr<Room> room;
    ~Session() {
        ++g_session_dtor;
    }
};

struct Room {
    std::string title;
    std::shared_ptr<Session> session;
    ~Room() {
        ++g_room_dtor;
    }
};

int main() {
    for (int i = 0; i < 1000; ++i) {
        auto s = std::make_shared<Session>();
        auto r = std::make_shared<Room>();
        s->room = r;
        r->session = s;
    }
    std::cout << "~Session " << g_session_dtor << "회, ~Room " << g_room_dtor << "회\n";
}