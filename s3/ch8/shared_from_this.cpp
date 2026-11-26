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
    void add(std::shared_ptr<Session> s) {
        sessions_.push_back(std::move(s));
    }

    void clear() {
        sessions_.clear();
    }

private:
    std::vector<std::shared_ptr<Session>> sessions_;
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
        r.add(shared_from_this());
    }

private:
    explicit Session(std::string name) : name_(std::move(name)) {}

    std::string name_;
};

int main() {
    Registry reg;
    std::cout << "[1]\n";
    std::shared_ptr<Session> s = Session::create("s1");
    std::cout << "count=" << s.use_count() << '\n';

    std::cout << "[2] register_to\n";
    s->register_to(reg);
    std::cout << "count=" << s.use_count() << '\n';

    std::cout << "[3] main의 s를 놓음\n";
    s.reset();
    std::cout << "(Registry가 아직 소유)\n";

    std::cout << "[4] Registry 비움\n";
    reg.clear();
    std::cout << "[end]\n";
}

// [1]
// count=1
// [2] register_to
// count=2
// [3] main의 s를 놓음
// (Registry가 아직 소유)
// [4] Registry 비움
//   ~Session(s1)
// [end]
