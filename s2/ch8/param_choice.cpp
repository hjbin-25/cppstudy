//
// Created by 황정빈 on 11/24/26.
//

#include "move_tracer.h"
#include <iostream>
#include <utility>

class Player {
public:
    void set_by_cref(const MoveTracer& t) {
        name_ = t;
    }

    void set_by_value(MoveTracer t) {
        name_ = std::move(t);
    }

    void set_by_rref(MoveTracer&& t) {
        name_ = std::move(t);
    }

private:
    MoveTracer name_{"empty"};
};

int main() {
    MoveTracer src("src");
    Player p;

    std::cout << "[1] set_by_cref(src)\n";
    p.set_by_cref(src);
    std::cout << "[2] set_by_cref(MoveTracer(\"t1\"))\n";
    p.set_by_cref(MoveTracer("t1"));

    std::cout << "[3] set_by_value(src)\n";
    p.set_by_value(src);
    std::cout << "[4] set_by_value(MoveTracer(\"t2\"))\n";
    p.set_by_value(MoveTracer("t2"));

    std::cout << "[5] set_by_rref(MoveTracer(\"t3\"))\n";
    p.set_by_rref(MoveTracer("t3"));
    // p.set_by_rref(src);  // 컴파일 에러: lvalue는 && 매개변수에 못 묶임
    std::cout << "[end]\n";
}

// #1 ctor src
// #2 ctor empty
// 1
// #2 copy assign "src"
// 2
// #3 ctor t1
// #2 copy assign "t1"
// #3 dtor "t1"
// 3
// #4 copy ctor "src"
// #2 move assign "src"
// #4 dtor ""
// 4
// #5 ctor "t2"
// #2 move assign "t2"
// #5 dtor ""
// 5
// #6 ctor "t3"
// #2 move assign "t3"
// #6 dtor ""
// end
// #2 dtor "t3"
// #1 dtor "src"