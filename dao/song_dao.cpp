#include "song_dao.h"
#include "../common/db.h"
#include <libpq-fe.h>

namespace jerrymusic {

nlohmann::json SongDao::listSongs() {
    nlohmann::json songs = nlohmann::json::array();
    PGconn* conn = openDb();
    if (!conn) return songs;

    PGresult* res = PQexec(conn,
        "SELECT id, title, artist, uri, cover_url, duration_ms FROM songs ORDER BY id");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        PQfinish(conn);
        return songs;
    }

    int n = PQntuples(res);
    for (int i = 0; i < n; i++) {
        songs.push_back({
            {"id", PQgetvalue(res, i, 0)},
            {"title", PQgetvalue(res, i, 1)},
            {"artist", PQgetvalue(res, i, 2)},
            {"uri", PQgetvalue(res, i, 3)},
            {"coverUrl", PQgetvalue(res, i, 4)},
            {"durationMs", std::stoll(PQgetvalue(res, i, 5))},
        });
    }
    PQclear(res);
    PQfinish(conn);
    return songs;
}

nlohmann::json SongDao::searchSongs(const std::string& keyword) {
    nlohmann::json songs = nlohmann::json::array();
    PGconn* conn = openDb();
    if (!conn) return songs;

    const char* params[1] = { keyword.c_str() };
    PGresult* res = PQexecParams(conn,
        "SELECT id, title, artist, uri, cover_url, duration_ms FROM songs "
        "WHERE title ILIKE '%' || $1 || '%' OR artist ILIKE '%' || $1 || '%' ORDER BY id",
        1, nullptr, params, nullptr, nullptr, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        PQfinish(conn);
        return songs;
    }

    int n = PQntuples(res);
    for (int i = 0; i < n; i++) {
        songs.push_back({
            {"id", PQgetvalue(res, i, 0)},
            {"title", PQgetvalue(res, i, 1)},
            {"artist", PQgetvalue(res, i, 2)},
            {"uri", PQgetvalue(res, i, 3)},
            {"coverUrl", PQgetvalue(res, i, 4)},
            {"durationMs", std::stoll(PQgetvalue(res, i, 5))},
        });
    }
    PQclear(res);
    PQfinish(conn);
    return songs;
}

} // namespace jerrymusic
