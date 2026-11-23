//
// Created by 황정빈 on 11/23/26.
//

#include "../../common/move_tracer.h"
#include <utility>

int main() {
    MoveTracer a("a");
    MoveTracer b = a;
    MoveTracer c = std::move(a);
    b = c;
    b = std::move(c);
}