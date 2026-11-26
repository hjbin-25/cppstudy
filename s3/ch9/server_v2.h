//
// Created by 황정빈 on 11/26/26.
//

#pragma once
#include "base/connection.h"
#include <memory>
#include <iostream>
#include <string>
#include <vector>

namespace v2 {
    // Connection 소유
    // 빌리지 않음
    // disconnect 하면 Connection이 죽음
    class Server {
    public:
        Server() = default;
        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;

        std::weak_ptr<Connection> accept(const char* path, std::string peer) {
            connections_.push_back(std::make_shared<Connection>(path, std::move(peer)));
            return connections_.back();
        }

        std::weak_ptr<Connection> find(int fd) const {
            for (const auto& c : connections_) {
                if (c->fd() == fd)
                    return c;
            }
            return {};
        }

        bool disconnect(int fd) {
            std::cout << "disconnect fd=" << fd << "\n";
            return std::erase_if(connections_, [fd](const std::shared_ptr<Connection>& c) {
                return c->fd() == fd;
            }) > 0;
        }

        std::size_t size() const {
            return connections_.size();
        }

    private:
        std::vector<std::shared_ptr<Connection> > connections_;
    };

    // 소유하지 않음
    // Connection 빌려 씀
    // Connection은 Server가 disconnect 해주면 해제됨
    class ChatRoom {
    public:
        void join(std::weak_ptr<Connection> c) {
            members_.push_back(std::move(c));
        }

        std::size_t broadcast(std::string_view msg) {
            std::size_t sent = 0;
            for (const auto& c : members_) {
                if (std::shared_ptr<Connection> s = c.lock()) {
                    std::cout << "  -> " << s->peer() << ": " << msg << "\n";
                    ++sent;
                }
            }
            std::erase_if(members_, [](std::weak_ptr<Connection> c) {
                return c.expired();
            });
            return sent;
        }

        std::size_t size() const {
            return members_.size();
        }

    private:
        std::vector<std::weak_ptr<Connection>> members_;
    };
};