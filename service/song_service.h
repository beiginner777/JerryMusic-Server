#pragma once
#include <string>

namespace jerrymusic {

/**
 * 歌曲业务逻辑。
 */
class SongService {
public:
    std::string listSongs();

    std::string searchSongs(const std::string& keyword);
};

} // namespace jerrymusic
