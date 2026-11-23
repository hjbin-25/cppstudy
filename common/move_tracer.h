//
// Created by 황정빈 on 11/23/26.
//

#pragma once
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

class MoveTracer {
public:
    explicit MoveTracer(std::string value) : id_(next_id_++), value_(std::move(value)) {
        log("ctor");
    };

    MoveTracer(const MoveTracer& other) : id_(next_id_++), value_(other.value_) {
        log("copy ctor", other);
    }

    MoveTracer(MoveTracer&& other) : id_(next_id_++), value_(std::move(other.value_)) {
        other.value_.clear();
        log("move ctor", other);
    }

    MoveTracer& operator=(const MoveTracer& other) {
        value_ = other.value_;
        log("copy assign", other);
        return *this;
    }

    MoveTracer& operator=(MoveTracer&& other) {
        if (this != &other) {
            value_ = std::move(other.value_);
            other.value_.clear();
        }
        log("move assign", other);
        return *this;
    }

    ~MoveTracer() { log("dtor"); }

    friend void swap(MoveTracer& a, MoveTracer& b) {
        a.value_.swap(b.value_);
        a.log("swap", b);
    }

    int id() const { return id_; }

    const std::string& value() const { return value_; }

private:
    void log(const std::string& what) const {
        std::cout << '#' << id_ << ' ' << pad(what) << '"' << value_ << "\"\n";
    }

    void log(const std::string& what, const MoveTracer& from) const {
        std::cout << '#' << id_ << ' ' << pad(what) << '"' << value_ << "\"  from #" << from.id_ << '\n';
    }

    static std::string pad(const std::string& s) {
        const std::size_t width = 12;
        return s.size() >= width ? s + ' ' : s + std::string(width - s.size(), ' ');
    }

    inline static int next_id_ = 1;
    int id_;
    std::string value_;
};
