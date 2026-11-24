//
// Created by 황정빈 on 11/24/26.
//

#pragma once
#include "base/fd.h"
#include <string>
#include <utility>

class Connection {
public:
    Connection(const char* path, std::string peer) : fd_(path), peer_(std::move(peer)) {}

    int fd() const { return fd_.get(); }

    const std::string& peer() const { return peer_; }

private:
    Fd fd_;
    std::string peer_;
};