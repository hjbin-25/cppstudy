//
// Created by 황정빈 on 11/24/26.
//

#include <cstdio>
#include <cstring>
#include <iostream>

struct Label {
    const char* text;
};

const char* make_text(int n) {
    char* buf = new char[16];
    std::snprintf(buf, 16, "label-%d", n);
    return buf;
}

int main() {
    std::size_t total = 0;
    for (int i = 0; i < 1000; ++i) {
        Label a("fixed");
        Label b(make_text(i));
        total += strlen(a.text) + strlen(b.text);
        // delete b.text;
        // 현재는 누수가 존재하는 코드지만 호출한 부분이기에 위와 같이 b.text를 delete 해주어야지 메모리 누수 방지 가능
    }
    std::cout << "total=" << total << "\n";
}

// 13890