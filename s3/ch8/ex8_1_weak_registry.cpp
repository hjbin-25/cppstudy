//
// Created by 황정빈 on 11/26/26.
//

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Session;

class Registry {
public:
    void add(std::weak_ptr<Session> s) {
        sessions_.push_back(std::move(s));
    }

    void clear() {
        sessions_.clear();
    }

    std::size_t alive() {
        size_t count = 0;

        for (const auto& s : sessions_) {
            if (!s.expired())
                ++count;
        }

        return count;
    }

private:
    std::vector<std::weak_ptr<Session>> sessions_;
};

class Session : public std::enable_shared_from_this<Session> {
public:
    static std::shared_ptr<Session> create(std::string name) {
        return std::shared_ptr<Session>(new Session(name));
    }

    ~Session() {
        std::cout << "  ~Session(" << name_ << ")\n";
    }

    void register_to(Registry& r) {
        r.add(weak_from_this());
    }

private:
    explicit Session(std::string name) : name_(std::move(name)) {}

    std::string name_;
};

int main() {
    std::cout << "[1]\n";
    Registry r;
    std::shared_ptr<Session> s = Session::create("s");
    s->register_to(r);
    std::cout << "count=" << s.use_count() << " alive=" << r.alive() << "\n";

    std::cout << "[2]\n";
    s.reset();
    std::cout << "alive=" << r.alive() << "\n";

    std::cout << "[end]\n";
}

// [1]
// count=1 alive=1
// [2]
//   ~Session(s)
// alive=0
// [end]