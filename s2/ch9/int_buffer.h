//
// Created by 황정빈 on 11/23/26.
//

#pragma once
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <utility>

class IntBuffer {
public:
    explicit IntBuffer(std::size_t size) : size_(size), data_(new int[size]{}) {}

    IntBuffer(const IntBuffer& other) : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    ~IntBuffer() { delete[] data_; }

    friend void swap(IntBuffer& a, IntBuffer& b) noexcept {
        using std::swap;
        swap(a.size_, b.size_);
        swap(a.data_, b.data_);
    }

    IntBuffer& operator=(const IntBuffer& other) {
        IntBuffer temp(other);
        swap(*this, temp);
        return *this;
    }

    std::size_t size() const { return size_; }

    int operator[](const std::size_t index) const { return data_[index]; }

    int& operator[](const std::size_t index) { return data_[index]; }

    int at(const std::size_t index) const {
        if (index < 0 || index >= size_)
            throw std::out_of_range("data 범위를 벗어났습니다.");

        return data_[index];
    }

    int& at(const std::size_t index) {
        if (index < 0 || index >= size_)
            throw std::out_of_range("data 범위를 벗어났습니다.");

        return data_[index];
    }

private:
    std::size_t size_;
    int* data_;
};