#include "auth_service.h"
#include "../dao/user_dao.h"
#include "../common/response.h"
#include "../common/jwt.h"
#include "../common/hash.h"

namespace jerrymusic {

std::string AuthService::registerUser(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty()) {
        return error(1000, "username and password are required");
    }
    UserDao dao;
    auto id = dao.createUser(username, sha256(password));
    if (!id) {
        return error(1001, "username already exists");
    }
    json user = {{"id", std::to_string(*id)}, {"username", username}};
    return ok(user);
}

std::string AuthService::login(const std::string& username, const std::string& password) {
    UserDao dao;
    auto found = dao.findByUsername(username);
    if (!found) {
        return error(1002, "wrong username or password");
    }
    auto [id, hash] = *found;
    if (hash != sha256(password)) {
        return error(1002, "wrong username or password");
    }
    std::string token = createToken(std::to_string(id));
    json user = {{"id", std::to_string(id)}, {"username", username}};
    return ok({{"token", token}, {"user", user}});
}

} // namespace jerrymusic
