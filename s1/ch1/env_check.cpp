#include <climits>
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int mode = argc > 1 ? std::atoi(argv[1]) : 0;

    if (mode == 1) {               // ASan: use-after-free
        int* p = new int{42};
        delete p;
        std::printf("%d\n", *p);
    } else if (mode == 2) {        // ASan: 배열 범위 밖 접근
        int* arr = new int[3]{};
        arr[3] = 1;
        delete[] arr;
    } else if (mode == 3) {        // UBSan: signed 오버플로
        int x = INT_MAX - 2 + argc; // 인자 하나면 argc == 2 → x == INT_MAX
        std::printf("%d\n", x + 1); // 컴파일 타임에 계산되지 않게 argc를 섞음
    } else if (mode == 4) {        // 누수: macOS ASan은 못 잡음
        for (int i = 0; i < 10; ++i) {
            int* leak = new int[100];
            leak[0] = i;
        }
    }
    std::puts("done");
}