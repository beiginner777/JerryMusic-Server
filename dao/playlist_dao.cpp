#include "playlist_dao.h"
#include "../common/db.h"
#include <libpq-fe.h>

namespace jerrymusic {

nlohmann::json PlaylistDao::listPlaylists() {
    nlohmann::json playlists = nlohmann::json::array();
    PGconn* conn = openDb();
    if (!conn) return playlists;

    PGresult* res = PQexec(conn, "SELECT id, name FROM playlists ORDER BY id");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        PQfinish(conn);
        return playlists;
    }

    int n = PQntuples(res);
    for (int i = 0; i < n; i++) {
        playlists.push_back({
            {"id", PQgetvalue(res, i, 0)},
            {"name", PQgetvalue(res, i, 1)},
        });
    }
    PQclear(res);
    PQfinish(conn);
    return playlists;
}

} // namespace jerrymusic
