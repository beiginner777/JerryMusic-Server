#pragma once
#include <string>
#include "../service/auth_service.h"

namespace jerrymusic {

/**
 * 认证 REST 接口：POST /api/auth/register、POST /api/auth/login。
 */
class AuthHandler {
public:
    std::string handleRegister(const std::string& body);
    std::string handleLogin(const std::string& body);
private:
    AuthService service_;
};

} // namespace jerrymusic
