#pragma once
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>

namespace jerrymusic {

// TODO: 生产环境用 bcrypt / argon2，SHA-256 只是 2.2 的临时占位
inline std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
    std::ostringstream oss;
    for (unsigned char c : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return oss.str();
}

} // namespace jerrymusic
