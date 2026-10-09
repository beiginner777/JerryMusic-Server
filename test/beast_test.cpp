#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
    try {
        net::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "beast server listening on http://127.0.0.1:8080" << std::endl;

        for (;;) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);

            // 读 HTTP 请求
            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(socket, buffer, req);

            // 构造响应
            http::response<http::string_body> res{http::status::ok, req.version()};
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/plain");
            res.body() = "Hello from boost.beast!";
            res.prepare_payload();

            // 写响应
            http::write(socket, res);
            socket.shutdown(tcp::socket::shutdown_send);
        }
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
