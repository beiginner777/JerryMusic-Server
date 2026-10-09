#pragma once
#include <nlohmann/json.hpp>

namespace jerrymusic {

/**
 * 歌曲表数据访问（PostgreSQL / libpqxx）。
 */
class SongDao {
public:
    // 查询所有歌曲，返回 JSON 数组
    nlohmann::json listSongs();
};

} // namespace jerrymusic
