//
// Created by 황정빈 on 11/26/26.
//

#include <iostream>
#include <memory>
#include <string>

struct Session {
    std::string name;

    ~Session() {
        std::cout << "  ~Session(" << name << ")\n";
    }

    std::shared_ptr<Session> self() {
        return std::shared_ptr<Session>(this);
    }
};

int main() {
    auto s = std::make_shared<Session>();
    s->name = "s1";
    {
        std::shared_ptr<Session> again = s->self();
        std::cout << "s count=" << s.use_count() << " again count=" << again.use_count() << '\n';
    }
    std::cout << "[end]\n";
}

// s count=1 again count=1
//   ~Session(s1)
// double free (by double owner)