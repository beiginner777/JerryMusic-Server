#pragma once
#include <string>

namespace jerrymusic {

/**
 * 认证业务逻辑：注册、登录（校验密码 + 签发 JWT）。
 */
class AuthService {
public:
    std::string registerUser(const std::string& username, const std::string& password);
    std::string login(const std::string& username, const std::string& password);
};

} // namespace jerrymusic
