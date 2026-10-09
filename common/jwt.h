#pragma once
#include <jwt-cpp/jwt.h>
#include <string>
#include <chrono>

namespace jerrymusic {

// TODO: 密钥要放到配置文件，不要硬编码
const std::string JWT_SECRET = "jerrymusic-secret-key-change-me";

// 签发 token，sub 存用户 id
inline std::string createToken(const std::string& userId) {
    return jwt::create()
        .set_issuer("jerrymusic")
        .set_subject(userId)
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{24})
        .sign(jwt::algorithm::hs256{JWT_SECRET});
}

// 校验 token，成功返回用户 id（sub），失败返回空串
inline std::string verifyToken(const std::string& token) {
    try {
        auto decoded = jwt::decode(token);
        jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{JWT_SECRET})
            .with_issuer("jerrymusic")
            .verify(decoded);
        return decoded.get_subject();
    } catch (...) {
        return "";
    }
}

} // namespace jerrymusic
