#include "playlist_handler.h"
#include "../common/response.h"
#include <nlohmann/json.hpp>

namespace jerrymusic {

using json = nlohmann::json;

std::string PlaylistHandler::handleList() {
    return service_.listPlaylists();
}

std::string PlaylistHandler::handleDetail(long playlistId) {
    return service_.getPlaylistDetail(playlistId);
}

std::string PlaylistHandler::handleAddSong(long playlistId, const std::string& body) {
    json req;
    try {
        req = json::parse(body);
    } catch (...) {
        return error(400, "invalid json");
    }
    long songId = 0;
    try {
        songId = std::stol(req.value("songId", ""));
    } catch (...) {
        return error(1006, "invalid songId");
    }
    if (songId <= 0) {
        return error(1006, "invalid songId");
    }
    return service_.addSongToPlaylist(playlistId, songId);
}

} // namespace jerrymusic
