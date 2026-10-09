#pragma once
#include <libpq-fe.h>

namespace jerrymusic {

// 打开一个 PostgreSQL 连接（libpq C API）。返回的连接用完要 PQfinish。
inline PGconn* openDb() {
    return PQconnectdb(
        "host=127.0.0.1 port=5432 dbname=jerrymusic user=postgres password=123456");
}

} // namespace jerrymusic
