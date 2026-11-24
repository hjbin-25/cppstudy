//
// Created by 황정빈 on 11/24/26.
//

#include <iostream>
#include <string>

// 소유
// 빌리지 않음
// 호출하는 애가 알아서 지움
struct Label {
    std::string text;
};

std::string make_text(int n) {
    return "label-" + std::to_string(n);
}

int main() {
    std::size_t total = 0;
    for (int i = 0; i < 1000; ++i) {
        // 빌림
        Label a("fixed");
        // 함수가 소유
        Label b(make_text(i));
        total += a.text.length() + b.text.length();
    }
    std::cout << "total=" << total << "\n";
}