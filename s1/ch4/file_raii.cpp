//
// Created by 황정빈 on 11/16/26.
//

#include <cstdio>
#include <stdexcept>

class File {
public:
    File(const char* path, const char* mode) : f(std::fopen(path, mode)) {
        if (!f)
            throw std::runtime_error("fopen failed");
    }

    ~File() {
        std::fclose(f);
        std::puts("file closed");
    }

    File(const File&) = delete;
    File& operator=(const File&) = delete;

    std::FILE* get() const {
        return f;
    }

private:
    std::FILE* f;
};

bool save_score(const char* path, int score) {
    File file(path, "w");

    if (score < 0)
        return false;

    if (std::fprintf(file.get(), "%d\n", score)  < 0)
        return false;

    return true;
}

int main() {
    save_score("score.txt", -1);
}