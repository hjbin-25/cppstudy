//
// Created by 황정빈 on 11/26/26.
//

#include <iostream>
#include <memory>

struct InCtor : std::enable_shared_from_this<InCtor> {
    InCtor() {
        try {
            auto self = shared_from_this();
        } catch (const std::bad_weak_ptr&) {
            std::cout << "  생성자 안: bad_weak_ptr\n";
        }
        std::cout << "  생성자 안 weak_from_this().expired()=" << weak_from_this().expired() << '\n';
    }
};

struct OnStack : std::enable_shared_from_this<OnStack> {};

class Hidden : std::enable_shared_from_this<Hidden> {
public:
    bool try_self() {
        try {
            shared_from_this();
            return true;
        } catch (const std::bad_weak_ptr&) {
            return false;
        }
    }
};

int main() {
    std::cout << std::boolalpha;
    std::cout << "[1] 생성자에서\n";
    auto a = std::make_shared<InCtor>();
    std::cout << "  생성 후 count=" << a->shared_from_this().use_count() << '\n';

    std::cout << "[2] 스택 객체에서\n";
    OnStack s;
    try {
        s.shared_from_this();
    } catch (const std::bad_weak_ptr&) {
        std::cout << "  스택 객체: bad_weak_ptr\n";
    }

    std::cout << "[3] private 상속\n";
    auto h = std::make_shared<Hidden>();
    std::cout << "  shared_from_this 성공? " << h->try_self() << '\n';
    std::cout << "[end]\n";
}

// [1] 생성자에서
//   생성자 안: bad_weak_ptr
//   생성자 안 weak_from_this().expired()=true
//   생성 후 count=2
// [2] 스택 객체에서
//   스택 객체: bad_weak_ptr
// [3] private 상속
//   shared_from_this 성공? false
// [end]