#pragma once
#include <string>
#include "../service/playlist_service.h"

namespace jerrymusic {

/**
 * 歌单 REST 接口：GET /api/playlists。
 */
class PlaylistHandler {
public:
    std::string handleList();
private:
    PlaylistService service_;
};

} // namespace jerrymusic
