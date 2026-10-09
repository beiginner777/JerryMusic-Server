#pragma once
#include <nlohmann/json.hpp>

namespace jerrymusic {

/**
 * 歌单表数据访问（PostgreSQL / libpqxx）。
 */
class PlaylistDao {
public:
    // 查询所有歌单，返回 JSON 数组
    nlohmann::json listPlaylists();
};

} // namespace jerrymusic
