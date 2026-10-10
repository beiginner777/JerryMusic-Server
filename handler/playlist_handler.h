#pragma once
#include <string>
#include "../service/playlist_service.h"

namespace jerrymusic {

/**
 * 歌单 REST 接口：GET /api/playlists、GET/POST /api/playlists/{playlistId}/songs。
 */
class PlaylistHandler {
public:
    std::string handleList();

    std::string handleDetail(long playlistId);

    std::string handleAddSong(long playlistId, const std::string& body);
private:
    PlaylistService service_;
};

} // namespace jerrymusic
