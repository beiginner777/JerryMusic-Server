#pragma once
#include <optional>
#include <string>
#include <utility>

namespace jerrymusic {

/**
 * 用户表数据访问（PostgreSQL / libpqxx）。
 */
class UserDao {
public:
    // 创建用户，返回新用户 id；用户名已存在返回 nullopt
    std::optional<long> createUser(const std::string& username, const std::string& passwordHash);

    // 按用户名查找，返回 (id, password_hash)；不存在返回 nullopt
    std::optional<std::pair<long, std::string>> findByUsername(const std::string& username);
};

} // namespace jerrymusic
