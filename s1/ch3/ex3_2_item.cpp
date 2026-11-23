//
// Created by 황정빈 on 11/16/26.
//

#include <string>

class Item {
public:
    Item(int id, std::string& owner) : id(id), owner(owner) {}

private:
    const int id;
    std::string& owner;
};
