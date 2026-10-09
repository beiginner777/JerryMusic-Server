#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/this_coro.hpp>
#include <iostream>
#include <string>

#include "handler/auth_handler.h"
#include "handler/song_handler.h"
#include "handler/playlist_handler.h"
#include "common/response.h"
#include "common/jwt.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

using namespace jerrymusic;

// 从 Authorization 头提取 token（去掉 "Bearer " 前缀）
static std::string extractToken(const std::string& authHeader) {
    const std::string prefix = "Bearer ";
    if (authHeader.size() >= prefix.size() && authHeader.compare(0, prefix.size(), prefix) == 0) {
        return authHeader.substr(prefix.size());
    }
    return "";
}

// 路由 + 鉴权
static std::string route(const std::string& target, http::verb method,
                         const std::string& body, const std::string& authHeader) {
    // 公开接口：注册、登录
    if (method == http::verb::post && target == "/api/auth/register") {
        AuthHandler h;
        return h.handleRegister(body);
    }
    if (method == http::verb::post && target == "/api/auth/login") {
        AuthHandler h;
        return h.handleLogin(body);
    }

    // 以下接口需要 JWT 鉴权
    if (verifyToken(extractToken(authHeader)).empty()) {
        return error(401, "unauthorized");
    }

    if (method == http::verb::get && target == "/api/songs") {
        SongHandler h;
        return h.handleList();
    }
    if (method == http::verb::get && target == "/api/playlists") {
        PlaylistHandler h;
        return h.handleList();
    }
    return error(404, "not found");
}

// 处理单个连接
static net::awaitable<void> handleSession(tcp::socket socket) {
    try {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        co_await http::async_read(socket, buffer, req, net::use_awaitable);

        std::string target(req.target());
        std::string body = req.body();
        std::string authHeader(req[http::field::authorization]);

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "JerryMusic");
        res.set(http::field::content_type, "application/json");
        res.body() = route(target, req.method(), body, authHeader);
        res.prepare_payload();
        res.keep_alive(req.keep_alive());

        co_await http::async_write(socket, res, net::use_awaitable);
    } catch (const std::exception& e) {
        std::cerr << "session error: " << e.what() << std::endl;
    }
}

// 监听循环：accept 后每个连接 co_spawn 一个协程
static net::awaitable<void> listener() {
    auto executor = co_await net::this_coro::executor;
    tcp::acceptor acceptor(executor, {tcp::v4(), 8080});
    std::cout << "JerryMusic server listening on http://127.0.0.1:8080" << std::endl;
    for (;;) {
        tcp::socket socket = co_await acceptor.async_accept(net::use_awaitable);
        net::co_spawn(executor, handleSession(std::move(socket)), net::detached);
    }
}

int main() {
    try {
        net::io_context ioc;
        net::co_spawn(ioc, listener(), net::detached);
        ioc.run();
    } catch (const std::exception& e) {
        std::cerr << "fatal: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
