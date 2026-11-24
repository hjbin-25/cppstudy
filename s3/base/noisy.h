//
// Created by 황정빈 on 11/24/26.
//

#pragma once
#include <iostream>
#include <string>
#include <utility>

class Noisy {
public:
    explicit Noisy(std::string name) : name_(std::move(name)) {
        std::cout << "  Noisy(" << name_ << ")\n";
    }

    Noisy(const Noisy& other) : name_(other.name_) {
        std::cout << "  copy(" << name_ << ")\n";
    }

    Noisy(Noisy&& other) noexcept : name_(std::exchange(other.name_, "-")) {
        std::cout << "  move(" << name_ << ")\n";
    }

    Noisy& operator=(const Noisy&) = delete;

    Noisy& operator=(Noisy&&) noexcept = delete;

    ~Noisy() {
        std::cout << "  ~Noisy(" << name_ << ")\n";
    }

    const std::string& name() const {
        return name_;
    }
    
private:
    std::string name_;
};