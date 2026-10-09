#include "auth_handler.h"
#include "../common/response.h"
#include <nlohmann/json.hpp>

namespace jerrymusic {

using json = nlohmann::json;

std::string AuthHandler::handleRegister(const std::string& body) {
    json req;
    try {
        req = json::parse(body);
    } catch (...) {
        return error(400, "invalid json");
    }
    return service_.registerUser(req.value("username", ""), req.value("password", ""));
}

std::string AuthHandler::handleLogin(const std::string& body) {
    json req;
    try {
        req = json::parse(body);
    } catch (...) {
        return error(400, "invalid json");
    }
    return service_.login(req.value("username", ""), req.value("password", ""));
}

} // namespace jerrymusic
