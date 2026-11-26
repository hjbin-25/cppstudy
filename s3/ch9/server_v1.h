//
// Created by 황정빈 on 11/26/26.
//

#pragma once
#include "base/connection.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <cstddef>
#include <utility>
#include <string_view>

namespace v1 {
    // Connection 소유
    // 빌리지 않음
    // 부른 곳에서 지워야됨
    class Server {
    public:
        Server() = default;
        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;

        Connection& accept(const char* path, std::string peer) {
            connections_.push_back(std::make_unique<Connection>(path, std::move(peer)));
            return *connections_.back();
        }

        const Connection* find(int fd) const {
            for (const auto& c : connections_) {
                if (c->fd() == fd)
                    return c.get();
            }
            return nullptr;
        }

        bool disconnect(int fd) {
            std::cout << "disconnect fd=" << fd << "\n";
            return std::erase_if(connections_, [fd](const std::unique_ptr<Connection>& c) {
                return c->fd() == fd;
            }) > 0;
        }

        std::size_t size() const {
            return connections_.size();
        }

    private:
        std::vector<std::unique_ptr<Connection>> connections_;
    };

    // 소유하지 않음
    // Connection 빌림
    // Server가 disconnect 전에 leave 호출하기
    class ChatRoom {
    public:
        void join(Connection& c) {
            members_.push_back(&c);
        }

        void leave(const Connection& c) {
            std::erase(members_, &c);
        }

        std::size_t broadcast(std::string_view msg) const {
            for (const auto& c : members_)
                std::cout << "  -> " << c->peer() << ": " << msg << "\n";
            return members_.size();
        }

        std::size_t size() const {
            return members_.size();
        }

    private:
        std::vector<Connection*> members_;
    };
}