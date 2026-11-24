//
// Created by 황정빈 on 11/24/26.
//

#include "move_tracer.h"

MoveTracer make_one(bool first) {
    MoveTracer x(first ? "x" : "y");
    return x;
}

int main() {
    MoveTracer a = make_one(true);
}