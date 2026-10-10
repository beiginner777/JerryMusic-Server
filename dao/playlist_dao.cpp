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

std::optional<std::pair<long, std::string>> PlaylistDao::getPlaylistById(long playlistId) {
    PGconn* conn = openDb();
    if (!conn) return std::nullopt;

    std::string idStr = std::to_string(playlistId);
    const char* params[1] = { idStr.c_str() };
    PGresult* res = PQexecParams(conn,
        "SELECT id, name FROM playlists WHERE id = $1",
        1, nullptr, params, nullptr, nullptr, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        PQclear(res);
        PQfinish(conn);
        return std::nullopt;
    }
    long id = std::stol(PQgetvalue(res, 0, 0));
    std::string name = PQgetvalue(res, 0, 1);
    PQclear(res);
    PQfinish(conn);
    return std::make_pair(id, name);
}

nlohmann::json PlaylistDao::getPlaylistSongs(long playlistId) {
    nlohmann::json songs = nlohmann::json::array();
    PGconn* conn = openDb();
    if (!conn) return songs;

    std::string idStr = std::to_string(playlistId);
    const char* params[1] = { idStr.c_str() };
    PGresult* res = PQexecParams(conn,
        "SELECT s.id, s.title, s.artist, s.uri, s.cover_url, s.duration_ms "
        "FROM songs s JOIN playlist_songs ps ON s.id = ps.song_id "
        "WHERE ps.playlist_id = $1 ORDER BY ps.position",
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

bool PlaylistDao::addSongToPlaylist(long playlistId, long songId) {
    PGconn* conn = openDb();
    if (!conn) return false;

    std::string pidStr = std::to_string(playlistId);
    std::string sidStr = std::to_string(songId);
    const char* params[2] = { pidStr.c_str(), sidStr.c_str() };
    PGresult* res = PQexecParams(conn,
        "INSERT INTO playlist_songs (playlist_id, song_id) VALUES ($1, $2) ON CONFLICT DO NOTHING",
        2, nullptr, params, nullptr, nullptr, 0);
    bool ok = (PQresultStatus(res) == PGRES_COMMAND_OK);
    PQclear(res);
    PQfinish(conn);
    return ok;
}

} // namespace jerrymusic
