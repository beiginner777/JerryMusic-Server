#include "user_dao.h"
#include "../common/db.h"
#include <libpq-fe.h>

namespace jerrymusic {

std::optional<long> UserDao::createUser(const std::string& username, const std::string& passwordHash) {
    PGconn* conn = openDb();
    if (!conn) return std::nullopt;

    const char* params[2] = { username.c_str(), passwordHash.c_str() };
    PGresult* res = PQexecParams(conn,
        "INSERT INTO users (username, password_hash) VALUES ($1, $2) RETURNING id",
        2, nullptr, params, nullptr, nullptr, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        PQfinish(conn);
        return std::nullopt; // 用户名已存在或其它错误
    }
    long id = std::stol(PQgetvalue(res, 0, 0));
    PQclear(res);
    PQfinish(conn);
    return id;
}

std::optional<std::pair<long, std::string>> UserDao::findByUsername(const std::string& username) {
    PGconn* conn = openDb();
    if (!conn) return std::nullopt;

    const char* params[1] = { username.c_str() };
    PGresult* res = PQexecParams(conn,
        "SELECT id, password_hash FROM users WHERE username = $1",
        1, nullptr, params, nullptr, nullptr, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        PQclear(res);
        PQfinish(conn);
        return std::nullopt;
    }
    long id = std::stol(PQgetvalue(res, 0, 0));
    std::string hash = PQgetvalue(res, 0, 1);
    PQclear(res);
    PQfinish(conn);
    return std::make_pair(id, hash);
}

} // namespace jerrymusic
