#pragma once
#include <string>
#include "../service/song_service.h"

namespace jerrymusic {

/**
 * 歌曲 REST 接口：GET /api/songs、GET /api/search。
 */
class SongHandler {
public:
    std::string handleList();

    std::string handleSearch(const std::string& query);
private:
    SongService service_;
};

} // namespace jerrymusic
