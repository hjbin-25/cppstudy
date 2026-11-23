//
// Created by 황정빈 on 11/23/26.
//

#include "move_tracer.h"
#include <iostream>
#include <utility>

class Bag {
public:
    void put_wrong(MoveTracer&& t) {
        item_ = t;
    }

    void put(MoveTracer&& t) {
        item_ = std::move(t);
    }

private:
    MoveTracer item_{"empty"};
};

int main() {
    Bag b;

    std::cout << "[put_wrong]\n";
    b.put_wrong(MoveTracer("x"));
    std::cout << "[put]\n";
    b.put(MoveTracer("y"));
    std::cout << "[end]\n";
}
// ctor empty
// put_wrong
// ctor x
// copy assign
// dtor "x"
// put
// ctor y
// move assign
// dtor ""
// end
// dtor "y"