//
// Created by 황정빈 on 11/17/26.
//

#include <stdexcept>
#include "../../common/tracer.h"
#include "maybetracer.h"


class Holder {
public:
    Holder() : a("a"), b("bad"), c("c") {
        std::puts("    Holder body");
    }

    ~Holder() {
        std::puts("    ~Holder body");
    }

private:
    Tracer a;
    MaybeTracer b;
    Tracer c;
};

int main() {
    try {
        Holder h;
    } catch (const std::exception& e) {
        std::printf("caught: %s\n", e.what());
    }
}