#pragma once
#include <string>
#include "../service/song_service.h"

namespace jerrymusic {

/**
 * 歌曲 REST 接口：GET /api/songs。
 */
class SongHandler {
public:
    std::string handleList();
private:
    SongService service_;
};

} // namespace jerrymusic
