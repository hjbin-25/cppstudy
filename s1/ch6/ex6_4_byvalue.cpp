//
// Created by 황정빈 on 11/17/26.
//

class T {
public:
    T() : ptr_(nullptr) {}

    ~T() { delete ptr_; }

    T(const T& other) : ptr_(other.ptr_) {}

    T& operator=(const T& other) {
        this->ptr_ = other.ptr_;
        return *this;
    }

private:
    int* ptr_;
};