//
// Created by 황정빈 on 11/16/26.
//

#include <chrono>
#include <unistd.h>

class ScopeTimer {
public:
    explicit ScopeTimer(const char* label) : label(label), start(std::chrono::steady_clock::now()) {}

    ~ScopeTimer() {
        auto elapsed = std::chrono::steady_clock::now() - start;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::printf("%s: %lld ms\n", label, static_cast<long long>(ms));
    }

    ScopeTimer(const ScopeTimer&) = delete;

    ScopeTimer& operator=(const ScopeTimer&) = delete;

private:
    const char* label;
    std::chrono::steady_clock::time_point start;
};

void heavy_work() {
    ScopeTimer("heavy_work");
    sleep(20);
}

int main() {
    heavy_work();
}