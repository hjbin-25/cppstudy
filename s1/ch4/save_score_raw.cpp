//
// Created by 황정빈 on 11/16/26.
//

#include <cstdio>
#include <unistd.h>

bool save_score(const char* path, int score) {
    std::FILE* f = std::fopen(path, "w");
    if (!f) return false;

    if (score < 0) {
        return false;               // fclose 빠뜨림 → 파일 핸들 누수
    }
    if (std::fprintf(f, "%d\n", score) < 0) {
        std::fclose(f);             // 여기는 챙김
        return false;
    }
    std::fclose(f);
    return true;
}

int main() {
    save_score("score.txt", -1);
    std::printf("pid = %d\n", getpid());
    std::getchar();
}